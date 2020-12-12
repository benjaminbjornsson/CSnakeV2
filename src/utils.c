#include "utils.h"

Range initRange(int start, int end) {
	Range temp = { .start = start, .end = end };
	return temp;
}

int midRange(Range range) {
	return (range.start + range.end) / 2;
}

int rangeLen(Range range) {
	return range.end - range.start;
}

bool inRange(Range range, int n) {
	return (n >= range.start) && (n <= range.end);
}

bool coordinateCompair(Coordinate coordinate1, Coordinate coordinate2) {
	return (coordinate1.row == coordinate2.row) && (coordinate1.col == coordinate2.col);
}
