#include "Playground.h"

int main() {
	initscr();
	start_color();
	refresh();
	noecho();

	Coordinate start = { .row = 5, .col = 5};
	int len = 5;

	Playground *playground;
	playground = initPlayground(20, 40, start, len);
	if(playground == NULL) {
		endwin();
		puts("Unable to initiate playground");
		return 1;
	}

	playground->runGame(playground);

	endwin();
	return 0;
}
