/*
Шифр Цезаря 
*/


#include <stdio.h>

int main()
{
    int N;
    scanf ("%d", &N);
    char c, p;
    while ( (c=getchar()) != '.')
    {
        if ( c >= 'A' && c <= 'Z' )
        {
            p = (c - 'A' + N)% 26 + 'A';
            putchar(p);
        }
        else if ( c >= 'a' && c <= 'z' )
        {
            p = (c - 'a' + N) % 26 + 'a';
            putchar(p);
        }
        else if ( c == ' ' )
            putchar(' ');

    }
    putchar('.');
    return 0;
}

