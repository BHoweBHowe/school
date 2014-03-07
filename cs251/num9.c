#include <stdio.h>
#include <stdlib.h>

void initArray(int *a, int m)
{
  a = malloc((m * 2) * sizeof(int));
}
int main()
{
  int m;
  int a[];

  printf("length of array: ");
  scanf("%d", &m);
  initArray(*a, m);

  printArray(a);
}
