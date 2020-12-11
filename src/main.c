#include "Snake.h"

int main() {
	Snake *snake;
	Coordinate start = { .row = 5, .col = 5};
	int len = 5;
	
	snake = initSnake(start, len);

	initscr();
	refresh();

	WINDOW *playground;
	playground = newwin(20, 20, 0, 0);
	if(playground == NULL) {
		endwin();
		puts("Unable to create playground window");
		return 1;
	}

	wdrawSnake(playground, snake);

	wrefresh(playground);
	getch();

	endwin();
	return 0;
}
