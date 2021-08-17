#ifndef GRID_H
#define GRID_H

#include <stdio.h>

extern int SIZE;

typedef struct {
  int x, y;
} pos;

void create(char *l);
void view(char *l);

#endif
