int int_size_is_32_safe32()
{
  return !(2 << 31);
}

int int_size_is_32_safe16()
{
  return !(2 << 15 << 15 << 1);
}
