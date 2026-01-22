/*  basic unsigned 128 bit functions 
   These do NOT need compiler support for 128 bit ints
   currently supports +,-,*,/,%,<<,>>,&,|,^,~, compare, as well as conversions from uint64_t and to and from float128.
   The are a number of multiply & divide functions as the general purpose one is relatively slow.
   
   Note that double-double.c contains a function to convert a u2_64 to a DDfloat128 (a pair of floats128's used as a "double-double" pair )
   
   With the ya_sprintf test program these functions are faster than using _int128 with msvcrt and a little slower when using the UCRT.
   
   Written by Peter Miller 25-10-2025

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
#include <stdio.h>
#include <stdint.h>
#include <math.h> /* fmal() */

#include "u2_64.h"


/* code below cannot be compiled with -Ofast as this makes the compiler break some C rules that we need, so make sure of this here */
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) || defined(__clang__)
 #pragma GCC push_options
 #pragma GCC optimize ("-O3") /* cannot use Ofast, normally -O3 is OK. Note macro expansion does not work here ! */
 #if defined(_WIN32) && !defined(_WIN64)
  #pragma GCC target("sse2")
 #endif
#endif


inline u2_64 u64_to_u2_64(uint64_t uhi, uint64_t ulo) // returns u2_64 created from two uint64's 
{u2_64 result={uhi,ulo};
 return result;
}

inline u2_64 uadd_u2_64(u2_64 x,  u2_64 y) // returns x+y
{
	uint64_t rlo =  x.lo + y.lo;
	uint64_t rhi =  x.hi + y.hi;
	if(rlo<x.lo) rhi++; // carry - it does not matter if we compare with x.lo or y.lo here 
	u2_64  result = {rhi,rlo};
	return result;
}

inline u2_64 usub_u2_64(u2_64 x,  u2_64 y) // returns x-y
{ 	
	return uadd_u2_64(x,uadd_u2_64(not_u2_64(y),u64_to_u2_64(0,1)));  // -y is 1's complement +1
}


inline int cmp_u2_64(u2_64 x,  u2_64 y) // returns -1 if x < y, 0 if x=y and 1 if x>y. Note if comparing to zero (x.hi|y.hi)==0 is more efficient
{if(x.hi>y.hi) return 1; // x>y
 if(x.hi==y.hi)
 	{if(x.lo>y.lo) return 1; // x>y
 	 if(x.lo==y.lo) return 0; // x==y
	}
 return -1; // x<y
}

inline u2_64 lshift_u2_64(u2_64 x, uint32_t y) // returns x<<y (ie x*2^y), if y>=128 returns 0
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
 
inline u2_64 rshift_u2_64(u2_64 x, uint32_t y) // returns x>>y (ie x/2^y), if y>=128 returns 0
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

u2_64 umul_u2_64(u2_64 x,  u2_64 y) // returns x*y : uses 6 64*64 bit multiplies
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
 
u2_64 umul_u2_64_by_u32(u2_64 x,  uint32_t y) // returns x*y where y is "only" u32 : uses 3 64*64 bit multiplies 
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

u2_64 umul_u2_64_by_ten(u2_64 x) // returns x*10 - uses only shifts and adds
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
 
inline u2_64 udiv_u2_64_by_u32(u2_64 x, uint32_t y) // returns x/y => note y is a uint32_t which is the largest type that allows an efficient division function
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

uint32_t uremainder_u2_64_by_u32(u2_64 x, uint32_t y) // returns x%y => note y is a uint32_t which is the largest type that allows an efficient division function
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

u2_64 udiv_u2_64(u2_64 x, u2_64  y,u2_64 * remainder) // returns x/y => this is normally slower than udiv_u2_62_by_u32(). Remainder can be NULL if its not required
{ 
  if(x.hi==y.hi && x.lo==y.lo) 
  	{ if(remainder) *remainder=u64_to_u2_64(0,0);// z/z=1, remainder 0 [ note this means we return 1 for 0/0 ] 
	  return u64_to_u2_64(0,1); 
	}
 // int cmp_u2_64(u2_64 x,  u2_64 y) // returns -1 if x < y, 0 if x=y and 1 if x>y. Note if comparing to zero (x.hi|y.hi)==0 is more efficient
 if(cmp_u2_64(x,y)<0) 
 	{if(remainder) *remainder=x;// x<y means x/y=0 , remainder x
	 return u64_to_u2_64(0,0);
	}
 if(y.hi==0 && y.lo==0) 
 	{if(remainder) *remainder=u64_to_u2_64(~(uint64_t)0,~(uint64_t)0);// x/0 return "max u2_64" as proxy for infinity for division & remainder
	 return u64_to_u2_64(~(uint64_t)0,~(uint64_t)0);// return "max u2_64" as proxy for infinity
	}
 if(y.hi==0 && (y.lo>>32) ==0) 
 	{if(remainder) *remainder=u64_to_u2_64(0,uremainder_u2_64_by_u32(x,y.lo&0xffffffff));
	 return  udiv_u2_64_by_u32(x,y.lo&0xffffffff); // use fast algorithm if possible (does not make much difference on test program - but see note on "shift" below ).
	}
 // if we get here a division is required, algorithm from Wirth,"Algorithms+Data Structures=Programs", pp 311. with some modifications to avoid overflows etc.
 u2_64 w,r,q;
 int shift=0;// counts number of shifts required to align magnitudes of x & y , so is 0 to 127-32  (=95) as we use udiv_u2_64_by_u32() for small y which is where the runtime here would be the largest (if x was large)
 r=x;
 q=u64_to_u2_64(0,0);
 w=y;
 if((r.hi&((uint64_t)1<<63))==0)
 	{// if msb of x (r) == 0 we don't need to worry about overflows 
  	 while(cmp_u2_64(w,r)<0 ) 
	   	{w=lshift_u2_64(w,1) ; // while(w<r) w=2*w;
	   	 shift++;
	   	}
  	}
 else
 	{//if msb x (r) ==1 we just need to shift w so its msb==1
     while((w.hi&((uint64_t)1<<63)) ==0) 
	 	{w=lshift_u2_64(w,1) ; // if highest bit of r set the loop above could overflow, so do this instead
	 	 shift++;
	 	 //printf(" in while msb w ==0 - w=%zx,%zx\n",w.hi,w.lo);
	 	}
    }
 //printf(" before main divide loop w=%zx,%zx (msb=%d) shift=%d\n",w.hi,w.lo,(int)(w.hi>>63),shift);

 // note loop above to align magnitudes of x & y mean that r>=w will normally happen on the 1st iteration of the for loop and at worse on the 2nd iteration 
#if 1 // on the test program with the author's cpu and gcc 15.2.0 #if 1 is a little faster. Both options pass the test program.
// always do at least 1 iteration, so pull that out of loop and remove q=2*q step as q is 0 initially
 if(cmp_u2_64(r,w)>=0 ) // if(r>=w) - which we expect to be true
 	{r=usub_u2_64(r,w); //r=r-w
 	 q.lo=1; // q=q+1 (q=0 initially)
 	} 
 w=rshift_u2_64(w,1); // w=w/2	
 // now loop for further steps 
 for(int i=0;i<shift;++i)
 	{q=lshift_u2_64(q,1) ; // q=2*q
 	 if(cmp_u2_64(r,w)>=0 ) // if(r>=w)
 	 	{r=usub_u2_64(r,w); //r=r-w
 	 	 q.lo|=1; // q=q+1 (we did q=2*q above so we know lsb=0 before this)
 	 	} 
	 w=rshift_u2_64(w,1); // w=w/2	
 	}
#else 
 for(int i=0;i<=shift;++i)
 	{q=lshift_u2_64(q,1) ; // q=2*q, q is 0 initially so no shift is needed on 1st iteration, as noted above q will probably be non-zero by 2nd iteration => however adding if(i!=0) increases the execution time of the test program
 	 if(cmp_u2_64(r,w)>=0 ) // if(r>=w)
 	 	{r=usub_u2_64(r,w); //r=r-w
 	 	 q.lo|=1; // q=q+1 (we did q=2*q above so we know lsb=0 before this)
 	 	} 
	 w=rshift_u2_64(w,1); // w=w/2	
 	}
#endif 	
 if(remainder) *remainder=r;// r=remainder
 return q; 
}

/* bitwise functions */
u2_64 and_u2_64(u2_64 x,  u2_64 y) // returns bitwise x&y
{u2_64 result;
 result.hi=x.hi & y.hi;
 result.lo=x.lo & y.lo;
 return result;
}

u2_64 or_u2_64(u2_64 x,  u2_64 y) // returns bitwise x|y
{u2_64 result;
 result.hi=x.hi | y.hi;
 result.lo=x.lo | y.lo;
 return result;
}
 
u2_64 xor_u2_64(u2_64 x,  u2_64 y) // returns bitwise x^y
{u2_64 result;
 result.hi=x.hi ^ y.hi;
 result.lo=x.lo ^ y.lo;
 return result;
} 

u2_64 not_u2_64(u2_64 x) // returns bitwise ~x
{u2_64 result;
 result.hi= ~x.hi ;
 result.lo= ~x.lo ;
 return result;
}

u2_64 ld_to_u2_64(long double f)
{// f80 long double has __LDBL_MANT_DIG__ 64 so  64 bits in mantissa (there is no hidden bit)
 // warning: this looses 64 bits of resolution - so you probably need to use this twice to create a double-double long double
 uint64_t c63=((uint64_t)1) << 63; // biggest shift possible with u64
 long double c64=c63,a;
 c64*=2; // 1<<64 - should be exact 
 a=f/c64;
 u2_64 result;
 result.hi=a; // upper 64 bits 
#if 1 
 result.lo=fmal(-c64,(long double)(result.hi),f); // fmal(a,b,c)=a*b+c
#else
 result.lo=f-c64*(long double)(result.hi);
#endif
 return result;
}

long double u2_64_to_ld(u2_64 x)
{// f80 long double has __LDBL_MANT_DIG__ 64 so  64 bits in mantissa (there is no hidden bit)
 // Note that accurately converting a u2_64 to a double-double long double is quite complex - see fast_strtold() in atof.c for the code required.
 uint64_t c63=((uint64_t)1) << 63; // biggest shift possible with u64
 long double c64=c63,r;
 c64*=2; // 1<<64 - should be exact 
#if 1
 r=fmal((long double)(x.hi),c64,(long double)(x.lo)); // fmal(a,b,c)=a*b+c
#else
 r=c64*(long double)(x.hi)+(long double)(x.lo);
#endif
 return r;
}

u2_64 d_to_u2_64(double f)
{// double has   53 bits in mantissa but these can be spread over the 128 bits in the u2_64
 uint64_t c63=((uint64_t)1) << 63; // biggest shift possible with u64
 double c64=c63,a;
 c64*=2; // 1<<64 - should be exact 
 a=f/c64;
 u2_64 result;
 result.hi=a; // upper 64 bits 
#if 1 
 result.lo=fma(-c64,(double)(result.hi),f); // fma(a,b,c)=a*b+c
#else
 result.lo=f-c64*(double)(result.hi);
#endif
 return result;
}

#if defined(__SIZEOF_FLOAT128__)   && !defined(__BORLANDC__)      /* Builder C++ Community version 12.1 patch 1 defines __SIZEOF_FLOAT128__ but __float128's cannot be used in sensible programs due to compiler bugs */

u2_64 flt128_to_u2_64(__float128 f) /* convert float128->u2_64 */
{uint64_t c63=((uint64_t)1) << 63; // biggest shift possible with u64
 __float128 c64=c63,a;
 c64*=2; // 1<<64 - should be exact 
 //f+=0.5; // round f
 a=f/c64;
 u2_64 result;
 result.hi=a; // upper 64 bits 
 result.lo=f-c64*result.hi;
 return result;
}

__float128 u2_64_to_flt128(u2_64 u) /* convert u2_64 -> float128 */
{uint64_t c63=((uint64_t)1) << 63; // biggest shift possible with u64
 __float128 c64=c63,a;
 c64*=2; // 1<<64 - should be exact 
 a=u.lo+c64*u.hi;
 return a;
}

#endif

/* now restore gcc options to those set by the user */
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) || defined(__clang__)
#pragma GCC pop_options
#endif