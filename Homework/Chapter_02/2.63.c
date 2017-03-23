unsigned srl(unsigned x, int k)
{  
  unsigned xsra = (int) x >> k;

  unsigned one = 1 << (8*sizeof(x) - k - 1);
  unsigned mask = (~one) ^ (~one + 1);
  return xsra & mask;
}

int sra(int x, int k)
{  
  int xsrl = (unsigned) x >> k;
  
  unsigned sign = (x & (1 << (8*sizeof(x) - 1))) && 1;
  unsigned one = sign << (8*sizeof(x) - k - 1);
  unsigned mask = ~((~one) ^ (~one + 1));
  return xsrl | mask;
}

