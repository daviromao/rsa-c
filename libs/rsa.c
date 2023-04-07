#include "euclides.c"
#include "utils.c"

typedef struct PublicKey{
    BigInt n;
    BigInt e;
} PublicKey;

typedef struct PrivateKey{
    BigInt n;
    BigInt d;
} PrivateKey;

PublicKey create_public_key(BigInt p, BigInt q, BigInt e){
    return (PublicKey) {multiply_bigint(p, q), e};
}

PrivateKey create_private_key(BigInt p, BigInt q, BigInt e){
    BigInt one = {{1}, 1, 1};
    BigInt phi = multiply_bigint(subtract_bigint(p, one), subtract_bigint(q, one));
    BigInt d = modular_inverse(e, phi);
    return (PrivateKey) {multiply_bigint(p, q), d};
}

void generate_public_key(){
    printf("Digite p: ");
    BigInt p = read_bigint();

    printf("Digite q: ");
    BigInt q = read_bigint();
    
    printf("Digite e: ");
    BigInt e = read_bigint();

    PublicKey public_key = create_public_key(p, q, e);

    printf("\nChave publica:\n");
    printf("n = ");
    print_big_int(public_key.n, "\n");
    printf("e = ");
    print_big_int(public_key.e, "\n");
}

BigInt char_to_bigint(char c){
    switch(c){
        case 'A': case'a': return (BigInt){{2}, 1, 1};
        case 'B': case'b': return (BigInt){{3}, 1, 1};
        case 'C': case'c': return (BigInt){{4}, 1, 1};
        case 'D': case'd': return (BigInt){{5}, 1, 1};
        case 'E': case'e': return (BigInt){{6}, 1, 1};
        case 'F': case'f': return (BigInt){{7}, 1, 1};
        case 'G': case'g': return (BigInt){{8}, 1, 1};
        case 'H': case'h': return (BigInt){{9}, 1, 1};
        case 'I': case'i': return (BigInt){{1,0}, 2, 1};
        case 'J': case'j': return (BigInt){{1,1}, 2, 1};
        case 'K': case'k': return (BigInt){{1,2}, 2, 1};
        case 'L': case'l': return (BigInt){{1,3}, 2, 1};
        case 'M': case'm': return (BigInt){{1,4}, 2, 1};
        case 'N': case'n': return (BigInt){{1,5}, 2, 1};
        case 'O': case'o': return (BigInt){{1,6}, 2, 1};
        case 'P': case'p': return (BigInt){{1,7}, 2, 1};
        case 'Q': case'q': return (BigInt){{1,8}, 2, 1};
        case 'R': case'r': return (BigInt){{1,9}, 2, 1};
        case 'S': case's': return (BigInt){{2,0}, 2, 1};
        case 'T': case't': return (BigInt){{2,1}, 2, 1};
        case 'U': case'u': return (BigInt){{2,2}, 2, 1};
        case 'V': case'v': return (BigInt){{2,3}, 2, 1};
        case 'W': case'w': return (BigInt){{2,4}, 2, 1};
        case 'X': case'x': return (BigInt){{2,5}, 2, 1};
        case 'Y': case'y': return (BigInt){{2,6}, 2, 1};
        case 'Z': case'z': return (BigInt){{2,7}, 2, 1};
        case ' ': return (BigInt){{2,8}, 2};
    }
}

char bigint_to_char(BigInt c){
    switch(c.size){
        case 1:
            switch(c.digits[0]){
                case 2: return 'A';
                case 3: return 'B';
                case 4: return 'C';
                case 5: return 'D';
                case 6: return 'E';
                case 7: return 'F';
                case 8: return 'G';
                case 9: return 'H';
            }
        case 2:
            switch(c.digits[0]){
                case 1:
                    switch(c.digits[1]){
                        case 0: return 'I';
                        case 1: return 'J';
                        case 2: return 'K';
                        case 3: return 'L';
                        case 4: return 'M';
                        case 5: return 'N';
                        case 6: return 'O';
                        case 7: return 'P';
                        case 8: return 'Q';
                        case 9: return 'R';
                    }
                case 2:
                    switch(c.digits[1]){
                        case 0: return 'S';
                        case 1: return 'T';
                        case 2: return 'U';
                        case 3: return 'V';
                        case 4: return 'W';
                        case 5: return 'X';
                        case 6: return 'Y';
                        case 7: return 'Z';
                        case 8: return ' ';
                    }
            }
    }
}

void encrypt(){
    char message[1000];
    printf("Digite a mensagem: ");
    scanf("%[^\n]s", message);
    scanf("%*c");


    printf("Digite n: ");
    BigInt n = read_bigint();

    printf("Digite e: ");
    BigInt e = read_bigint();


    printf("\nMensagem criptografada: ");
    for(int i = 0; i < strlen(message); i++){
        BigInt m = char_to_bigint(message[i]);
        BigInt c = exp_mod_bigint(m, e, n);
        print_big_int(c, " ");
    }
    printf("\n");
}

void decrypt(){
    char message[1000];
    printf("Digite a mensagem: ");
    scanf("%[^\n]s", message);
    scanf("%*c");

    printf("Digite p: ");
    BigInt p = read_bigint();

    printf("Digite q: ");
    BigInt q = read_bigint();

    printf("Digite e: ");
    BigInt e = read_bigint();

    PrivateKey private_key = create_private_key(p, q, e);

    printf("\nMensagem descriptografada: ");
    char *token = strtok(message, " ");
    while(token != NULL){
        BigInt c = string_to_bigint(token);
        BigInt m = exp_mod_bigint(c, private_key.d, private_key.n);
        printf("%c", bigint_to_char(m));
        token = strtok(NULL, " ");
    }
}