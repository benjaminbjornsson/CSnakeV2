#include <stdlib.h>
#include "utils.h"
#include <ncurses.h>

typedef struct Wall Wall;

struct Wall {
	Coordinate **coordinates;
};

void wdrawWall(WINDOW *, Wall *);
bool intersectWall(Wall *, Coordinate);
