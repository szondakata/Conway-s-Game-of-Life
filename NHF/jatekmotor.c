#include <stdlib.h>
#include <stdbool.h>
#include "din_mem.h"
#include "jatekmotor.h"

/**< ez a f�ggv�ny egy ismert m�ret� 2D logikai t�mbb�l (j�t�kmez�) kisz�m�tja annak k�vetkez� �llapot�t.
Param�terk�nt a t�mb�t, �s annak m�reteit k�ri, �s visszat�r az �j t�mbre mutat� pointerrel.
A k�rt t�bl�n�l nagyobb t�mb�t hoz l�tre, hogy majd a sz�l�n l�v� mez�ket ne haszn�ljuk*/
bool ** kov_kep (bool ** kep, int szeles, int magas){
    int i, j, k, l, szomszed;
    bool **uj;
    kep_letrehoz(&uj, szeles, magas);
    for (i = 0; i <= szeles; i++){
        for (j = 0; j <= magas; j++){
            if (j == 0 || i == 0 || i == szeles + 1 || j == magas + 1)
                uj [i][j] = false;
                continue;
            szomszed = 0;
            for (k = i - 1; k <= i + 1; k++){
                for (l = j - 1; l <= j + 1; l++){
                    if (l == j && k == i)
                        continue;
                    if (kep[i][j] == true)
                        szomszed++;
                }
            }
            if ((szomszed == 2 && kep[i][j] == true) || (szomszed == 3))
                uj [i][j] = true;
            else
                uj [i][j] = false;
        }
    }
    kep_felszabadit(kep, szeles, magas);
    return uj;
}
