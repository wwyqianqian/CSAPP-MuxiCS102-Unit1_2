/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 * @wwyqianqian
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x) | (~y));
}
/*
 * getByte - Extract byte n from word x
 从数x中提取从右数的第n个字节 (0 <= n <= 3)
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  n = n << 3;//n = n * 8;变成位
  x = x >> n;//x右移8n位

  return 0xff & x;

}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
  //拓展：unsigned int a, b, mask = 0x0000ff00;
  //a = 0x12345678;
  //b = (a & mask) >> 8; /* 0x00000056 */
//即 b = (a >> 8) & ~(~0 << 8);

  //拓展完毕。本题：
  //0x8765432 & ~(10000000000000000000000000000000) >> n << 1
  //0x8765432 & ~(11111000000000000000000000000000) << 1    注意：右移，负数在前面填1
  //0x8765432 & ~(1111000000000000000000000000000)
  //0x8765432 & ~(0000111111111111111111111111111)
                //   0   8   7   6   5   4   3   2
int logicalShift(int x, int n) {
  return (x >> n) & (~((1<<31) >> n << 1));
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) 101= 2, bitCount(7) 111 = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
 //好像不让for···尴尬
 int bitCount(int x) {

   int temp1 ;
   int temp2 ;
   int res ;

   temp1 = 0x01|(0x01<<8)|(0x01<<16)|(0x01<<24) ;
   temp2 = x&temp1 ;
   temp2 += temp1&(x>>1) ;
   temp2 += temp1&(x>>2) ;
   temp2 += temp1&(x>>3) ;
   temp2 += temp1&(x>>4) ;
   temp2 += temp1&(x>>5) ;
   temp2 += temp1&(x>>6) ;
   temp2 += temp1&(x>>7) ;

   temp2 = temp2 + (temp2>>16) ;
   temp2 = temp2 + (temp2>>8)  ;
   res = 0xff&temp2 ;
   return res ;
 }
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */

 //-x  就是  ~x + 1 ，"补码 == 反码 + 1";
int bang(int x) {
  return ((x >> 31) | ((~x + 1) >> 31)) + 1;

}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */


int tmin(void) {
  return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 如果x可以表示为n位二进制补码形式,则返回1，否则返回0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
 int fitsBits(int x, int n) {
   int c = ~n + 33;
   int changedX = x << c;
   int changedY = changedX>> c;

   return !(changedY ^ x);
 }
/*
 * divpwr2 - Compute 算 x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int mask = (1 << n) + ~0;// Use & operator on mask and sign bit of x
  int equalizer = (x >> 31) & mask;// Adds 1 if x was originally negative
                                  // Adds 0 if x was originally positive
  return (x + equalizer) >> n;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 x>0返回1,x<=0返回0
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int m = x >> 31;//0,1;
  return !m & (!!x);//(!!x)判断x是否不为零
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 x<=y返回1否则返回0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int m = (~x + 1) + y;
  int p = !!(x>>31);
  int q = !!(y>>31);

  return (!(m>>31)&(!(p^q))) | (p&!q);

}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
 int ilog2(int x) {
   int bitsNumber = 0;
   bitsNumber = (!!(x >> 16)) << 4;
   bitsNumber = bitsNumber + (!!(x >> (bitsNumber + 8)) << 3);
   bitsNumber = bitsNumber + (!!(x >> (bitsNumber + 4)) << 2);
   bitsNumber = bitsNumber + (!!(x >> (bitsNumber + 2)) << 1);
   bitsNumber = bitsNumber + (!!(x >> (bitsNumber + 1)));

   return bitsNumber;
 }
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 返回和浮点数参数-f相等的二进制数，返回参数本身是NaN
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  unsigned temp;

   temp = uf ^ 0x80000000;

   int t = uf & 0x7fffffff;
   if(t > 0x7f800000)
     return uf;
   return temp;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
 unsigned float_i2f(int x) {
   unsigned s = 0, exp = 31, frac = 0, d = 0;
   if (x == 0x00000000u) return 0x00000000u;
   if (x & 0x80000000u) { s = 0x80000000u; x = -x; }
   while (1) {
     if (x & 0x80000000u) break;
     //exp记录最高位的位置
     exp -= 1;
     x <<= 1;
   }
   //最后舍掉的8位若最高位为1且低七位仍有数，要进位
   if ((x & 0x000001ff) == 0x180) d = 1;
   else if ((x & 0xff) > 0x80) d = 1;
   //franc记录尾数
   frac = ((x & 0x7fffffffu) >> 8) + d;

   return s + ((exp + 127) << 23) + frac;
 }
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  if((uf & 0x7F800000) == 0)
    return (uf << 1) | (0x80000000 & uf);

  else if((uf & 0x7fffffff) >= 0x7f800000)
    return uf;
  return uf + 0x00800000;

}
