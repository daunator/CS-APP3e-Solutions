#include "float_bits.h"

/* Compute (int) f
 * If conversion causes overflow or if is NaN, return 0x80000000
 */
int float_f2i(float_bits f)
{
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  unsigned sign = f & 0x80000000;
  int res = 0;
  
  int E = exp - 127;
  if(E < 0) {
    res = 0;
  }
  else if(E < 24) {
    res = (frac | 0x800000) >> (23 - E);
    if (sign)
      res = -res;
  }
  else if(E < 31) {
    res = (frac | 0x800000) << (E - 23);
    if (sign)
      res = -res;
  }
  else {
    res = 0x80000000;
  }
   
  return res;
}

