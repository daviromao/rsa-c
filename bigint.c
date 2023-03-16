#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 1000

typedef struct BigInt {
    short digits[MAX_DIGITS];   
    int size;
} BigInt;

typedef struct {
    BigInt quotient;
    BigInt remainder;
} BigIntDivision;

BigInt invert_bigint(BigInt a){
    short temp;
    for(int i = 0; i < a.size/2; i++){
        temp = a.digits[i];
        a.digits[i] = a.digits[a.size-i-1];
        a.digits[a.size-i-1] = temp;
    }

    return a;
}

BigInt multiply_bigint(BigInt a, BigInt b){
    BigInt c;

    c.size = MAX_DIGITS;
    memset(c.digits, 0, sizeof(c.digits));

    for(int i=0; i<a.size; i++){
        for(int j=0; j<b.size; j++){
            c.digits[i+j] += a.digits[a.size-i-1] * b.digits[b.size-j-1];
            c.digits[i+j+1] += c.digits[i+j] / 10;
            c.digits[i+j] %= 10;
        }
    }

    while(c.digits[c.size-1] == 0 && c.size > 1){
        c.size--;
    }

    c = invert_bigint(c);

    return c;
}

BigInt read_bigint(){
    BigInt b;

    char c[MAX_DIGITS];

    fgets(c, MAX_DIGITS, stdin);

    b.size = strlen(c) - 1;
    
    for(int i = 0; i < b.size; i++){
        b.digits[i] = c[i] - '0';
    }

    return b;
}