DIRS = src include build
objects = build/main.o

CSnake : $(objects)
	cc -o CSnake $(objects) -lncurses

build/main.o : 
	cc -c src/main.c -o build/main.o

clean : 
	rm CSnake $(objects)
