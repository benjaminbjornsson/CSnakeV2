#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

typedef enum Direction Direction;
typedef struct SnakeBody SnakeBody;
typedef struct Snake Snake;

enum Direction {
	left = 'j', 
	down = 'k', 
	up = 'i', 
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
bool stepSnake(Snake *, bool, int, int);
Coordinate nextCoordinate(const Snake *, const int, const int);
bool intersectSnake(Snake *, Coordinate);
