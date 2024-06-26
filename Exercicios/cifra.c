#include <stdio.h>
#include <math.h>
#include <string.h>

double lista[] = {43.31, 10.56, 23.13, 17.25, 56.88, 9.24, 12.59, 15.31, 38.45,
                  1, 5.61, 27.98, 15.36, 33.92, 36.51, 16.14, 1,
                  38.64, 29.23, 35.43, 18.51, 5.13, 6.57, 1.48, 9.06,
                  1.39};

char alfabeto[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char alfabeto2[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void avanca_alfabeto(char *texto) {
    while (*texto) {
        if ((*texto >= 'A' && *texto < 'Z') || (*texto >= 'a' && *texto < 'z')) {
            *texto += 1;
        }else if ((*texto == 'z')) {
                *texto = 'a'; 
        }
        else if (*texto == 'Z') {
            *texto = 'A';
        }
        texto++;
    }
}

void verifica_quant(const char lista[], const char alfabeto[], const char alfabeto2[], int somatorio[26][26]) {
    int soma = 0;
    for (int i = 0; i < 26; i++) {
        for (size_t t = 0; t < strlen(lista); t++) {
            if (alfabeto[i] == lista[t] || alfabeto2[i] == lista[t]) {
                soma++;
            }
        }
        somatorio[i][0] = soma; 
        soma = 0;
    }
    for (int j = 1; j < 26; j++) {
        avanca_alfabeto((char *)lista); 
        for (int i = 0; i < 26; i++) {
            for (size_t t = 0; t < strlen(lista); t++) {
                if (alfabeto[i] == lista[t] || alfabeto2[i] == lista[t]) {
                    soma++;
                }
            }
            somatorio[i][j] = soma;
            soma = 0;
        }
    }
}

void cifraCesar(char *texto, int r) {
    while (*texto) {
        if ((*texto >= 'A' && *texto <= 'Z')|| (*texto >= 'a' && *texto <= 'z')) {
            if (*texto >= 'a') {
                *texto = (*texto - 'a' + r + 1) % 26 + 'a';
            } else {
                *texto = (*texto - 'A' + r + 1) % 26 + 'A';
        }
        }
        texto++;
    }
}


int main() {
    int max_length = pow(10, 4); 
    char input[max_length];
    double soma_final = pow(10, 4);
    int k = 0;
    if (fgets(input, sizeof(input), stdin) == NULL) {
    return 1; 
}
    int somatorio[26][26];
    verifica_quant(input, alfabeto, alfabeto2, somatorio);
    for (int j = 0; j < 26; j++) {
        double soma = 0;
        for (int i = 0; i < 26; i++) {
            soma += pow(lista[i] - somatorio[i][j], 2) / lista[i];
        }
        if(soma < soma_final) {
            soma_final = soma;
            k = j;
        }
    }
    cifraCesar(input,k);
    printf("%d %s", k, input);
    return 0;
}