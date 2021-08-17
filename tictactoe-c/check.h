#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>
#include "win.h"
#include "grid.h"
#include "check.h"

int isMarked(char *l, int row, int column);
int isFinished(char *l);
int isWin(char *l);

#endif
