/* 
   Copyright (c) 2012,2013   Axel Kohlmeyer <akohlmey@gmail.com> 
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
   * Neither the name of the <organization> nor the
     names of its contributors may be used to endorse or promote products
     derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* faster versions of 2**x, e**x, and 10**x in single and double precision.
 *
 * Based on the Cephes math library 2.8
 */

#include "fastermath.h"
#include "fm_internal.h"

#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

/*  Seriani: basic Pade` implementation of exp(x).
 */

     static const double pad_exp_p[] __attribute__ ((aligned(_FM_ALIGN))) = {
         5.95238095238095238095e-4,
         1.19047619047619047619e-2,
         1.07142857142857142857e-1,
         5.00000000000000000000e-1,
         1.00000000000000000000e0,
         };
                   
       double pad_exp(double x)
          {
       double  px, qx;

       px =         pad_exp_p[0];
       qx =         pad_exp_p[0];
       px = px*x + pad_exp_p[1];
       qx = -qx*x + pad_exp_p[1];
       px = px*x + pad_exp_p[2];
       qx = -qx*x + pad_exp_p[2];
       px = px*x + pad_exp_p[3];
       qx = -qx*x + pad_exp_p[3];
       px = px*x + pad_exp_p[4];
       qx = -qx*x + pad_exp_p[4];
       x = px/qx;
      return x;
     }

double fast_exp(double x) {
	double a_0 = 2.30933477057345225087e-2;
	double a_1 = 2.02020656693165307700e1;
	double a_2 = 1.51390680115615096133e3;
	double b_1 = 2.33184211722314911771e2;
	double b_2 = 4.36821166879210612817e3;
	
	double y= x* FM_DOUBLE_LOG2OFE;
	
	int int_y = FLOAT_TO_INT(y);
	double float_y = y - int_y;
	
	double fy_exp5 = float_y*float_y*float_y*float_y*float_y;
	double fy_exp4 = float_y*float_y*float_y*float_y;
	double fy_exp3 = float_y*float_y*float_y;
	double fy_exp2 = float_y*float_y;
	
	
	double exptwo_int = pow(2, int_y);
	
	double p_x = a_0 * fy_exp5 + a_1 * fy_exp3 + a_2 * float_y;
	double q_x = fy_exp4 + b_1 * fy_exp2 + b_2;
	double f_x = 1. + 2. * (p_x / (q_x - p_x));

	return exptwo_int * f_x;
}



static const double fm_exp_t[] __attribute__ ((aligned(_FM_ALIGN))) = {
    1.00000000000000000000e0,
    5.00000000000000000000e-1,
    1.66666666666666666666e-1,
    4.16666666666666666666e-2,
    8.33333333333333333333e-3,
    1.38888888888888888888e-3,
    1.98412698412698412698e-4
};
    
 
double t_exp(double x)
{
    double   tx;
           tx =        fm_exp_t[6];
           tx = tx*x + fm_exp_t[5];
           tx = tx*x + fm_exp_t[4];
           tx = tx*x + fm_exp_t[3];
           tx = tx*x + fm_exp_t[2];
           tx = tx*x + fm_exp_t[1];
           tx = tx*x + fm_exp_t[0];
           tx = tx*x + fm_exp_t[0];
 return tx;
 }


/* 
 * Local Variables:
 * mode: c
 * compile-command: "make -C .."
 * c-basic-offset: 4
 * fill-column: 76 
 * indent-tabs-mode: nil 
 * End: 
 */
