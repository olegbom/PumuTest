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
        .pos = {
                .x = LCD_TFTWIDTH / 2,
                .y = LCD_TFTHEIGHT / 2
        },
        .dir_angle = 0,
        .rotation = 0,
        .speed = 0
};



volatile uint16_t asteroids_count = 3;

volatile Asteroid_TypeDef asteroids[3] = {
    { .size = 5,
      .pos = { 100, 100 },
      .dir_angle = 20,
      .speed = 2,
      .delta_angle = 1,
      .rotation = 30,
    },
    { .size = 3,
      .pos = { 50, 100 },
      .dir_angle = 90,
      .speed = 1,
      .delta_angle = 2,
      .rotation = 170,
    },
    { .size = 6,
      .pos = { 100, 50 },
      .dir_angle = 240,
      .speed = 3,
      .delta_angle = -1,
      .rotation = 0,
    },
};

#define ASTEROID_POINT_COUNT 8
const Point_TypeDef Asteroid_Points[] =
{   { -10, -5 },
    { -10, 4 },
    { 0, 4 },
    { 0, 9 },
    { 9, 0 },
    { 9, -1 },
    { 0, -10 },
    { 0, -5 },
};

#define PLAYER_POINT_COUNT 3
const Point_TypeDef Player_Points[] =
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

Point_TypeDef rotate_vector(Point_TypeDef point, uint16_t angle)
{
    float sin_rot = sinus(angle);
    float cos_rot = cosinus(angle);
    Point_TypeDef result = {
            point.x*cos_rot - point.y*sin_rot,
            point.x*sin_rot + point.y*cos_rot
    };
    return result;
}



void asteroid_pos_update() {
    for (uint16_t i = 0; i < asteroids_count; ++i) {
        float dx = sinus(asteroids[i].dir_angle)*asteroids[i].speed;
        float dy = cosinus(asteroids[i].dir_angle)*asteroids[i].speed;

        asteroids[i].pos.x += dx;
        asteroids[i].pos.y += dy;

        if(asteroids[i].pos.x < 10)
            asteroids[i].pos.x += LCD_TFTWIDTH - 20;
        else if(asteroids[i].pos.x > LCD_TFTWIDTH - 10)
            asteroids[i].pos.x -= LCD_TFTWIDTH - 20;

        if(asteroids[i].pos.y < 10)
            asteroids[i].pos.y += LCD_TFTHEIGHT - 20;
        else if(asteroids[i].pos.y > LCD_TFTHEIGHT - 10)
            asteroids[i].pos.y -= LCD_TFTHEIGHT - 20;


        asteroids[i].rotation+=asteroids[i].delta_angle;
        if(asteroids[i].rotation >=360)
            asteroids[i].rotation %=asteroids[i].rotation;
        else if(asteroids[i].rotation < 0)
            asteroids[i].rotation = 360 + asteroids[i].rotation;
    }
}

void player_pos_update()
{
    float dx = sinus(player.dir_angle)*player.speed;
    float dy = cosinus(player.dir_angle)*player.speed;

    player.pos.x += dx;
    player.pos.y += dy;


    if(player.pos.x < 10)
        player.pos.x += LCD_TFTWIDTH - 20;
    else if(player.pos.x > LCD_TFTWIDTH - 10)
        player.pos.x -= LCD_TFTWIDTH - 20;

    if(player.pos.y < 10)
        player.pos.y += LCD_TFTHEIGHT - 20;
    else if(player.pos.y > LCD_TFTHEIGHT - 10)
        player.pos.y -= LCD_TFTHEIGHT - 20;


    player.rotation += joystick_delta_x;

    if(player.rotation >=360)
        player.rotation %=player.rotation;
    else if(player.rotation < 0)
        player.rotation = 360 + player.rotation;

    if(joystick_delta_y != 0)
    {
        float s1 = player.speed;
        float s2 = joystick_delta_y*0.2f;
        int alpha_inv = 180-player.dir_angle + player.rotation;
        if(alpha_inv >=360) alpha_inv %=alpha_inv;
        else if(alpha_inv < 0) alpha_inv = 360 + alpha_inv;
        player.speed = sqrtf(s1*s1+s2*s2 - 2*s1*s2*cosinus(alpha_inv));
        player.dir_angle += (uint16_t)asinf(s2*sinus(alpha_inv));
    }

    joystick_delta_y = 0;
    joystick_delta_x = 0;
}

void line_strip_draw_rot(const Point_TypeDef * points, uint16_t size, uint16_t color,
        Point_TypeDef position, uint16_t angle) {
    Point_TypeDef p0, p1;
    p0 = Asteroid_Points[0];
    p0 = rotate_vector(p0, angle);

    for (uint16_t j = 0; j < size; ++j) {
        p1 = Asteroid_Points[(j + 1) % size];

        p1 = rotate_vector(p1, angle);

        uint16_t x0 = (uint16_t) (position.x + p0.x);
        uint16_t y0 = (uint16_t) (position.y + p0.y);
        uint16_t x1 = (uint16_t) (position.x + p1.x);
        uint16_t y1 = (uint16_t) (position.y + p1.y);
        LCD_DrawLine(x0, y0, x1, y1, color);
        p0 = p1;
    }
}


void asteroids_draw(uint16_t color) {
    for (uint16_t i = 0; i < asteroids_count; ++i) {
        line_strip_draw_rot(Asteroid_Points, ASTEROID_POINT_COUNT,
                color, asteroids[i].pos, asteroids[i].rotation);
    }
}



void player_draw(uint16_t color) {
    //line_strip_draw_rot(Player_Points, PLAYER_POINT_COUNT,
    //        color, player.pos, player.rotation);

    line_strip_draw_rot(Asteroid_Points, ASTEROID_POINT_COUNT,
                    color,  player.pos, player.rotation);
    line_strip_draw_rot(Player_Points, PLAYER_POINT_COUNT,
            color,  player.pos, player.dir_angle);
}

void set_joystick_input(int x, int y)
{
    joystick_delta_x = x;
    joystick_delta_y = y;
}

void asteroids_game_draw()
{
    asteroids_draw(BLACK);
    asteroid_pos_update();
    asteroids_draw(WHITE);

    player_draw(BLACK);
    player_pos_update();
    player_draw(WHITE);

}

