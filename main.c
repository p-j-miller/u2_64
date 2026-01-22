/* Test program for u2_64.c

 This does need 128 bit integer support from the compiler (as thats used to check the results).
 We do calculations with uint128_t and u2_64 and check results are identical.
 
  Written by Peter Miller 25-10-2025
  
To compile under Windows using winlibs gcc 15.2.0 (the changes for Linux should be obvious):
  C:\winlibs\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r2\mingw64\bin\gcc -Wall -m64 -fexcess-precision=standard -Ofast  -std=c99 -I. main.c u2_64.c  -static -o test.exe
  
 expected output: 
Test 1: checking a relatively small set of arguments - using all available functions except /, %
 a,b,r:80000000000000000000000000000000,d34609964b58eca1c1aee26d48e8c6a5,534609964b58eca1c1aee26d48e8c6a5
 x,y,z:80000000000000000000000000000000,d34609964b58eca1c1aee26d48e8c6a5,534609964b58eca1c1aee26d48e8c6a5
 a1   :80000000000000000000000000000000
 a1_1 :80000000000000000000000000000000

 a10  :004afe56c4cd3021394f829e14000000
 x10  :004afe56c4cd3021394f829e14000000

 r1   :00000000000000000000000000000001

 x equals a
 x10 equals a10
 a1 equals a
 a1 equals a1_1
 y equals b
 z equals r
 r1 equals one

Test 2 (/,%):
 checking division by zero (0/0 and 1/0)
 dividing aadec8c3186345282b4e141f3a1232d5 (aadec8c3186345282b4e141f3a1232d5) by powers of 2
 dividing 556f64618c31a29415a70a0f9d09196a (556f64618c31a29415a70a0f9d09196a) by powers of 2
 dividing 2ab7b230c618d14a0ad38507ce848cb5 (2ab7b230c618d14a0ad38507ce848cb5) by powers of 2
 dividing 155bd918630c68a50569c283e742465a (155bd918630c68a50569c283e742465a) by powers of 2
 dividing 0aadec8c3186345282b4e141f3a1232d (0aadec8c3186345282b4e141f3a1232d) by powers of 2
 dividing 0556f64618c31a29415a70a0f9d09196 (0556f64618c31a29415a70a0f9d09196) by powers of 2
 dividing 02ab7b230c618d14a0ad38507ce848cb (02ab7b230c618d14a0ad38507ce848cb) by powers of 2
 dividing 0155bd918630c68a50569c283e742465 (0155bd918630c68a50569c283e742465) by powers of 2
 dividing 00aadec8c3186345282b4e141f3a1232 (00aadec8c3186345282b4e141f3a1232) by powers of 2
 dividing 00556f64618c31a29415a70a0f9d0919 (00556f64618c31a29415a70a0f9d0919) by powers of 2
 dividing 002ab7b230c618d14a0ad38507ce848c (002ab7b230c618d14a0ad38507ce848c) by powers of 2
 dividing 00155bd918630c68a50569c283e74246 (00155bd918630c68a50569c283e74246) by powers of 2
 dividing 000aadec8c3186345282b4e141f3a123 (000aadec8c3186345282b4e141f3a123) by powers of 2
 dividing 000556f64618c31a29415a70a0f9d091 (000556f64618c31a29415a70a0f9d091) by powers of 2
 dividing 0002ab7b230c618d14a0ad38507ce848 (0002ab7b230c618d14a0ad38507ce848) by powers of 2
 dividing 000155bd918630c68a50569c283e7424 (000155bd918630c68a50569c283e7424) by powers of 2
 dividing 0000aadec8c3186345282b4e141f3a12 (0000aadec8c3186345282b4e141f3a12) by powers of 2
 dividing 0000556f64618c31a29415a70a0f9d09 (0000556f64618c31a29415a70a0f9d09) by powers of 2
 dividing 00002ab7b230c618d14a0ad38507ce84 (00002ab7b230c618d14a0ad38507ce84) by powers of 2
 dividing 0000155bd918630c68a50569c283e742 (0000155bd918630c68a50569c283e742) by powers of 2
 dividing 00000aadec8c3186345282b4e141f3a1 (00000aadec8c3186345282b4e141f3a1) by powers of 2
 dividing 00000556f64618c31a29415a70a0f9d0 (00000556f64618c31a29415a70a0f9d0) by powers of 2
 dividing 000002ab7b230c618d14a0ad38507ce8 (000002ab7b230c618d14a0ad38507ce8) by powers of 2
 dividing 00000155bd918630c68a50569c283e74 (00000155bd918630c68a50569c283e74) by powers of 2
 dividing 000000aadec8c3186345282b4e141f3a (000000aadec8c3186345282b4e141f3a) by powers of 2
 dividing 000000556f64618c31a29415a70a0f9d (000000556f64618c31a29415a70a0f9d) by powers of 2
 dividing 0000002ab7b230c618d14a0ad38507ce (0000002ab7b230c618d14a0ad38507ce) by powers of 2
 dividing 000000155bd918630c68a50569c283e7 (000000155bd918630c68a50569c283e7) by powers of 2
 dividing 0000000aadec8c3186345282b4e141f3 (0000000aadec8c3186345282b4e141f3) by powers of 2
 dividing 0000000556f64618c31a29415a70a0f9 (0000000556f64618c31a29415a70a0f9) by powers of 2
 dividing 00000002ab7b230c618d14a0ad38507c (00000002ab7b230c618d14a0ad38507c) by powers of 2
 dividing 0000000155bd918630c68a50569c283e (0000000155bd918630c68a50569c283e) by powers of 2
 dividing 00000000aadec8c3186345282b4e141f (00000000aadec8c3186345282b4e141f) by powers of 2
 dividing 00000000556f64618c31a29415a70a0f (00000000556f64618c31a29415a70a0f) by powers of 2
 dividing 000000002ab7b230c618d14a0ad38507 (000000002ab7b230c618d14a0ad38507) by powers of 2
 dividing 00000000155bd918630c68a50569c283 (00000000155bd918630c68a50569c283) by powers of 2
 dividing 000000000aadec8c3186345282b4e141 (000000000aadec8c3186345282b4e141) by powers of 2
 dividing 000000000556f64618c31a29415a70a0 (000000000556f64618c31a29415a70a0) by powers of 2
 dividing 0000000002ab7b230c618d14a0ad3850 (0000000002ab7b230c618d14a0ad3850) by powers of 2
 dividing 000000000155bd918630c68a50569c28 (000000000155bd918630c68a50569c28) by powers of 2
 dividing 0000000000aadec8c3186345282b4e14 (0000000000aadec8c3186345282b4e14) by powers of 2
 dividing 0000000000556f64618c31a29415a70a (0000000000556f64618c31a29415a70a) by powers of 2
 dividing 00000000002ab7b230c618d14a0ad385 (00000000002ab7b230c618d14a0ad385) by powers of 2
 dividing 0000000000155bd918630c68a50569c2 (0000000000155bd918630c68a50569c2) by powers of 2
 dividing 00000000000aadec8c3186345282b4e1 (00000000000aadec8c3186345282b4e1) by powers of 2
 dividing 00000000000556f64618c31a29415a70 (00000000000556f64618c31a29415a70) by powers of 2
 dividing 000000000002ab7b230c618d14a0ad38 (000000000002ab7b230c618d14a0ad38) by powers of 2
 dividing 00000000000155bd918630c68a50569c (00000000000155bd918630c68a50569c) by powers of 2
 dividing 000000000000aadec8c3186345282b4e (000000000000aadec8c3186345282b4e) by powers of 2
 dividing 000000000000556f64618c31a29415a7 (000000000000556f64618c31a29415a7) by powers of 2
 dividing 0000000000002ab7b230c618d14a0ad3 (0000000000002ab7b230c618d14a0ad3) by powers of 2
 dividing 000000000000155bd918630c68a50569 (000000000000155bd918630c68a50569) by powers of 2
 dividing 0000000000000aadec8c3186345282b4 (0000000000000aadec8c3186345282b4) by powers of 2
 dividing 0000000000000556f64618c31a29415a (0000000000000556f64618c31a29415a) by powers of 2
 dividing 00000000000002ab7b230c618d14a0ad (00000000000002ab7b230c618d14a0ad) by powers of 2
 dividing 0000000000000155bd918630c68a5056 (0000000000000155bd918630c68a5056) by powers of 2
 dividing 00000000000000aadec8c3186345282b (00000000000000aadec8c3186345282b) by powers of 2
 dividing 00000000000000556f64618c31a29415 (00000000000000556f64618c31a29415) by powers of 2
 dividing 000000000000002ab7b230c618d14a0a (000000000000002ab7b230c618d14a0a) by powers of 2
 dividing 00000000000000155bd918630c68a505 (00000000000000155bd918630c68a505) by powers of 2
 dividing 000000000000000aadec8c3186345282 (000000000000000aadec8c3186345282) by powers of 2
 dividing 000000000000000556f64618c31a2941 (000000000000000556f64618c31a2941) by powers of 2
 dividing 0000000000000002ab7b230c618d14a0 (0000000000000002ab7b230c618d14a0) by powers of 2
 dividing 000000000000000155bd918630c68a50 (000000000000000155bd918630c68a50) by powers of 2
 dividing 0000000000000000aadec8c318634528 (0000000000000000aadec8c318634528) by powers of 2
 dividing 0000000000000000556f64618c31a294 (0000000000000000556f64618c31a294) by powers of 2
 dividing 00000000000000002ab7b230c618d14a (00000000000000002ab7b230c618d14a) by powers of 2
 dividing 0000000000000000155bd918630c68a5 (0000000000000000155bd918630c68a5) by powers of 2
 dividing 00000000000000000aadec8c31863452 (00000000000000000aadec8c31863452) by powers of 2
 dividing 00000000000000000556f64618c31a29 (00000000000000000556f64618c31a29) by powers of 2
 dividing 000000000000000002ab7b230c618d14 (000000000000000002ab7b230c618d14) by powers of 2
 dividing 00000000000000000155bd918630c68a (00000000000000000155bd918630c68a) by powers of 2
 dividing 000000000000000000aadec8c3186345 (000000000000000000aadec8c3186345) by powers of 2
 dividing 000000000000000000556f64618c31a2 (000000000000000000556f64618c31a2) by powers of 2
 dividing 0000000000000000002ab7b230c618d1 (0000000000000000002ab7b230c618d1) by powers of 2
 dividing 000000000000000000155bd918630c68 (000000000000000000155bd918630c68) by powers of 2
 dividing 0000000000000000000aadec8c318634 (0000000000000000000aadec8c318634) by powers of 2
 dividing 0000000000000000000556f64618c31a (0000000000000000000556f64618c31a) by powers of 2
 dividing 00000000000000000002ab7b230c618d (00000000000000000002ab7b230c618d) by powers of 2
 dividing 0000000000000000000155bd918630c6 (0000000000000000000155bd918630c6) by powers of 2
 dividing 00000000000000000000aadec8c31863 (00000000000000000000aadec8c31863) by powers of 2
 dividing 00000000000000000000556f64618c31 (00000000000000000000556f64618c31) by powers of 2
 dividing 000000000000000000002ab7b230c618 (000000000000000000002ab7b230c618) by powers of 2
 dividing 00000000000000000000155bd918630c (00000000000000000000155bd918630c) by powers of 2
 dividing 000000000000000000000aadec8c3186 (000000000000000000000aadec8c3186) by powers of 2
 dividing 000000000000000000000556f64618c3 (000000000000000000000556f64618c3) by powers of 2
 dividing 0000000000000000000002ab7b230c61 (0000000000000000000002ab7b230c61) by powers of 2
 dividing 000000000000000000000155bd918630 (000000000000000000000155bd918630) by powers of 2
 dividing 0000000000000000000000aadec8c318 (0000000000000000000000aadec8c318) by powers of 2
 dividing 0000000000000000000000556f64618c (0000000000000000000000556f64618c) by powers of 2
 dividing 00000000000000000000002ab7b230c6 (00000000000000000000002ab7b230c6) by powers of 2
 dividing 0000000000000000000000155bd91863 (0000000000000000000000155bd91863) by powers of 2
 dividing 00000000000000000000000aadec8c31 (00000000000000000000000aadec8c31) by powers of 2
 dividing 00000000000000000000000556f64618 (00000000000000000000000556f64618) by powers of 2
 dividing 000000000000000000000002ab7b230c (000000000000000000000002ab7b230c) by powers of 2
 dividing 00000000000000000000000155bd9186 (00000000000000000000000155bd9186) by powers of 2
 dividing 000000000000000000000000aadec8c3 (000000000000000000000000aadec8c3) by powers of 2
 dividing 000000000000000000000000556f6461 (000000000000000000000000556f6461) by powers of 2
 dividing 0000000000000000000000002ab7b230 (0000000000000000000000002ab7b230) by powers of 2
 dividing 000000000000000000000000155bd918 (000000000000000000000000155bd918) by powers of 2
 dividing 0000000000000000000000000aadec8c (0000000000000000000000000aadec8c) by powers of 2
 dividing 0000000000000000000000000556f646 (0000000000000000000000000556f646) by powers of 2
 dividing 00000000000000000000000002ab7b23 (00000000000000000000000002ab7b23) by powers of 2
 dividing 0000000000000000000000000155bd91 (0000000000000000000000000155bd91) by powers of 2
 dividing 00000000000000000000000000aadec8 (00000000000000000000000000aadec8) by powers of 2
 dividing 00000000000000000000000000556f64 (00000000000000000000000000556f64) by powers of 2
 dividing 000000000000000000000000002ab7b2 (000000000000000000000000002ab7b2) by powers of 2
 dividing 00000000000000000000000000155bd9 (00000000000000000000000000155bd9) by powers of 2
 dividing 000000000000000000000000000aadec (000000000000000000000000000aadec) by powers of 2
 dividing 000000000000000000000000000556f6 (000000000000000000000000000556f6) by powers of 2
 dividing 0000000000000000000000000002ab7b (0000000000000000000000000002ab7b) by powers of 2
 dividing 000000000000000000000000000155bd (000000000000000000000000000155bd) by powers of 2
 dividing 0000000000000000000000000000aade (0000000000000000000000000000aade) by powers of 2
 dividing 0000000000000000000000000000556f (0000000000000000000000000000556f) by powers of 2
 dividing 00000000000000000000000000002ab7 (00000000000000000000000000002ab7) by powers of 2
 dividing 0000000000000000000000000000155b (0000000000000000000000000000155b) by powers of 2
 dividing 00000000000000000000000000000aad (00000000000000000000000000000aad) by powers of 2
 dividing 00000000000000000000000000000556 (00000000000000000000000000000556) by powers of 2
 dividing 000000000000000000000000000002ab (000000000000000000000000000002ab) by powers of 2
 dividing 00000000000000000000000000000155 (00000000000000000000000000000155) by powers of 2
 dividing 000000000000000000000000000000aa (000000000000000000000000000000aa) by powers of 2
 dividing 00000000000000000000000000000055 (00000000000000000000000000000055) by powers of 2
 dividing 0000000000000000000000000000002a (0000000000000000000000000000002a) by powers of 2
 dividing 00000000000000000000000000000015 (00000000000000000000000000000015) by powers of 2
 dividing 0000000000000000000000000000000a (0000000000000000000000000000000a) by powers of 2
 dividing 00000000000000000000000000000005 (00000000000000000000000000000005) by powers of 2
 dividing 00000000000000000000000000000002 (00000000000000000000000000000002) by powers of 2
 dividing 00000000000000000000000000000001 (00000000000000000000000000000001) by powers of 2
 dividing 80000000000000000000000000000000 (80000000000000000000000000000000) by powers of 2
 dividing 40000000000000000000000000000000 (40000000000000000000000000000000) by powers of 2
 dividing 20000000000000000000000000000000 (20000000000000000000000000000000) by powers of 2
 dividing 10000000000000000000000000000000 (10000000000000000000000000000000) by powers of 2
 dividing 08000000000000000000000000000000 (08000000000000000000000000000000) by powers of 2
 dividing 04000000000000000000000000000000 (04000000000000000000000000000000) by powers of 2
 dividing 02000000000000000000000000000000 (02000000000000000000000000000000) by powers of 2
 dividing 01000000000000000000000000000000 (01000000000000000000000000000000) by powers of 2
 dividing 00800000000000000000000000000000 (00800000000000000000000000000000) by powers of 2
 dividing 00400000000000000000000000000000 (00400000000000000000000000000000) by powers of 2
 dividing 00200000000000000000000000000000 (00200000000000000000000000000000) by powers of 2
 dividing 00100000000000000000000000000000 (00100000000000000000000000000000) by powers of 2
 dividing 00080000000000000000000000000000 (00080000000000000000000000000000) by powers of 2
 dividing 00040000000000000000000000000000 (00040000000000000000000000000000) by powers of 2
 dividing 00020000000000000000000000000000 (00020000000000000000000000000000) by powers of 2
 dividing 00010000000000000000000000000000 (00010000000000000000000000000000) by powers of 2
 dividing 00008000000000000000000000000000 (00008000000000000000000000000000) by powers of 2
 dividing 00004000000000000000000000000000 (00004000000000000000000000000000) by powers of 2
 dividing 00002000000000000000000000000000 (00002000000000000000000000000000) by powers of 2
 dividing 00001000000000000000000000000000 (00001000000000000000000000000000) by powers of 2
 dividing 00000800000000000000000000000000 (00000800000000000000000000000000) by powers of 2
 dividing 00000400000000000000000000000000 (00000400000000000000000000000000) by powers of 2
 dividing 00000200000000000000000000000000 (00000200000000000000000000000000) by powers of 2
 dividing 00000100000000000000000000000000 (00000100000000000000000000000000) by powers of 2
 dividing 00000080000000000000000000000000 (00000080000000000000000000000000) by powers of 2
 dividing 00000040000000000000000000000000 (00000040000000000000000000000000) by powers of 2
 dividing 00000020000000000000000000000000 (00000020000000000000000000000000) by powers of 2
 dividing 00000010000000000000000000000000 (00000010000000000000000000000000) by powers of 2
 dividing 00000008000000000000000000000000 (00000008000000000000000000000000) by powers of 2
 dividing 00000004000000000000000000000000 (00000004000000000000000000000000) by powers of 2
 dividing 00000002000000000000000000000000 (00000002000000000000000000000000) by powers of 2
 dividing 00000001000000000000000000000000 (00000001000000000000000000000000) by powers of 2
 dividing 00000000800000000000000000000000 (00000000800000000000000000000000) by powers of 2
 dividing 00000000400000000000000000000000 (00000000400000000000000000000000) by powers of 2
 dividing 00000000200000000000000000000000 (00000000200000000000000000000000) by powers of 2
 dividing 00000000100000000000000000000000 (00000000100000000000000000000000) by powers of 2
 dividing 00000000080000000000000000000000 (00000000080000000000000000000000) by powers of 2
 dividing 00000000040000000000000000000000 (00000000040000000000000000000000) by powers of 2
 dividing 00000000020000000000000000000000 (00000000020000000000000000000000) by powers of 2
 dividing 00000000010000000000000000000000 (00000000010000000000000000000000) by powers of 2
 dividing 00000000008000000000000000000000 (00000000008000000000000000000000) by powers of 2
 dividing 00000000004000000000000000000000 (00000000004000000000000000000000) by powers of 2
 dividing 00000000002000000000000000000000 (00000000002000000000000000000000) by powers of 2
 dividing 00000000001000000000000000000000 (00000000001000000000000000000000) by powers of 2
 dividing 00000000000800000000000000000000 (00000000000800000000000000000000) by powers of 2
 dividing 00000000000400000000000000000000 (00000000000400000000000000000000) by powers of 2
 dividing 00000000000200000000000000000000 (00000000000200000000000000000000) by powers of 2
 dividing 00000000000100000000000000000000 (00000000000100000000000000000000) by powers of 2
 dividing 00000000000080000000000000000000 (00000000000080000000000000000000) by powers of 2
 dividing 00000000000040000000000000000000 (00000000000040000000000000000000) by powers of 2
 dividing 00000000000020000000000000000000 (00000000000020000000000000000000) by powers of 2
 dividing 00000000000010000000000000000000 (00000000000010000000000000000000) by powers of 2
 dividing 00000000000008000000000000000000 (00000000000008000000000000000000) by powers of 2
 dividing 00000000000004000000000000000000 (00000000000004000000000000000000) by powers of 2
 dividing 00000000000002000000000000000000 (00000000000002000000000000000000) by powers of 2
 dividing 00000000000001000000000000000000 (00000000000001000000000000000000) by powers of 2
 dividing 00000000000000800000000000000000 (00000000000000800000000000000000) by powers of 2
 dividing 00000000000000400000000000000000 (00000000000000400000000000000000) by powers of 2
 dividing 00000000000000200000000000000000 (00000000000000200000000000000000) by powers of 2
 dividing 00000000000000100000000000000000 (00000000000000100000000000000000) by powers of 2
 dividing 00000000000000080000000000000000 (00000000000000080000000000000000) by powers of 2
 dividing 00000000000000040000000000000000 (00000000000000040000000000000000) by powers of 2
 dividing 00000000000000020000000000000000 (00000000000000020000000000000000) by powers of 2
 dividing 00000000000000010000000000000000 (00000000000000010000000000000000) by powers of 2
 dividing 00000000000000008000000000000000 (00000000000000008000000000000000) by powers of 2
 dividing 00000000000000004000000000000000 (00000000000000004000000000000000) by powers of 2
 dividing 00000000000000002000000000000000 (00000000000000002000000000000000) by powers of 2
 dividing 00000000000000001000000000000000 (00000000000000001000000000000000) by powers of 2
 dividing 00000000000000000800000000000000 (00000000000000000800000000000000) by powers of 2
 dividing 00000000000000000400000000000000 (00000000000000000400000000000000) by powers of 2
 dividing 00000000000000000200000000000000 (00000000000000000200000000000000) by powers of 2
 dividing 00000000000000000100000000000000 (00000000000000000100000000000000) by powers of 2
 dividing 00000000000000000080000000000000 (00000000000000000080000000000000) by powers of 2
 dividing 00000000000000000040000000000000 (00000000000000000040000000000000) by powers of 2
 dividing 00000000000000000020000000000000 (00000000000000000020000000000000) by powers of 2
 dividing 00000000000000000010000000000000 (00000000000000000010000000000000) by powers of 2
 dividing 00000000000000000008000000000000 (00000000000000000008000000000000) by powers of 2
 dividing 00000000000000000004000000000000 (00000000000000000004000000000000) by powers of 2
 dividing 00000000000000000002000000000000 (00000000000000000002000000000000) by powers of 2
 dividing 00000000000000000001000000000000 (00000000000000000001000000000000) by powers of 2
 dividing 00000000000000000000800000000000 (00000000000000000000800000000000) by powers of 2
 dividing 00000000000000000000400000000000 (00000000000000000000400000000000) by powers of 2
 dividing 00000000000000000000200000000000 (00000000000000000000200000000000) by powers of 2
 dividing 00000000000000000000100000000000 (00000000000000000000100000000000) by powers of 2
 dividing 00000000000000000000080000000000 (00000000000000000000080000000000) by powers of 2
 dividing 00000000000000000000040000000000 (00000000000000000000040000000000) by powers of 2
 dividing 00000000000000000000020000000000 (00000000000000000000020000000000) by powers of 2
 dividing 00000000000000000000010000000000 (00000000000000000000010000000000) by powers of 2
 dividing 00000000000000000000008000000000 (00000000000000000000008000000000) by powers of 2
 dividing 00000000000000000000004000000000 (00000000000000000000004000000000) by powers of 2
 dividing 00000000000000000000002000000000 (00000000000000000000002000000000) by powers of 2
 dividing 00000000000000000000001000000000 (00000000000000000000001000000000) by powers of 2
 dividing 00000000000000000000000800000000 (00000000000000000000000800000000) by powers of 2
 dividing 00000000000000000000000400000000 (00000000000000000000000400000000) by powers of 2
 dividing 00000000000000000000000200000000 (00000000000000000000000200000000) by powers of 2
 dividing 00000000000000000000000100000000 (00000000000000000000000100000000) by powers of 2
 dividing 00000000000000000000000080000000 (00000000000000000000000080000000) by powers of 2
 dividing 00000000000000000000000040000000 (00000000000000000000000040000000) by powers of 2
 dividing 00000000000000000000000020000000 (00000000000000000000000020000000) by powers of 2
 dividing 00000000000000000000000010000000 (00000000000000000000000010000000) by powers of 2
 dividing 00000000000000000000000008000000 (00000000000000000000000008000000) by powers of 2
 dividing 00000000000000000000000004000000 (00000000000000000000000004000000) by powers of 2
 dividing 00000000000000000000000002000000 (00000000000000000000000002000000) by powers of 2
 dividing 00000000000000000000000001000000 (00000000000000000000000001000000) by powers of 2
 dividing 00000000000000000000000000800000 (00000000000000000000000000800000) by powers of 2
 dividing 00000000000000000000000000400000 (00000000000000000000000000400000) by powers of 2
 dividing 00000000000000000000000000200000 (00000000000000000000000000200000) by powers of 2
 dividing 00000000000000000000000000100000 (00000000000000000000000000100000) by powers of 2
 dividing 00000000000000000000000000080000 (00000000000000000000000000080000) by powers of 2
 dividing 00000000000000000000000000040000 (00000000000000000000000000040000) by powers of 2
 dividing 00000000000000000000000000020000 (00000000000000000000000000020000) by powers of 2
 dividing 00000000000000000000000000010000 (00000000000000000000000000010000) by powers of 2
 dividing 00000000000000000000000000008000 (00000000000000000000000000008000) by powers of 2
 dividing 00000000000000000000000000004000 (00000000000000000000000000004000) by powers of 2
 dividing 00000000000000000000000000002000 (00000000000000000000000000002000) by powers of 2
 dividing 00000000000000000000000000001000 (00000000000000000000000000001000) by powers of 2
 dividing 00000000000000000000000000000800 (00000000000000000000000000000800) by powers of 2
 dividing 00000000000000000000000000000400 (00000000000000000000000000000400) by powers of 2
 dividing 00000000000000000000000000000200 (00000000000000000000000000000200) by powers of 2
 dividing 00000000000000000000000000000100 (00000000000000000000000000000100) by powers of 2
 dividing 00000000000000000000000000000080 (00000000000000000000000000000080) by powers of 2
 dividing 00000000000000000000000000000040 (00000000000000000000000000000040) by powers of 2
 dividing 00000000000000000000000000000020 (00000000000000000000000000000020) by powers of 2
 dividing 00000000000000000000000000000010 (00000000000000000000000000000010) by powers of 2
 dividing 00000000000000000000000000000008 (00000000000000000000000000000008) by powers of 2
 dividing 00000000000000000000000000000004 (00000000000000000000000000000004) by powers of 2
 dividing 00000000000000000000000000000002 (00000000000000000000000000000002) by powers of 2
 dividing 00000000000000000000000000000001 (00000000000000000000000000000001) by powers of 2
 Now checking Max u2_64 (all 1's) divided by 1,3,7,.... 0xffffffff:
  last division was ffffffffffffffffffffffffffffffff / 0xffffffff = 00000001000000010000000100000001 with remainder  0x0
 repeating with udiv_u2_64()
  last division was ffffffffffffffffffffffffffffffff / ffffffffffffffffffffffffffffffff = 00000000000000000000000000000001 with remainder  00000000000000000000000000000000
 Now dividing random number u2_64 by random number u32
  last division was 47a7da05bae4ab327fae137c515d0c01 / 0x8a57dc01 = 000000008498c138291d15d17d71c502 with remainder  0x6ef8eff
 Now repeating with random u2_64 divided by random u2_64:
  last division was 47a7da05bae4ab327fae137c515d0c01 / b91a74147bb29ac76c5661d28a57dc01 = 00000000000000000000000000000000 with remainder 47a7da05bae4ab327fae137c515d0c01
 Test 2 200037029 tests completed - 0 error(s) so far

Test 3 - random number checks for *,+,&,|,^,~ :
 a,b,r:b91a74147bb29ac76c5661d28a57dc01,47a7da05bae4ab327fae137c515d0c01,00c24e1a369745f9ec04754edbb4e802
 x,y,z:b91a74147bb29ac76c5661d28a57dc01,47a7da05bae4ab327fae137c515d0c01,00c24e1a369745f9ec04754edbb4e802
 x equals a
 y equals b
 z equals r

Finished : 0 errors found

 
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
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include "u2_64.h"

#ifdef __SIZEOF_INT128__  /* if 128 bit integers are supported */
typedef __uint128_t uint128_t; // same format as stdint.h
#else
 #error "test program needs __uint128_t"
#endif

/* test program for u2_64 [ 128 bit unsigned] functions */
int print_uint128_hex(uint128_t big) /* unsigned hex print to stdout */
{return     printf("%016"PRIx64"%016"PRIx64,
            (uint64_t)(big>>64),(uint64_t)big);
}

int print_u2_64_hex(u2_64 big) /* unsigned hex print to stdout */
{return     printf("%016"PRIx64"%016"PRIx64,
            big.hi,big.lo);
}

u2_64 uint128_to_u2_64(uint128_t big) /* convert uint128 to u2_64 */
{u2_64 r={(uint64_t)(big>>64),(uint64_t)big};
 return r;
}

uint128_t u2_64_to_uint128(u2_64 big) /* convert u64 to uint128  */
{
 return ( ((uint128_t)(big.hi)) << 64 ) + (uint128_t)(big.lo); 
}

int main(int argc, char *argv[]) 
{unsigned int errs=0;
u2_64 a={0,1},a1,a1_1,a10,b={0,1},r,r1,c1={0,1},t;// a=b=c1=1 a10=a*10
uint128_t x,x10,y,z;// x10=x*10
__float128 f1;
bool cr;
x=1; y=1;
printf("Test 1: checking a relatively small set of arguments - using all available functions except /, %%\n"); 
// test a relatively small set of arguments - using all available functions except /, % 
for(int i=0;i<127;++i)
	{
	 x=x*2;
	 y=y*0xe817fb2d; // 32 bit constant 0xe817fb2d is from https://arxiv.org/pdf/2001.05304 table 7 should give pseudo 64 bit random numbers, here we generate 128 bits so they should be "moderately random" to provide a reasonable check of functions
	 z=x+y;
	 if(i<100) x10=x*10;
	  else if(i==100) x10=0xe817fb2d; // more complex number, swap at 100 so we have tried most single bit positions, without this we end up with x10=0
	  else x10=x10*10;
	 
	 a=umul_u2_64_by_u32(a,2);// a=a*2
	 b=umul_u2_64_by_u32(b,0xe817fb2d);// b=b*0xe817fb2d
	 r=uadd_u2_64(a,b); // r=a+b
	 a1=lshift_u2_64(c1,i+1); // should be the same as a (and x)
	 f1=u2_64_to_flt128(a1);
	 a1_1=flt128_to_u2_64(f1); // a1_1 should be identical to a1 as all powers of 2 should be round loop exact via flt128 [ thats not true in general as a flt128 has less than 128 bits in its mantissa]
	 
	 r1=rshift_u2_64(a1_1,i+1); // should get us back to 1 again
	 
	 if(i<100) a10=umul_u2_64_by_ten(a);
	  else if(i==100) {a10.hi=0; a10.lo=0xe817fb2d;}
	  else a10=umul_u2_64_by_ten(a10);
	 
	 t=uint128_to_u2_64(x); // check results
	 cr=cmp_u2_64(t,a)==0 ; // x & a
	 if(!cr) errs++;
	 t=uint128_to_u2_64(x10); 
	 cr=cmp_u2_64(t,a10)==0 ; // x10 & a10
	 if(!cr) errs++;	 
	 cr=cmp_u2_64(a1,a)==0 ; // a1 & a
	 if(!cr) 
	 	{errs++;	 
	 	 printf("Error a1!=a: a1=");
	 	 print_u2_64_hex(a1);
	 	 printf(" a=");
	 	 print_u2_64_hex(a);
	 	 printf("\n");
	 	}

	 cr=cmp_u2_64(a1,a1_1)==0 ; // a1 & a1_1
	 if(!cr) 
	 	{errs++;	 
	 	 printf("Error a1!=a1_1: a1=");
	 	 print_u2_64_hex(a1);
	 	 printf(" a1_1=");
	 	 print_u2_64_hex(a1_1);
	 	 printf("\n");
	 	}

	 cr=cmp_u2_64(c1,r1)==0 ; // c1 & r1
	 if(!cr) 
	 	{errs++;	 
	 	 printf("Error c1!=r1: x1=");
	 	 print_u2_64_hex(c1);
	 	 printf(" r1=");
	 	 print_u2_64_hex(r1);
	 	 printf("\n");
	 	}
	 
	 t=uint128_to_u2_64(y); 
	 cr=cmp_u2_64(t,b)==0; // y & b
	 if(!cr) errs++;
	 
	 t=uint128_to_u2_64(z);
	 cr=cmp_u2_64(t,r)==0; // z & r
	 if(!cr) errs++;	 
	}
printf(" a,b,r:");
print_u2_64_hex(a);
printf(",");
print_u2_64_hex(b);
printf(",");
print_u2_64_hex(r);
printf("\n");
printf(" x,y,z:");
print_uint128_hex(x);
printf(",");
print_uint128_hex(y);
printf(",");
print_uint128_hex(z);
printf("\n");
printf(" a1   :");
print_u2_64_hex(a1);
printf("\n");
printf(" a1_1 :");
print_u2_64_hex(a1_1);
printf("\n\n");

printf(" a10  :");
print_u2_64_hex(a10);
printf("\n");
printf(" x10  :");
print_uint128_hex(x10);
printf("\n\n");
printf(" r1   :");
print_u2_64_hex(r1);
printf("\n\n");

// now compare final results (again, as already done in loop above)
t=uint128_to_u2_64(x);
cr=cmp_u2_64(t,a)==0 ;
if(!cr) errs++;
printf(" x %s a\n",cr?"equals":"not equals");

t=uint128_to_u2_64(x10);
cr=cmp_u2_64(t,a10)==0 ;
if(!cr) errs++;
printf(" x10 %s a10\n",cr?"equals":"not equals");

cr=cmp_u2_64(a1,a)==0 ;
if(!cr) errs++;
printf(" a1 %s a\n",cr?"equals":"not equals");

cr=cmp_u2_64(a1,a1_1)==0 ;
if(!cr) errs++;
printf(" a1 %s a1_1\n",cr?"equals":"not equals");

t=uint128_to_u2_64(y);
cr=cmp_u2_64(t,b)==0;
if(!cr) errs++;
printf(" y %s b\n",cr?"equals":"not equals");
t=uint128_to_u2_64(z);
cr=cmp_u2_64(t,r)==0;
if(!cr) errs++;
printf(" z %s r\n",cr?"equals":"not equals");

cr=cmp_u2_64(c1,r1)==0;
if(!cr) errs++;
printf(" r1 %s one\n",cr?"equals":"not equals");

printf("\nTest 2 (/,%%):\n");
/* u2_64 a={0,1},a1,a1_1,a10,b={0,1},r,r1,c1={0,1},t;// a=b=c1=1 a10=a*10
uint128_t x,x10,y,z;// x10=x*10
*/
unsigned int nos_tests=0;
uint32_t div,rem;
u2_64 u2_div,u2_rem;
uint128_t m128= ( ((uint128_t)0xaadec8c318634528L) << 64 ) + (uint128_t)0X2b4e141f3a1232d5L; 
// 1st check division by 0 as special case
printf(" checking division by zero (0/0 and 1/0)\n");
// check 0/0 1st which we have defined to be 1 with 0 remainder
nos_tests++;
r=u64_to_u2_64(0,0);
div=0;
u2_div=u64_to_u2_64(0,0);
a=udiv_u2_64_by_u32(r,div);// 0/0
if(cmp_u2_64(u64_to_u2_64(0,1),a)!=0) 
 	{errs++;
 	 printf("  0/0 gave ");
 	 print_u2_64_hex(a);
 	 printf(" - expected 1\n");
 	}
rem=uremainder_u2_64_by_u32(r,div);
if(rem!= 0) 
 	{errs++;
 	 printf("  0/0 gave 0x%x - expected 0\n",rem);
 	}
 	
nos_tests++;
a=udiv_u2_64(r,u2_div,NULL); // 1st do without calculating remainder
if(cmp_u2_64(u64_to_u2_64(0,1),a)!=0) 
 	{errs++;
 	 printf("  0/0 [without calculating remainder] gave ");
 	 print_u2_64_hex(a);
 	 printf(" - expected 1\n");
 	}
a=udiv_u2_64(r,u2_div,&u2_rem); // with remainder
if(cmp_u2_64(u64_to_u2_64(0,1),a)!=0) 
 	{errs++;
 	 printf("  0/0 gave ");
 	 print_u2_64_hex(a);
 	 printf(" - expected 1\n");
 	}
if(cmp_u2_64(u64_to_u2_64(0,0),u2_rem)!=0) 
 	{errs++;
 	 printf("  0/0 gave remainder of ");
 	 print_u2_64_hex(u2_rem);
 	 printf(" - expected 0\n");
 	} 	

// 1/0 :  which we have defined to be "infinity" with remainder "infinity"
nos_tests++;
r=u64_to_u2_64(0,1);
div=0;
u2_div=u64_to_u2_64(0,0);
a=udiv_u2_64_by_u32(r,div);// 0/0
if(cmp_u2_64(u64_to_u2_64(~(uint64_t)0,~(uint64_t)0),a)!=0) 
 	{errs++;
 	 printf("  0/0 gave ");
 	 print_u2_64_hex(a);
 	 printf(" - expected ");
	 print_uint128_hex(~(uint128_t)0);
	 printf("\n");
 	}
rem=uremainder_u2_64_by_u32(r,div);
if(rem!= ~(uint32_t)0) 
 	{errs++;
 	 printf("  0/0 gave 0x%x - expected 0x%x\n",rem,~(uint32_t)0);
 	}
 	
nos_tests++;
a=udiv_u2_64(r,u2_div,NULL); // 1st do without calculating remainder
if(cmp_u2_64(u64_to_u2_64(~(uint64_t)0,~(uint64_t)0),a)!=0) 
 	{errs++;
 	 printf("  0/0 [without calculating remainder] gave ");
 	 print_u2_64_hex(a);
 	 printf(" - expected ");
	 print_uint128_hex(~(uint128_t)0);
	 printf("\n");
 	}
a=udiv_u2_64(r,u2_div,&u2_rem); // with remainder
if(cmp_u2_64(u64_to_u2_64(~(uint64_t)0,~(uint64_t)0),a)!=0) 
 	{errs++;
 	 printf("  0/0 gave ");
 	 print_u2_64_hex(a);
 	 printf(" - expected ");
	 print_uint128_hex(~(uint128_t)0);
	 printf("\n");
 	}
if(cmp_u2_64(u64_to_u2_64(~(uint64_t)0,~(uint64_t)0),u2_rem)!=0) 
 	{errs++;
 	 printf("  0/0 gave remainder of ");
 	 print_u2_64_hex(u2_rem);
 	 printf(" - expected ");
	 print_uint128_hex(~(uint128_t)0);
	 printf("\n");
 	} 	
 	
 	
/* check aadec8c3186345282b4e141f3a1232d5,556f64618c31a29415a70a0f9d09196a,.. -> 05,02,01 divided by 1,2,4,... [ in 2 nested loops] so we check all relative magnitudes and z/z(=1) */
while(m128!=0)
   {
	printf(" dividing ");
	print_uint128_hex(m128);
	printf(" (");
	r=uint128_to_u2_64(m128);
	print_u2_64_hex(r);
	printf(") by powers of 2\n"); 
	// first check division by powers of 2
	for(int i=0;i<32;++i)
		{
		 nos_tests++;
		 div=1<<i; // powers of 2
		 a=udiv_u2_64_by_u32(r,div);
		 x=m128/div;
		 rem=uremainder_u2_64_by_u32(r,div);
		 y=m128%div;
		 
		 t=uint128_to_u2_64(x); // check results - convert int128 to u2_64 and check
		 if(cmp_u2_64(t,a)!=0) 
		 	{errs++;
		 	 printf("   division by 0x%x failed gave ",div);
		 	 print_u2_64_hex(a);
		 	 printf(" - expected ");
			 print_uint128_hex(x);
			 printf("\n");
		 	}
	
		 if(y!=rem) 
		 	{errs++;	 // y & rem
		 	 printf("   remainder after division by 0x%x failed gave 0x%x expected ",div,rem);
			 print_uint128_hex(y);	 
			 printf("\n");		 	
		 	}
		}
		
	// repeat above with udiv_u2_64()
	for(int i=0;i<128;++i)
		{
		 nos_tests++;
		 u2_div=lshift_u2_64(u64_to_u2_64(0,1),i); // u2_div=1<<i
		 a=udiv_u2_64(r,u2_div,NULL); // 1st do without calculating remainder
		 x=m128/u2_64_to_uint128(u2_div);
		 y=m128%u2_64_to_uint128(u2_div);
		 
		 t=uint128_to_u2_64(x); // check results - convert int128 to u2_64 and check
		 if(cmp_u2_64(t,a)!=0) 
		 	{errs++;
		 	 printf("   division by ");
		 	 print_u2_64_hex(u2_div);
			 printf(" [without calculating remainder] failed gave ");
		 	 print_u2_64_hex(a);
		 	 printf(" - expected ");
			 print_uint128_hex(x);
			 printf("\n");
		 	}

		 a=udiv_u2_64(r,u2_div,&u2_rem); // repeat, this time calculating remainder - no need to recalculate x,y,t

		 if(cmp_u2_64(t,a)!=0) 
		 	{errs++;
		 	 printf("   division by ");
		 	 print_u2_64_hex(u2_div);
			 printf(" failed gave ");
		 	 print_u2_64_hex(a);
		 	 printf(" - expected ");
			 print_uint128_hex(x);
			 printf("\n");
		 	}	
		 t=uint128_to_u2_64(y); // check remainder - convert int128 to u2_64 and check
		 if(cmp_u2_64(t,u2_rem)!=0) 
		 	{errs++;
		 	 printf("   division by ");
		 	 print_u2_64_hex(u2_div);
			 printf(" failed gave remainder of ");
		 	 print_u2_64_hex(u2_rem);
		 	 printf(" - expected ");
			 print_uint128_hex(y);
			 printf("\n");
		 	}
		 	
		}
	 m128>>=1; // divide by 2 and repeat
	}
	
// repeat again starting with dividend==8000000000000000 , this has z/z(=1) for each value of dividend
m128=((uint128_t)1)<<127;
while(m128!=0)
   {
	r=uint128_to_u2_64(m128);
	printf(" dividing ");
	print_uint128_hex(m128);
	printf(" (");
	r=uint128_to_u2_64(m128);
	print_u2_64_hex(r);
	printf(") by powers of 2\n"); 
	for(int i=0;i<128;++i)
		{
		 nos_tests++;
		 u2_div=lshift_u2_64(u64_to_u2_64(0,1),i); // u2_div=1<<i
		 a=udiv_u2_64(r,u2_div,NULL);// division, without remainder
		 x=m128/u2_64_to_uint128(u2_div);
		 y=m128%u2_64_to_uint128(u2_div);
		 
		 t=uint128_to_u2_64(x); // check results - convert int128 to u2_64 and check
		 if(cmp_u2_64(t,a)!=0) 
		 	{errs++;
		 	 printf("   division by ");
		 	 print_u2_64_hex(u2_div);
			 printf(" [without calculating remainder] failed gave ");
		 	 print_u2_64_hex(a);
		 	 printf(" - expected ");
			 print_uint128_hex(x);
			 printf("\n");
		 	}

		 a=udiv_u2_64(r,u2_div,&u2_rem);// repeat, this time also calculating remainder - x,y,t unchanged from above
		 if(cmp_u2_64(t,a)!=0) 
		 	{errs++;
		 	 printf("   division by ");
		 	 print_u2_64_hex(u2_div);
			 printf(" failed gave ");
		 	 print_u2_64_hex(a);
		 	 printf(" - expected ");
			 print_uint128_hex(x);
			 printf("\n");
		 	}
		 	
		 t=uint128_to_u2_64(y); // check remainder - convert int128 to u2_64 and check
		 if(cmp_u2_64(t,u2_rem)!=0) 
		 	{errs++;
		 	 printf("   division by ");
		 	 print_u2_64_hex(u2_div);
			 printf(" failed gave remainder of ");
		 	 print_u2_64_hex(u2_rem);
		 	 printf(" - expected ");
			 print_uint128_hex(y);
			 printf("\n");
		 	}	 	 	
		}
	 m128>>=1; // divide by 2 and repeat
	}		

// check all u2_64 1's divided by uint32_t all 1's to make sure this works ok
printf(" Now checking Max u2_64 (all 1's) divided by 1,3,7,.... 0xffffffff:\n");
r=u64_to_u2_64(~0,~0); // all 1's
y=u2_64_to_uint128(r);
div=0;
for(int i=0;i<=32;++i)
	{
	 nos_tests++;
	 div=div*2+1; // 1,3,7,...
	 a=udiv_u2_64_by_u32(r,div);
	 x=y/div;
	 rem=uremainder_u2_64_by_u32(r,div);
	 z=y%div;
	 
	 t=uint128_to_u2_64(x); // check results - convert int128 to u2_64 and check
	 if(cmp_u2_64(t,a)!=0) 
	 	{errs++;
	 	 printf("   division by 0x%x failed gave ",div);
	 	 print_u2_64_hex(a);
	 	 printf(" - expected ");
		 print_uint128_hex(x);
		 printf("\n");
	 	}

	 if(z!=rem) 
	 	{errs++;	 // y & rem
	 	 printf("   remainder after division by 0x%x failed gave 0x%x expected ",div,rem);
		 print_uint128_hex(z);	 
		 printf("\n");		 	
	 	}
	} 
printf("  last division was ");
print_uint128_hex(y);
printf(" / 0x%x = ",div);
print_u2_64_hex(a);
printf(" with remainder  0x%x",rem);
printf("\n");	
 
printf(" repeating with udiv_u2_64()\n");
r=u64_to_u2_64(~0,~0); // all 1's
m128=u2_64_to_uint128(r);
u2_div=u64_to_u2_64(0,0);
for(int i=0;i<128;++i)
	{
	 nos_tests++;
	 u2_div=lshift_u2_64(u2_div,1); // u2_div<<1
	 u2_div.lo|=1; // set lsb so we have u2_div=u2_div<<1+1 i.e. 1,3,7,f,...
	 a=udiv_u2_64(r,u2_div,&u2_rem);
	 x=m128/u2_64_to_uint128(u2_div);
	 y=m128%u2_64_to_uint128(u2_div);
	 
	 t=uint128_to_u2_64(x); // check results - convert int128 to u2_64 and check
	 if(cmp_u2_64(t,a)!=0) 
	 	{errs++;
	 	 printf("   division by ");
	 	 print_u2_64_hex(u2_div);
		 printf(" failed gave ");
	 	 print_u2_64_hex(a);
	 	 printf(" - expected ");
		 print_uint128_hex(x);
		 printf("\n");
	 	}
	 	
	 t=uint128_to_u2_64(y); // check remainder - convert int128 to u2_64 and check
	 if(cmp_u2_64(t,u2_rem)!=0) 
	 	{errs++;
	 	 printf("   division by ");
	 	 print_u2_64_hex(u2_div);
		 printf(" failed gave remainder of ");
	 	 print_u2_64_hex(u2_rem);
	 	 printf(" - expected ");
		 print_uint128_hex(y);
		 printf("\n");
	 	}
		 
	// now repeat division without calculating remainder to check that works
	 a=udiv_u2_64(r,u2_div,NULL);	 	
	 t=uint128_to_u2_64(x); // check results - convert int128 to u2_64 and check
	 if(cmp_u2_64(t,a)!=0) 
	 	{errs++;
	 	 printf("   division by ");
	 	 print_u2_64_hex(u2_div);
		 printf(" [without calculating remainder] failed gave ");
	 	 print_u2_64_hex(a);
	 	 printf(" - expected ");
		 print_uint128_hex(x);
		 printf("\n");
	 	} 	
	} 
printf("  last division was ");
print_uint128_hex(m128);
printf(" / ");
print_u2_64_hex(u2_div);
printf(" = ");
print_u2_64_hex(a);
#if 1
printf(" with remainder  ");
print_uint128_hex(y);
#endif
printf("\n") ; 	

// Use two MCG (Multiplicative Congruential Generator) pseudo random number generators for 2^128 from table 9 of https://arxiv.org/pdf/2001.05304
// 64 bit :  0x7e91d554f7f50a65
// 128 bit : 0xaadec8c318634528 2b4e141f3a1232d5
// we don't really care that we are generating pseudo random numbers, we just want a reasonable set of test patterns for the routines.
const uint64_t m64=0x7e91d554f7f50a65L;
m128= ( ((uint128_t)0xaadec8c318634528L) << 64 ) + (uint128_t)0X2b4e141f3a1232d5L; 
x=1;y=1;
printf(" Now dividing random number u2_64 by random number u32\n");
for(int i=0;i<100000000;++i) /* 100,000,000 iterations takes ~ 7 secs */
	{nos_tests++;
	 x=m64*x; // generate 2 random numbers in x,y
	 y=m128*y;
	 r=uint128_to_u2_64(y);
	 div=x&0xffffffff; // 32 bits
	 a=udiv_u2_64_by_u32(r,div);
	 z=y/div;
	 
	 t=uint128_to_u2_64(z); // check results - convert int128 to u2_64 and check
	 if(cmp_u2_64(t,a)!=0) 
	 	{errs++;
	 	 printf("   division of ");
	 	 print_u2_64_hex(r);
	 	 printf(" by 0x%x failed gave ",div);
	 	 print_u2_64_hex(a);	 	 
	 	 printf(" - expected ");
		 print_uint128_hex(z);
		 printf("\n");
	 	}
	 rem=uremainder_u2_64_by_u32(r,div);
	 z=y%div;
	 if(z!=rem) 
	 	{errs++;	 // z & rem
	 	 printf("   remainder after division of ");
	 	 print_u2_64_hex(r);
	 	 printf(" by 0x%x failed gave 0x%x expected ",div,rem);
		 print_uint128_hex(z);
		 printf("\n");	 			 	
	 	}
	}
printf("  last division was ");
print_uint128_hex(y);
printf(" / 0x%x = ",div);
print_u2_64_hex(a);
printf(" with remainder  0x%x",rem);
printf("\n");
printf(" Now repeating with random u2_64 divided by random u2_64:\n");	
x=1;y=1;// reset random numbers
for(int i=0;i<100000000;++i) /* 100,000,000 iterations takes ~ 7 secs */
	{nos_tests++;
	 x=m64*x; // generate 2 random numbers in x,y
	 y=m128*y;
	 r=uint128_to_u2_64(y);
	 u2_div=uint128_to_u2_64(x);
	 a=udiv_u2_64(r,u2_div,NULL); // 1st do without calculating remainder
	 z=y/x;
	 t=uint128_to_u2_64(z); // check results - convert int128 to u2_64 and check
	 if(cmp_u2_64(t,a)!=0) 
	 	{errs++;
	 	 printf("   division of ");
	 	 print_u2_64_hex(r);
	 	 printf(" by ");
	 	 print_u2_64_hex(u2_div);		  
		 printf(" [without calculating remainder] failed gave ");
	 	 print_u2_64_hex(a);	 	 
	 	 printf(" - expected ");
		 print_uint128_hex(z);
		 printf("\n");
	 	}
	 	
	 a=udiv_u2_64(r,u2_div,&u2_rem);// repeat, this time with remainder - z,t unchanged from above
	 if(cmp_u2_64(t,a)!=0) 
	 	{errs++;
	 	 printf("   division of ");
	 	 print_u2_64_hex(r);
	 	 printf(" by ");
	 	 print_u2_64_hex(u2_div);		  
		 printf(" failed gave ");
	 	 print_u2_64_hex(a);	 	 
	 	 printf(" - expected ");
		 print_uint128_hex(z);
		 printf("\n");
	 	}
		 	 	
	 z=y%x;	
	 t=uint128_to_u2_64(z); // check remainder - convert int128 to u2_64 and check
	 if(cmp_u2_64(t,u2_rem)!=0) 
	 	{errs++;
	 	 printf("   division of ");
	 	 print_u2_64_hex(r);
	 	 printf(" by ");
	 	 print_u2_64_hex(u2_div);
		 printf(" failed gave remainder of ");
	 	 print_u2_64_hex(u2_rem);
	 	 printf(" - expected ");
		 print_uint128_hex(z);
		 printf("\n");
	 	}	 
 	
	}

printf("  last division was ");
print_uint128_hex(y);
printf(" / ");
print_uint128_hex(x);
printf(" = ");
print_u2_64_hex(a);
printf(" with remainder ");
print_uint128_hex(z);
printf("\n");
printf(" Test 2 %u tests completed - %u error(s) so far\n",nos_tests,errs);

printf("\nTest 3 - random number checks for *,+,&,|,^,~ :\n");
// Use the same two MCG (Multiplicative Congruential Generator) pseudo random number generators as we used above
// we don't really care that we are generating pseudo random numbers, we just want a reasonable set of test patterns for the routines.
// we only test a subset of the functions here (the 3 that take 2 u2_64 arguments) and test them over a very wide range of arguments.
x=1; y=1;
a.hi=0;a.lo=1; b.hi=0;b.lo=1;
//uint64_t m64=0x7e91d554f7f50a65L; already set above
// m128= ( ((uint128_t)0xaadec8c318634528L) << 64 ) + (uint128_t)0X2b4e141f3a1232d5L; 
// check u64_to_u2_64() 
r=u64_to_u2_64(0xaadec8c318634528L,0X2b4e141f3a1232d5L);
r1=uint128_to_u2_64(m128);
cr=cmp_u2_64(r,r1)==0 ; // r & r1 
if(!cr) errs++;

for(int i=0;i<100000000;++i) /* 100,000,000 iterations takes ~ 3.5 secs */
	{
	 x=m64*x;
	 y=m128*y;
	 z=x+y;

	 a=umul_u2_64(uint128_to_u2_64(m64),a);// a=m64*a
	 b=umul_u2_64(uint128_to_u2_64(m128),b);// b=m128*b
	 r=uadd_u2_64(a,b); // r=a+b
	 
	 t=uint128_to_u2_64(x); // check results
	 cr=cmp_u2_64(t,a)==0 ; // x & a
	 if(!cr) errs++;
	 
	 t=uint128_to_u2_64(y); 
	 cr=cmp_u2_64(t,b)==0; // y & b
	 if(!cr) errs++;
	 
	 t=uint128_to_u2_64(z);
	 cr=cmp_u2_64(t,r)==0; // z & r
	 if(!cr) errs++;
	 
	 // now check bitwise operations
	 x10=x&y;
	 a10=and_u2_64(a,b);
	 t=uint128_to_u2_64(x10);
	 cr=cmp_u2_64(t,a10)==0; // x10 and a10 for "&"
	 if(!cr) errs++;	 

	 x10=x|y;
	 a10=or_u2_64(a,b);
	 t=uint128_to_u2_64(x10);
	 cr=cmp_u2_64(t,a10)==0; // x10 and a10 for "|"
	 if(!cr) errs++;	 
	 	 
	 x10=x^y;
	 a10=xor_u2_64(a,b);
	 t=uint128_to_u2_64(x10);
	 cr=cmp_u2_64(t,a10)==0; // x10 and a10 for "^"
	 if(!cr) errs++;	 

	 x10=~x;
	 a10=not_u2_64(a);
	 t=uint128_to_u2_64(x10);
	 cr=cmp_u2_64(t,a10)==0; // x10 and a10 for "~"
	 if(!cr) errs++;	 
	 	 	 	 		  	 	 
	}
printf(" a,b,r:");
print_u2_64_hex(a);
printf(",");
print_u2_64_hex(b);
printf(",");
print_u2_64_hex(r);
printf("\n");
printf(" x,y,z:");
print_uint128_hex(x);
printf(",");
print_uint128_hex(y);
printf(",");
print_uint128_hex(z);
printf("\n");
// now compare final results (again, as already done in loop above)
t=uint128_to_u2_64(x);
cr=cmp_u2_64(t,a)==0 ;
if(!cr) errs++;
printf(" x %s a\n",cr?"equals":"not equals");

t=uint128_to_u2_64(y);
cr=cmp_u2_64(t,b)==0;
if(!cr) errs++;
printf(" y %s b\n",cr?"equals":"not equals");
t=uint128_to_u2_64(z);
cr=cmp_u2_64(t,r)==0;
if(!cr) errs++;
printf(" z %s r\n",cr?"equals":"not equals");


printf("\nFinished : %u errors found\n",errs);
}