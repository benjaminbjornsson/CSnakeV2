#include "Snake.h"

typedef struct Playground Playground;

struct Playground {
	int rows;
	int cols;
	WINDOW *win;
	Snake *snake;
	int (* runGame)(Playground *);
};

Playground *initPlayground(int, int, Coordinate, int);
int getLastKey(Playground *);
int runGame(Playground *);
