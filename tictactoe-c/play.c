#include "play.h"

//Play a single player game
int play(char *name1, char *name2, char sym1, void(*mark_func)(char*, char))
{
  char l[SIZE * SIZE];
  create(l);
  /* name1 -> Name of player 1, sym1 -> Symbol for player 1
     name2 -> computer, sym2 -> Symbol for computer  */
  char sym2;
  if ((sym1=='O') || (sym1=='o'))
  {
    sym1 = 'O';
    sym2 = 'X';
  } else
  {
    sym1 = 'X';
    sym2 = 'O';
  }
  int i;
  i = 0;
  //For even numbers player 1 plays and for odd numbers player 2 plays
  while (1)
  {
    view(l);
    if (i%2==0)
    {
      printf("\n%s(%c) playing...\n", name1, sym1);
      mark(l, sym1);
      i++;
      if (isWin(l))
      {
		view(l);
        printf("\n\033[38;2;0;255;0m%s won!\033[0m\n", name1);
		system("sleep 1");
        return 1;
      }
    }
    else
    {
      printf("\n%s(%c) playing...\n\n", name2, sym2);
      (*mark_func)(l, sym2);
      i++;
      if (isWin(l))
      {
        view(l);
        printf("\n\033[38;2;0;255;0m%s won!\033[0m\n", name2);
		system("sleep 1");
		return 2;
      }
    }
    if (isFinished(l))
    {
      view(l);
      break;
    }
  }
  if ((isWin(l)==0) && (isFinished(l)))
  {
    view(l);
    printf("\n\033[38;2;100;230;200mGame tied!\033[0m\n");
	system("sleep 1");
    return 0;
  }
  return 0;
}
