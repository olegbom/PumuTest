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
    float size;
} SpaceObject_TypeDef;


typedef struct
{
	SpaceObject_TypeDef so;
} Player_TypeDef;

typedef struct
{
	SpaceObject_TypeDef so;
	int delta_angle;
} Asteroid_TypeDef;


void space_object_draw(const Vector2f * points, uint16_t p_count,  uint16_t color, volatile SpaceObject_TypeDef *so);
void asteroids_draw(uint16_t color);
void player_draw(uint16_t color);

void asteroids_game_draw();


float sinus(uint16_t angle);
float cosinus(uint16_t angle);

void vector_rotate(Vector2f *point, uint16_t angle);
void vector_translate(volatile Vector2f *point, Vector2f tr);
void vector_scale(Vector2f *point, float scale);

void line_strip_draw_rot(const Vector2f * points, uint16_t p_count, uint16_t color,
        Vector2f position, uint16_t angle, float count);
void set_input(uint16_t joy1x,  uint16_t joy1y,
        uint16_t joy2x,  uint16_t joy2y);
