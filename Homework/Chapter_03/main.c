#include <stdint.h>
#include <limits.h>
#include <stdio.h>

typedef __int128 int128_t;
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

/* function prototypes */
long decode2(long x, long y, long z);
void store_prod(int128_t *dest, int64_t x, int64_t y);
long loop(long, long);
long cred_alt(long *xp);
long switch3(long *p1, long *p2, mode_t action);

int main()
{
  /*** 3.58 ***/
  decode2(1l, 2l, 3l);

  /*** 3.59 ***/
  int128_t dest;
  store_prod(&dest, LONG_MAX, LONG_MAX);

  /*** 3.60 ***/
  loop(1l, 2l);

  /*** 3.61 ***/
  long l1;
  cred_alt(&l1);

  /*** 3.63 ***/
  long l2;
  switch3(&l1, &l2, MODE_E);

  return 0;
}

