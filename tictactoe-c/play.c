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
      if (i%2==0){
          nline();
          printf("%s(%c) playing...", name1, sym1);
          nline();
          mark(l, sym1);
          i++;
          if (isWin(l)){
              view(l);
              nline();
              printf("\e[38;2;0;255;0m%s won!\e[0m", name1);
              nline();
              system("sleep 1");
              return 1;
          }
      }
      else{
          nline();
          printf("%s(%c) playing...", name2, sym2);
          nline();
          nline();
          (*mark_func)(l, sym2);
          i++;
          if (isWin(l))
          {
              view(l);
              nline();
              printf("\e[38;2;0;255;0m%s won! \e[0m", name2);
              nline();
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
      nline();
      printf("\e[38;2;100;230;200mGame tied!\e[0m");
      nline();
      system("sleep 1");
      return 0;
  }
  return 0;
}
