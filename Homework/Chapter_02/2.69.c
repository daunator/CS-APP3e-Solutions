unsigned rotate_left(unsigned x, int n)
{
  unsigned ls_bits_num = (sizeof(int) << 3) - n;
  /* shift to right and clear sign bit => new least significant part*/
  unsigned new_ls = (x >> ls_bits_num) & ~(~0 << n);
  /* shift to left => new most significant part*/
  unsigned new_ms = x << n;
  return new_ms | new_ls;
}
