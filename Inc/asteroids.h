#include "stm32f407xx.h"


typedef struct
{
	float x;
	float y;
} Point_TypeDef;



typedef struct
{
	Point_TypeDef pos;
	float speed;
	uint16_t dir_angle;
	uint16_t rotation;
} Player_TypeDef;

typedef struct
{
	uint16_t size;
	Point_TypeDef pos;
	float speed;
	uint16_t dir_angle;
	int delta_angle;
	int rotation;
} Asteroid_TypeDef;


void asteroid_pos_update();
void asteroids_draw(uint16_t color);
void player_draw(uint16_t color);
void asteroids_game_draw();
float sinus(uint16_t angle);
float cosinus(uint16_t angle);
Point_TypeDef rotate_vector(Point_TypeDef point, uint16_t angle);
void line_strip_draw_rot(const Point_TypeDef * points, uint16_t size, uint16_t color,
        Point_TypeDef position, uint16_t angle);
void set_joystick_input(int x, int y);
