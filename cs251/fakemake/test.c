#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hmap.h"

void test_dict() {
char word[128];

  HMAP_PTR dict0 = hmap_create(0,1.0);
  HMAP_PTR dict1 = hmap_create(0,1.0);

  hmap_set_hfunc(dict0, NAIVE_HFUNC);

  while(scanf("%s", word) == 1) {
	hmap_set(dict0, word, NULL);
	hmap_set(dict1, word, NULL);
	if(!hmap_contains(dict0, word))
		fprintf(stderr, "hmap failure (0)\n");
	if(!hmap_contains(dict1, word))
		fprintf(stderr, "hmap failure (1)\n");
  }

  // sanity check on removal
  hmap_set(dict0, "wonka", NULL);
  if(!hmap_contains(dict0, "wonka"))
	fprintf(stderr, "hmap failure (2)\n");

  hmap_remove(dict0, "wonka");
  if(hmap_contains(dict0, "wonka"))
	fprintf(stderr, "hmap failure (3)\n");

  printf("----- NAIVE HASH FUNCTION -----\n");
  hmap_display(dict0);
  printf("----- WEIGHTED HASH FUNCTION -----\n");
  hmap_display(dict1);

  hmap_print_stats(dict0);
  hmap_print_stats(dict1);

  hmap_free(dict0, 0);
  hmap_free(dict1, 0);
}

  
  

  


int main() {

  test_dict();


}
