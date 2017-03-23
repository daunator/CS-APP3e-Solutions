#include <stdlib.h>
#include <string.h>

void *my_calloc(size_t nmemb, size_t size)
{
  void *block = NULL;
  size_t nbytes = nmemb * size;

  /* check that no overflow has occured */
  if (nmemb && size && nbytes / nmemb == size)
  {
    block = malloc(nbytes);
    if (block)
      memset(block, 0, nbytes);
  }

  return block;
}

