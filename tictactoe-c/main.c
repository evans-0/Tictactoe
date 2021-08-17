#include <string.h>
#include "grid.h"
#include "win.h"
#include "check.h"
#include "mark.h"
#include "win.h"
#include "play.h"

int NAME_SIZE = 100;
int SIZE;
data wr, wc, ld, rd;

void clrscr()
{
	printf("\033[2;H");
	printf("\033[J");
}

extern void flush_stdin();
extern void getint();

int main()
{
    printf("\033[1J"); // erase lines above current line
    printf("\033[;H"); // move cursor to home
    printf("\033[94;1;7m");
    printf("\t\tTICTACTOE\t\t");
    printf("\033[0m");
    while (1)
    {
        int ch;
        clrscr();
		printf("\nOptions:\n\t1. Single Player\n\t2. Double Player\n\t3. Exit");
        printf("\nEnter choice: ");
        int status = scanf("%d", &ch);
		flush_stdin();
		if (!status)
		{
            clrscr();
			printf("\033[38;2;255;0;0mInvalid choice!\033[0m\n");
            system("sleep 0.5");
			continue;
            }

		if ((ch == 1) || (ch == 2))
        {
            getint("Enter size of grid: ", &SIZE);
            
            wr = whole_row(SIZE);
            wc = whole_column(SIZE);
            ld = left_diagonal(SIZE);
            rd = right_diagonal(SIZE);

            /* n1 -> player 1 name, s1 -> player 1 symbol
               n2 -> player 2 name, s2 -> player 2 symbol */
            char *n1 = malloc(NAME_SIZE * sizeof(char));
            char *buffer = malloc(NAME_SIZE * sizeof(char));
            char *n2 = malloc(NAME_SIZE * sizeof(char));
            char s1;
            printf("Enter player 1 name: ");
            scanf("%s", buffer);
            fgetc(stdin);    // to clear the \n scanf left
            strncpy(n1, buffer, NAME_SIZE);
            if (ch == 1)
                strcpy(n2, "Computer");
            else
			{
                printf("Enter player 2 name: ");
                scanf("%s", buffer);
                fgetc(stdin);
                strncpy(n2, buffer, NAME_SIZE);
            }
            free(buffer);    // freeing the buffer
            int success = 1;
            do
            {
                if (!success)
                    printf("\033[1A");
                printf("\033[2K");
                printf("Enter symbol for %s(O/X): ", n1);
                scanf("%c", &s1);
                flush_stdin();
                success = 0;
            } while ((s1 != 'X') && (s1 != 'O'));

		  //n -> No. of games, w1 -> No. of games won by player 1, w2 -> No. of games won by player 2
		  int n, w1 = 0, w2 = 0;
          getint("Number of games: ", &n);
          
		  int res;
		  for(int i = 1; i<=n; i++)
		  {
			clrscr();
			printf("\n\033[38;2;255;0;0mMatch %d of %d\033[0m\n", i, n);
			system("sleep 0.5");
			if (ch == 1)
			  res = play(n1, n2, s1, &comp_mark);
			else
			  res = play(n1, n2, s1, &mark);
			if (res==1)
			  w1++;
			else if (res==2)
			  w2++;
		  }
		  clrscr();
		  printf("\nScores:\n%s -> %d\n%s -> %d\n", n1, w1, n2, w2);
		  system("sleep 1");
		  free(n1);
		  free(n2);
		  free(wr.arr);
		  free(wc.arr);
		  free(ld.arr);
		  free(rd.arr);
        }
        else if (ch == 3)
            break;
        else{
		  clrscr();
		  printf("Invalid choice...\n");
		  system("sleep 0.5");
		  clrscr();
		}
    }
}
