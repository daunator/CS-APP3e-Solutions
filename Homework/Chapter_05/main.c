#include <stdlib.h>

#include "combine.h"

/* function prototypes */
void inner41(vec_ptr u, vec_ptr v, data_t *dest);
void inner42(vec_ptr u, vec_ptr v, data_t *dest);
void inner41a(vec_ptr u, vec_ptr v, data_t *dest);
void *basic_memset(void *s, int c, size_t n);

int main()
{ 
  /* Initialize vectors */
  vec_ptr u = new_vec(300);
  vec_ptr v = new_vec(300);
  for(int ii = 0; ii < 300; ii++) {
    int jj = (ii % 10) + 1;
    set_vec_element(u, ii, (data_t)jj);
    set_vec_element(v, ii, (data_t) (10 - jj));
  }

  data_t dest;
  inner41(u, v, &dest);
  inner42(u, v, &dest);
  inner41a(u, v, &dest);

  void *block = malloc(123);
  basic_memset(block, 321 , 123);
  free(block);
  
  return 0;
}

