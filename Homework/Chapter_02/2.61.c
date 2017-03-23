int test_A(int x)
{
  return x && 1; /* alternative: !!x */
}

int test_B(int x)
{
  return ~x && 1; /* alternative: !! ̃x */
}

int test_C(int x)
{
  return (x & 0xFF) && 1; /* alternative: !!(x & 0xFF) */
}

int test_D(int x)
{
  return (~x & (~0u >> 8)) && 1; /* alternative: !!(~x & (~0u >> 8)) */
}

