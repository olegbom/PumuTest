/*
 * asteroids.c
 *
 *  Created on: 10 но€б. 2018 г.
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



volatile uint16_t asteroids_count = 3;

volatile Asteroid_TypeDef asteroids[3] = {
	{
		.so = {
			.size = 1,
			.pos = {100, 100},
			.velocity = {-1, 2},
			.rotation = 30
		},
		.delta_angle = 1,
	},
	{
		.so = {
			.size = 0.8f,
			.pos = {50, 100},
			.velocity = {1, 2},
			.rotation = 170,
		},
		.delta_angle = 2,
	},
	{
		.so = {
			.size = 1.4f,
			.pos = {100, 50},
			.velocity = {0.4f, -1},
			.rotation = 0,
		},
		.delta_angle = -1,
	}
};

#define ASTEROID_POINTS_COUNT 8
const Vector2f Asteroid_Points[] =
{   { -10, -5 },
    { -10, 4 },
    { 0, 4 },
    { 0, 9 },
    { 9, 0 },
    { 9, -1 },
    { 0, -10 },
    { 0, -5 },
};

#define PLAYER_POINTS_COUNT 3
const Vector2f Player_Points[] =
{   { -5, -5 },
    { 5, 0 },
    { -5, 5 }
};


volatile int joystick_delta_x = 0;
volatile int joystick_delta_y = 0;


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

void rotate_vector(Vector2f *point, uint16_t angle)
{
    float sin_rot = sinus(angle);
    float cos_rot = cosinus(angle);
    float x = point->x*cos_rot - point->y*sin_rot;
    float y = point->x*sin_rot + point->y*cos_rot;
    point->x = x;
    point->y = y;
}

void translate_vector(volatile Vector2f *point, Vector2f tr)
{
	point->x += tr.x;
	point->y += tr.y;
}

void scale_vector(Vector2f *point, float scale)
{
	point->x *= scale;
	point->y *= scale;
}


void space_object_position_update(volatile SpaceObject_TypeDef *so)
{
	translate_vector(&so->pos, so->velocity);

	        if(so->pos.x < 10)
	            so->pos.x += LCD_TFTWIDTH - 20;
	        else if(so->pos.x > LCD_TFTWIDTH - 10)
	        	so->pos.x -= LCD_TFTWIDTH - 20;

	        if(so->pos.y < 10)
	        	so->pos.y += LCD_TFTHEIGHT - 20;
	        else if(so->pos.y > LCD_TFTHEIGHT - 10)
	        	so->pos.y -= LCD_TFTHEIGHT - 20;

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


    player.so.rotation += joystick_delta_x;

    if(player.so.rotation >=360)
        player.so.rotation %=player.so.rotation;
    else if(player.so.rotation < 0)
        player.so.rotation = 360 + player.so.rotation;

    if(joystick_delta_y != 0)
    {
    	float dvx = sinus(player.so.rotation)*joystick_delta_y*0.2f;
    	float dvy = cosinus(player.so.rotation)*joystick_delta_y*0.2f;

    	player.so.velocity.x += dvx;
    	player.so.velocity.y += dvy;
    }

    joystick_delta_y = 0;
    joystick_delta_x = 0;
}



void space_object_draw(const Vector2f * points, uint16_t p_count,  uint16_t color, volatile SpaceObject_TypeDef *so)
{
	Vector2f p0, p1;
	p0 = points[0];
	rotate_vector(&p0, so->rotation);
	scale_vector(&p0, so->size);
	translate_vector(&p0, so->pos);
	for (uint16_t j = 0; j < p_count; ++j) {
		p1 = points[(j + 1) % p_count];

		rotate_vector(&p1, so->rotation);
		scale_vector(&p1, so->size);
		translate_vector(&p0, so->pos);


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
    float min_distance = so1->size + so2->size;

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

			}
		 }
	 }
}

void set_joystick_input(int x, int y)
{
    joystick_delta_x = x;
    joystick_delta_y = y;
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

