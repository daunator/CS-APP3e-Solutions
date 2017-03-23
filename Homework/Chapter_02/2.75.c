/* dummy code, to allow compilation */
int signed_high_prod(int x, int y){ return 0;}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
  unsigned p = (unsigned) signed_high_prod((int) x, (int) y);

  if ((int) x < 0) /* x_{w-1} = 1 */
    p += y;
  if ((int) y < 0) /* y_{w-1} = 1 */
    p += x;
  return p;
}

