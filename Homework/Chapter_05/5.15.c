#include "combine.h"

void inner42(vec_ptr u, vec_ptr v, data_t *dest)
{
  long i;
  long length = vec_length(u);
  long limit = length - 5;
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(v);
  data_t acc[6] = {(data_t) 0, (data_t) 0, (data_t) 0, (data_t) 0, (data_t) 0, (data_t) 0};
  data_t sum = (data_t) 0;

  /* Do six separate elements at a time */
  for (i = 0; i < limit; i += 6) {
      acc[0] += udata[i] * vdata[i];
      acc[1] += udata[i+1] * vdata[i+1];
      acc[2] += udata[i+2] * vdata[i+2];
      acc[3] += udata[i+3] * vdata[i+3];
      acc[4] += udata[i+4] * vdata[i+4];
      acc[5] += udata[i+5] * vdata[i+5];
  }

  /* Finish off any remaining elements */
  for (; i < length; i++) {
    sum += udata[i] * vdata[i];
  }
  
  /* Add acumulated sums */
  for (i = 0; i < 6; i++) {
    sum += acc[i];
  }
  *dest = sum;
}
