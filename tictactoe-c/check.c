#include "check.h"

extern data wr, wc, ld, rd;
extern int SIZE;

//Checks if the position is marked already
int isMarked(char *l, int row, int column)
{
  if (l[SIZE*(row-1) + (column-1)]=='-')
    return 0;
  else
    return 1;
}

//Checks if game is finished
int isFinished(char *l)
{
  for (int i = 0; i<SIZE; i++)
    for (int j = 0; j<SIZE; j++)
      if (l[SIZE*i + j]=='-')
        return 0;
  return 1;
}

int count(char *arr, char arg)
{
  int c = 0;
  while (1)
    if ((int) arr[c]==(int) arg)
      c++;
    else
      break;
  return c;
}

//Checks if the player won the game
int isWin(char *l)
{
  //Left diagonal
  char c_ld[ld.size];
  for (int i = 0; i<ld.size; i++)
    c_ld[i] = l[SIZE*ld.arr[i].x + ld.arr[i].y];
  if ((count(c_ld, 'O')==SIZE) || (count(c_ld, 'X')==SIZE))
    return 1;

  //Right diagonal
  char c_rd[rd.size];
  for (int i = 0; i<rd.size; i++)
    c_rd[i] = l[SIZE*rd.arr[i].x + rd.arr[i].y];
  if ((count(c_rd, 'O')==SIZE) || (count(c_rd, 'X')==SIZE))
    return 1;

  //Row Check
  for (int i = 0; i<SIZE; i++)
  {
    char c_wr[SIZE];
    for (int j = 0; j<SIZE; j++)
      c_wr[j] = l[SIZE*wr.arr[SIZE*i +j].x + wr.arr[SIZE*i +j].y];
    if ((count(c_wr, 'O')==SIZE) || (count(c_wr, 'X')==SIZE))
      return 1;
  }
  //Column Check
  for (int i = 0; i<SIZE; i++)
  {
      char c_wc[SIZE];
      for (int j = 0; j<SIZE; j++)
        c_wc[j] = l[SIZE*wc.arr[SIZE*i +j].x + wc.arr[SIZE*i +j].y];
      if ((count(c_wc, 'O')==SIZE) || (count(c_wc, 'X')==SIZE))
        return 1;
  }

  return 0;
}
