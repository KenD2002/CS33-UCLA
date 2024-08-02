/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Our checker requires that you do NOT define a variable after 
     a statement that does not define a variable.

     For example, this is NOT allowed:

     int illegal_function_for_this_lab(int x, int y) {
      // this statement doesn't define a variable
      x = x + y + 1;
      
      // The checker for this lab does NOT allow the following statement,
      // because this variable definition comes after a statement 
      // that doesn't define a variable
      int z;

      return 0;
     }
     
  2. VERY IMPORTANT: Use the dlc (data lab checker) compiler (described in the handout)
     to check the legality of your solutions.
  3. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  4. Use the btest to check your functions for correctness.
  5. The maximum number of ops for each function is given in the
     header comment for each function. 

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest to verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//1
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* Only Tmax and -1 would flip all the bits while add 1, so use ^ to 
  check if its one of them. Then use a mask to exclude -1. */
  int result = !(~(x ^ (x + 1)));
  int maskNegOne = !!(x + 1);
  return result & maskNegOne;
}
//2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  /* evenBits should return 0b0101...0101, which is 0x55555555. */
  int firstByte = 0x55 << 24;
  int secondByte = 0x55 << 16;
  int thirdByte = 0x55 << 8;
  int fourthByte = 0x55;
  return firstByte + secondByte + thirdByte + fourthByte;
}
//3
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  /* if x == y, then x ^ ~y should be -1. Then add 1 to it should 
  give 0. And then use ! to get 1. */
  return !((x ^ (~y)) + 1);
}
//4
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* since - is not allowed, define -1 first. Then perform a right 
  shift of n-1 bits on x. If x can be expressed with n bits, the 
  result should 0x00000000 or 0x11111111, which is 0 or -1. Then 
  test if the result is either of them. */
  int negOne = ~0;
  int result = x >> (n + negOne);
  return (!result) + (!(result + 1));
}
//5
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* since - is not allowed, define -1 first. Then we want the result
  be y if x = 0, and be z if x != 0. Thus, !!x and !x would give 0 or 1
  depend on whether x is zero or not. Then use ~ to get 0b111...11 if 0
  and get 0b000...0 if -1. Then use & to exclude either y or z. */
  int negOne = ~0;
  int resulty = (~((!!x) + negOne)) & y;
  int resultz = (~((!x) + negOne)) & z;
  int result = resulty + resultz;
  return result;
}
//6
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /* 2 conditions: x,y not same sign; x,y same sign. 
  If not same sign, return 1 if x >= 0, y < 0; else return 0; and does
  not consider the same sign situation.
  If same sign, return 1 if x - y - 1 >= 0, wich is x + (~ y) and return 1 elsewise.
  Since overflow occurs only when same sign, and x, ~y have different sign, this is valid.
  Then return the sum of these two conditions. */
  int signx = !(x >> 31); // 1 if x >= 0, 0 if x < 0
  int signy = !(y >> 31); // 1 if y >= 0, 0 if y < 0
  int signxeqy = !((signx ^ (~signy)) + 1); // 1 if signx = signy, 0 if signx != signy
  int resultNeqSign = (!signxeqy) & (!(signx + (~signy))); // 1 if x >= 0 and y < 0. else 0
  int resultEqSign = (signxeqy) & (!((x + (~y)) >> 31)); // 1 if x > y. else 0
  int result = resultNeqSign + resultEqSign;
  return result;
}
//7
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  /* calculate x * 5 and perform a bias to make it round towards zero. */
  int fivex = (x << 2) + x;
  int sign = (fivex >> 31); // 0b11..1 if 5*x < 0, 0b00..0 if 5*x >= 0;
  int result = (fivex + (sign & 7)) >> 3;
  return result;
}
//8
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /* 0 is the only number that will both have 0 in the most significant bit
  for itself and its opposite number. */
  int result = (((x | (~x + 1)) >> 31) & 1) ^ 1;
  return result;
}
//9
/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
  /* use a mask to see if x is negative. If x is non-negative, return x itself.
  if x is negative, take -x, which is ~x + 1, and add a 1 at the MSB. */
  int mask = x >> 31; // 0b11..1 if x <= 0, 0b00..0 if x > 0
  int resultNonNeg = (~mask) & x;
  int resultNeg = mask & ((~x + 1) + (1 << 31));
  int result = resultNonNeg + resultNeg;
  return result;
}
//10
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  /* check if x is positive, and check if x&(x-1)=0. */
  int mask1 = !(x >> 31) & (!!x); // 1 if x>=0 and x!=0
  int mask2 = !(x & (x + (~0))); // 1 if x&(x-1)=0
  int result = mask1 & mask2;
  return result;
}
