#ifndef BIGINT_H
#define BIGINT_H

#define MAX_DIGITS 1000

typedef struct BigInt {
    short digits[MAX_DIGITS];   
    int size;
} BigInt;

typedef struct BigIntDivision {
    BigInt quotient;
    BigInt remainder;
} BigIntDivision;

int compare_bigint(BigInt a, BigInt b);
BigInt read_bigint();
BigInt invert_bigint(BigInt a);
BigInt multiply_bigint(BigInt a, BigInt b);
BigInt subtract_bigint(BigInt a, BigInt b);
void append_bigint(BigInt *a, short digit);
BigIntDivision divide_bigint(BigInt a, BigInt b);
BigInt exp_mod_bigint(BigInt a, BigInt e, BigInt m);


#endif