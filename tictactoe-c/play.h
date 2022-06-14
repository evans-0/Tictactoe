#ifndef PLAY_H
#define PLAY_H

#include <stdio.h>
#include "grid.h"
#include "mark.h"
#include "check.h"
#include "win.h"

extern int SIZE;
extern void clrscr();
extern void nline();
extern int c_row, c_col;

int play(char *name1, char *name2, char sym1, void(*mark_func)(char*, char));

#endif
