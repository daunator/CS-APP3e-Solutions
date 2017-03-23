#include "float_bits.h"

/* Compute 2*f. If f is Nan, then return f. */
float_bits float_twice(float_bits f)
{
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  if (exp == 0xFF) {
    /* NaN and oo*/
    return f;
  } else if (!exp) {
    /* Denormalized */
    if (frac & 0x400000) {
      exp = 1;
      frac = (frac << 1) & 0x7FFFFF;
    } else {
      frac <<= 1;
    }
  } else {
    /* Normalized */
    exp++;
    if (exp == 0xFF)
      frac = 0;
  }

  /* Reassemble bits */
  return (f & 0x80000000) | exp << 23 | frac;
}
