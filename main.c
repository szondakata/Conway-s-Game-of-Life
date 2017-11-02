#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int next_state (bool **sejt, int, int);
int mellette (bool **sejt, int, int);

int main()
{
    return 0;
}
int next_state (bool **sejt, int magassag, int szelesseg)
{
    int i, j;
    for (i = 0; i < magassag; i++)
    {
        for (j = 0; j < szelesseg; j++)
        {
            int szomszed = mellette(sejt, magassag, szelesseg);
            if (szomszed < 2 || szomszed > 3)
                sejt[i][j] = false;
            else if ((szomszed == 2 && sejt[i][j] == true ) || szomszed == 3)
                sejt[i][j] = true;
        }
    }
    return 0;
}

int mellette(bool **sejt, int magassag, int szelesseg)
{
    int mennyi, i, j;
    for (i = -1; i < 2; i++)
    {
        for (j = -1; j < 2; j++)
        {
            if ((i != 0) && (j != 0))
            {
                if (sejt[i][j] == true)
                    mennyi ++;
            }
        }
    }
}
