#include <stdbool.h>
#include <stdlib.h>
#include "din_mem.h"

/**< A f�ggv�ny l�trehoz egy j�t�kt�bl�t �s visszat�r egy arra mutat� pinterrel. Param�terk�nt a majd l�tsz� t�bla m�reteit v�rja, a k�perny�re
ker�l� t�bl�zat minden oldal�n m�g egy �res sor/oszlop �ll, hogy a mez�k szomsz�dainak sz�mol�s�n�l a fontos mez�knek minden oldalr�l legyen szomsz�dja.
A dinamikusan foglalt mem�ri�t k�s�bb fel kell szabaditani.*/
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

/**< A f�ggv�ny felszabad�tja a dinamikusan foglalt j�t�kt�bl�t.
Param�terk�nt sz�ks�ge van egy, a t�bl�ra mutat� pointerre, a t�bla sz�less�g�re �s magass�g�ra*/
void kep_felszabadit(bool** palya, int szeles, int magas)
{
    int i;
    for (i = 0; i < szeles + 1; i++)
        free(palya[i]);
    free(palya);
    palya = NULL;
    return;
}

/**<  A fv v�letlenszer�en felt�lti a p�ly�t elemekkel. Param�terk�nt a t�bla m�ret�t, �s a r�mutat� pointert v�rja.*/
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
