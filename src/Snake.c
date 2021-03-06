#include "Snake.h"

enum Direction initDirection(SnakeBody *head) {
	if(head->position.row != head->next->position.row)
		return (head->position.row - head->next->position.row) > 0 ? up : down;
	else
		return (head->position.col - head->next->position.col > 0) ? right : left;
}

Snake *initSnake(Coordinate **initialSnake) {
	Snake *snake = (Snake *)malloc(sizeof(Snake));
	SnakeBody *stepper;

	snake->head = (SnakeBody *)malloc(sizeof(SnakeBody));
	
	stepper = snake->head;
	
	while(*initialSnake != NULL) {
		stepper->position.row = (*initialSnake)->row;
		stepper->position.col = (*initialSnake)->col;
		stepper->next = (SnakeBody *)malloc(sizeof(SnakeBody));
		stepper = stepper->next;
		initialSnake++;
	}

	snake->direction = snake->prev_direction = initDirection(snake->head);

	stepper->next = NULL;

	return snake;
}

void wdrawSnake(WINDOW *playground, const Snake *snake) {
	SnakeBody *stepper;
	stepper = snake->head;
	do {
		if(stepper == snake->head)
			mvwaddch(playground, stepper->position.row, stepper->position.col, 'O');
		else
			mvwaddch(playground, stepper->position.row, stepper->position.col, 'o');
		stepper = stepper->next;
	} while(stepper != NULL);
}

Coordinate nextCoordinate(const Snake *snake, const int maxrow, const int maxcol) {
	Coordinate temp;
	temp = snake->head->position;
	switch(snake->direction) {
		case left:
			temp.col = (temp.col + maxcol - 2) % maxcol;
			temp.col = temp.col + temp.col % 2;
			return temp;
		case down:
			temp.row = ++temp.row % maxrow;
			return temp;
		case up:
			temp.row = (--temp.row + maxrow) % maxrow;
			return temp;
		case right:
			temp.col = (temp.col + 2) % maxcol;
			temp.col = temp.col == 1 ? 0 : temp.col;
			return temp;
	}
}

void updateSnakeDirection(Snake *snake, int ch) {
    switch(ch) {
        case left:
            if(snake->prev_direction != right) { snake->direction = left; }
            break;
        case down:
            if(snake->prev_direction != up) { snake->direction = down; }
            break;
        case up:
            if(snake->prev_direction != down) { snake->direction = up; }
            break;
        case right:
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

bool intersectSelf(const Snake *snake) {
	SnakeBody *stepper;
	stepper = snake->head;
	while(stepper->next) {
		stepper = stepper->next;
		if(coordinateCompair(stepper->position, snake->head->position))
			return true;
	}
	return false;
}

bool stepSnake(Snake *snake, bool ateApple, int maxrows, int maxcolumns) {
	SnakeBody *newHead;
	newHead = (SnakeBody *)malloc(sizeof(SnakeBody));
	newHead->position = nextCoordinate(snake, maxrows, maxcolumns);
	newHead->next = snake->head;
	snake->head = newHead;
	snake->prev_direction = snake->direction;
	if(!ateApple)
		deleteTail(snake);
	if(intersectSelf(snake))
		return false;
	else
		return true;
}

bool intersectSnake(Snake *snake, Coordinate position) {
	SnakeBody *stepper;
	stepper = snake->head;
	do {
		if(coordinateCompair(position, stepper->position))
			return true;
		stepper = stepper->next;
	} while(stepper != NULL);
	return false;
}
