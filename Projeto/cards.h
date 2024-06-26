#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<wchar.h>
#include<locale.h>
#include<math.h>
#include<assert.h>
#include <stdbool.h>

typedef enum Naipes {ESPADAS, COPAS, OUROS, PAUS} Naipe;
typedef enum Combinacoes {NADA, CONJUNTO, SEQUENCIA, DUPLA} Combinacao;
typedef enum Excepcoes {NENHUMA, K, KK, KKK} Excepcao;

typedef struct baralho {
    
    wchar_t* cartas;   
    int cont [14];     
    int naipes[14][4]; 
    int num_cards;     
    int diff_cards;    
    Combinacao combinacao;
    Excepcao excepcao;
    
} Baralho;

typedef struct auxiliar
{
    int indice;
    wchar_t maior_carta;

} Auxiliar_Ord;

Baralho *criaBaralho(int nMaos);

Auxiliar_Ord *criaAux(int nMaos);

wchar_t *getCartas(Baralho *mao);

int *getCont(Baralho *mao);

int *getNaipe(Baralho *mao);

int getNum_cards(Baralho *mao);

int getDiff_cards(Baralho *mao);

wchar_t getMaior_carta(Auxiliar_Ord *a);

Combinacao getCombinacao(Baralho *mao);

Excepcao getExcepcao(Baralho *mao);

Naipe qualNaipe(wchar_t carta);

Combinacao qualCombinacao(Baralho *mao);

int toValor(wchar_t carta, Naipe naipe);

void setCont_Naipes(Baralho *mao);

void setNum_cards(Baralho *mao);

void setDiff_cards(Baralho *mao);

wchar_t toCarta(int c, int n);

wchar_t maiorCarta(Baralho *mao);

void setMaior_carta(Auxiliar_Ord *aux, Baralho *mao);

void setCombinacao(Baralho *mao);

void setExcepcao(Baralho *mao);

int todosSeguidos(Baralho *mao);

int quantidadesIguais (Baralho* mao, int i);

int eSequencia(Baralho *mao);

int eDuplaSequencia(Baralho *mao);

int eConjunto(Baralho *mao);

int compara(const void *a, const void *b);

int comparaAux(const void *a, const void *b);

int numCards_iguais(Baralho *mao, int nMaos);

int combinacoes_iguais(Baralho *mao, int nMaos);

void ordenaCartas(Baralho *mao, int nMaos);

void ordenaMaos(Auxiliar_Ord *aux, int nMaos);

void imprimeBaralho(Baralho *mao);

int presenteNaMao(Baralho *jogada_pretendida, Baralho *mao_Jogador);

int jogadasAnteriores3PASSO(Baralho *jogadas, int nJogadas);

int jogadaValida(Baralho *mao_Jogador, Baralho *jogada_pretendida, Baralho *jogadas_anteriores, int nJogadas);

void atualizaMao(Baralho *mao_Jogador, Baralho *jogada_pretendida);
