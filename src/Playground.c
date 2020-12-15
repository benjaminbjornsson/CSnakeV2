#include "Playground.h"

#define LEVELS		9
#define MAXINPUT	15

#define abs(A)		(A) > 0 ? (A) : -(A)
#define min(A, B)	(A) < (B) ? (A) : (B)

static char *filenames[] = {
	"",
	"levels/level1.csv", "levels/level2.csv", "levels/level3.csv",
	"levels/level4.csv", "levels/level5.csv", "levels/level6.csv",
	"levels/level7.csv", "levels/level8.csv", "levels/level9.csv"
};

int countCoordinates(char *line) {
	int start = 0, end = 0;
	while(*line != '\0' && *line != ',' && *line != ':')
		start = start * 10 + *line++ - '0';
	if(*line++ == ',')
		return countCoordinates(line);
	while(*line != '\0' && *line!= '\n' && *line!= ',' && *line!= ':')
		end = end * 10 + *line++ - '0';
	return abs(end - start + 1);
}

Range getColonSeparatedRange(char *line) {
	Range temp = { .start = 0, .end = 0 };
	while(*line != '\0' && *line != '\n' && *line != ':')
		temp.start = 10 * temp.start + *line++ - '0';
	if(*line != ':') {
		temp.end = temp.start;
	} else {
		line++;
		while(*line != '\0' && *line != '\n')
			temp.end = 10 * temp.end + *line++ - '0';
	}
	return temp;
}

Coordinate **createCoordinates(Coordinate **coordinates, char *line) {
	char *lineptr;
	lineptr = line;

	while(*lineptr != ',')
		lineptr++;
	*lineptr++ = '\0';

	Range lower, upper;
	lower = getColonSeparatedRange(line);
	upper = getColonSeparatedRange(lineptr);

	int i, j;
	if(lower.start <= lower.end && upper.start <= upper.end) {
		for(i = lower.start; i <= lower.end; i++) {
			for(j = upper.start; j <= upper.end; j++) {
				if(j % 2)
					continue;
				*coordinates = (Coordinate *)malloc(sizeof(Coordinate));
				(*coordinates)->row = i;
				(*coordinates)->col = j;
				coordinates++;
			}
		}
	} else {
		for(i = lower.start; i >= lower.end; i--) {
			for(j = upper.start; j >= upper.end; j--) {
				if(j % 2)
					continue;
				*coordinates = (Coordinate *)malloc(sizeof(Coordinate));
				(*coordinates)->row = i;
				(*coordinates)->col = j;
				coordinates++;
			}
		}
	}
	return coordinates;
}

void loadLevel(char *filename, Level *level) {
	FILE *fileptr;
	fileptr = fopen(filename, "r");
	
	char line[MAXINPUT];
	int sum = 0;
	fgets(line, MAXINPUT, fileptr);
	level->initialSnake = (Coordinate **)malloc((countCoordinates(line) + 1) * sizeof(Coordinate *));

	while(fgets(line, MAXINPUT, fileptr))
		sum += countCoordinates(line);

	Coordinate **current;
	level->wall->coordinates = (Coordinate **)malloc((sum + 1) * sizeof(Coordinate *));

	rewind(fileptr);
	
	current = level->initialSnake;
	fgets(line, MAXINPUT, fileptr);
	current = createCoordinates(current, line);
	current = NULL;

	current = level->wall->coordinates;
	while(fgets(line, MAXINPUT, fileptr))
		current = createCoordinates(current, line);
	current = NULL;

	fclose(fileptr);
}

Level **loadLevels() {
	Level **levels;
	levels = (Level **)malloc((LEVELS + 1) * sizeof(Level *));
	int i;
	for(i = 0; i <= LEVELS; i++) {
		levels[i] = (Level *)malloc(sizeof(Level));
		levels[i]->level = i;
		levels[i]->wall = (Wall *)malloc(sizeof(Wall));
	}
	
	for(i = 1; i <= LEVELS; i++)
		loadLevel(filenames[i], levels[i]);

	return levels;
}

Playground *initPlayground(WINDOW *window) {
	Playground *temp;
	temp = (Playground *)malloc(sizeof(Playground));
	getmaxyx(window, temp->rows, temp->columns);
	temp->snake = NULL;
	temp->win = window;
	temp->apple = NULL;
	temp->levels = loadLevels();
	temp->score = 0;
	temp->level = 1;
	temp->speed = 1;
	temp->stepGame = stepGame;
	nodelay(temp->win, TRUE);
	return temp;
}

void wdrawApple(WINDOW *window, Apple *apple) {
	if (apple == NULL)
		return;
	mvwaddch(window, apple->position.row, apple->position.col, apple->symbol);
}

void stepApple(Playground *playground) {
	if(playground->apple == NULL) {
		do {
			free(playground->apple);
			playground->apple = newApple(playground->rows, playground->columns);
		} while(intersectSnake(playground->snake, playground->apple->position) || intersectWall(playground->levels[playground->level]->wall, playground->apple->position));
	} else {
		if(playground->apple->timeLeft == 0) {
			free(playground->apple);
			playground->apple = NULL;
			stepApple(playground);
		} else {
			playground->apple->timeLeft--;
		}
	}
}

bool ateApple(Playground *playground) {
	Coordinate next;
	bool ateApple;
	if(playground->apple == NULL)
		return FALSE;
	next = nextCoordinate(playground->snake, playground->rows, playground->columns);
	ateApple = coordinateCompair(next, playground->apple->position);
	if(ateApple) {
		playground->score++;
		free(playground->apple);
		playground->apple = NULL;
	}
	return ateApple;
}

int stepGame(Playground *playground, int nextKey) {
	int speed;
	speed = min(playground->speed + playground->score / 2, 9);
	updateSnakeDirection(playground->snake, nextKey);
	wclear(playground->win);
	if(!stepSnake(playground->snake, ateApple(playground), playground->rows, playground->columns) || intersectWall(playground->levels[playground->level]->wall, playground->snake->head->position))
		return -1;
	stepApple(playground);
	wdrawSnake(playground->win, playground->snake);
	wdrawWall(playground->win, playground->levels[playground->level]->wall);
	wdrawApple(playground->win, playground->apple);
	wrefresh(playground->win);
	napms(275 - 25 * (speed - 1));
	return playground->score;
}
