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
	int score;
	int (* stepGame)(Playground *, int);
};

Playground *initPlayground(WINDOW *, Coordinate, int);
int stepGame(Playground *, int);
