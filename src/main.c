#include "Playground.h"

void updateScore(WINDOW *window, int score) {
	int rows, columns;
	getmaxyx(window, rows, columns);
	wclear(window);
	mvwprintw(window, 0, 0, " Highscore: %2d", 15);
	mvwprintw(window, 0, (columns - 10) / 2, "Score: %d", score);
	mvwprintw(window, 0, (columns - 10), "Level %d", 3);
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
	levelBar = 0, speedBar, newGameBar
};

void mainMenu(WINDOW *window) {
	WINDOW *shadow, *border;
	int rows, columns;
	getmaxyx(window, rows, columns);
	border = derwin(window, 4 * rows / 5, 4 * columns / 5, rows / 10, columns / 10);
	shadow = derwin(window, 4 * rows / 5, 4 * columns / 5, rows / 10 + 1, columns / 10 + 2);

	wbkgd(shadow, COLOR_PAIR(3));
	wbkgd(border, COLOR_PAIR(2));

	wshadowBorder(border, COLOR_PAIR(4), COLOR_PAIR(2));
	wrefresh(shadow);
	wrefresh(border);

	getmaxyx(border, rows, columns);
	WINDOW *levelWindow, *speedWindow, *newGameWindow;
	levelWindow = derwin(border, 3, (columns - 3) / 2, 1, 1);
	speedWindow = derwin(border, 3, (columns - 3) / 2, 1, 1 + (columns - 3) / 2);
	newGameWindow = derwin(border, 3, 9, 4, (columns - 8) / 2);

	int level = 1, speed = 1, speeds = 9, levels = 9;
	enum Hoover hoover = levelBar;
	bool isSelected = false;

	int ch = 0;
	do {
		switch(ch) {
			case 'h':
				if(isSelected && hoover == levelBar)
					level = level > 1 ? level - 1 : level;
				else if(isSelected && hoover == speedBar)
					speed = speed > 1 ? speed - 1 : speed;
				else
					hoover = (hoover - 1) % 3;
				break;
			case 'l':
				if(isSelected && hoover == levelBar)
					level = level < levels ? level + 1 : level;
				else if(isSelected && hoover == speedBar)
					speed = speed < speeds ? speed + 1 : speed;
				else
					hoover = (hoover + 1) % 3;
				break;
			case ' ':
				if(hoover == newGameBar)
					return;
				isSelected = !isSelected;
				break;
			default:
				break;
		}
		selectMenu(levelWindow, level, levels, "Level:", isSelected, hoover == levelBar);
		selectMenu(speedWindow, speed, speeds, "Speed:", isSelected, hoover == speedBar);
		button(newGameWindow, "NewGame", hoover == newGameBar);
		wrefresh(levelWindow);
		wrefresh(speedWindow);
		wrefresh(newGameWindow);
	} while((ch = wgetch(window)) != 'q');
}

int main() {
	initscr();
	start_color();
	refresh();
	noecho();
	curs_set(0);

	Coordinate windowPosition = { .row = 1, .col = 1 };

	WINDOW *lowerWindow, *centerWindow, *upperWindow;
	initWindows(&lowerWindow, &centerWindow, &upperWindow, 21, 76, windowPosition);

	if(lowerWindow == NULL || centerWindow == NULL || upperWindow == NULL) {
		endwin();
		puts("Unable to initiate windows");
		return 1;
	}

	mainMenu(centerWindow);

	Coordinate start = { .row = 6, .col = 6 };
	int len = 5;

	Playground *playground;
	playground = initPlayground(centerWindow, start, len);
	
	int lastKey;

	while((lastKey = getLastKey(centerWindow)) != ' ') {
		updateScore(lowerWindow, playground->score);
		if(playground->stepGame(playground, lastKey) == -1)
			break;
	}

	endwin();
	return 0;
}
