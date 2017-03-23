int divide_power2(int x, int k)
{
  int mask = x >> ((sizeof(x) << 3) - 1);
  int bias = (1 << k) - 1;
  return (x  + (mask & bias)) >> k;
}

