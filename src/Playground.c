#include "Playground.h" 

Playground *initPlayground(WINDOW *window, Coordinate start, int len) {
	Playground *temp;
	temp = (Playground *)malloc(sizeof(Playground));
	getmaxyx(window, temp->rows, temp->columns);
	temp->win = window;
	temp->snake = initSnake(start, len);
	temp->apple = NULL;
	temp->score = 0;

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

	temp->stepGame = stepGame;
	nodelay(temp->win, TRUE);
	return temp;
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
		playground->score++;
		free(playground->apple);
		playground->apple = NULL;
	}
	return ateApple;
}

int stepGame(Playground *playground, int nextKey) {
	updateSnakeDirection(playground->snake, nextKey);
	wclear(playground->win);
	if(!stepSnake(playground->snake, ateApple(playground), playground->rows, playground->columns) || intersectWall(playground->wall, playground->snake->head->position))
		return -1;
	stepApple(playground);
	wdrawApple(playground->win, playground->apple);
	wdrawSnake(playground->win, playground->snake);
	wdrawWall(playground->win, playground->wall);
	wrefresh(playground->win);
	napms(250);
	return playground->score;
}
