int tsub_ok(int x, int y)
{
  unsigned sign_mask = ~(~0u >> 1);
  int subt = (unsigned)x - (unsigned)y; /* signed int addition overflow causes undefined behavior */
  int pos_overflow = (~x & y & subt) & sign_mask;
  int neg_overflow = (x & ~y & ~subt) & sign_mask;
  
  return !(pos_overflow || neg_overflow);
}

