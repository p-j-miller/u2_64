/*  header for basic unsigned 128 bit functions 
   These do NOT need compiler support for 128 bit ints, as they use a pair of uint64_t variables.
   
   Note multiple and divide functions provide multiple options, with the most restrictive being the fastest (so umul_u2_64_by_ten() is faster than umul_u2_64_by_u32() which is faster than umul_u2_64() )
   These have a similar execution speed to using __int128's so in most cases its not worth creating (e.g. via #ifdef's) specific options to use __int128 if it exists.
   
   Written by Peter Miller 25-10-2025

*/
/*----------------------------------------------------------------------------
 * MIT License:
 *
 * Copyright (c) 2025,2026 Peter Miller
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT HOLDER BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *--------------------------------------------------------------------------*/
 
#ifndef _u2_64_h
#define _u2_64_h
#include <stdint.h>  /* for int64_t etc */
 #ifdef __cplusplus
 extern "C" {
 #endif 
	struct _u2_64
	{/* by putting hi first we can initialise is u2_64 r={hi,lo}, e.g. to initialise to 0xaadec8c318634528 2b4e141f3a1232d5 it would be {0xaadec8c318634528L,0x2b4e141f3a1232d5L} */
		uint64_t hi;  
		uint64_t lo;
	};
	typedef struct _u2_64 u2_64;

	u2_64 u64_to_u2_64(uint64_t uhi, uint64_t ulo); // returns u2_64 created from two uint64's 
	u2_64 uadd_u2_64(u2_64 x,  u2_64 y); // returns x+y
	u2_64 usub_u2_64(u2_64 x,u2_64 y); // returns x-y  

	int cmp_u2_64(u2_64 x,  u2_64 y); // returns -1 if x < y, 0 if x=y and 1 if x>y

	u2_64 lshift_u2_64(u2_64 x, uint32_t y); // returns x<<y (ie x*2^y), if y>=128 returns 0
	u2_64 rshift_u2_64(u2_64 x, uint32_t y); // returns x>>y (ie x/2^y), if y>=128 returns 0

	u2_64 umul_u2_64(u2_64 x,  u2_64 y); // returns x*y
	u2_64 umul_u2_64_by_u32(u2_64 x,  uint32_t y); // returns x*y where y is "only" u32
	u2_64 umul_u2_64_by_ten(u2_64 x); // returns x*10 - uses only shifts and adds

	u2_64 udiv_u2_64(u2_64 x, u2_64 y, u2_64 *remainder); // returns x/y => this is normally slower than udiv_u2_62_by_u32(). Remainder can be NULL if its not required
	u2_64 udiv_u2_64_by_u32(u2_64 x, uint32_t y); // returns x/y => note y is a uint32_t which is the largest type that allows an efficient division function
	uint32_t uremainder_u2_64_by_u32(u2_64 x, uint32_t y); // returns x%y => note y is a uint32_t which sets the type of the return value

	 /* bitwise functions */
	u2_64 and_u2_64(u2_64 x,  u2_64 y); // returns bitwise x&y
	u2_64 or_u2_64(u2_64 x,  u2_64 y); // returns bitwise x|y
	u2_64 xor_u2_64(u2_64 x,  u2_64 y); // returns bitwise x^y
	u2_64 not_u2_64(u2_64 x); // returns bitwise ~x

	u2_64 ld_to_u2_64(long double f); /* convert long double to u2_64 - assumes f will not cause an overflow as a u2_64 */
	long double u2_64_to_ld(u2_64 x); /* convert u2_64 to long double */
	u2_64 d_to_u2_64(double f); /* convert double to u2_64 - assumes f will not cause an overflow as a u2_64 */

	#ifdef __SIZEOF_FLOAT128__ /* i.e. of we have __float128 */

	u2_64 flt128_to_u2_64(__float128 f); /* convert float128->u2_64 - assumes f will not cause an overflow as a u2_64 */
	__float128 u2_64_to_flt128(u2_64 u); /* convert u2_64 -> float128 */
	#endif

 #ifdef __cplusplus
    }
 #endif
	
#endif /* _u2_64_h */