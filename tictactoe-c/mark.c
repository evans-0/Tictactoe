#include "mark.h"

extern int SIZE;
extern int isWin();
extern void getint();

//Marks the position
void mark(char *l, char symbol)
{
    int r, c;//, status, success;
    while (1)
    {
        getint("Which row do you want to mark? ", &r);
        getint("Which column do you want to mark? ", &c);
        if (((r > SIZE) || (c > SIZE)) || ((r < 1) || (c < 1)))
            printf("\nEnter a valid row or column.\n");
        else
        {
            if(isMarked(l, r, c))
                printf("\nAlready marked\n");
            else
            {
                l[SIZE*(r-1) + (c-1)] = symbol;
                break;
            }
        }
    }
    return;
}

//Computer marking
void comp_mark(char *l, char symbol)
{
    //Finding available positions
    pos avail[SIZE * SIZE];
    int c = 0;
    for (int i = 0; i<SIZE; i++)
      for (int j = 0; j<SIZE; j++)
        if ((int) l[SIZE*i + j]==(int) '-')
        {
          avail[c].x = i;
          avail[c].y = j;
          c++;
        }

    //Copying array l to array l1
    char l1[SIZE * SIZE];
    for (int i = 0; i<SIZE; i++)
      for (int j = 0; j<SIZE; j++)
          l1[SIZE*i + j] = l[SIZE*i + j];

    char o_symbol = (symbol == 'X') ? 'O' : 'X';

    //Checking if computer won
    for (int i = 0; i<c; i++)
    {
      l1[SIZE*avail[i].x + avail[i].y] = symbol;
      if (isWin(l1))
      {
        l[SIZE*avail[i].x + avail[i].y] = symbol;
        return;
      }
      else
      {
        l1[SIZE*avail[i].x + avail[i].y] = '-';
      }
    }

    //Checking if player won after player marks
    for (int i = 0; i<c; i++)
    {
      l1[SIZE*avail[i].x + avail[i].y] = o_symbol;
      if (isWin(l1))
      {
        l[SIZE*avail[i].x + avail[i].y] = symbol;
        return;
      }
      else
        l1[SIZE*avail[i].x + avail[i].y] = '-';

    }

      srand(time(NULL));   // Initialization, should only be called once.
      int n = rand() % c;
      int row = avail[n].x;
      int col = avail[n].y;
      l[SIZE*row + col] = symbol;
}
