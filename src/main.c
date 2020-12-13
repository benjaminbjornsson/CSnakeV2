#include "Playground.h"

int main() {
	initscr();
	start_color();
	refresh();
	noecho();

	WINDOW *playgroundWindow;

	Coordinate windowPosition = { .row = 1, .col = 1 };
	playgroundWindow = initPlaygroundWindow(25, 50, windowPosition);
	if(playgroundWindow == NULL) {
		endwin();
		puts("Unable to initiate playground window");
		return 1;
	}

	Playground *playground;

	Coordinate start = { .row = 6, .col = 6};
	int len = 5;
	playground = initPlayground(playgroundWindow, start, len);
	playground->runGame(playground);

	endwin();
	return 0;
}
