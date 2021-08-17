main: main.c getint.o grid.o mark.o check.o win.o play.o
	gcc main.c getint.o grid.o mark.o check.o win.o play.o
getint.o: getint.c
	gcc -c getint.c
grid.o: grid.c
	gcc -c grid.c
mark.o: mark.c
	gcc -c mark.c
check.o: check.c
	gcc -c check.c
win.o: win.c
	gcc -c win.c
play.o: play.c
	gcc -c play.c
clean:
	rm grid.o mark.o check.o win.o play.o a.out getint.o
