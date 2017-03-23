#include "float_bits.h"

/* Compute |f|. If F is Nan then return f. */
float_bits float_absval(float_bits f)
{
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  if (exp == 0xFF && frac)
    return f;
  
  return f & 0x7FFFFFFF;
}
