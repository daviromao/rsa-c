#include <stdio.h>
#include "bigint.c"

BigInt modular_inverse(BigInt a, BigInt b){
    BigInt s = {{0}, 1, 1}, old_s = {{1}, 1, 1};
    BigInt t = {{1}, 1, 1}, old_t = {{0}, 1, 1};
    BigInt r = b, old_r = a;
    BigInt q, temp;

    while (r.size > 1 || r.digits[0] != 0){
        q = divide_bigint(old_r, r).quotient;

        temp = r;
        r = subtract_bigint(old_r, multiply_bigint(q, r));
        old_r = temp;

        temp = s;
        s = subtract_bigint(old_s, multiply_bigint(q, s));
        old_s = temp;

        temp = t;
        t = subtract_bigint(old_t, multiply_bigint(q, t));
        old_t = temp;
    }

    if (old_s.sign == -1){
        old_s = sum_bigint(old_s, b);
    }

    return old_s;
}
