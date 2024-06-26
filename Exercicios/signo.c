#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main()
{
    int d, m;
    setlocale(LC_CTYPE, "C.UTF-8");
    if(scanf("%d%d", &d, &m) == 2) {
    wchar_t c;


    if((m==3 && d >=21 && d <= 31) || (m == 4 && d >= 1 && d <= 20)){
        c=0x2648;
    }
    else if((m==4 && d >=21 && d <= 31) || (m == 5 && d >= 1 && d <= 20)){
        c=0x2649;
    }
    else if((m==5 && d >=21 && d <= 31) || (m == 6 && d >= 1 && d <= 20)){
        c=0x264a;
    }
    else if((m==6 && d >=21 && d <= 31) || (m == 7 && d >= 1 && d <= 22)){
        c=0x264b;
    }    
    else if((m==7 && d >=23 && d <= 31) || (m == 8 && d >= 1 && d <= 22)){
        c=0x264c;
    }
    else if((m==8 && d >=23 && d <= 31) || (m == 9 && d >= 1 && d <= 22)){
        c=0x264d;
    }
    else if((m==9 && d >=23 && d <= 31) || (m == 10 && d >= 1 && d <= 22)){
        c=0x264e;
    }
    else if((m==10 && d >=23 && d <= 31) || (m == 11 && d >= 1 && d <= 21)){
        c=0x264f;
    }
    else if((m==11 && d >=22 && d <= 31) || (m == 12 && d >= 1 && d <= 21)){
        c=0x2650;
    }
    else if((m==12 && d >=22 && d <= 31) || (m == 1 && d >= 1 && d <= 19)){
        c=0x2651;
    }
    else if((m==1 && d >=20 && d <= 31) || (m == 2 && d >= 1 && d <= 18)){
        c=0x2652;
    }
    else if((m==2 && d >=19 && d <= 31) || (m == 3 && d >= 1 && d <= 20)){
        c=0x2653;
    }

    	wprintf(L"%lc\n", c);
    }

    return 0;
}




