#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    e0, e1, e2, e3, e4, e5, e6, e7, ERRO
} Estado;


int isDigit(char c) {
    return c >= '0' && c <= '9';
}


Estado delta(Estado estado, char c) {
    switch (estado) {
        case e0:
            if (c == '+' || c == '-') return e1;
            if (isDigit(c)) return e3;
            if (c == '.') return e2;
            break;

        case e1:
            if (isDigit(c)) return e3;
            if (c == '.') return e2;
            break;

        case e2:
            if (isDigit(c)) return e4;
            break;

        case e3:
            if (isDigit(c)) return e3;
            if (c == '.') return e4;
            if (c == 'E') return e5;
            break;

        case e4:
            if (isDigit(c)) return e4;
            if (c == 'E') return e5;
            break;

        case e5:
            if (c == '+' || c == '-') return e6;
            if (isDigit(c)) return e7;
            break;

        case e6:
            if (isDigit(c)) return e7;
            break;

        case e7:
            if (isDigit(c)) return e7;
            break;

        default:
            return ERRO;
    }

    return ERRO;
}


int estadoFinal(Estado e) {
    return (e == e3 || e == e4 || e == e7);
}

int main() {
    char entrada[100];
    printf("Digite um numero: ");
    scanf("%s", entrada);

    Estado atual = e0;

    for (int i = 0; i < strlen(entrada); i++) {
        atual = delta(atual, entrada[i]);

        if (atual == ERRO) {
            printf("Numero INVALIDO\n");
            return 0;
        }
    }

    if (estadoFinal(atual)) {
        printf("Numero VALIDO\n");
    } else {
        printf("Numero INVALIDO\n");
    }

    return 0;
}
