#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 1000

typedef struct BigInt {
    short digits[MAX_DIGITS];   
    int size;
    short sign;
} BigInt;

typedef struct {
    BigInt quotient;
    BigInt remainder;
} BigIntDivision;

BigInt subtract_bigint(BigInt a, BigInt b);

void print_big_int(BigInt a, char *end){
    if(a.sign == -1){
        printf("-");
    }

    for(int i = 0; i < a.size; i++){
        printf("%d", a.digits[i]);
    }
    printf("%s", end);
}

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
    c.sign = a.sign * b.sign;

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

BigInt sum_bigint(BigInt a, BigInt b){
    if(a.sign == -1 && b.sign == 1){
        a.sign = 1;
        BigInt c = subtract_bigint(b, a);
        return c;
    } else if(a.sign == 1 && b.sign == -1){
        b.sign = 1;
        return subtract_bigint(a, b);
    } else if(a.sign == -1 && b.sign == -1){
        a.sign = 1;
        b.sign = 1;
        BigInt c = sum_bigint(a, b);
        c.sign = -1;
        return c;
    }

    BigInt c;
    c.size = MAX_DIGITS;
    c.sign = a.sign;
    memset(c.digits, 0, sizeof(c.digits));

    for(int i = 0; i < a.size; i++){
        c.digits[i] += a.digits[a.size-i-1];
    }

    for(int i = 0; i < b.size; i++){
        c.digits[i] += b.digits[b.size-i-1];
    }

    for(int i = 0; i < c.size; i++){
        if(c.digits[i] >= 10){
            c.digits[i+1] += c.digits[i] / 10;
            c.digits[i] %= 10;
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
    
    int i;

    if(c[0] == '-'){
        b.sign = -1;
        for(i = 1; i < b.size; i++){
            b.digits[i-1] = c[i] - '0';
        }
        b.size--;
    } else {
        b.sign = 1;
        i = 0;
        for(i = 0; i < b.size; i++){
            b.digits[i] = c[i] - '0';
        }
    }

    return b;
}

int compare_bigint(BigInt a, BigInt b){
    if(a.size > b.size){
        return 1;
    } else if(a.size < b.size){
        return -1;
    }

    for(int i = 0; i < a.size; i++){
        if(a.digits[i] > b.digits[i]){
            return 1;
        } else if(a.digits[i] < b.digits[i]){
            return -1;
        }
    }

    return 0;
}

BigInt subtract_bigint(BigInt a, BigInt b){
    if(a.sign == -1 && b.sign == 1){
        a.sign = 1;
        BigInt c = sum_bigint(a, b);
        c.sign = -1;
        return c;
    } else if(a.sign == 1 && b.sign == -1){
        b.sign = 1;
        return sum_bigint(a, b);
    } else if(a.sign == -1 && b.sign == -1){
        a.sign = 1;
        b.sign = 1;
        return subtract_bigint(b, a);
    } else if(compare_bigint(a, b) == -1){
        BigInt c = subtract_bigint(b, a);
        c.sign = -1;
        return c;
    }

    a = invert_bigint(a);
    b = invert_bigint(b);
    
    for(int i = 0; i < b.size; i++){
        if(a.digits[i] < 0){
            a.digits[i] += 10;
            a.digits[i+1] --;
        }

        if(a.digits[i] < b.digits[i]){
            a.digits[i]+=10;
            a.digits[i+1]--;
        }
    
        a.digits[i] -= b.digits[i];
    }

    while(a.digits[a.size-1] == 0 && a.size > 1){
        a.size--;
    }

    a = invert_bigint(a);

    return a;
}

void append_bigint(BigInt *a, short digit){
    a->digits[a->size] = digit;
    a->size++;
}

BigIntDivision divide_bigint(BigInt a, BigInt b){
    BigInt quotient;
    BigInt remainder;

    quotient.size = 0;
    quotient.sign = 1;
    remainder.size = 0;
    remainder.sign = 1;

    for(int i = 0; i < a.size; i++){
        append_bigint(&remainder, a.digits[i]);
        int x = 0;

        while (compare_bigint(remainder, b) != -1){
            remainder = subtract_bigint(remainder, b);
            x++;
        }

        append_bigint(&quotient, x);
    }

    while(quotient.digits[0] == 0 && quotient.size > 1){
        for(int i = 0; i < quotient.size; i++){
            quotient.digits[i] = quotient.digits[i+1];
        }
        quotient.size--;
    }

    while(remainder.digits[0] == 0 && remainder.size > 1){
        for(int i = 0; i < remainder.size; i++){
            remainder.digits[i] = remainder.digits[i+1];
        }
        remainder.size--;
    }

    return (BigIntDivision){quotient, remainder};
}

BigInt exp_mod_bigint(BigInt b, BigInt e, BigInt m){
    if(m.size == 1 && m.digits[0] == 1){
        BigInt c;
        c.size = 1;
        c.digits[0] = 0;
        return c;
    }

    BigInt result;
    result.size = 1;
    result.digits[0] = 1;

    b = divide_bigint(b, m).remainder;


    while(e.size > 1 || e.digits[0] != 0){
        if(e.digits[e.size-1] % 2 == 1){
            result = divide_bigint(multiply_bigint(result, b), m).remainder;

        }
        e = divide_bigint(e, (BigInt){{2}, 1}).quotient;
        b = divide_bigint(multiply_bigint(b, b), m).remainder;
    }

    return result;
}
