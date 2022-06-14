#include "grid.h"

//Creates array
void create(char *l)
{
  for (int i = 0; i<(SIZE * SIZE); i++)
    l[i] = '-';
}

//Displays the grid
void view(char *l)
{
    clrscr();
    printf("\e[%d;%dH", c_row++, c_col);
    printf("\033[40;33m");
    for (int i = 0; i<2*SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
            if (i%2==0)
                printf(" %c |", l[SIZE*i/2 + j]);
            else
                printf("___|");
        printf("\e[%d;%dH", c_row++, c_col);
    }
    printf("\e[0m");
}
