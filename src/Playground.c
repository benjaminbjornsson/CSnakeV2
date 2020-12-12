#include "Playground.h"

Playground *initPlayground(int rows, int columns, Coordinate start, int len) {
	Playground *temp;
	temp = (Playground *)malloc(sizeof(Playground));

	temp->rows = rows;
	temp->columns = columns;

	temp->win = newwin(rows, columns, 0, 0);
	if(temp->win == NULL)
		return NULL;

	temp->snake = initSnake(start, len);
	temp->apple = NULL;

	temp->runGame = runGame;
	nodelay(temp->win, TRUE);
	return temp;
}

int getLastKey(Playground *playground) {
	int ch, last = '\0';
 	while((ch = wgetch(playground->win)) != ERR)
		last = ch;
	return last;
}

void wdrawApple(WINDOW *window, Apple *apple) {
	if (apple == NULL)
		return;
	mvwaddch(window, apple->position.row, apple->position.col, apple->symbol);
}

void stepApple(Playground *playground) {
	if(playground->apple == NULL) {
		playground->apple = newApple(playground->rows, playground->columns);
		return;
	} else {
		if(playground->apple->timeLeft == 0) {
			free(playground->apple);
			playground->apple = NULL;
			playground->apple = newApple(playground->rows, playground->columns);
			return;
		} else {
			playground->apple->timeLeft--;
		}
	}
}

_Bool ateApple(Playground *playground) {
	Coordinate next;
	_Bool ateApple;
	if(playground->apple == NULL)
		return FALSE;
	next = nextCoordinate(playground->snake, playground->rows, playground->columns);
	ateApple = (next.row == playground->apple->position.row) && (next.col == playground->apple->position.col);
	if(ateApple) {
		free(playground->apple);
		playground->apple = NULL;
	}
	return ateApple;
}

int runGame(Playground *playground) {
	int ch = 0, i = 0;
    while(ch != ' ') {
        stepSnake(playground->snake, ateApple(playground), playground->rows, playground->columns);
		stepApple(playground);
        wdrawSnake(playground->win, playground->snake);
		wdrawApple(playground->win, playground->apple);
        wrefresh(playground->win);
        wclear(playground->win);
        napms(500);
        ch = getLastKey(playground);
        updateSnakeDirection(playground->snake, ch);
		i++;
    }
	return i;
}
