CC=gcc

CFILES=main.c grid.c mark.c check.c win.c play.c
OBJECTS=main.o grid.o mark.o check.o win.o play.o

BINARY=game

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $^

clean:
	rm $(BINARY) $(OBJECTS)
