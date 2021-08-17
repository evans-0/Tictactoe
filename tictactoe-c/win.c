#include "win.h"

data whole_row(int SIZE)  // Coordinates of whole row victory
{
    // wr number -> n^2
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

data whole_column(int SIZE)  // Coordinates for whole column victory
{
    // wc number -> n^2
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
data left_diagonal(int SIZE)  //Coordinates for left diagonal victory
{
    //ld number -> n
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
data right_diagonal(int SIZE)  //Coordinates for right diagonal victory
{
    //rd number -> n
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
