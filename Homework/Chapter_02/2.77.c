int mul_by_17(int x)
{
  return (x << 4) + x;
}

int mul_by_minus7(int x)
{
  return x - (x << 3);
}

int mul_by_60(int x)
{
  return (x << 6) - (x << 2);
}

int mul_by_minus112(int x)
{
  return (x << 4) - (x << 7);
}

