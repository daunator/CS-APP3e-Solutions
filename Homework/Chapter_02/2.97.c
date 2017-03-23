#include "float_bits.h"

/* Compute (float) i */
float_bits float_i2f(int x) {
  int temp;
  int pos;
  int msb_pos = 0;
  int correction = 0;

  unsigned frac = 0;
  unsigned exp = 0;
  unsigned sgn = x & 0x80000000;

  /* Special cases: 0 and INT_MIN */
  if (x == 0)
    return 0;
  else if (x == 0x80000000)
    return 0xCF000000;

  /* Negative numbers are handled as positive ones */
  /* and the sign bit is set at the end            */
  if (sgn)
    x = -x;

  temp = x;
  while(temp >>= 1)
    msb_pos++;

  if (msb_pos <= 23) {
    x <<= 23 - msb_pos;
  } else {
    pos = msb_pos - 23;
    
    /* Calculate if correction(rounding) is needed */
    int temp = 1 << (pos - 1);
    if ((x & temp) && (x & (temp << 1) || x & (temp - 1)))
      correction = 1;
    
    x >>= pos;

    /* Handle the case when correction would change the MSB */
    if (x == 0xFFFFFF && correction) {
      x >>= 1;
      exp++;
    }
  }

  frac = (x + correction) & 0x7FFFFF;
  exp += msb_pos + 127;

  /* Reassemble bits */
  return sgn | (exp << 23) | frac;
}

