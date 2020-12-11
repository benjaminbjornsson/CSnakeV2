#include <ncurses.h>
#include <stdlib.h>

typedef enum Direction Direction;
typedef struct Coordinate Coordinate; 
typedef struct SnakeBody SnakeBody;
typedef struct Snake Snake;

enum Direction {
	left = 'h', 
	down = 'j', 
	up = 'k', 
	right = 'l'
};

struct Coordinate {
	int row;
	int col;
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
void wdrawSnake(WINDOW *playground, Snake *snake);
