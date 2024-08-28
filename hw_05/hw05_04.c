#include <stdio.h>


int count_zeros_in_binary(int num) 
{
    int count = 0;
    while (num > 0) 
    {
        if ((num & 1) == 0) 
            count++;
        num >>= 1;
    }
    return count;
}

int main() 
{
    int N, K;
    int count = 0;
    scanf("%d %d", &N, &K);
    
    for (int i = 1; i <= N; i++) 
    {
        if (count_zeros_in_binary(i) == K) 
            count++;
    }
    printf("%d\n", count);
    return 0;
}
