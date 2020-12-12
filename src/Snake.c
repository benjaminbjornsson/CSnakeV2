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
		stepper->position.row = start.row;
		stepper->position.col = start.col - 2 * i;
	}
	stepper = NULL;

	return snake;
}

void wdrawSnake(WINDOW *playground, const Snake *snake) {
	SnakeBody *stepper;
	stepper = snake->head;
	do {
		mvwaddch(playground, stepper->position.row, stepper->position.col, 'x');
		stepper = stepper->next;
	} while(stepper != NULL);
}

Coordinate nextCoordinate(const Snake *snake, const int maxrow, const int maxcol) {
	Coordinate temp;
	temp = snake->head->position;
	switch(snake->direction) {
		case left:
			temp.col = (temp.col + maxcol - 2) % maxcol;
			return temp;
		case down:
			temp.row = ++temp.row % maxrow;
			return temp;
		case up:
			temp.row = (--temp.row + maxrow) % maxrow;
			return temp;
		case right:
			temp.col = (temp.col + 2) % maxcol;
			return temp;
	}
}

void updateSnakeDirection(Snake *snake, int ch) {
    switch(ch) {
        case 'h':
            if(snake->prev_direction != right) { snake->direction = left; }
            break;
        case 'j':
            if(snake->prev_direction != up) { snake->direction = down; }
            break;
        case 'k':
            if(snake->prev_direction != down) { snake->direction = up; }
            break;
        case 'l':
            if(snake->prev_direction != left) { snake->direction = right; }
            break;
        default:
            break;
    }
}

void deleteTail(Snake *snake) {
	SnakeBody *stepper;
	stepper = snake->head;
	while((stepper->next)->next != NULL)
		stepper = stepper->next;
	free(stepper->next);
	stepper->next = NULL;
}

void stepSnake(Snake *snake, _Bool ateApple, int maxrows, int maxcolumns) {
	SnakeBody *newHead;
	newHead = (SnakeBody *)malloc(sizeof(SnakeBody));
	newHead->position = nextCoordinate(snake, maxrows, maxcolumns);
	newHead->next = snake->head;
	snake->head = newHead;
	snake->prev_direction = snake->direction;
	if(ateApple)
		return;
	else
		deleteTail(snake);
}
