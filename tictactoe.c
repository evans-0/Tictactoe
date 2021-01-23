#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SIZE;  //Size of the grid

/*wr -> Whole row, wc -> Whole column, ld -> Left diagonal, rd -> Right diagonal
n_wr -> size of wr, n_wc -> size of wc, n_ld -> size of ld, n_rd -> size of rd
*/

typedef struct pos     //Position datatype for storing the coordinates
{
    int x;
    int y;
} pos;

typedef struct data  //Data datatype for storing the possible places of victory
{
    pos *arr;
    int size;
} data;

data whole_row()  //Coordinates of whole row victory
{
    // size of wr -> n^2
    pos *wr = malloc(SIZE * SIZE * 2* sizeof(int));
    int n_wr = 0;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            wr[n_wr].x = i;
            wr[n_wr].y = j;
            n_wr++;
        }
    }
    data result;
    result.arr = wr;
    result.size = n_wr;

    return result;
}

data whole_column()  //Coordinates for whole column victory
{
    // size of wc -> n^2
    pos *wc = malloc(SIZE * SIZE * 2 * sizeof(int));
    int n_wc = 0;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            wc[n_wc].x = j;
            wc[n_wc].y = i;
            n_wc++;
        }
    }
    data result;
    result.arr = wc;
    result.size = n_wc;

    return result;
}

/*
Left diagonal
* | - | -
- | * | -
- | - | *
*/
data left_diagonal()  //Coordinates for left diagonal victory
{
    // size of ld -> n
    pos *ld = malloc(SIZE * 2 * sizeof(int));
    int n_ld = 0;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            if (i - j==0)
            {
                ld[n_ld].x = i;
                ld[n_ld].y = j;
                n_ld++;
            }
        }
    }

    data result;
    result.arr = ld;
    result.size = n_ld;

    return result;
}

/*
Right diagonal
- | - | *
- | * | -
* | - | -

*/
data right_diagonal()  //Coordinates for right diagonal victory
{
    // size of rd -> n
    pos *rd = malloc(SIZE * 2 * sizeof(int));
    int n_rd = 0;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            if (i + j==SIZE - 1)
            {
                rd[n_rd].x = i;
                rd[n_rd].y = j;
                n_rd++;
            }
        }
    }
    data result;
    result.arr = rd;
    result.size = n_rd;

    return result;
}

pos *wr, *wc, *ld, *rd;
int n_wr, n_wc, n_ld, n_rd;

void create(char *l);
void view(char *l);
int isMarked(char *l, int row, int column);
void mark(char *l, int row, int column, char symbol);
void comp_mark(char *l, char symbol);
int isFinished(char *l);
int isWin(char *l);
int play1(char name1[20], char name2[20], char sym1);
int play2(char name1[20], char name2[20], char sym1);
int count(char *arr, char arg);

int main()
{
    while (1)
    {
        int ch;
        printf("\nOptions:\n\t1. Single Player\n\t2. Double Player\n\t3. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        if (ch==1)
        {
            printf("Enter size of grid: ");
            scanf("%d", &SIZE);

            data res = whole_row();
            wr = res.arr;
            n_wr = res.size;

            res = whole_column();
            wc = res.arr;
            n_wc = res.size;

            res = left_diagonal();
            ld = res.arr;
            n_ld = res.size;

            res = right_diagonal();
            rd = res.arr;
            n_rd = res.size;

            /*
            n1 -> player 1 name, s1 -> player 1 symbol
            n2 -> player 2 name, s2 -> player 2 symbol
            */
            char *n1 = malloc(sizeof(char));
            char *n2 = "Computer";
            char *s1 = malloc(sizeof(char));
            char s2;
            printf("Enter player name: ");
            scanf("%s", n1);
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
        }

        else if (ch==2)
        {
            printf("Enter size of grid: ");
            scanf("%d", &SIZE);

            data res = whole_row();
            wr = res.arr;
            n_wr = res.size;

            res = whole_column();
            wc = res.arr;
            n_wc = res.size;

            res = left_diagonal();
            ld = res.arr;
            n_ld = res.size;

            res = right_diagonal();
            rd = res.arr;
            n_rd = res.size;

            /*
            n1 -> player 1 name, s1 -> player 1 symbol
            n2 -> player 2 name, s2 -> player 2 symbol
            */
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
            free(s1);
        }
        else if (ch==3)
        {
            break;
        }
        else
        {
            printf("\nInvalid choice\n");
        }
    }
}

//Creates array
void create(char *l)
{
    for (int i = 0; i<(SIZE * SIZE); i++)
    {
        l[i] = '-';
    }
}

//Displays the grid
void view(char *l)
{
    for (int i = 0; i<2*SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            if (i%2==0)
            {
                printf(" %c |", l[SIZE*i/2 + j]);
            }
            else
            {
                printf("___|");
            }
        }
        printf("\n");
    }
}

//Checks if the position is marked already
int isMarked(char *l, int row, int column)
{
    if (l[SIZE*(row-1) + (column-1)]=='-')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//Marks the position
void mark(char *l, int row, int column, char symbol)
{
    l[SIZE*(row-1) + (column-1)] = symbol;
}

//Computer marking
void comp_mark(char *l, char symbol)
{
    //Finding available positions
    pos avail[SIZE * SIZE];
    int c = 0;
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            if ((int) l[SIZE*i + j]==(int) '-')
            {
                avail[c].x = i;
                avail[c].y = j;
                c++;
            }
        }
    }

    //Copying array l to array l1
    char l1[SIZE * SIZE];
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            l1[SIZE*i + j] = l[SIZE*i + j];
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
        {
            l1[SIZE*avail[i].x + avail[i].y] = '-';
        }

    }
    srand(time(NULL));   // Initialization, should only be called once.
    int n = rand() % c;
    int row = avail[n].x;
    int col = avail[n].y;
    l[SIZE*row + col] = symbol;
}

//Checks if game is finished
int isFinished(char *l)
{
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
        {
            if (l[SIZE*i + j]=='-')
            {
                return 0;
            }
        }
    }
    return 1;
}

int count(char *arr, char arg)
{
    int c = 0;
    while (1)
    {
        if ((int) arr[c]==(int) arg)
        {
            c++;
        }
        else
        {
            break;
        }
    }
    return c;
}

//Checks if the player won the game
int isWin(char *l)
{
    //Left diagonal
    char c_ld[n_ld];
    for (int i = 0; i<n_ld; i++)
    {
        c_ld[i] = l[SIZE*ld[i].x + ld[i].y];
    }
    if ((count(c_ld, 'O')==SIZE) || (count(c_ld, 'X')==SIZE))
    {
        return 1;
    }

    //Right diagonal
    char c_rd[n_rd];
    for (int i = 0; i<n_rd; i++)
    {
        c_rd[i] = l[SIZE*rd[i].x + rd[i].y];
    }
    if ((count(c_rd, 'O')==SIZE) || (count(c_rd, 'X')==SIZE))
    {
        return 1;
    }

    //Row Check
    for (int i = 0; i<SIZE; i++)
    {
        char c_wr[SIZE];
        for (int j = 0; j<SIZE; j++)
        {
            c_wr[j] = l[SIZE*wr[SIZE*i +j].x + wr[SIZE*i +j].y];
        }
        if ((count(c_wr, 'O')==SIZE) || (count(c_wr, 'X')==SIZE))
        {
            return 1;
        }
    }

    //Column Check
    for (int i = 0; i<SIZE; i++)
    {
        char c_wc[SIZE];
        for (int j = 0; j<SIZE; j++)
        {
            c_wc[j] = l[SIZE*wc[SIZE*i +j].x + wc[SIZE*i +j].y];
        }
        if ((count(c_wc, 'O')==SIZE) || (count(c_wc, 'X')==SIZE))
        {
            return 1;
        }
    }

    return 0;
}

//Play a single player game
int play1(char name1[20], char name2[20], char sym1)
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
            if (((r>SIZE) || (c>SIZE)) || ((r<1) || (c<1))) 
            {
                printf("\nEnter valid row or column.\n");
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
            if (isWin(l))
            {
                view(l);
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
    char l[SIZE * SIZE];
    create(l);
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
            if (((r>SIZE) || (c>SIZE)) || ((r<1) || (c<1))) 
            {
                printf("\nEnter valid row or column.\n");
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
            if (((r>SIZE) || (c>SIZE)) || ((r<1) || (c<1))) 
            {
                printf("\nEnter valid row or column.\n");
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
