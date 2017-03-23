int func280_A(int k)
{
  return ~0 << k;
}

int func280_B(int j, int k)
{
  return (~0 << j) & ~(~0 << (j + k));
}
