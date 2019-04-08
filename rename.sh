#!/bin/bash
function rename {
  old_file=$1
  new_file=$2
  old_name=$3
  new_name=$4
  git mv $old_file.c $new_file.c
  git ls-files | grep -v rename.sh | grep -v .git | xargs sed -E -i "s/$old_name([^\.])/$new_name\1/g"
  git ls-files | grep -v rename.sh | grep -v .git | xargs sed -E -i "s/$old_file\./$new_file./g"
  git ls-files | grep -v rename.sh | grep -v .git | xargs sed -E -i "s/${old_file^^}/${new_file^^}/g"
}

rename bn_mp_balance_mul              bn_s_mp_balance_mul            mp_balance_mul              s_mp_balance_mul
rename bn_reverse                     bn_s_mp_reverse                bn_reverse                  s_mp_reverse
rename bn_mp_exptmod_fast             bn_s_mp_exptmod_fast           mp_exptmod_fast             s_mp_exptmod_fast
rename bn_mp_invmod_slow              bn_s_mp_invmod_slow            mp_invmod_slow              s_mp_invmod_slow
rename bn_fast_mp_invmod              bn_s_mp_invmod_fast            fast_mp_invmod              s_mp_invmod_fast
rename bn_mp_toom_sqr                 bn_s_mp_toom_sqr               mp_toom_sqr                 s_mp_toom_sqr
rename bn_mp_karatsuba_sqr            bn_s_mp_karatsuba_sqr          mp_karatsuba_sqr            s_mp_karatsuba_sqr
rename bn_mp_toom_mul                 bn_s_mp_toom_mul               mp_toom_mul                 s_mp_toom_mul
rename bn_mp_karatsuba_mul            bn_s_mp_karatsuba_mul          mp_karatsuba_mul            s_mp_karatsuba_mul
rename bn_fast_s_mp_mul_digs          bn_s_mp_mul_digs_fast          fast_s_mp_mul_digs          s_mp_mul_digs_fast
rename bn_fast_s_mp_mul_high_digs     bn_s_mp_mul_high_digs_fast     fast_s_mp_mul_high_digs     s_mp_mul_high_digs_fast
rename bn_fast_s_mp_sqr               bn_s_mp_sqr_fast               fast_s_mp_sqr               s_mp_sqr_fast
rename bn_fast_mp_montgomery_reduce   bn_mp_montgomery_reduce_fast   fast_mp_montgomery_reduce   s_mp_montgomery_reduce_fast
