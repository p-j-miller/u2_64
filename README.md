# u2_64
C functions that provide unsigned 128 bit integer functions using a pair of uint64_t's (so do not need compiler support for __int128)

 Currently supports +,-,*,/,%,<<,>>,&,|,^,~, compare, as well as conversions from uint64_t and to and from float128.
 
  The are a number of multiply & divide functions as the general purpose ones are relatively slow.
   
  Note that double-double.c (in the double-double repository) contains a function to convert a u2_64 to a DDfloat128 (a pair of floats128's used as a "double-double" pair )
   
  With the ya_sprintf test program (in the ya-sprintf repository) these functions are faster than using _int128 with msvcrt and a little slower when using the UCRT.

These functions are useful to create portable software as typically 32 bit compilers don't support __int128's, while 64 bit compilers do. For example, "gcc -m64" provides __int128, while "gcc -m32" does not.

The following functions are provided:
~~~
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
~~~
# Instalation
Copy the files to a directory named u2_64-128bits-with-two-u64

main.c is a test program.
To compile the test program under Windows using winlibs gcc 15.2.0 (the changes for Linux should be obvious):
~~~
  C:\winlibs\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r2\mingw64\bin\gcc -Wall -m64 -fexcess-precision=standard -Ofast  -std=c99 -I. main.c u2_64.c  -static -o test.exe
~~~
The expected output from the test program is provided in the comments at the start of main.c , but when run its last line of output should be
~~~
Finished : 0 errors found
~~~
Note the test program does need support for __int128's as these are used as a comparison.
