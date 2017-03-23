int fits_bits(int x, int n)
{
  int is_positive = !(x >> ((sizeof(x) << 3) - 1));
  return (is_positive && !(x >> (n - 1))) || 
         (!is_positive && !(~x >> (n - 1))); /* ~x = -x - 1 */
}
