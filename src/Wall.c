#include "Wall.h"

void wdrawWall(WINDOW *window, Wall *wall) {
	Coordinate **stepper;
	stepper = wall->coordinates;
	while(*stepper != NULL) {
		mvwaddch(window, (*stepper)->row, (*stepper)->col, 'x');
		stepper++;
	}
}

bool intersectWall(Wall *wall, Coordinate position) {
	Coordinate **stepper;
	stepper = wall->coordinates;
	while(*stepper != NULL) {
		if(coordinateCompair(**stepper, position))
			return true;
		stepper++;
	}
	
	return false;
}
