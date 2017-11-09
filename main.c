#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int w, h;
int kov_kep (bool const**, bool** kov, int w, int h);

int main()
{
    printf("");
    return 0;
}

int kov_kep (bool const** kep, bool** kov, int w, int h)
{
    int i, j, k, l, szomszed;
    for (i = 1; i != w + 1; i++)
    {
        for (j= 1; j != h+1; j++)
        {
            if (j == 0 || i == 0 || i == w+1 || j == h+1)
                continue;
            for (k = i-1; k != k+2; k++)
            {
                szomszed = 0;
                for (l = j - 1; l != l + 2; l++)
                {
                    if (l == j && k == i)
                        continue;
                    if (kep[l][k] == true)
                        szomszed++;
                }
                if (szomszed < 2 || szomszed > 3)
                    kov [i][j] = false;
                if ((szomszed == 2 && kep [i][j] == true) || (szomszed == 3))
                    kov [i][j] = true;
            }
        }
    }
    return 0;
}
