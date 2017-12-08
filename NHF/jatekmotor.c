#include <stdlib.h>
#include <stdbool.h>
#include "din_mem.h"
#include "jatekmotor.h"

/**< ez a függvény egy ismert méretû 2D logikai tömbbõl (játékmezõ) kiszámítja annak következõ állapotát.
Paraméterként a tömböt, és annak méreteit kéri, és visszatér az új tömbre mutató pointerrel.
A kért táblánál nagyobb tömböt hoz létre, hogy majd a szélén lévö mezöket ne használjuk*/
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
