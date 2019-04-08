#include "tommath_private.h"
#ifdef BN_MP_MUL_C
/* LibTomMath, multiple-precision integer library -- Tom St Denis */
/* SPDX-License-Identifier: Unlicense */

/* high level multiplication (handles sign) */
int mp_mul(const mp_int *a, const mp_int *b, mp_int *c)
{
   int res, neg, min_len, digs;
   min_len = MIN(a->used, b->used);
   digs = a->used + b->used + 1;
   neg = (a->sign == b->sign) ? MP_ZPOS : MP_NEG;

   if (0) {
   }

#ifdef BN_MP_BALANCE_MUL_C
   else if ((a->used != b->used) &&

            /* Check sizes. The smaller one needs to be larger than the Karatsuba cut-off.
             * The bigger one needs to be at least about one KARATSUBA_MUL_CUTOFF bigger
             * to make some sense, but it depends on architecture, OS, position of the
             * stars... so YMMV.
             * Using it to cut the input into slices small enough for fast_s_mp_mul_digs
             * was actually slower on the author's machine, but YMMV.
             */
            (min_len >= KARATSUBA_MUL_CUTOFF) &&
            (MAX(a->used, b->used) / 2 >= KARATSUBA_MUL_CUTOFF) &&

            /* Not much effect was observed below a ratio of 1:2, but again: YMMV. */
            (MAX(a->used, b->used) >= (2 * min_len))) {

      res = mp_balance_mul(a,b,c);
   }
#endif

#ifdef BN_MP_TOOM_MUL_C
   else if (min_len >= TOOM_MUL_CUTOFF) {
      res = mp_toom_mul(a, b, c);
   }
#endif

#ifdef BN_MP_KARATSUBA_MUL_C
   else if (min_len >= KARATSUBA_MUL_CUTOFF) {
      res = mp_karatsuba_mul(a, b, c);
   }
#endif

#ifdef BN_FAST_S_MP_MUL_DIGS_C
   /* can we use the fast multiplier?
    *
    * The fast multiplier can be used if the output will
    * have less than MP_WARRAY digits and the number of
    * digits won't affect carry propagation
    */
   else if ((digs < (int)MP_WARRAY) &&
            (min_len <=
             (int)(1u << ((CHAR_BIT * sizeof(mp_word)) - (2u * (size_t)DIGIT_BIT))))) {
      res = fast_s_mp_mul_digs(a, b, c, digs);
   }
#endif

   else {
#ifdef BN_S_MP_MUL_DIGS_C
      res = s_mp_mul(a, b, c); /* uses s_mp_mul_digs */
#else
      res = MP_VAL;
#endif
   }

   c->sign = (c->used > 0) ? neg : MP_ZPOS;
   return res;
}
#endif
