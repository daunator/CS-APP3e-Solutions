long decode2(long x, long y, long z)
{
  y -= z;
  x *= y;
  return x ^ ((y << 63) >> 63);
}

