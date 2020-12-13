#include "utils.h"

#define UPPERHEIGHT	3
#define LOWERHEIGHT	3
#define BORDERWIDTH	2

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

int getLastKey(WINDOW *window) {
	int ch, last = '\0';
 	while((ch = wgetch(window)) != ERR)
		last = ch;
	return last;
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

void initWindows(WINDOW **lower, WINDOW **center, WINDOW **upper, int rows, int columns, Coordinate position) {
	WINDOW *mainWindow, *lowerWindow, *centerWindow, *upperWindow, *lowerContentWindow, *centerContentWindow, *upperContentWindow, *shadowWindow;

	init_color(COLOR_GREY, 500, 500, 500);
	init_color(COLOR_LIGHTGREY, 800, 800, 800);
	init_pair(1, COLOR_BLACK, COLOR_BLUE);
	init_pair(2, COLOR_BLACK, COLOR_GREY);
	init_pair(3, COLOR_BLACK, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_GREY);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_LIGHTGREY, COLOR_GREY);


	mainWindow = newwin(rows, columns, position.row, position.col);
	shadowWindow = newwin(rows, columns, position.row + 1, position.col + 2);

	lowerWindow = derwin(mainWindow, LOWERHEIGHT, columns - BORDERWIDTH, rows - 2 * BORDERWIDTH, 1);
	centerWindow = derwin(mainWindow, rows - UPPERHEIGHT - LOWERHEIGHT - BORDERWIDTH, columns - BORDERWIDTH, 1 + UPPERHEIGHT, 1);
	upperWindow = derwin(mainWindow, UPPERHEIGHT, 20, 1, (columns - BORDERWIDTH - 20) / 2);

	lowerContentWindow = derwin(lowerWindow, LOWERHEIGHT - BORDERWIDTH, columns - 2 * BORDERWIDTH, 1, 1);
	centerContentWindow = derwin(centerWindow, rows - UPPERHEIGHT - LOWERHEIGHT - 2 * BORDERWIDTH, columns - 2 * BORDERWIDTH, 1, 1);
	upperContentWindow = derwin(upperWindow, UPPERHEIGHT - BORDERWIDTH, 20 - BORDERWIDTH, 1, 1);

	bkgd(COLOR_PAIR(1));
	wbkgd(mainWindow, COLOR_PAIR(2));
	wbkgd(shadowWindow, COLOR_PAIR(3));

	wbkgd(lowerContentWindow, COLOR_PAIR(2));
	wbkgd(centerContentWindow, COLOR_PAIR(5));
	wbkgd(upperContentWindow, COLOR_PAIR(2));

	wshadowBorder(mainWindow, COLOR_PAIR(4), COLOR_PAIR(2));
	wshadowBorder(lowerWindow, COLOR_PAIR(2), COLOR_PAIR(4));
	wshadowBorder(centerWindow, COLOR_PAIR(2), COLOR_PAIR(4));
	wshadowBorder(upperWindow, COLOR_PAIR(2), COLOR_PAIR(4));
	
/*	----------------------------------	*/

	char title[] = "CSnake";
	wattron(upperContentWindow, A_BOLD);
	mvwaddstr(upperContentWindow, 0, (20 - BORDERWIDTH - strlen(title)) / 2, title);
	wattroff(upperContentWindow, A_BOLD);

/*	----------------------------------	*/

	refresh();
	wrefresh(shadowWindow);
	wrefresh(mainWindow);
	wrefresh(lowerWindow);
	wrefresh(centerWindow);
	wrefresh(upperWindow);

	*lower = lowerContentWindow;
	*center = centerContentWindow;
	*upper = upperContentWindow;
}
