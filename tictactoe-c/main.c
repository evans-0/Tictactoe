#include <string.h>
#include "grid.h"
#include "win.h"
#include "check.h"
#include "mark.h"
#include "win.h"
#include "play.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

#define MAX_COLOR 256

int NAME_SIZE = 100;
int SIZE;
data wr, wc, ld, rd;
int row,col;
int c_row = 3, c_col = 3;

void clrscr();
void nline();
void flush_stdin();

int main()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    row = w.ws_row - 1;
    col = w.ws_col;
    printf("\e[1J\e[;H");
    for (int i = 0; i<row; i++){
        for (int j = 0; j<col; j++){
            if ((i==0) || (i==(row-1)))
                printf("\e[1;7m \e[0m");
            else{
                if ((j==0) || (j==(col-1)))
                    printf("\e[1;7m \e[0m");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("\e[2;2H");
    srand(time(NULL));
    int r = rand() % MAX_COLOR;
    int g = rand() % MAX_COLOR;
    int b = rand() % MAX_COLOR;
    for (int i=0; i<col-2; i++)
        printf("\e[38;2;%d;%d;%d;7m \e[0m", r, g, b);
    printf("\e[%d;%dH", 2, col/2-5);
    printf("\e[38;2;%d;%d;%d;1;7mTIC-TAC-TOE\e[0m", r, g, b);
    printf("\e[3;2H");
    fflush(stdout);
    while (1)
    {
        int ch;
        clrscr();
        printf("\e[%d;%dH", c_row, c_col);
		printf("Options:\n\t1. Single Player\n\t2. Double Player\n\t3. Exit");
        c_row += 4; // Skipping 3 lines
        printf("\e[%d;%dH", c_row++, c_col);
        printf("Enter choice: ");
        int status = scanf("%d", &ch);
		flush_stdin();
		if (!status){
            clrscr();
			printf("\e[38;2;255;0;0mInvalid choice!\e[0m\n");
            system("sleep 0.5");
			continue;
        }

		if ((ch == 1) || (ch == 2))
        {
            printf("\e[%d;%dH", c_row++, c_col);
            printf("Enter size of grid: ");
            scanf("%d", &SIZE);
            
            wr = whole_row(SIZE);
            wc = whole_column(SIZE);
            ld = left_diagonal(SIZE);
            rd = right_diagonal(SIZE);

// n1 -> player 1 name, s1 -> player 1 symbol
// n2 -> player 2 name, s2 -> player 2 symbol
            char *n1 = malloc(NAME_SIZE * sizeof(char));
            char *buffer = malloc(NAME_SIZE * sizeof(char));
            char *n2 = malloc(NAME_SIZE * sizeof(char));
            char s1;
            printf("\e[%d;%dH", c_row++, c_col);
            printf("Enter player 1 name: ");
            scanf("%s", buffer);
            fgetc(stdin);    // to clear the \n scanf left
            strncpy(n1, buffer, NAME_SIZE);
            if (ch == 1)
                strcpy(n2, "Computer");
            else
			{
                printf("\e[%d;%dH", c_row++, c_col);
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
                printf("\e[%d;%dH", c_row++, c_col);
                printf("Enter symbol for %s(O/X): ", n1);
                scanf("%c", &s1);
                flush_stdin();
                success = 0;
            } while ((s1 != 'X') && (s1 != 'O'));

		  //n -> No. of games, w1 -> No. of games won by player 1, w2 -> No. of games won by player 2
		  int n, w1 = 0, w2 = 0;
          printf("\e[%d;%dH", c_row++, c_col);
          printf("Number of games: ");
          scanf("%d", &n);
          
		  int res;
		  for(int i = 1; i<=n; i++)
		  {
			clrscr();
            printf("\e[%d;%dH", c_row++, c_col);
			printf("\e[38;2;255;0;0mMatch %d of %d\e[0m\n", i, n);
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
          printf("\e[%d;%dH", c_row++, c_col);
		  printf("Scores:\t");
          nline();
          printf("\t%s -> %d", n1, w1);
          nline();
          printf("\t%s -> %d", n2, w2);
          nline();
          printf("Press enter to continue...");
          flush_stdin();
          char sc;
          scanf("%c", &sc);
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
		printf("\e[91;1mInvalid choice...\e[0m");
		c_row++;
       	nline();
	   	system("sleep 0.5");
		clrscr();
		}
    }
}

void clrscr(){
	printf("\e[3;H");
	for (int i = 3; i<row; i++){
    	for (int j = 0; j<col; j++){
       		if ((i==0) || (i==(row-1)))
                printf("\e[1;7m \e[0m");
            else{
                if ((j==0) || (j==(col-1)))
                    printf("\e[1;7m \e[0m");
                else
                    printf(" ");
            }
    	}
        printf("\n");
    }
    c_row = 3;
    printf("\e[%d;%dH", c_row, c_col);
    fflush(stdout);
}

void nline(){
    printf("\e[%d;%dH", c_row++, c_col);
    fflush(stdout);
}

void flush_stdin(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
