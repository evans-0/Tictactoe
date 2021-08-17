#ifndef WIN_H
#define WIN_H

#include <stdlib.h>
#include "grid.h"

typedef struct {  // Data datatype for storing the possible places of victory
    pos *arr;
    int size;
} data;

data whole_row(int SIZE);  // Coordinates of whole row victory
data whole_column(int SIZE);  // Coordinates for whole column victory
data left_diagonal(int SIZE);  //Coordinates for left diagonal victory
data right_diagonal(int SIZE);  //Coordinates for right diagonal victory

#endif
