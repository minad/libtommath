#include "tommath_private.h"
#ifdef BN_MP_TC_DIV_2D_C
/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * SPDX-License-Identifier: Unlicense
 */

/* two complement right shift */
int mp_tc_div_2d(const mp_int *a, int b, mp_int *c)
{
   int res;
   if (a->sign == MP_ZPOS) {
      return mp_div_2d(a, b, c, NULL);
   }

   res = mp_add_d(a, 1uL, c);
   if (res != MP_OKAY) {
      return res;
   }

   res = mp_div_2d(c, b, c, NULL);
   return (res == MP_OKAY) ? mp_sub_d(c, 1uL, c) : res;
}
#endif

/* ref:         $Format:%D$ */
/* git commit:  $Format:%H$ */
/* commit time: $Format:%ai$ */
