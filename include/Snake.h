#include <ncurses.h>
#include <stdlib.h>
#include "utils.h"

typedef enum Direction Direction;
typedef struct SnakeBody SnakeBody;
typedef struct Snake Snake;

enum Direction {
	left = 'h', 
	down = 'j', 
	up = 'k', 
	right = 'l'
};

struct SnakeBody {
	Coordinate position;
	SnakeBody *next;
};

struct Snake {
	Direction prev_direction, direction;
	SnakeBody *head;
};

Snake *initSnake(Coordinate, int);
void wdrawSnake(WINDOW *, const Snake *);
void updateSnakeDirection(Snake *, int);
void stepSnake(Snake *, _Bool, int, int);
Coordinate nextCoordinate(const Snake *, const int, const int);
