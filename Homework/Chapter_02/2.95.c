#include "float_bits.h"

static void rshift_round(unsigned *u)
{
  unsigned last_two = *u & 3;
  *u >>= 1;
  if (last_two == 3)
    (*u)++;
}

/* Compute 0.5*f. If f is Nan, then return f. */
float_bits float_half(float_bits f)
{
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  if (exp == 0xFF) {
    /* NaN and oo*/
    return f;
  } else if (!exp) {
    /* Denormalized */
      rshift_round(&frac);
  } else {
    /* Normalized */
    exp--;
    if (!exp) {
      frac |= 0x800000;
      rshift_round(&frac);
    }
  }

  /* Reassemble bits */
  return (f & 0x80000000) | exp << 23 | frac;
}
