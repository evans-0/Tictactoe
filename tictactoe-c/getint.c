#include <stdio.h>

void flush_stdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getint(char *s, int *n)
{
    int status, success = 1;
    do
    {
        if (!success)
            printf("\033[1A");
        printf("\033[2K");
        printf("%s", s);
        status = scanf("%d", n);
        flush_stdin();
        success = 0;
    } while (!status);
}
