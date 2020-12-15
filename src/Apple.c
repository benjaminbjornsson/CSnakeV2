#include "Apple.h"

Apple *newApple(int rows, int columns) {
	Apple *temp;
	temp = (Apple *)malloc(sizeof(Apple));
	temp->position.row = rand() % rows;
	temp->position.col = rand() % columns;
	if(temp->position.col % 2)
		temp->position.col--;
	temp->symbol = '@';
	temp->timeLeft = 50;
	return temp;
}
