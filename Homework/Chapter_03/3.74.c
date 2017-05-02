typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range_2(float x)
{
  int result;

  asm("mov $2,%[r]         # Put POS in result\n\t"
      "xor %%esi,%%esi     # Put NEG in esi\n\t"
      "mov $1,%%edx        # Put ZERO in edx\n\t"
      "mov $3,%%ecx        # Put OTHER in ecx\n\t"
      "vxorps %%xmm1,%%xmm1,%%xmm1  # Put zero in xmm1\n\t"
      "vucomiss %%xmm1,%[x]         # Compare to 0\n\t"
      "cmovc %%esi,%[r]             # Negative\n\t"
      "cmovz %%edx,%[r]             # Zero\n\t"
      "cmovp %%ecx,%[r]             # NaN"
      : [r] "=r" (result)             /* Output */
      : [x] "x" (x)                   /* Input */
      : "%xmm1","%esi","%edx","%ecx"  /* Overwrites */
     );

  return (range_t)result;
}

