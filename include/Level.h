#include "utils.h"
#include "Wall.h"

typedef struct Level Level;

struct Level {
	Wall *wall;
	int highscore;
};
