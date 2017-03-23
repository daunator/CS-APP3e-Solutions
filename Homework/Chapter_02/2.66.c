int leftmost_one(unsigned x)
{
    /* This technique is called bit smearing */
    /* Smear the bits which is to say take the left most bit and make sure all the bits to its left become ones*/
    /* Example:
       1000 0000 0000 0000 0000 0000 0000 0000 (Initial)
       1000 0000 0000 0000 1000 0000 0000 0000 (x |= x >> 16)
       1000 0000 1000 0000 1000 0000 1000 0000 (x |= x >> 8)
       1000 1000 1000 1000 1000 1000 1000 1000 (x |= x >> 4)
       1010 1010 1010 1010 1010 1010 1010 1010 (x |= x >> 2)
       1111 1111 1111 1111 1111 1111 1111 1111 (x |= x >> 2) 
    */

    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return x ^ (x >> 1);
}
