#ifndef MARK_H
#define MARK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "check.h"

extern int SIZE;
extern int isWin();
extern void nline();

void mark(char *l, char symbol);
void comp_mark(char *l, char symbol);

#endif
