int mul3div4(int x)
{
  int xmul3 = (x << 2) - x;
  int mask = xmul3 >> ((sizeof(x) << 3) - 1);
  return (xmul3 + (mask & 3)) >> 2;
}
