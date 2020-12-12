#ifndef	UTILS_H
#define	UTILS_H

#include <stdbool.h>

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

#endif
