#include "cards.h"

void preencheBaralho (Baralho* mao)
{
    setCont_Naipes(mao);
    setNum_cards(mao);        
    setDiff_cards(mao);
    setCombinacao(mao);
    setExcepcao(mao);
}

void preencheAux (Baralho* mao, Auxiliar_Ord* aux, int i)
{
    aux -> indice = i;
    setMaior_carta(aux, mao);
}

void leJogadas (Baralho* jogadas, int nJogadas)
{
    for (int i = 0; i < nJogadas; i++)
    {
        assert(wscanf (L"%ls", jogadas[i].cartas) == 1);
        if (wcscmp(jogadas[i].cartas,L"PASSO"))
        {
            preencheBaralho(&jogadas[i]);
        }
    }
    
    ordenaCartas(jogadas, nJogadas);
}

int main()
{

    setlocale(LC_CTYPE, "C.UTF-8");
    
    int nTestes;
    assert(wscanf (L"%d", &nTestes) == 1);

    for (int i = 1; i <= nTestes; i++)
    {
        int nJogadas; 
        assert(wscanf (L"%d", &nJogadas) == 1);

        Baralho* mao_Jogador = criaBaralho(1); 
        assert(wscanf (L"%ls", mao_Jogador->cartas) == 1);
        preencheBaralho(mao_Jogador);
        ordenaCartas(mao_Jogador,1); 

        Baralho* jogadas = criaBaralho(nJogadas); 

        leJogadas (jogadas, nJogadas);

        Baralho* jogada_pretendida = criaBaralho(1); 
        assert(wscanf (L"%ls", jogada_pretendida -> cartas) == 1); 
        
        if (wcscmp(jogada_pretendida->cartas, L"PASSO") != 0)
        {
            preencheBaralho(jogada_pretendida);
            ordenaCartas(jogada_pretendida,1);
        }
        
        wprintf(L"Teste %d\n", i);
        
        if (nJogadas == 0)
        {
            if(presenteNaMao(jogada_pretendida, mao_Jogador) && jogada_pretendida -> combinacao != NADA)
            {
                atualizaMao(mao_Jogador,jogada_pretendida);
            }
        }
        else if(jogadaValida(mao_Jogador,jogada_pretendida,jogadas,nJogadas))
        {
            atualizaMao(mao_Jogador,jogada_pretendida);
        }
        
        imprimeBaralho(mao_Jogador);
        
        free(jogadas);
        free(mao_Jogador);
        free(jogada_pretendida);
    }
}
