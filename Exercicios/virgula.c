
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    int N, e, m;
    int j = 0;
    double expo = 0;
    double man = 0;
    double w = 0;
    double sinal = 0;
    int u = 0;
    int x = 0;

    if (scanf("%d", &N) == 1) {
        char (*final)[13] = malloc(N * sizeof(*final));

        while (j < N) {
            if (scanf("%d %d", &e, &m) == 2) {
                if (e > 5 || e < 1 || m > 7 || m < 1) {
                    j++;
                    continue;
                }

                char string[1 + e + m];
                if (scanf("%s", string) == 1) {
                    int allOnesInExponent = 1;

                    for (int i = e; i >= 1; i--) {
                        if (string[i] != '1') {
                            allOnesInExponent = 0;
                            break;
                        }
                    }

                    if (allOnesInExponent) {
                        int anyOneInMantissa = 0;
                        for (int i = 1 + e; i < 1 + m + e; i++) {
                            if (string[i] == '1') {
                                anyOneInMantissa = 1;
                                break;
                            }
                        }

                        if (anyOneInMantissa) {
                            strcpy(final[u], "NaN");
                        } else {
                            strcpy(final[u], (string[0] == '0') ? "+Infinity" : "-Infinity");
                        }

                        u++;
                        j++;
                        continue;
                    }

                    for (int i = e; i >= 1; i--) {
                        if (string[i] == '1') {
                            expo += pow(2, x);
                        }
                        x++;
                    }

                    x = 1;
                    for (int i = 1 + e; i < 1 + m + e; i++) {
                        if (string[i] == '1') {
                            man += pow(2, -x);
                        }
                        x++;
                    }

                    sinal = (string[0] == '1') ? -1 : 1;

                    w = expo - (pow(2, e - 1) - 1);
                    if (e == 1 && expo == 0) {
                        w = 1;

                        double c = sinal * pow(2, 1) * man;
                        sprintf(final[u], "%lg", c);
                        j++;
                        u++;
                        man = 0;
                        expo = 0;
                        x = 0;
                        continue;
                    }

                    if (w < 0 && man != 0 && expo == 0) {
                        w += 1;
                        double c = sinal * pow(2, w) * man;
                        sprintf(final[u], "%lg", c);
                        u++;
                    }else if(w < 0 && man == 0 && expo != 0){
                        
                        double c = sinal * pow(2, w) * 1;
                        sprintf(final[u], "%lg", c);
                        u++;
                    }
                    else if(w <0 && man == 0 && expo == 0){
                        w += 1;
                        double c = sinal * pow(2, w) * 0;
                        sprintf(final[u], "%lg", c);
                        u++;
                    }
                     else {
                        double c = sinal * pow(2, w) * (1 + man);
                        sprintf(final[u], "%lg", c);
                        u++;
                    }
                }
            }
            man = 0;
            expo = 0;
            j++;
            x = 0;
        }

        for (int f = 0; f < N; f++) {
            printf("%s\n", final[f]);
        }

        free(final); 
    }

    return 0;
}







