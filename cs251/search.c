#include <stdio.h>
#include <stdlib.h>

int comparisons = 0;

void initArray(int list[], int length)
{
  int i;
  for(i =0; i < length; i++)
  {
    list[i] = rand() % 500;
  }

  list[rand() % length] = 5;
}

int find(int list[], int length, int x)
{
  int i;
  for(i = 0; i < length; i++)
  {
    if(list[i] == x)
    {
      return i;
    }
  }

  return -1;
}

void mSort(int a[], int lo, int hi, int scratch[])
{
  int i, j, k, m;

  if(lo >= hi)
  {
    return;
  }
  m = (lo + hi)/2;
  mSort(a, lo, m, scratch);
  mSort(a, m+1, hi, scratch);

  i = lo;
  j = m+1;
  k = 0;

  while(i <= m && j <= hi)
  {
    if(a[i] <= a[j])
    {
      scratch[k] = a[i];
      i++;
    }
    else
    {
      scratch[k] = a[j];
      j++;
    }
    k++;
  }
  while(i <= m)
  {
    scratch[k] = a[i];
    i++;
    k++;
  }
  while(j <= hi)
  {
    scratch[k] =a[j];
    j++;
    k++;
  }
  for(k = 0, i = lo; i <= hi; i++, k++)
  {
    a[i] = scratch[k];
  }
}

void mSort_init(int a[], int n)
{
  int *scratch;
  scratch = malloc(n * sizeof(int));

  mSort(a, 0, n-1, scratch);
  free(scratch);
}

int bSearch(int list[], int start, int end, int x)
{
  end--;
  int m = (start + end) / 2;

  comparisons++;
  if(list[m] < x)
  {
    return bSearch(list, m + 1, end, x);
  }
  comparisons++;
  if(list[m] > x)
  {
    return bSearch(list, 0, m, x);
  }
  comparisons++;
  if(list[m] == x)
  {
    return m;
  }

  return -1;
}

void printList(int list[], int length)
{
  int i;
  for(i = 0; i < length; i++)
  {
    if(i == (length -1))
    {
      printf("%d", list[i]);
    }
    else
    {
      printf("%d, ", list[i]);
    }
  }
  printf("\n");
}

int main()
{
  int x;
  int size;
  printf("Enter the length of the array: ");
  scanf("%d", &size);

  int list1[size];
  initArray(list1, size);

  printf("Number to find: ");
  scanf("%d", &x);

  int index = find(list1, size, x);

  if(index >= 0)
  {
    printf("The value %d is located in index %d.\n", x, index);
  }
  else
  {
    printf("The value %d was not found in the array.\n", x);
  }

  mSort_init(list1, size);
  printList(list1, size);

  if(index >= 0)
  {
    index = bSearch(list1, 0, size, x);
    printf("When list is sorted the value %d is located in index %d.\n", x, index);
  }

  printf("Comparisons made: %d\n", comparisons);
  comparisons = 0;

  return 0;
}


