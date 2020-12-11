#include "Snake.h"

Snake *initSnake(Coordinate start, int len) {
	Snake *snake = (Snake *)malloc(sizeof(Snake));
	SnakeBody *stepper;

	snake->direction = snake->prev_direction = right;
	snake->head = (SnakeBody *)malloc(sizeof(SnakeBody));
	
	stepper = snake->head;
	stepper->position.row = start.row;
	stepper->position.col = start.col;

	int i;
	for(i = 1; i < len; i++) {
		stepper->next = (SnakeBody *)malloc(sizeof(SnakeBody));
		stepper = stepper->next;
		stepper->position.row = 5;
		stepper->position.col = start.col - i;
	}
	stepper = NULL;

	return snake;
}

void wdrawSnake(WINDOW *playground, Snake *snake) {
	SnakeBody *stepper;
	stepper = snake->head;
	do {
		mvwaddch(playground, stepper->position.row, stepper->position.col, 'x');
		stepper = stepper->next;
	} while(stepper != NULL);
}
