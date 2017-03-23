#include <limits.h>

int saturating_add(int x, int y)
{
  unsigned sign_shift = (sizeof(int) << 3) - 1;
  int sum = (unsigned)x + (unsigned)y; /* signed int overflow causes undefined behavior */
  int pos_overflow = (~x & ~y & sum) >> sign_shift;
  int neg_overflow = (x & y & ~sum) >> sign_shift;
  
  return (pos_overflow & INT_MAX) | (neg_overflow & INT_MIN) | ((x + y) & ~pos_overflow & ~neg_overflow);
}

