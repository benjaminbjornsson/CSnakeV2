#include "Playground.h"

Playground *initPlayground(int rows, int cols, Coordinate start, int len) {
	Playground *temp;
	temp = (Playground *)malloc(sizeof(Playground));

	temp->rows = rows;
	temp->cols = cols;

	temp->win = newwin(rows, cols, 0, 0);
	if(temp->win == NULL)
		return NULL;

	temp->snake = initSnake(start, len);
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

int runGame(Playground *playground) {
	int ch = 0, i = 0;
    while(ch != ' ') {
        stepSnake(playground->snake, FALSE, playground->rows, playground->cols);
        wdrawSnake(playground->win, playground->snake);
        wrefresh(playground->win);
        napms(500);
        ch = getLastKey(playground);
        updateSnakeDirection(playground->snake, ch);
        wclear(playground->win);
		i++;
    }
	return i;
}
