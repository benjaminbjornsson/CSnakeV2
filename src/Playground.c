#include "Playground.h" 

Playground *initPlayground(WINDOW *window, Coordinate start, int len) {
	Playground *temp;
	temp = (Playground *)malloc(sizeof(Playground));
	getmaxyx(window, temp->rows, temp->columns);
	temp->win = window;
	temp->snake = initSnake(start, len);
	temp->apple = NULL;

/*	----------------------------------	*/
	Coordinate **coordinates;
	coordinates = (Coordinate **)malloc(5*sizeof(Coordinate *));

	int i;
	for(i = 0; i < 4; i++) {
		coordinates[i] = (Coordinate *)malloc(sizeof(Coordinate));
		coordinates[i]->row = 0;
		coordinates[i]->col = 2 * i;
	}
	coordinates[3]->row = 16;
	coordinates[4] = NULL;
	
	temp->wall = (Wall *)malloc(sizeof(Wall));
	temp->wall->coordinates = coordinates;
/*	----------------------------------	*/

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
		do {
			free(playground->apple);
			playground->apple = newApple(playground->rows, playground->columns);
		} while(intersectSnake(playground->snake, playground->apple->position) || intersectWall(playground->wall, playground->apple->position));
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

bool ateApple(Playground *playground) {
	Coordinate next;
	bool ateApple;
	if(playground->apple == NULL)
		return FALSE;
	next = nextCoordinate(playground->snake, playground->rows, playground->columns);
	ateApple = coordinateCompair(next, playground->apple->position);
	if(ateApple) {
		free(playground->apple);
		playground->apple = NULL;
	}
	return ateApple;
}

int runGame(Playground *playground) {
	int ch = 0, i = 0;
    while(ch != ' ') {
        wclear(playground->win);
        if(!stepSnake(playground->snake, ateApple(playground), playground->rows, playground->columns) || intersectWall(playground->wall, playground->snake->head->position))
			break;
		stepApple(playground);
		wdrawApple(playground->win, playground->apple);
        wdrawSnake(playground->win, playground->snake);
		wdrawWall(playground->win, playground->wall);
        wrefresh(playground->win);
        napms(250);
        ch = getLastKey(playground);
        updateSnakeDirection(playground->snake, ch);
		i++;
    }
	return i;
}
