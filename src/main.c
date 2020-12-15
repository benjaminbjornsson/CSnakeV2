#include "Playground.h"

void updateScore(WINDOW *window, int score, int highscore, int level) {
	int rows, columns;
	getmaxyx(window, rows, columns);
	mvwprintw(window, 0, 0, " Highscore: %2d", highscore);
	mvwprintw(window, 0, (columns - 10) / 2, "Score: %2d", score);
	mvwprintw(window, 0, (columns - 10), "Level %2d", level);
	wrefresh(window);
}

void selectMenu(WINDOW *window, int current, int n, char *label, bool isSelected, bool hoover) {
	if(isSelected && hoover)
		wshadowBorder(window, COLOR_PAIR(2), COLOR_PAIR(4));
	else if(hoover)
		wshadowBorder(window, COLOR_PAIR(4), COLOR_PAIR(4));
	else
		wshadowBorder(window, COLOR_PAIR(4), COLOR_PAIR(2));
	mvwaddstr(window, 1, 1, label);
	int i;
	for(i = 1; i <= n; i++) {
		if(i == current)
			wattron(window, A_BOLD | A_STANDOUT);
		mvwaddch(window, 1, 2 * i + strlen(label), i + '0');
		if(i == current)
			wattroff(window, A_BOLD | A_STANDOUT);
	}
}

void button(WINDOW *window, char *label, bool hoover) {
	int rows, columns;
	getmaxyx(window, rows, columns);
	mvwaddstr(window, 1, (columns - strlen(label)) / 2, label);
	if(hoover)
		wshadowBorder(window, COLOR_PAIR(4), COLOR_PAIR(4));
	else
		wshadowBorder(window, COLOR_PAIR(4), COLOR_PAIR(2));
}

enum Hoover {
	levelBar = 0, speedBar, newGameBar, quitGameBar
};

bool mainMenu(WINDOW *window, WINDOW *stats, Playground *playground) {
	WINDOW *shadow, *border;
	int rows, columns;
	int *speed, *level;
	level = &playground->level;
	speed = &playground->speed;
	getmaxyx(window, rows, columns);
	border = derwin(window, 4 * rows / 5, 4 * columns / 5, rows / 10, columns / 10);
	shadow = derwin(window, 4 * rows / 5, 4 * columns / 5, rows / 10 + 1, columns / 10 + 2);
	
	wclear(border);

	wbkgd(shadow, COLOR_PAIR(3));
	wbkgd(border, COLOR_PAIR(2));

	wshadowBorder(border, COLOR_PAIR(4), COLOR_PAIR(2));
	wrefresh(shadow);
	wrefresh(border);

	getmaxyx(border, rows, columns);
	WINDOW *levelWindow, *speedWindow, *newGameWindow, *quitGameWindow;
	levelWindow = derwin(border, 3, (columns - 3) / 2, 1, 1);
	speedWindow = derwin(border, 3, (columns - 3) / 2, 1, 1 + (columns - 3) / 2);
	newGameWindow = derwin(border, 3, 10, 4, columns / 2 - 10);
	quitGameWindow = derwin(border, 3, 10, 4, columns / 2);

	int speeds = 9, levels = 9;
	enum Hoover hoover = levelBar;
	bool isSelected = false;

	updateScore(stats, playground->score, playground->levels[playground->level]->highscore, playground->level);
	int ch = 0;
	do {
		switch(ch) {
			case left:
				if(isSelected && hoover == levelBar) {
					*level = *level > 1 ? *level - 1 : *level;
					updateScore(stats, playground->score, playground->levels[playground->level]->highscore, playground->level);
				}
				else if(isSelected && hoover == speedBar)
					*speed = *speed > 1 ? *speed - 1 : *speed;
				else
					hoover = (hoover - 1 + 4) % 4;
				break;
			case right:
				if(isSelected && hoover == levelBar) {
					*level = *level < levels ? *level + 1 : *level;
					updateScore(stats, playground->score, playground->levels[playground->level]->highscore, playground->level);
				}
				else if(isSelected && hoover == speedBar)
					*speed = *speed < speeds ? *speed + 1 : *speed;
				else
					hoover = (hoover + 1) % 4;
				break;
			case ' ':
				if(hoover == newGameBar)
					goto deleteWin;
				if(hoover == quitGameBar)
					goto deleteWin;
				isSelected = !isSelected;
				break;
			default:
				break;
		}

		selectMenu(levelWindow, *level, levels, "Level:", isSelected, hoover == levelBar);
		selectMenu(speedWindow, *speed, speeds, "Speed:", isSelected, hoover == speedBar);
		button(newGameWindow, "New Game", hoover == newGameBar);
		button(quitGameWindow, "Quit", hoover == quitGameBar);
		wrefresh(shadow);
		wrefresh(border);
		wrefresh(levelWindow);
		wrefresh(speedWindow);
		wrefresh(newGameWindow);
		wrefresh(quitGameWindow);
	} while((ch = wgetch(window)) != 'q');

	deleteWin:
	delwin(shadow);
	delwin(border);
	delwin(levelWindow);
	delwin(speedWindow);
	delwin(newGameWindow);
	delwin(quitGameWindow);
	return hoover == newGameBar;
}

bool playMenu(Playground *playground) {
	WINDOW *shadow, *border;
	int rows, columns;
	getmaxyx(playground->win, rows, columns);
	border = derwin(playground->win, 4 * rows / 5, 4 * columns / 5, rows / 10, columns / 10);
	shadow = derwin(playground->win, 4 * rows / 5, 4 * columns / 5, rows / 10 + 1, columns / 10 + 2);
	
	wclear(border);

	wbkgd(shadow, COLOR_PAIR(3));
	wbkgd(border, COLOR_PAIR(2));

	wshadowBorder(border, COLOR_PAIR(4), COLOR_PAIR(2));

	wrefresh(shadow);
	wrefresh(border);

	WINDOW *newGameWindow, *quitGameWindow;

	getmaxyx(border, rows, columns);
	newGameWindow = derwin(border, 3, 10, (rows - 3) / 2, columns / 2 - 10);
	quitGameWindow = derwin(border, 3, 10, (rows - 3) / 2, columns / 2);
	
	int ch = 0;
	bool hoover = true;

	do {
		switch(ch) {
			case left: case right:
				hoover = !hoover;
				break;
			case ' ':
				goto deleteWindow;
			default:
				break;
		}
		button(newGameWindow, "New Game", hoover);
		button(quitGameWindow, "Quit", !hoover);
		wrefresh(newGameWindow);
		wrefresh(quitGameWindow);
	} while((ch = wgetch(border)));
	deleteWindow:
	delwin(shadow);
	delwin(border);
	delwin(newGameWindow);
	delwin(quitGameWindow);
	return hoover;
}

void freeSnakeBody(SnakeBody *head) {
	if(head->next != NULL)
		freeSnakeBody(head->next);
	free(head);
}

void freeSnake(Snake *snake) {
	freeSnakeBody(snake->head);
	free(snake);
}

void newGame(Playground *playground) {
	if(playground->snake != NULL)
		freeSnake(playground->snake);
	playground->snake = initSnake(playground->levels[playground->level]->initialSnake);
	playground->score = 0;
	free(playground->apple);
	playground->apple = NULL;
}

int main() {
	initscr();
	start_color();
	refresh();
	noecho();
	curs_set(0);

	Coordinate windowPosition = { .row = 1, .col = 2 };

	WINDOW *lowerWindow, *centerWindow, *upperWindow;
	initWindows(&lowerWindow, &centerWindow, &upperWindow, 21, 75, windowPosition);

	if(lowerWindow == NULL || centerWindow == NULL || upperWindow == NULL) {
		endwin();
		puts("Unable to initiate windows");
		return 1;
	}
	
	Playground *playground;
	playground = initPlayground(centerWindow);

	bool isPlaying = false;
	int lastKey;

	while(true) {
		if(!isPlaying && !mainMenu(centerWindow, lowerWindow, playground))
			break;
		else
			isPlaying = true;

		while(isPlaying) {
			newGame(playground);
			while((lastKey = getLastKey(centerWindow)) != ' ') {
				updateScore(lowerWindow, playground->score, playground->levels[playground->level]->highscore, playground->level);
				if(playground->stepGame(playground, lastKey) == -1)
					break;
				if(playground->score > playground->levels[playground->level]->highscore)
					playground->levels[playground->level]->highscore = playground->score;
			}
			playground->score = 0;
			if(!playMenu(playground))
				isPlaying = false;
		}
	}

	endwin();
	return 0;
}
