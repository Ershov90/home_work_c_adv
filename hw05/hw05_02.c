#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define max_lenght 104


int main()
{
    char str1[max_lenght]={0}, str2[max_lenght]={0};
    scanf("%s", str1);
    scanf("%s", str2);
    int a=0,b=0;
    
    for (int i = 1; i <= (strlen(str1)) && i <= (strlen(str2)); i++) 
    {
        if (strncmp(str1, str2 + (strlen(str2)) - i, i) == 0)
            a = i;
    }
    for (int i = 1; i <= (strlen(str1)) && i <= (strlen(str2)); i++) 
    {
        if (strncmp(str1 + (strlen(str1)) - i, str2, i) == 0)
            b = i;
    }
    printf("%d %d\n",a,b);
    return 0;
} 



