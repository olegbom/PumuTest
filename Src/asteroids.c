/*
 * asteroids.c
 *
 *  Created on: 10 но¤б. 2018 г.
 *      Author: olegbom
 */

#include "asteroids.h"
#include "ili9341.h"
#include "math.h"

const float sinus_table[] = { 0., 0.017452406, 0.034899497, 0.052335956,
        0.069756474, 0.087155743, 0.104528463, 0.121869343, 0.139173101,
        0.156434465, 0.173648178, 0.190808995, 0.207911691, 0.224951054,
        0.241921896, 0.258819045, 0.275637356, 0.292371705, 0.309016994,
        0.325568154, 0.342020143, 0.35836795, 0.374606593, 0.390731128,
        0.406736643, 0.422618262, 0.438371147, 0.4539905, 0.469471563,
        0.48480962, 0.5, 0.515038075, 0.529919264, 0.544639035, 0.559192903,
        0.573576436, 0.587785252, 0.601815023, 0.615661475, 0.629320391,
        0.64278761, 0.656059029, 0.669130606, 0.68199836, 0.69465837,
        0.707106781, 0.7193398, 0.731353702, 0.743144825, 0.75470958,
        0.766044443, 0.777145961, 0.788010754, 0.79863551, 0.809016994,
        0.819152044, 0.829037573, 0.838670568, 0.848048096, 0.857167301,
        0.866025404, 0.874619707, 0.882947593, 0.891006524, 0.898794046,
        0.906307787, 0.913545458, 0.920504853, 0.927183855, 0.933580426,
        0.939692621, 0.945518576, 0.951056516, 0.956304756, 0.961261696,
        0.965925826, 0.970295726, 0.974370065, 0.978147601, 0.981627183,
        0.984807753, 0.987688341, 0.990268069, 0.992546152, 0.994521895,
        0.996194698, 0.99756405, 0.998629535, 0.999390827, 0.999847695, 1
};



volatile Player_TypeDef player = {
	.so = {
		.pos = {
				.x = LCD_TFTWIDTH / 2,
				.y = LCD_TFTHEIGHT / 2
		},
		.velocity = {0, 0},
		.rotation = 0,
		.size = 1,
	}
};



volatile uint16_t asteroids_count = 2;

volatile Asteroid_TypeDef asteroids[2] = {
	{
		.so = {
			.size = 2,
			.pos = {100, 100},
			.velocity = {-0.2f, 0},
			.rotation = 30
		},
		.delta_angle = 0,
	},
	{
		.so = {
			.size = 1,
			.pos = {50, 100},
			.velocity = {0,0},
			.rotation = 170,
		},
		.delta_angle = 0,
	},

};

#define ASTEROID_POINTS_COUNT 11
const Vector2f Asteroid_Points[] =
{
        {-2, -10},
        {-10, -4},
        {-4, 1},
        {-7, 7},
        {-4, 10},
        {1, 8},
        {6, 10},
        {10, 4},
        {8, 0},
        {8, -7},
        {4, -10},


};

#define PLAYER_POINTS_COUNT 3
const Vector2f Player_Points[] =
{   { -5, -5 },
    { 10, 0 },
    { -5, 5 }
};


volatile int joystick_alpha = -1;
volatile int joystick_y = 0;


float sinus(uint16_t angle)
{
    angle %= 360;
    if(angle < 91)
        return sinus_table[angle];
    else if (angle < 181)
        return sinus_table[180 - angle];
    else if (angle < 271)
        return -sinus_table[angle - 180];
    else return -sinus_table[360 - angle];
}

float cosinus(uint16_t angle)
{
    angle %= 360;
    if(angle < 91)
        return sinus_table[90 - angle];
    else if (angle < 181)
        return -sinus_table[angle - 90];
    else if (angle < 271)
        return -sinus_table[270 - angle];
    else return sinus_table[angle - 270];
}

void vector_rotate(Vector2f *point, uint16_t angle)
{
    float sin_rot = sinus(angle);
    float cos_rot = cosinus(angle);
    float x = point->x*cos_rot - point->y*sin_rot;
    float y = point->x*sin_rot + point->y*cos_rot;
    point->x = x;
    point->y = y;
}

void vector_translate(volatile Vector2f *point, Vector2f tr)
{
	point->x += tr.x;
	point->y += tr.y;
}

void vector_scale(Vector2f *point, float scale)
{
	point->x *= scale;
	point->y *= scale;
}

float vectors_dot(Vector2f a, Vector2f b)
{
    return a.x*b.x+a.y*b.y;
}

float vector_length(Vector2f a)
{
    return sqrtf(a.x*a.x + a.y*a.y);
}

void vector_normalize(Vector2f *a)
{
    vector_scale(a, 1/vector_length(*a));
}


void space_object_position_update(volatile SpaceObject_TypeDef *so)
{
	vector_translate(&so->pos, so->velocity);

    if(so->pos.x < 10 || so->pos.x > LCD_TFTWIDTH - 10)
        so->velocity.x = -so->velocity.x;


    if(so->pos.y < 10 || so->pos.y > LCD_TFTHEIGHT - 10)
        so->velocity.y = -so->velocity.y;


}

void asteroid_pos_update() {
    for (uint16_t i = 0; i < asteroids_count; ++i) {
    	space_object_position_update(&asteroids[i].so);



        asteroids[i].so.rotation+=asteroids[i].delta_angle;
        if(asteroids[i].so.rotation >=360)
            asteroids[i].so.rotation %=asteroids[i].so.rotation;
        else if(asteroids[i].so.rotation < 0)
            asteroids[i].so.rotation = 360 + asteroids[i].so.rotation;
    }
}

void player_pos_update()
{
	space_object_position_update(&player.so);


	if (joystick_alpha != -1) {
        int delta = player.so.rotation - joystick_alpha;
        if (delta < -180)
            player.so.rotation--;
        else if (delta < 0)
            player.so.rotation++;
        else if (delta < 180)
            player.so.rotation--;
        else
            player.so.rotation++;
    }

    if(player.so.rotation >=360)
        player.so.rotation %=player.so.rotation;
    else if(player.so.rotation < 0)
        player.so.rotation = 360 + player.so.rotation;

    if(joystick_y != 0)
    {
    	float dvx = cosinus(player.so.rotation)*joystick_y*0.002f;
    	float dvy = sinus(player.so.rotation)*joystick_y*0.002f;

    	player.so.velocity.x -= dvx;
    	player.so.velocity.y -= dvy;
    }

    joystick_y = 0;
    joystick_alpha = -1;
}



void space_object_draw(const Vector2f * points, uint16_t p_count,  uint16_t color, volatile SpaceObject_TypeDef *so)
{
	Vector2f p0, p1;
	p0 = points[0];
	vector_rotate(&p0, so->rotation);
	vector_scale(&p0, so->size);
	vector_translate(&p0, so->pos);
	for (uint16_t j = 0; j < p_count; ++j) {
		p1 = points[(j + 1) % p_count];

		vector_rotate(&p1, so->rotation);
		vector_scale(&p1, so->size);
		vector_translate(&p1, so->pos);


 	  	LCD_DrawLine((uint16_t) p0.x, (uint16_t) p0.y,
					 (uint16_t) p1.x, (uint16_t) p1.y,
					 color);
		p0 = p1;
	}
}


void asteroids_draw(uint16_t color) {
    for (uint16_t i = 0; i < asteroids_count; ++i) {
        space_object_draw(Asteroid_Points, ASTEROID_POINTS_COUNT, color, &asteroids[i].so);
    }
}



void player_draw(uint16_t color) {
    space_object_draw(Player_Points, PLAYER_POINTS_COUNT, color, &player.so);
}

uint8_t is_collision(volatile SpaceObject_TypeDef *so1, volatile SpaceObject_TypeDef *so2)
{
    float dx = so1->pos.x - so2->pos.x;
    float dy = so1->pos.y - so2->pos.y;
    float min_distance = so1->size*10 + so2->size*10;

    if(dx > min_distance || dy > min_distance)
        return 0;
    if(dx*dx + dy*dy > min_distance*min_distance)
        return 0;
    return 1;
}

void calc_collisions()
{
	 for (uint16_t i = 0; i < asteroids_count; ++i)
	 {
		 for (uint16_t j = i+1; j < asteroids_count; ++j)
		 {
			if(is_collision(&asteroids[i].so, &asteroids[j].so))
			{
			    Vector2f o1 = asteroids[i].so.pos,
			             o2 = asteroids[j].so.pos;
			    Vector2f axis = {o2.x - o1.x, o2.y - o1.y};
			    vector_normalize(&axis);

			    float m1_sqr = asteroids[i].so.size
                        * asteroids[i].so.size;
			    float m2_sqr = asteroids[j].so.size
			             * asteroids[j].so.size;
			    volatile float p1 = vectors_dot(asteroids[i].so.velocity, axis) * m1_sqr;
                volatile float p2 = vectors_dot(asteroids[j].so.velocity, axis) * m2_sqr;

                if(p1 < 0) p1 = -p1;
                if(p2 < 0) p2 = -p2;
                volatile float p = p1 + p2;
                Vector2f v2 = { axis.x*p,
                        axis.y*p
                };
                Vector2f v1 = { -v2.x, -v2.y};
                vector_scale(&v1, 1/m1_sqr);
                vector_scale(&v2, 1/m2_sqr);
                vector_translate(&asteroids[i].so.velocity,  v1);
                vector_translate(&asteroids[j].so.velocity,  v2);
			}
		 }
	 }
}

void set_input(uint16_t joy1x,  uint16_t joy1y,
        uint16_t joy2x,  uint16_t joy2y)
{
    int x = (joy1x - 2048) /8;
    int y = (2048 - joy1y) /8;
    if(x>-8 && x <8) x = 0;
    if(y>-8 && y <8) y = 0;
    uint16_t alpha = (uint16_t)(atan2f(y,x)/((float)M_PI)*180.1f + 179.0f);
    if(x != 0 && y != 0)
    {
        joystick_alpha = alpha;
    }


    joystick_y = (joy2y - 2048) /256;
}

void asteroids_game_draw()
{
    asteroids_draw(BLACK);
    player_draw(BLACK);


    asteroid_pos_update();
    player_pos_update();
    calc_collisions();


    asteroids_draw(WHITE);
    player_draw(WHITE);

}

