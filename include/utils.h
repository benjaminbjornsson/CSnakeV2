#ifndef	UTILS_H
#define	UTILS_H

#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

#define HEIGHT	24
#define WIDTH	80

#define COLOR_GREY	8

typedef struct Range Range; 
typedef struct Coordinate Coordinate; 

struct Range {
	int start;
	int end;
};

struct Coordinate {
	int row;
	int col;
};

Range initRange(int, int);
int midRange(Range);
int rangeLen(Range);
bool inRange(Range, int);

bool coordinateCompair(Coordinate, Coordinate);

void wshadowBorder(WINDOW *, short, short);
WINDOW *initPlaygroundWindow();

#endif
