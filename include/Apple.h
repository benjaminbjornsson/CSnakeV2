#include <stdlib.h>
#include "utils.h"

typedef struct Apple Apple;

struct Apple {
    Coordinate position;
	char symbol;
    int timeLeft;
};

Apple *newApple();
