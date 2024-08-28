#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define max_lenght 100

uint32_t combo(uint8_t array[], uint64_t size)
{
  bool found[1000];
  for (uint16_t i = 0; i < 1000; i++)
    found[i] = false;
  for (uint64_t i = 0; i < size - 2; i++)
  {
    for (uint64_t j = i + 1; j < size - 1; j++)
    {
      for (uint64_t k = j + 1; k < size; k++)
        found[array[i] * 100 + array[j] * 10 + array[k]] = true;
    }
  }
  uint32_t count = 0;
  for (uint16_t i = 0; i < 1000; i++)
  {
    if (found[i])
      count++;
  }
  return count;
}

int main()
{
  uint8_t array[max_lenght];
  uint64_t size = 0;
  char c = 0;
  while ((c = getchar()) != '\n')
    array[size++] = c - '0';
  printf("%d\n", combo(array, size));
  return 0;
}
