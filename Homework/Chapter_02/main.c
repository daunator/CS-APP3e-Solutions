#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#include "float_bits.h"

/* function prototypes */
int is_little_endian(void);
unsigned replace_byte(unsigned x, int i, unsigned char b);
int int_shifts_are_arithmetic(void);
unsigned srl(unsigned x, int k);
int sra(int x, int k);
int any_odd_one(unsigned x);
int odd_ones(unsigned x);
int leftmost_one(unsigned x);
int int_size_is_32_safe32(void);
int int_size_is_32_safe16(void);
int lower_one_mask(int n);
unsigned rotate_left(unsigned x, int n);
int fits_bits(int x, int n);
int xbyte(unsigned word, int bytenum);
int saturating_add(int x, int y);
int tsub_ok(int x, int y);
void *my_calloc(size_t nmemb, size_t size);
int mul_by_17(int x);
int mul_by_minus7(int x);
int mul_by_60(int x);
int mul_by_minus112(int x);
int divide_power2(int x, int k);
int mul3div4(int x);
int threefourths(int x);
int func280_A(int k);
int func280_B(int j, int k);
int float_le(float x, float y);
float fpwr2(int x);
float_bits float_negate(float_bits f);
float_bits float_absval(float_bits f);
float_bits float_twice(float_bits f);
float_bits float_half(float_bits f);
int float_f2i(float_bits f);
float_bits float_i2f(int i);

/* Helper functions */
float u2f(unsigned u);
unsigned f2u(float f);

int main()
{ 
  const unsigned uval = 0x12345678;

  printf("\n *** 2.58 ***\n");
  printf("is little endian: %d\n", is_little_endian());

  printf("\n *** 2.60 ***\n");
  const unsigned v1 = replace_byte(uval, 2, 0xAB); 
  const unsigned v2 = replace_byte(uval, 0, 0xAB);
  printf("%x -> %x \n%x -> %x\n", uval, v1, uval, v2);

  printf("\n *** 2.62 ***\n");
  printf("int shifts are arithmetic: %d\n", is_little_endian());

  /*** 2. 63 ***/
  int x = -123;
  unsigned y = ~0u - 1;
  assert(x >> 2 == sra(x, 2) && y >> 3 == srl(y, 3));

  /*** 2.64 ***/
  assert(!any_odd_one(5) && any_odd_one(6));

  /*** 2.65 ***/
  assert(odd_ones(11) && odd_ones(7) && !odd_ones(3) && !odd_ones(9));

  /*** 2.66 ***/
  assert(leftmost_one(0xFF00) == 0x8000 && leftmost_one(0x6600) == 0x4000);

  printf("\n *** 2.67 ***\n");
  printf("int size is 32(32 bit int machine): %d\n"
         "int size is 32(16 bit int machine): %d\n", 
          int_size_is_32_safe32(), int_size_is_32_safe16());

  /*** 2.68 ***/
  assert(lower_one_mask(6) == 0x3F && lower_one_mask(17) == 0x1FFFF &&
         lower_one_mask(sizeof(int) * 8) == ~0);

  /*** 2.69 ***/
  assert(rotate_left(uval, 4)  == 0x23456781 && 
         rotate_left(uval, 20) == 0x67812345 &&
         rotate_left(uval, 0)  == uval);

  /*** 2.70 ***/
  assert(fits_bits(0, 1) && fits_bits(-1, 1) && !fits_bits(1, 1) &&
         fits_bits(127, 8) && fits_bits(-128, 8) && !fits_bits(128, 8));

  /*** 2.71 ***/
  const unsigned xbytetest = 0xC9EDFF0D;
  assert(xbyte(xbytetest, 0) ==  13 && xbyte(xbytetest, 1) == -1 &&
         xbyte(xbytetest, 2) == -19 && xbyte(xbytetest, 3) == -55);

  /*** 2.73 ***/
  assert(saturating_add(INT_MAX, INT_MAX) == INT_MAX &&
         saturating_add(INT_MIN, INT_MIN) == INT_MIN &&
         saturating_add(INT_MAX/2, INT_MAX/2) == INT_MAX-1 &&
         saturating_add(INT_MIN/2, INT_MIN/2+1) == INT_MIN+1);

  /*** 2.74 ***/
  assert(tsub_ok(INT_MAX/2, INT_MAX) == 1 &&
         tsub_ok(0,  INT_MIN) == 0 &&
         tsub_ok(-1, INT_MIN) == 1 &&
         tsub_ok(INT_MAX, -1) == 0);        

  /*** 2.76 ***/
  assert(my_calloc(1, 1) && my_calloc((size_t)-1, (size_t)-1) == NULL);

  /*** 2.77 ***/
  assert(mul_by_17(1) == 17 && mul_by_minus7(1) == -7 && 
         mul_by_60(1) == 60 && mul_by_minus112(1) == -112);

  /*** 2.78 ***/
  assert(divide_power2(19, 3) == 19/8 && divide_power2(-19, 3) == -19/8);
  assert(divide_power2(-1073741827, 2) == -1073741827/4);

  /*** 2.79 ***/
  assert(mul3div4(19) == (19*3)/4 && mul3div4(-19) == (-19*3)/4);
  assert(mul3div4(INT_MAX) == ((INT_MAX) * 3) / 4);

  /*** 2.80 ***/
  assert(threefourths(-5) == -3 && threefourths(-6) == -4 && 
         threefourths(-7) == -5 && threefourths(11) == 8);

  /*** 2.81 ***/
  assert(func280_A(3) == 0xFFFFFFF8 && func280_B(13, 15) == 0xFFFE000);

  /*** 2.84 ***/
  assert(float_le(3.0f, 4.0f) && float_le(-3.0f, 3.0f) && 
        !float_le(3.0f, -3.0f));

  /*** 2.90 ***/
  for (int ii = -150; ii < 128; ii++)
    assert(fpwr2(ii) == (float)pow(2.0, ii));
  assert(isinf(fpwr2(128)));

  /*** 2.92 - 2.97 ***/
  /* These tests take a few minutes to run, so they are disabled */
#if 0
  for(unsigned ii = 0; ; ii++) {

    float neg_f = u2f(float_negate(ii));
    assert(isnan(neg_f) || neg_f == -u2f(ii));

    float abs_f = u2f(float_absval(ii));
    assert(isnan(abs_f) || abs_f == fabsf(u2f(ii)));

    float twice_f = u2f(float_twice(ii));
    assert(isnan(twice_f) || twice_f == 2.0f*u2f(ii));

    float half_f = u2f(float_half(ii));
    assert(isnan(half_f) || half_f == 0.5f*u2f(ii));

    assert(float_f2i(ii) == (int)u2f(ii));

    assert(u2f(float_i2f((int)ii)) == (float)(int)ii);

    if(ii == ~0u)
      break;
  }
#endif

  return 0;
}
