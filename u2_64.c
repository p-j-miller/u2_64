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
#include <stdio.h>
#include <stdint.h>
#include <math.h> /* fmal() */

#include "u2_64.h"


/* code below cannot be compiled with -Ofast as this makes the compiler break some C rules that we need, so make sure of this here */
/* we also need -msse2 and -mfpmath=sse to actually use the sse instructions for float and double maths */
/* there seems to be no way to duplicate "-fexcess-precision=standard" using a pragma - so that must be present on the command line [see comments at head of this file that suggest "-fexcess-precision=standard" is not required any more ] */
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) || defined(__clang__)
 #pragma GCC push_options
 #pragma GCC optimize ("-O3") /* cannot use Ofast, normally -O3 is OK. Note macro expansion does not work here ! */
 // based on  https://jdebp.uk/FGA/predefined-macros-processor.html "__i386__" is set by GCC,Clang,Intel which is good enough as the outer #if limits us to gcc and clang
 #ifdef __i386__
   #pragma GCC target("sse2,fpmath=sse") /* -msse2 and -mfpmath=sse */
 #endif 
#endif

// udiv_u2_64 is realy too complex to inline, so its left as a function.
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

// functions that work with doubles/LD/f128's  are also left here as we want to turn off -Ofast just in case if does something unexpected ! (and its not clear if this would work correctly if functions were inlined in a header).
u2_64 ld_to_u2_64(long double f)
{// f80 long double has __LDBL_MANT_DIG__ 64 so  64 bits in mantissa (there is no hidden bit)
 uint64_t c63=((uint64_t)1) << 63; // biggest shift possible with u64
 long double c64=c63,a;
 c64*=2; // 1<<64 - should be exact 
 a=f/c64;
 u2_64 result;
 result.hi=a; // upper 64 bits 
 result.lo=fmal(-c64,(long double)(result.hi),f); // fmal(a,b,c)=a*b+c
 return result;
}

long double u2_64_to_ld(u2_64 x)
{// f80 long double has __LDBL_MANT_DIG__ 64 so  64 bits in mantissa (there is no hidden bit)
 // Note that accurately converting a u2_64 to a double-double long double is quite complex - see fast_strtold() in atof.c for the code required.
 uint64_t c63=((uint64_t)1) << 63; // biggest shift possible with u64
 long double c64=c63,r;
 c64*=2; // 1<<64 - should be exact 
 r=fmal((long double)(x.hi),c64,(long double)(x.lo)); // fmal(a,b,c)=a*b+c
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
 result.lo=fma(-c64,(double)(result.hi),f); // fma(a,b,c)=a*b+c
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