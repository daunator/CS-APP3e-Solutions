int lower_one_mask(int n)
{
  return ~(~0 << (n - 1) << 1);
}

