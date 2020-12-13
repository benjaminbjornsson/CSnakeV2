#include "utils.h"

Range initRange(int start, int end) {
	Range temp = { .start = start, .end = end };
	return temp;
}

int midRange(Range range) {
	return (range.start + range.end) / 2;
}

int rangeLen(Range range) {
	return range.end - range.start;
}

bool inRange(Range range, int n) {
	return (n >= range.start) && (n <= range.end);
}

bool coordinateCompair(Coordinate coordinate1, Coordinate coordinate2) {
	return (coordinate1.row == coordinate2.row) && (coordinate1.col == coordinate2.col);
}

void wshadowBorder(WINDOW *window, short color1, short color2) {
	int i, rows, columns;
	getmaxyx(window, rows, columns);
	/*add upper left corner*/
	mvwaddch(window, 0, 0, ACS_ULCORNER | color1);

	/*add upper horizontal line*/
	for(i = 1; i < columns - 1; i++)
		waddch(window, ACS_HLINE | color1);

	/*add upper right corner*/
	waddch(window, ACS_URCORNER | color2);

	/*add left vertical line*/
	for(i = 1; i < rows - 1; i++)
		mvwaddch(window, i, 0, ACS_VLINE | color1);

	/*add right vertical line*/
	for(i = 1; i < rows - 1; i++)
		mvwaddch(window, i, columns - 1, ACS_VLINE | color2);

	/*add lower left corner*/
	waddch(window, ACS_LLCORNER | color1);

	/*add lower horizontal line*/
	for(i = 1; i < columns - 1; i++)
		waddch(window, ACS_HLINE | color2);

	/*add lower right corner*/
	waddch(window, ACS_LRCORNER | color2);
}

WINDOW *initPlaygroundWindow(int rows, int columns, Coordinate position) {
	WINDOW *mainWindow, *centerWindow, *playgroundWindow, *titleWindow, *scoreWindow, *shadowWindow;

	mainWindow = newwin(rows, columns, position.row, position.col);
	centerWindow = derwin(mainWindow, rows - 8, columns - 2, 4, 1);
	playgroundWindow = derwin(centerWindow, rows - 10, columns - 4, 1, 1);
	titleWindow = derwin(mainWindow, 3, 20, 1, (columns - 2 - 20) / 2);
	scoreWindow = derwin(mainWindow, 3, columns - 2, rows - 4, 1);
	shadowWindow = newwin(rows, columns, position.row + 2, position.col + 4);

	init_color(COLOR_GREY, 500, 500, 500);

	init_pair(1, COLOR_BLACK, COLOR_BLUE);
	init_pair(2, COLOR_BLACK, COLOR_GREY);
	init_pair(3, COLOR_BLACK, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_GREY);
	
	bkgd(COLOR_PAIR(1));
	wbkgd(mainWindow, COLOR_PAIR(2));
	wbkgd(shadowWindow, COLOR_PAIR(3));
	wbkgd(titleWindow, COLOR_PAIR(2));
	wbkgd(scoreWindow, COLOR_PAIR(2));
	
	char title[] = "CSnake";
	mvwaddstr(titleWindow, 1, (18 - strlen(title)) / 2, title);

	mvwprintw(scoreWindow, 1, 1, "Highscore: %2d", 15);
	mvwprintw(scoreWindow, 1, (columns - 9 - 2) / 2, "Score: %d", 5);
	mvwprintw(scoreWindow, 1, (columns - 2 - 8), "Level %d", 3);

	wshadowBorder(mainWindow, COLOR_PAIR(4), COLOR_PAIR(2));
	wshadowBorder(centerWindow, COLOR_PAIR(2), COLOR_PAIR(4));
	wshadowBorder(titleWindow, COLOR_PAIR(2), COLOR_PAIR(4));
	wshadowBorder(scoreWindow, COLOR_PAIR(2), COLOR_PAIR(4));

	refresh();
	wrefresh(shadowWindow);
	wrefresh(mainWindow);
	wrefresh(titleWindow);
	wrefresh(scoreWindow);

	return playgroundWindow;
}
