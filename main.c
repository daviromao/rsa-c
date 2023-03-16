#include "bigint.h"
#include <stdio.h>

int main(){
    BigInt a = read_bigint();
    printf("a = %d", a.size);
}