int odd_ones(unsigned x)
{
   x ^= x >> 16; /* the low 16 bits have the same parity as the original */
   x ^= x >> 8;
   x ^= x >> 4;
   x &= 0xf;
   return (0x6996 >> x) & 1; /* 0x6996 serves as a lookup table */
}

