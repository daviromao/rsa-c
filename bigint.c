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