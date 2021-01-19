#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char l[3][3];

typedef struct pos
{
    int x;
    int y;
} pos;

void view(char l[3][3]);                                          //View the grid
int isMarked(char l[3][3], int row, int column);                  //Check if the position is already marked
void mark(char l[3][3], int row, int column, char symbol);        //Mark at a position(Player)
void comp_mark(char l[3][3], char symbol);                        //Mark at a position(Computer)
int isFinished(char l[3][3]);                                     //Check if game finished
int isWin(char l[3][3]);                                          //Check if game won
int play1(char name1[20], char *name2, char sym1);                //Single player game
int play2(char name1[20], char name2[20], char sym1);             //Double player game

int main()
{
    int ch;
    printf("Options:\n\t1. Single Player\n\t2. Double Player");
    printf("\nEnter choice: ");
    scanf("%d", &ch);

    if (ch==1) //Single player
    {
    /*n1 -> player 1 name, s1 -> player 1 symbol
    n2 -> computer, s2 -> computer symbol*/
    char *n1 = malloc(sizeof(char));
    char *n2 = "Computer";
    char *s1 = malloc(sizeof(char));
    char s2;
    printf("Enter player name: ");
    scanf("%s", n1);
    printf("Enter symbol for %s(O/X): ", n1);
    scanf("%s", s1);
    
    //n -> No. of games, w1 -> No. of games won by player 1, w2 -> No. of games won by computer
    int n, w1 = 0, w2 = 0;
    printf("Number of games: ");
    scanf("%d", &n);
    if (n<1)
    {
        printf("Please enter valid no. of games.\n");
        return 1;
    }
    for(int i = 1; i<=n; i++)
    {
        printf("\nMatch %d of %d\n", i, n);
        int res = play1(n1, n2, s1[0]);
        if (res==1)
        {
            w1++;
        }
        else if (res==2)
        {
            w2++;
        }
    }

    printf("\nScores:\n%s -> %d\n%s -> %d\n", n1, w1, n2, w2);
    printf("Thank you for playing!\n");
    free(n1);
    free(s1);
    return 0;
    }
    else if (ch==2) //Double player
    {
        char *n1 = malloc(sizeof(char));
        char *n2 = malloc(sizeof(char));
        char *s1 = malloc(sizeof(char));
        char s2;
        printf("Enter player 1 name: ");
        scanf("%s", n1);
        printf("Enter player 2 name: ");
        scanf("%s", n2);
        printf("Enter symbol for %s(O/X): ", n1);
        scanf("%s", s1);
        
        //n -> No. of games, w1 -> No. of games won by player 1, w2 -> No. of games won by player 2
        int n, w1 = 0, w2 = 0;
        printf("Number of games: ");
        scanf("%d", &n);
        if (n<1)
        {
            printf("Please enter valid no. of games.\n");
            return 1;
        }
        for(int i = 1; i<=n; i++)
        {
            printf("\nMatch %d of %d\n", i, n);
            int res = play2(n1, n2, s1[0]);
            if (res==1)
            {
                w1++;
            }
            else if (res==2)
            {
                w2++;
            }
        }

        printf("\nScores:\n%s -> %d\n%s -> %d\n", n1, w1, n2, w2);
        printf("Thank you for playing!\n");
        free(n1);
        free(n2);
        free(s1);
        return 0;
    }
    else
    {
        printf("Invalid choice!");
        return 0;
    }
}

//Displays the grid
void view(char l[3][3])
{
    printf("\n");
    printf(" ____ ____ ____\n");
    printf("|  %c |  %c |  %c |\n", l[0][0], l[0][1], l[0][2]);
    printf("|____|____|____|\n");
    printf("|  %c |  %c |  %c |\n", l[1][0], l[1][1], l[1][2]);
    printf("|____|____|____|\n");
    printf("|  %c |  %c |  %c |\n", l[2][0], l[2][1], l[2][2]);
    printf("|____|____|____|\n");
}

//Checks if the position is marked already
int isMarked(char l[3][3], int row, int column)
{
    if (l[row-1][column-1]=='-')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//Marks the position
void mark(char l[3][3], int row, int column, char symbol)
{
    l[row-1][column-1] = symbol;
}

//Computer marking
void comp_mark(char l[3][3], char symbol)
{
    //Finding available positions
    pos avail[9];
    int c = 0;
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if ((int) l[i][j]==45)
            {
                avail[c].x = i;
                avail[c].y = j;
                c++;
            }
        }
    }

    //Copying array l to array l1
    char l1[3][3];
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            l1[i][j] = l[i][j];
        }
    }

    char o_symbol;
    if ((int) symbol == (int) 'X')
    {
        o_symbol = 'O';
    }
    else
    {
        o_symbol = 'X';
    }

     //Checking if computer won
    for (int i = 0; i<c; i++)
    {
        l1[avail[i].x][avail[i].y] = symbol;
        if (isWin(l1))
        {
            l[avail[i].x][avail[i].y] = symbol;
            return;
        }
        else
        {
            l1[avail[i].x][avail[i].y] = '-';
        }
    }
    //Checking if player won after player marks
    for (int i = 0; i<c; i++)
    {
        l1[avail[i].x][avail[i].y] = o_symbol;
        if (isWin(l1)) 
        {
            l[avail[i].x][avail[i].y] = symbol;
            return;
        }
        else
        {
            l1[avail[i].x][avail[i].y] = '-';
        }

    }
    srand(time(NULL));   // Initialization, should only be called once.
    int n = rand() % c;
    int row = avail[n].x;
    int col = avail[n].y;
    l[row][col] = symbol;
}

//Checks if game is finished
int isFinished(char l[3][3])
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (l[i][j]=='-')
            {
                return 0;
            }
        }
    }
    return 1;
}

//Checks if the player won the game
int isWin(char l[3][3])
{
    for (int i = 0; i<3; i++)
    {
        if (((l[i][0]==l[i][1]) && (l[i][1]==l[i][2])) && (l[i][2]!='-'))      //Row check
        {
            return 1;
        }
        else if (((l[0][i]==l[1][i]) && (l[1][i]==l[2][i])) && (l[2][i]!='-'))  //Columns check
        {
            return 1;
        }
        else if ((l[0][0]==l[1][1]) && (l[1][1]==l[2][2]) && (l[2][2]!='-'))  //Diagonal from left top to right bottom
        {
            return 1;
        }
        else if ((l[0][2]==l[1][1]) && (l[1][1]==l[2][0]) && (l[2][0]!='-'))  //Diagonal from right top to left bottom
        {
            return 1;
        }
    }
    return 0;
}

//Play a single player game
int play1(char name1[20], char *name2, char sym1)
{
    char l[3][3] = {{'-','-','-'}, {'-','-','-'}, {'-','-','-'}};
    /* name1 -> Name of player 1, sym1 -> Symbol for player 1
       name2 -> computer, sym2 -> Symbol for computer  */
    char sym2;
    if ((sym1=='O') || (sym1=='o'))
    {
        sym1 = 'O';
        sym2 = 'X';
    } 
    else
    {
        sym1 = 'X';
        sym2 = 'O';
    }
    int i, r, c;
    i = 0;
    //For even numbers player 1 plays and for odd numbers player 2 plays
    while (1)
    {
        if (i%2==0)
        {
            view(l);
            printf("\n%s(%c) playing...\n", name1, sym1);
            printf("Which row do you want to mark? ");
            scanf("%d", &r);
            printf("Which column do you want to mark? ");
            scanf("%d", &c);
            if (((r>3) || (c>3)) || ((r<1) || (c<1))) 
            {
                printf("\nEnter valid row or column.");
            }
            else
            {
                if (isMarked(l, r,c))
                {
                    printf("\nAlready marked\n");
                }
                else
                {
                    mark(l, r, c, sym1);
                    i++;
                }
            }
            view(l);
            if (isWin(l))
            {
                printf("\n%s won!\n", name1);
                return 1;
            }
        }
        else
        {
            printf("\n%s(%c) playing...\n", name2, sym2);
            comp_mark(l, sym2);
            i++;
            if (isWin(l))
            {   
                view(l);
                printf("\n%s won!\n", name2);
                return 2;
            }
        }
        if (isFinished(l))
        {
            break;
        }
    }
    if ((isWin(l)==0) && (isFinished(l)))
    {
        printf("\nGame tied!\n");
        return 0;
    }
    return 0;
}

//Play a double player game
int play2(char name1[20], char name2[20], char sym1)
{
    char l[3][3] = {{'-','-','-'}, {'-','-','-'}, {'-','-','-'}};
    /* name1 -> Name of player 1, sym1 -> Symbol for player 1
       name2 -> Name of player 2, sym2 -> Symbol for player 2  */
    char sym2;
    if ((sym1=='O') || (sym1=='o'))
    {
        sym1 = 'O';
        sym2 = 'X';
    } 
    else
    {
        sym1 = 'X';
        sym2 = 'O';
    }
    int i, r, c;
    i = 0;
    view(l);
    //For even numbers player 1 plays and for odd numbers player 2 plays
    while (1)
    {
        if (i%2==0)
        {
            printf("\n%s(%c) playing...\n", name1, sym1);
            printf("Which row do you want to mark? ");
            scanf("%d", &r);
            printf("Which column do you want to mark? ");
            scanf("%d", &c);
            if (((r>3) || (c>3)) || ((r<1) || (c<1))) 
            {
                printf("\nEnter valid row or column.");
            }
            else
            {
                if (isMarked(l, r,c))
                {
                    printf("\nAlready marked\n");
                }
                else
                {
                    mark(l, r, c, sym1);
                    i++;
                }
            }
            view(l);
            if (isWin(l))
            {
                printf("\n%s won!\n", name1);
                return 1;
            }
        }
        else
        {
            printf("\n%s(%c) playing...\n", name2, sym2);
            printf("Which row do you want to mark? ");
            scanf("%d", &r);
            printf("Which column do you want to mark? ");
            scanf("%d", &c);
            if (((r>3) || (c>3)) || ((r<1) || (c<1))) 
            {
                printf("\nEnter valid row or column.");
            }
            else
            {
                if (isMarked(l, r,c))
                {
                    printf("\nAlready marked\n");
                }
                else
                {
                    mark(l, r, c, sym2);
                    i++;
                }
            }
            view(l);
            if (isWin(l))
            {
                printf("\n%s won!\n", name2);
                return 2;
            }
        }
        if (isFinished(l))
        {
            break;
        }
    }
    if ((isWin(l)==0) && (isFinished(l)))
    {
        printf("\nGame tied!\n");
        return 0;
    }
    return 0;
}
