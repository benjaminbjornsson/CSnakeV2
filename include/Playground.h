#include "Snake.h"
#include "Apple.h"
#include "Level.h"
#include "utils.h"

typedef struct Playground Playground;

struct Playground {
	int rows;
	int columns;
	WINDOW *win;
	Snake *snake;
	Apple *apple;
	Level **levels;
	int score;
	int level;
	int speed;
	int (* stepGame)(Playground *, int);
};

Playground *initPlayground(WINDOW *);
int stepGame(Playground *, int);
