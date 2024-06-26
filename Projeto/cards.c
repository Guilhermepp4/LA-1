#include "cards.h"

Baralho* criaBaralho (int nMaos)
{
    Baralho* a = (Baralho*)calloc(nMaos, sizeof(Baralho));
    assert(a != NULL);

    for (int i = 0; i < nMaos; i++)
    {
        a[i].cartas = (wchar_t*)calloc(56 + 1, sizeof(wchar_t));
        assert(a[i].cartas != NULL);
    }

    return a;
}

Auxiliar_Ord* criaAux (int nMaos)
{
    Auxiliar_Ord* aux = (Auxiliar_Ord*)calloc(nMaos, sizeof(Auxiliar_Ord));
    assert(aux != NULL);

    return aux;
}

wchar_t* getCartas (Baralho* mao)
{
    return &(mao -> cartas[0]);
}

int* getCont(Baralho* mao) 
{
    return &(mao -> cont[0]);
}

int* getNaipe (Baralho* mao)
{
    return &(mao -> naipes[0][0]);
}

int getNum_cards (Baralho* mao)
{
    return (mao -> num_cards);
}

int getDiff_cards (Baralho* mao)
{
    return (mao -> diff_cards);
}

wchar_t getMaior_carta(Auxiliar_Ord* a)
{
    return (a -> maior_carta);
}

Combinacao getCombinacao (Baralho* mao)
{
    return (mao -> combinacao);
}

Excepcao getExcepcao (Baralho* mao)
{
    return (mao -> excepcao);
}

Naipe qualNaipe (wchar_t carta) 
{
    if (carta >= 0x1F0A1 && carta <= 0x1F0AE) 
    {
        return ESPADAS;
    }
    else if (carta >= 0x1F0B1 && carta <= 0x1F0BE) 
    {
        return COPAS;
    }
    else if (carta >= 0x1F0C1 && carta <= 0x1F0CE) 
    {
        return OUROS;
    }
    else 
    {
        return PAUS;
    }
}

Combinacao qualCombinacao(Baralho* mao)
{
    if(eConjunto(mao)) 
    {
        return CONJUNTO;
    }
    else if (eSequencia(mao)) 
    {
        return SEQUENCIA;
    }
    else if (eDuplaSequencia(mao)) 
    {
        return DUPLA;
    }
    else 
    {
        return NADA;
    }
}

int toValor (wchar_t carta, Naipe naipe) 
{
    return (carta - (0x1F0A1 + 16 * naipe));
}

void setCont_Naipes(Baralho* mao) 
{
    Naipe naipe;
    int valor;

    for (int i = 0;mao -> cartas[i];i++)
    {
        naipe = qualNaipe(mao -> cartas[i]);
        valor = toValor(mao -> cartas[i], naipe);
        mao -> cont[valor]++;
        mao -> naipes[valor][naipe]++;
    }
}

void setNum_cards(Baralho* mao) 
{
    int num_cards = 0;

    for (int i = 0; mao -> cartas[i]; i++) 
    {
        num_cards++;
    }

    mao -> num_cards = num_cards;
}

void setDiff_cards(Baralho* mao) 
{
    int diff_cards = 0;

    for (int i = 0; i < 14; i++) 
    {
        if (mao -> cont[i] > 0) diff_cards++;
    }

    mao -> diff_cards = diff_cards;
}

wchar_t toCarta (int c, int n) 
{
    return (c + 0x1F0A1 + 16 * n);
}

wchar_t maiorCarta (Baralho* mao)
{
    int* naipes = getNaipe(mao);
    int* cont = getCont(mao);
    int valor = 0;
    int naipe = 0;

    for (int i = 0; i < 14; i++)
    {
        if (cont[i] != 0)
        {
            valor = i;
        }
    }

    for (int j = 0; j < 4; j++)
    {
        if (naipes[valor * 4 + j] != 0)
        {
            naipe = j;
        }
    }

    return toCarta(valor, naipe);
}

void setMaior_carta(Auxiliar_Ord* aux, Baralho* mao)
{
    aux -> maior_carta = maiorCarta(mao);
}

void setCombinacao(Baralho* mao)
{
    mao -> combinacao = qualCombinacao(mao);
}

void setExcepcao (Baralho* mao)
{
    Combinacao combinacao = getCombinacao(mao);
    int* cont = getCont(mao);
    if (combinacao == CONJUNTO && cont[13] != 0)
    {
        if (cont[13] == 1)
        {
            mao -> excepcao = K;
        }
        else if (cont[13] == 2)
        {
            mao -> excepcao = KK;
        }
        else 
        {
            mao -> excepcao = KKK;
        }
    }
    else 
    {
        mao -> excepcao = NENHUMA;
    }
}

int todosSeguidos (Baralho* mao)
{
    int* cont = getCont(mao);
    int diff_cards = getDiff_cards(mao);
    int i = 0, seguidos = 0;

    while (cont[i] == 0 && i < 14) 
    {
        i++;
    }

    while (cont[i] != 0 && i < 14) 
    {
        seguidos++;
        i++;
    }

    return (seguidos == diff_cards);
}

int quantidadesIguais (Baralho* mao, int n)
{
    int* cont = getCont(mao);
    int diff_cards = getDiff_cards(mao);
    int i = 0, count = 0;

    while (cont[i] == 0 && i < 14)
    {
        i++;
    }

    while (cont[i] == n && i < 14)
    {
        count++;
        i++;
    }

    return (count == diff_cards);
}

int eSequencia (Baralho* mao) 
{
    int num_cards = getNum_cards(mao);
    int diff_cards = getDiff_cards(mao);

    if (diff_cards > 2 && num_cards / diff_cards == 1 && todosSeguidos(mao) && quantidadesIguais(mao, 1))
    {
        return 1;
    }

    return 0;
}

int eDuplaSequencia (Baralho* mao)
{
    int num_cards = getNum_cards(mao);
    int diff_cards = getDiff_cards(mao);

    if (diff_cards > 2 && num_cards / diff_cards == 2 && todosSeguidos(mao) && quantidadesIguais(mao, 2))
    {
        return 1;
    }

    return 0;
}

int eConjunto (Baralho* mao)
{
    int diff_cards = getDiff_cards(mao);

    if (diff_cards != 1) 
    {
        return 0;
    }

    return 1;
}

int compara (const void* a, const void* b) 
{
    const wchar_t* carta1 = (wchar_t*) a;
    const wchar_t* carta2 = (wchar_t*) b;

    int valor = toValor(*carta1,qualNaipe(*carta1)) - toValor(*carta2,qualNaipe(*carta2));
    int naipe = qualNaipe(*carta1) - qualNaipe(*carta2);

    if (valor != 0) 
    {
        return valor;
    }

    return naipe;
}

int comparaAux (const void* a, const void* b)
{
    const Auxiliar_Ord *carta1 = (const Auxiliar_Ord*) a;
    const Auxiliar_Ord *carta2 = (const Auxiliar_Ord*) b;

    int valor = toValor(carta1 -> maior_carta, qualNaipe(carta1 -> maior_carta)) - toValor(carta2 -> maior_carta, qualNaipe(carta2 -> maior_carta));
    int naipe = qualNaipe(carta1 -> maior_carta) - qualNaipe(carta2 -> maior_carta);

    if(valor != 0) return valor;
    return naipe;
}

int numCards_iguais (Baralho* mao, int nMaos)
{
    int num_cards = getNum_cards(&mao[0]);

    for (int i = 1; i < nMaos; i++)
    {
        if (mao[i].num_cards != num_cards)
        {
            return 0;
        }
    }

    return 1;
}

int combinacoes_iguais(Baralho* mao,int nMaos)
{
    Combinacao combinacao = qualCombinacao(&mao[0]);

    for (int i = 1; i < nMaos; i++)
    {
        if (combinacao != qualCombinacao(&mao[i])) return 0;
    }
    return 1;
}

void ordenaCartas (Baralho* mao, int nMaos)
{
    for (int i = 0; i < nMaos; i++)
    {
        qsort (mao[i].cartas, mao[i].num_cards, sizeof(wchar_t), compara);
    }
}

void ordenaMaos(Auxiliar_Ord* aux, int nMaos)
{
    qsort(aux, nMaos, sizeof(Auxiliar_Ord), comparaAux);
}

void imprimeBaralho (Baralho* mao)
{
    int tamanho = getNum_cards(mao);

    if (tamanho != 0)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (j == tamanho - 1) 
            {
                wprintf(L"%lc\n",mao -> cartas[j]);
            }
            else 
            {
                wprintf(L"%lc ",mao -> cartas[j]);
            }
        }
    }
    else
    {
        wprintf(L"\n");
    }
}

int presenteNaMao(Baralho* jogada_pretendida,Baralho* mao_Jogador)
{
    int tamanho_jogada = getNum_cards(jogada_pretendida);
    int tamanho_mao = getNum_cards(mao_Jogador);
    int count = 0;

    for (int i = 0; i < tamanho_mao; i++)
    {
        for (int j = 0; j < tamanho_jogada; j++)
        {
            if (mao_Jogador -> cartas[i] == jogada_pretendida -> cartas[j])
            {
                count++;
            }   
        } 
    }

    return (count == tamanho_jogada);
}

int jogadasAnteriores3PASSO(Baralho* jogadas, int nJogadas)
{
    for (int i = nJogadas - 1; i != nJogadas - 4; i--)
    {
        if(wcscmp(jogadas[i].cartas, L"PASSO")) 
        {
            return 0;
        }
    }

    return 1;
}


int jogadaValida(Baralho* mao_Jogador,Baralho* jogada_pretendida, Baralho* jogadas_anteriores, int nJogadas)
{
    if (!presenteNaMao(jogada_pretendida, mao_Jogador))
    {
        return 0;
    }

    if (jogadasAnteriores3PASSO(jogadas_anteriores, nJogadas) && jogada_pretendida -> combinacao != NADA)
    {
        return 1;
    }

    int i = nJogadas - 1;   
    
    while (!wcscmp(jogadas_anteriores[i].cartas, L"PASSO")) 
    {
        i--; 
    }

    Excepcao tipo_jogada = jogadas_anteriores[i].excepcao; 
    Combinacao combinacao = jogadas_anteriores[i].combinacao;
    int tamanho_jogada = jogadas_anteriores[i].num_cards;
    int jogada_pretendidaNUmCards = getNum_cards (jogada_pretendida);

    if (tipo_jogada == K) 
    { 
        return ((eConjunto(jogada_pretendida) && ((jogada_pretendida -> num_cards == 4) || compara (&jogada_pretendida -> cartas[0], &jogadas_anteriores[i].cartas[0]) > 0)) || (eDuplaSequencia(jogada_pretendida) && (jogada_pretendida -> diff_cards == 3)));
    }
    else if (tipo_jogada == KK) 
    {
        return (eDuplaSequencia(jogada_pretendida) && ((jogada_pretendida -> diff_cards == 4)));
    }
    else if (tipo_jogada == KKK)
    {
        return (eDuplaSequencia(jogada_pretendida) && (jogada_pretendida -> diff_cards == 5));
    }
    else 
    {
        return (combinacao == qualCombinacao(jogada_pretendida) && tamanho_jogada == jogada_pretendida -> num_cards && compara(&jogadas_anteriores[i].cartas[tamanho_jogada - 1], &jogada_pretendida -> cartas[jogada_pretendidaNUmCards - 1]) < 0); 
    }

    return 0;
}

void indicestoCarta (int* contagem, int (*naipes)[4], Baralho* mao_Jogador)
{
    int i = 0, j = 0, r = 0;

    for (i = 0; i < 14; i++) 
    {
        if (contagem[i] != 0)
        {
            for (j = 0; j < 4; j++)
            {
                if (naipes[i][j] != 0)
                {
                    mao_Jogador -> cartas[r] = toCarta (i, j);
                    r++;
                }
            }
        }
    }

    mao_Jogador -> cartas[r] = '\0';
}

void atualizaMao(Baralho* mao_Jogador, Baralho* jogada_pretendida)
{
    int* maoJogadorCont = getCont(mao_Jogador);
    int* jogadaPretendidaCont = getCont(jogada_pretendida);
    int* maoJogadorNaipes = getNaipe(mao_Jogador);
    int* jogadaPretendidaNaipes = getNaipe(jogada_pretendida);

    int contagemAux[14];
    int naipesAux[14][4];

    for (int i = 0; i < 14; i++)  
    {
        contagemAux[i] = maoJogadorCont[i] - jogadaPretendidaCont[i];
    }

    int j = 0;

    for (int i = 0; i < 14; i++)  
    {
        for (j = 0; j < 4; j++)
        {
            naipesAux[i][j] = maoJogadorNaipes[i * 4 + j] - jogadaPretendidaNaipes[i * 4 + j];
        }
    }

    indicestoCarta(contagemAux, naipesAux, mao_Jogador);

    mao_Jogador -> num_cards -= jogada_pretendida -> num_cards;
}
