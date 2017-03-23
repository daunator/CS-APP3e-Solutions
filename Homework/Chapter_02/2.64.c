int any_odd_one(unsigned x)
{
  return (x & 0xAAAAAAAAu) && 1;
}

