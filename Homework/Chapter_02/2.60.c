unsigned replace_byte(unsigned x, int i, unsigned char b)
{
  unsigned clear_mask = ~(0xFF << (i * 8));
  unsigned new_val = (unsigned)b << (i * 8);
  return (x & clear_mask) | new_val;
}

