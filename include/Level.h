#include "utils.h"
#include "Wall.h"

typedef struct Level Level;

struct Level {
	int level;
	Wall *wall;
	int highscore;
	Coordinate **initialSnake;
};
