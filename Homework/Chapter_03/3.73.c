typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x)
{
  int result;

  asm("vxorps %%xmm1,%%xmm1,%%xmm1  # Put zero in xmm1\n\t"
      "vucomiss %%xmm1,%[x]         # Compare to 0\n\t"
      "jp 0f                        # Check if Nan\n\t"
      "jc 1f                        # Check if negative\n\t"
      "jz 2f                        # Check if zero\n\t"
      "mov $2,%[r]                  # Positive\n\t"
      "jmp 3f                       # Jump to end\n\t"
      "0:                           # Nan\n\t"
      "mov $3,%[r]                  # OTHER\n\t"
      "jmp 3f                       # Jump to end\n\t"
      "1:                           # Negative\n\t"
      "xor %[r],%[r]                # NEG\n\t"
      "jmp 3f                       # Jump to end\n\t"
      "2:                           # Zero\n\t"
      "mov $1,%[r]                  # \n\t"
      "3:                           # End"
      : [r] "=r" (result)       /* Output */
      : [x] "x" (x)             /* Input */
      : "%xmm1"                 /* Overwrites */
     );

  return (range_t)result;
}

