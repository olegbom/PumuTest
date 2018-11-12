#include "stm32f407xx.h"


typedef struct
{
	float x;
	float y;
} Vector2f;



typedef struct
{
	Vector2f pos;
	Vector2f velocity;
	int rotation;
} Player_TypeDef;

typedef struct
{
	uint16_t size;
	Vector2f pos;
	Vector2f velocity;
	int delta_angle;
	int rotation;
} Asteroid_TypeDef;


void asteroid_pos_update();
void asteroids_draw(uint16_t color);
void player_draw(uint16_t color);
void asteroids_game_draw();
float sinus(uint16_t angle);
float cosinus(uint16_t angle);
Vector2f rotate_vector(Vector2f point, uint16_t angle);
void line_strip_draw_rot(const Vector2f * points, uint16_t size, uint16_t color,
        Vector2f position, uint16_t angle);
void set_joystick_input(int x, int y);
