#include "Snake.h"
#include "Apple.h"
#include "utils.h"

typedef struct Playground Playground;

struct Playground {
	int rows;
	int columns;
	WINDOW *win;
	Snake *snake;
	Apple *apple;
	int (* runGame)(Playground *);
};

Playground *initPlayground(int, int, Coordinate, int);
int getLastKey(Playground *);
int runGame(Playground *);
