/*  header for basic unsigned 128 bit functions 
   These do NOT need compiler support for 128 bit ints, as they use a pair of uint64_t variables.
   
   Note multiple and divide functions provide multiple options, with the most restrictive being the fastest (so umul_u2_64_by_ten() is faster than umul_u2_64_by_u32() which is faster than umul_u2_64() )
   These have a similar execution speed to using __int128's so in most cases its not worth creating (e.g. via #ifdef's) specific options to use __int128 if it exists.
   
   Written by Peter Miller 25-10-2025
   This version 5/3/2026 
	- most functions moved to (this) header so they can be inlined.
	- added u2_64 u2_64_mult_u64_u64(uint64_t x, uint64_t y) - 64*64bits=>u2_64 (128 bits)


The following functions are provided:
	u2_64 u64_to_u2_64(uint64_t uhi, uint64_t ulo); // returns u2_64 created from two uint64's 
	u2_64 uadd_u2_64(u2_64 x,  u2_64 y); // returns x+y
	u2_64 usub_u2_64(u2_64 x,u2_64 y); // returns x-y  

	int cmp_u2_64(u2_64 x,  u2_64 y); // returns -1 if x < y, 0 if x=y and 1 if x>y

	u2_64 lshift_u2_64(u2_64 x, uint32_t y); // returns x<<y (ie x*2^y), if y>=128 returns 0
	u2_64 rshift_u2_64(u2_64 x, uint32_t y); // returns x>>y (ie x/2^y), if y>=128 returns 0

	u2_64 umul_u2_64(u2_64 x,  u2_64 y); // returns x*y
	u2_64 umul_u2_64_by_u32(u2_64 x,  uint32_t y); // returns x*y where y is "only" u32
	u2_64 umul_u2_64_by_ten(u2_64 x); // returns x*10 - uses only shifts and adds
	u2_64 u2_64_mult_u64_u64(uint64_t x, uint64_t y)  // 64*64bits=>u2_64 (128 bits)

	u2_64 udiv_u2_64(u2_64 x, u2_64 y, u2_64 *remainder); // returns x/y => this is normally slower than udiv_u2_62_by_u32(). Remainder can be NULL if its not required
	u2_64 udiv_u2_64_by_u32(u2_64 x, uint32_t y); // returns x/y => note y is a uint32_t which is the largest type that allows an efficient division function
	uint32_t uremainder_u2_64_by_u32(u2_64 x, uint32_t y); // returns x%y => note y is a uint32_t which sets the type of the return value

	 // bitwise functions 
	u2_64 and_u2_64(u2_64 x,  u2_64 y); // returns bitwise x&y
	u2_64 or_u2_64(u2_64 x,  u2_64 y); // returns bitwise x|y
	u2_64 xor_u2_64(u2_64 x,  u2_64 y); // returns bitwise x^y
	u2_64 not_u2_64(u2_64 x); // returns bitwise ~x

	u2_64 ld_to_u2_64(long double f); // convert long double to u2_64 - assumes f will not cause an overflow as a u2_64 
	long double u2_64_to_ld(u2_64 x); // convert u2_64 to long double 
	u2_64 d_to_u2_64(double f); // convert double to u2_64 - assumes f will not cause an overflow as a u2_64 

	u2_64 flt128_to_u2_64(__float128 f); // convert float128->u2_64 - assumes f will not cause an overflow as a u2_64 
	__float128 u2_64_to_flt128(u2_64 u); // convert u2_64 -> float128 

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
#if (defined(_M_AMD64) || defined(_M_IX86)) && !defined(__BORLANDC__)  // "Intel" 32 or 64 bits - note "64" or "128" functions need a 64 bit processor
 #include <intrin.h>  // __lzcnt64/_umul128/__umulh
#endif
 #ifdef __cplusplus
 extern "C" {
 #endif 
	struct _u2_64
	{/* by putting hi first we can initialise is u2_64 r={hi,lo}, e.g. to initialise to 0xaadec8c318634528 2b4e141f3a1232d5 it would be {0xaadec8c318634528L,0x2b4e141f3a1232d5L} */
		uint64_t hi;  
		uint64_t lo;
	};
	typedef struct _u2_64 u2_64;

	u2_64 udiv_u2_64(u2_64 x, u2_64 y, u2_64 *remainder); // returns x/y => this is normally slower than udiv_u2_62_by_u32(). Remainder can be NULL if its not required

	u2_64 ld_to_u2_64(long double f); /* convert long double to u2_64 - assumes f will not cause an overflow as a u2_64 */
	long double u2_64_to_ld(u2_64 x); /* convert u2_64 to long double */
	u2_64 d_to_u2_64(double f); /* convert double to u2_64 - assumes f will not cause an overflow as a u2_64 */

	#ifdef __SIZEOF_FLOAT128__ /* i.e. of we have __float128 */

	u2_64 flt128_to_u2_64(__float128 f); /* convert float128->u2_64 - assumes f will not cause an overflow as a u2_64 */
	__float128 u2_64_to_flt128(u2_64 u); /* convert u2_64 -> float128 */
	#endif

	// following functions are in this header so they can be inlined for speed
	
	static inline u2_64 u64_to_u2_64(uint64_t uhi, uint64_t ulo) // returns u2_64 created from two uint64's 
	{u2_64 result={uhi,ulo};
	 return result;
	}

	/* bitwise functions */
	static inline u2_64 and_u2_64(u2_64 x,  u2_64 y) // returns bitwise x&y
	{u2_64 result;
	 result.hi=x.hi & y.hi;
	 result.lo=x.lo & y.lo;
	 return result;
	}

	static inline u2_64 or_u2_64(u2_64 x,  u2_64 y) // returns bitwise x|y
	{u2_64 result;
	 result.hi=x.hi | y.hi;
	 result.lo=x.lo | y.lo;
	 return result;
	}
	 
	static inline u2_64 xor_u2_64(u2_64 x,  u2_64 y) // returns bitwise x^y
	{u2_64 result;
	 result.hi=x.hi ^ y.hi;
	 result.lo=x.lo ^ y.lo;
	 return result;
	} 

	static inline u2_64 not_u2_64(u2_64 x) // returns bitwise ~x
	{u2_64 result;
	 result.hi= ~x.hi ;
	 result.lo= ~x.lo ;
	 return result;
	}
	
	// maths functions
	static inline u2_64 uadd_u2_64(u2_64 x,  u2_64 y) // returns x+y
	{
	 uint64_t rlo =  x.lo + y.lo;
#if 1
	 uint64_t rhi =  x.hi + y.hi + (rlo<x.lo); // (rlo<x.lo) is carry - it does not matter if we compare with x.lo or y.lo here  
#else	 
	 uint64_t rhi =  x.hi + y.hi;
	 if(rlo<x.lo) rhi++; // carry - it does not matter if we compare with x.lo or y.lo here 
#endif	 
	 u2_64  result = {rhi,rlo};
	 return result;
	}

	static inline u2_64 usub_u2_64(u2_64 x,  u2_64 y) // returns x-y
	{ 	
	 return uadd_u2_64(x,uadd_u2_64(not_u2_64(y),u64_to_u2_64(0,1)));  // -y is 1's complement +1
	}

	static inline int cmp_u2_64(u2_64 x,  u2_64 y) // returns -1 if x < y, 0 if x=y and 1 if x>y. Note if comparing to zero (x.hi|y.hi)==0 is more efficient
	{if(x.hi>y.hi) return 1; // x>y
	 if(x.hi==y.hi)
		{if(x.lo>y.lo) return 1; // x>y
		 if(x.lo==y.lo) return 0; // x==y
		}
	 return -1; // x<y
	}
	
	static inline u2_64 lshift_u2_64(u2_64 x, uint32_t y) // returns x<<y (ie x*2^y), if y>=128 returns 0
	{u2_64 result ={0,0};
	 if(y==0) return x;
	 if(y>=128) return result; // 0  
	 if(y<64)
		{
		 result.lo=x.lo<<y;
		 result.hi=x.hi<<y;
		 result.hi |=x.lo>>(64-y); // top bits of lo move into lower bits of hi
		}
	 else
		result.hi=x.lo<<(y-64); // all bits of lo move into hi (lo will be 0)
	 return result; 
	}
	 
	static inline u2_64 rshift_u2_64(u2_64 x, uint32_t y) // returns x>>y (ie x/2^y), if y>=128 returns 0
	{u2_64 result ={0,0};
	 if(y==0) return x;
	 if(y>=128) return result; // 0  
	 if(y<64)
		{
		 result.lo=x.lo>>y;
		 result.hi=x.hi>>y;
		 result.lo |=x.hi<<(64-y); // low bits of hi move into top bits of lo
		}
	 else
		result.lo=x.hi>>(y-64); // all bits of lo move into hi (lo will be 0)
	 return result; 
	} 

	static inline u2_64 umul_u2_64(u2_64 x,  u2_64 y) // returns x*y : uses 6 64*64 bit multiplies
	{ /* need to split lo into two 32 bit "chunks" so intermediate results fit into a u64 */
	  uint64_t a32 = x.lo >> 32;
	  uint64_t a00 = x.lo  & 0xffffffff;
	  uint64_t b32 = y.lo >> 32;
	  uint64_t b00 = y.lo & 0xffffffff;
	  u2_64 result = { x.hi * y.lo + x.lo * y.hi  + a32 * b32, a00 * b00 };// can add several values to "hi" part as we don't need to worry about carries
	  uint64_t t1=a32*b00;
	  u2_64 t2={t1 >> 32,t1<<32};
	  result=uadd_u2_64(result,t2);
	  t1=a00 * b32;
	  u2_64 t3={t1 >> 32,t1<<32};
	  result=uadd_u2_64(result,t3);  
	  return result;
	}
	 
	static inline u2_64 umul_u2_64_by_u32(u2_64 x,  uint32_t y) // returns x*y where y is "only" u32 : uses 3 64*64 bit multiplies 
	{ /* need to split x.lo into two 32 bit "chunks" so intermediate results fit into a u64 */
	  uint64_t a32 = x.lo >> 32;
	  uint64_t a00 = x.lo  & 0xffffffff;
	  uint64_t b00 = y;
	  u2_64 result = { x.hi * b00, a00 * b00 };
	  uint64_t t1=a32*b00;
	  u2_64 t2={t1 >> 32 , t1<<32};
	  result=uadd_u2_64(result,t2); 
	  return result;
	}

	static inline u2_64 umul_u2_64_by_ten(u2_64 x) // returns x*10 - uses only shifts and adds
	{// x*10 = x*8+x*2 = x<<3 + x<<1
	 u2_64 x8,x2;
	 x8.lo=x.lo<<3;
	 x8.hi=x.hi<<3;
	 x8.hi |=x.lo>>(64-3); // top bits of lo move into lower bits of hi
	 x2.lo=x.lo<<1;
	 x2.hi=x.hi<<1;
	 x2.hi |=x.lo>>(64-1); // top bit of lo move into lower bit of hi
	 return uadd_u2_64(x8,x2);
	}
	 
	
	// Computes 128-bit result of multiplication of two 64-bit unsigned integers. Its here so it can be inlined
	static inline u2_64 u2_64_mult_u64_u64(uint64_t x, uint64_t y) 
	{
	#if defined(_M_AMD64) && !defined(__BORLANDC__)
	 uint64_t hi = 0;
	 uint64_t lo = _umul128(x, y, &hi);
	 u2_64 result = {hi, lo};
	 return result;
	#elif defined(_M_ARM64)
	 u2_64 result = {__umulh(x, y), x * y};
	 return result;
	#else
	 // following code is used on 32 bit (or less) processors where 128 bit ints or specific builtin's don't exist 
	 uint64_t a = x >> 32;
	 uint64_t b = (uint32_t)(x);
	 uint64_t c = y >> 32;
	 uint64_t d = (uint32_t)(y);

	 uint64_t ac = a * c;
	 uint64_t bc = b * c;
	 uint64_t ad = a * d;
	 uint64_t bd = b * d;

	 uint64_t cs = (bd >> 32) + ad + (uint32_t)(bc);  // "middle" bits of result - see https://stackoverflow.com/questions/28868367/getting-the-high-part-of-64-bit-integer-multiplication/51587262#51587262 for proof this cannot overflow
	 u2_64 result = {ac + (bc >> 32) + (cs >> 32),
						(cs << 32) | (uint32_t)(bd)};	// | is all that's needed for lower 64 bits (+ would also work but is not required)                   
	 return result;
    #endif	 
	}	
	
	static inline u2_64 udiv_u2_64_by_u32(u2_64 x, uint32_t y) // returns x/y => note y is a uint32_t which is the largest type that allows an efficient division function
	{ // as with multiply we need to split x into 32 bit chunks so we can work with at most 64/32 divisions 
	 if(x.hi==0 && x.lo==y) return u64_to_u2_64(0,1); // z/z=1 [ note this means we return 1 for 0/0 ]
	 if(y==0) return u64_to_u2_64(~(uint64_t)0,~(uint64_t)0);// return "max u2_64" as proxy for infinity
	 if(x.hi==0)
		{if(x.lo<y) return u64_to_u2_64(0,0);// x<y means x/y=0
		 return u64_to_u2_64(0,x.lo/y);// only 1 division needed for this case
		}
	 uint64_t a32 = x.lo >> 32;
	 uint64_t a00 = x.lo  & 0xffffffff;
	 uint64_t d1=x.hi/y; // upper 64 bits of result is simple
	 uint64_t r1=(x.hi%y)<<32; // remainder must be <y so remainder must fit into 32 bits, <<32 gets ready for next step
	 uint64_t d2=(r1+a32)/y;// r1+a32 could be 64 bits so this is again 64 bit maths
	 uint64_t r2=((r1+a32)%y)<<32; // again remainder must fit into 32 bits, <<32 gets ready for next step
	 uint64_t d3=(r2+a00)/y;
	 return  u64_to_u2_64(d1,(d2<<32)+d3);
	}

	static inline uint32_t uremainder_u2_64_by_u32(u2_64 x, uint32_t y) // returns x%y => note y is a uint32_t which is the largest type that allows an efficient division function
	{ //basically the same as udiv, but we return the remainder which is a uint32_t as that's the type of y
	 if(x.hi==0 && x.lo==y) return 0; // z/z=1 so there is no remainder
	 if(y==0) return ~(uint32_t)0;// /0, return "max uint32_t" as proxy for infinity
	 if(x.hi==0)
		{if(x.lo<y) return x.lo;// x<y means x/y=0, so remainder=x
		 else return x.lo%y;// can directly calculate result
		}
	 uint64_t a32 = x.lo >> 32;
	 uint64_t a00 = x.lo  & 0xffffffff;
	 uint64_t r1=x.hi%y; // remainder must be <y so must fit into 32 bits
	 uint64_t r2=((r1<<32)+a32)%y; // again remainder must fit into 32 bits
	 return  ((r2<<32)+a00)%y;
	}

	
 #ifdef __cplusplus
    }
 #endif
	
#endif /* _u2_64_h */