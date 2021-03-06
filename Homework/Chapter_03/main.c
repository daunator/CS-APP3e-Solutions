#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef __int128 int128_t;
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;
typedef union { unsigned int u; float f; } float_int_t;
typedef enum {NEG, ZERO, POS, OTHER} range_t;

/* function prototypes */
long decode2(long x, long y, long z);
void store_prod(int128_t *dest, int64_t x, int64_t y);
long loop(long, long);
long cred_alt(long *xp);
long switch3(long *p1, long *p2, mode_t action);
long switch_prob(long x, long n);
long store_ele(long i, long j, long k, long *dest);
void transpose(long A[15][15]);
long sum_col(long n, long A[3*n][4*n + 1], long j);
void good_echo(void);
range_t find_range_1(float x);
range_t find_range_2(float x);

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

  /*** 3.62 ***/
  long l2;
  switch3(&l1, &l2, MODE_E);

  /*** 3.63 ***/
  switch_prob(1l, 2l);

  /*** 3.64 ***/
  store_ele(1l, 2l, 3l, &l1);

  /*** 3.65 ***/
  long A1[15][15];
  transpose(A1);

  /*** 3.66 ***/
  long l3 = 3, A2[3*l3][4*l3 + 1];
  sum_col(l3, A2, l3*2);

  /*** 3.71 ***/
  //good_echo();

  /*** 3.73-74 ***/
  for (unsigned int ii = 0; ii < UINT_MAX; ii++) {
    float_int_t value = { .u = ii };
    range_t range_1 = find_range_1(value.f);
    range_t range_2 = find_range_2(value.f);
    switch(fpclassify(value.f)) {
      case FP_NAN:
        assert(range_1 == OTHER);
        assert(range_2 == OTHER);
        break;
      case FP_ZERO:
        assert(range_1 == ZERO);
        assert(range_2 == ZERO);
        break;
      default:
        assert((value.f < 0.0f && range_1 == NEG) ||
            (value.f > 0.0f && range_1 == POS));
        assert((value.f < 0.0f && range_2 == NEG) ||
            (value.f > 0.0f && range_2 == POS));
        break;
    }
  }

  return 0;
}
