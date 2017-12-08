#include <stdbool.h>
#include <stdlib.h>
#include "din_mem.h"

/**< A függvény létrehoz egy játéktáblát és visszatér egy arra mutató pinterrel. Paraméterként a majd látszó tábla méreteit várja, a képernyöre
kerülö táblázat minden oldalán még egy üres sor/oszlop áll, hogy a mezök szomszédainak számolásánál a fontos mezöknek minden oldalról legyen szomszédja.
A dinamikusan foglalt memóriát késöbb fel kell szabaditani.*/
int kep_letrehoz(bool ***ide, int szeles, int magas)
{
    int i, j;
    bool** uj;

    uj = (bool**) malloc ((magas + 1)* sizeof(bool*));
    for (i = 0; i <= magas + 1; i++)
    {
        uj[i] = (bool*) malloc ((szeles + 1)* sizeof(bool));


        for (j=0; j < szeles+1; j++)
            uj[i][j]=false;
    }

    *ide = uj;
    return 0;
}

/**< A függvény felszabadítja a dinamikusan foglalt játéktáblát.
Paraméterként szüksége van egy, a táblára mutató pointerre, a tábla szélességére és magasságára*/
void kep_felszabadit(bool** palya, int szeles, int magas)
{
    int i;
    for (i = 0; i < szeles + 1; i++)
        free(palya[i]);
    free(palya);
    palya = NULL;
    return;
}

/**<  A fv véletlenszerûen feltölti a pályát elemekkel. Paramáterként a tábla méretét, és a rámutató pointert várja.*/
void palya_rand(bool*** palya, int x, int y)
{
    int i, j;
    for (i = 1; i < x; i++)
    {
        for (j = 1; j < y; j++)
        {
            if (0 == rand() % 2)
                *palya[i][j] = true;
            else *palya [i][j] = false;
        }
    }
    return;
}
