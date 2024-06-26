#include <stdio.h>


char *lista[] = {"䷀", "䷁", "䷂", "䷃", "䷄", "䷅", "䷆", "䷇", "䷈",
                 "䷉", "䷊", "䷋", "䷌", "䷍", "䷎", "䷏", "䷐",
                 "䷑", "䷒", "䷓", "䷔", "䷕", "䷖", "䷗", "䷘",
                 "䷙", "䷚", "䷛", "䷜", "䷝", "䷞", "䷟", "䷠",
                 "䷡", "䷢", "䷣", "䷤", "䷥", "䷦", "䷧", "䷨",
                 "䷩", "䷪", "䷫", "䷬", "䷭", "䷮", "䷯", "䷰",
                 "䷱", "䷲", "䷳", "䷴", "䷵", "䷶", "䷷", "䷸",
                 "䷹", "䷺", "䷻", "䷼", "䷽", "䷾", "䷿"};


int main() {
    unsigned long long int N; // Recebe um número decimal
    int o=1;
    if (scanf("%llu", &N) == 1) {
        unsigned long long int y = N;
        if (N == 0) { // Verifica se o número é zero
            printf("%s\n", lista[0]);
        } else {
            int indice = 0;
            while (y > 0){ // Determina quantos caracteres serão necessários para representar o número na base 64
                y/=64;
                o++;
            }
            char *elementosEncontrados[o]; // Cria um array para armazenar os caracteres na ordem correta
            
            while (N > 0) { // Converte o número para a base 64 e armazena os caracteres no array
                int N2 = N % 64;
                elementosEncontrados[indice++] = lista[N2];
                N /= 64;
            }

            for (int i = indice - 1; i >= 0; i--) {
                printf("%s", elementosEncontrados[i]);
            if (i > 0) {
                printf(" ");
            }
            }
            printf("\n"); 
        }
    }
    return 0;
    
}
