/**
 * @file MandelbrotSetDouble.ino
 * @brief To perform Mandelbrot set calculations using data type double
 * @author armw
 *
 * millis - returns elapsed time, in milliseconds as unsigned long, since the start of the current program
 * Serial - serial communication library
 */

#include <RPC.h>

/**
 * this section runs once at startup
 */
void setup() {                          // basic initialization
  RPC.begin();                          // faster speeds may be supported
}

/**
 * basic calculation of Mandelbrot Set using double precision arithmetic
 * @param n the number of primes to be calculated
 *
 * memset - set memory to specified value
 * sizeof - number of bytes used by the parameter; data type: size_t
 *
 * adapted from published work by Michael Ashley / UNSW / 13-Mar-2003 (he owns the rights)
 *
 * References:
 * https://www.geeksforgeeks.org/c-program-for-sieve-of-eratosthenes/
 * https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/
 * https://newt.phys.unsw.edu.au/~mcba/phys2020/notes/mandelbrot.html
 */

#define UCHAR_MAX 255

const float xCentre = -0.75;
const float yCentre = +0.0;
const int    nx      = 40000;
const int    ny      = 40000;
const float dxy     = 0.005;

/**
 *  estimate a set of points such that z(n+1) = z(n)^2 +c remains bounded
 */
void MandelbrotFloat()
{
  float cx, cy;
  float zx, zy, new_zx;
  unsigned char n;
  int i, j;
  // unsigned long MAX_q = 65536;
  // unsigned long MAX_q = 131072;
  // unsigned long MAX_q = 262144;
  // unsigned long MAX_q = 524288;
  // unsigned long MAX_q = 1048576;
  // unsigned long MAX_q = 2097152;
  // unsigned long MAX_q = 4194304;
  // unsigned long MAX_q = 8388608;
  // unsigned long MAX_q = 16777216;
  // unsigned long MAX_q = 33554432;
  // unsigned long MAX_q = 67108864;
  // unsigned long MAX_q = 134217728;
  // unsigned long MAX_q = 268435456;
  // unsigned long MAX_q = 536870912;
  // unsigned long MAX_q = 1073741824;
   unsigned long MAX_q = 2147483648;
  // unsigned long MAX_q = 4294967295;

  // The Mandelbrot calculation is to iterate the equation
  // z = z*z + c, where z and c are complex numbers, z is initially
  // zero, and c is the coordinate of the point being tested. If
  // the magnitude of z remains less than 2 for ever, then the point
  // c is in the Mandelbrot set. We write out the number of iterations
  // before the magnitude of z exceeds 2, or UCHAR_MAX, whichever is
  // smaller.

  for (unsigned long q = 0; q < MAX_q; q++)
  {
    for (j = 0; j < ny; j++) {
      cy = yCentre + (j - ny/2)*dxy;
      for (i = 0; i < nx; i++) {
        cx = xCentre + (i - nx/2)*dxy;
        zx = 0.0; 
        zy = 0.0; 
        n = 0;
        while ((zx*zx + zy*zy < 4.0) && (n != UCHAR_MAX)) {
          new_zx = zx*zx - zy*zy + cx;
          zy = 2.0*zx*zy + cy;
          zx = new_zx;
          n++;
        }
      }
    }
  }
}

/**
 * this section runs indefinitely
 */
void loop() {                           // repeat the calculations
   int i_max = 2;
  // int i_max = 4;
  // int i_max = 8;
  // int i_max = 16;
  // int i_max = 32;
  // int i_max = 64;
  unsigned long started = millis();

  for (int i = 0; i < i_max; i++)
  {
    MandelbrotFloat();
  }
 
  unsigned long elapsed = millis() - started;
  RPC.print("Elapsed time = ");
  RPC.println(elapsed);
}
