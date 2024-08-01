/*
Задача 1-10-Упаковать массив
В программе реализована структура данных:
struct pack_array {
    uint32_t array; // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
}

Необходимо реализовать только одну функцию
(всю программу писать не надо!!!), которая упаковывает переданный ей
массив из 32-ух элементов 0 и 1 в указанную структуру данных.
Функция должна строго соответствовать прототипу:
void array2struct(int [], struct pack_array *)
Загрузите только одну функцию или просто вставьте ее текст
void array2struct(int [], struct pack_array *)

*/


#include <stdio.h>
#include <inttypes.h>

struct pack_array {
    uint32_t array;             // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8;        // счетчик нулей в array
    uint32_t count1 : 8;        // счетчик единиц в array
};

void array2struct(int *array, struct pack_array *a)
{
    for (int i = 0; i < 32; i++)
    {
        a->array <<= 1;
        if ( array[i] == 1 )
        {
            a->count1++;
            a->array++;
        }
        else
        {
            a->count0++;
        }
    }
}

void print_struct (struct pack_array a)
{
    printf("\n%x\n", a.array);
    printf ("count0=%d\n", a.count0);
    printf ("count1=%d\n", a.count1);
}

int main()
{
    struct pack_array a = {0};
    int array[32] = {1,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1};
    array2struct (array, &a);
    print_struct (a);
    return 0;
}
