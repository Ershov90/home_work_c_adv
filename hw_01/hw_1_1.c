/*На стандартном потоке ввода задается натуральное число N (N > 0),
 после которого следует последовательность из N целых чисел.
На стандартный поток вывода напечатайте, сколько раз в этой 
последовательности встречается максимум.
*/


#include <stdio.h>

int main()
{
    int N, c, max, count = 1;
    scanf ("%d", &N);
    scanf ("%d", &c);
    max = c;
    for (int i = 1; i < N; i++)
    {
        scanf ("%d", &c);
        if ( max == c)
            count++;
        if (max < c)
        {
            max = c;
            count = 1;
        }
    }
    printf ("%d\n", count);
    return 0;
}

