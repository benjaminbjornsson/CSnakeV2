#include "Snake.h"
#include "Apple.h"
#include "Wall.h"
#include "utils.h"

typedef struct Playground Playground;

struct Playground {
	int rows;
	int columns;
	WINDOW *win;
	Snake *snake;
	Apple *apple;
	Wall *wall;
	int (* runGame)(Playground *);
};

Playground *initPlayground(WINDOW *, Coordinate, int);
int getLastKey(Playground *);
int runGame(Playground *);
