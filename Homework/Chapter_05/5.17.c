#include <stddef.h>

void *basic_memset(void *s, int c, size_t n)
{
  int i;
  size_t cnt = 0;
  size_t limit = n - sizeof(unsigned long) - 1;
  unsigned long pack;
  unsigned long *pul = s;
  unsigned char *puc = (unsigned char *)pul;
  unsigned char uc = (unsigned char) c;

  /* Single step until have memory alignment */
  while ((((size_t) puc) % sizeof(unsigned long)) != 0 && cnt++ < n)
    *puc++ = uc;
  
  if ((int)limit > 0 && cnt < limit) {
    pul = (unsigned long *)puc;

    /* Initialiaze word with char c, k times */
    puc = (unsigned char*)&pack;
    for (i = 0; i < sizeof(unsigned long); i++)
      *puc++ = uc;

    /* Write one word at a time */
    for (; cnt < limit; cnt += sizeof(unsigned long))
      *pul++ = pack;

    puc = (unsigned char *)pul;
  }

  /* Finish off any remaining elements */  
  for (; cnt < n; cnt++) {
    *puc++ = uc;
  }

  return s;
}

