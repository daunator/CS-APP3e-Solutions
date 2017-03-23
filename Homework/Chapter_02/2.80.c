/*   0x..x11  bias = 1    */
/*   1x..x01  bias = 1    */
/*   1x..x10  bias = 1    */
/*   1x..x11  bias = 2    */
int threefourths(int x)
{
    int sign_mask = ~(~0u >> 1);
    int sign = x & sign_mask;
    int both_1 = x & (x >> 1) & 1;
    int at_least_one_1 = (x | (x >> 1)) & 1;
    int base = (x >> 1) + (x >> 2); 
    int bias = both_1 + (sign && at_least_one_1);

    return base + bias;
}

