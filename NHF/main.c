#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "jatekmotor.h"
#include "din_mem.h"


Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

void tabla_rajzol (bool ** jatek, int db_w, int db_h, int w, int h, SDL_Surface *screen){
    int i, j;
    int rw = w/db_w;
    int rh = h/db_h;
    for (i = 1; i <= db_w; i++)
        {
            for (j = 1; j <= db_h; j++)
            {
                if (jatek[i][j])
                    boxRGBA(screen, i*rw, j*rh, (i+1)*rw, (j+1)*rh-1, 250, 250, 240, 255);
                else
                    boxRGBA(screen, i*rw, j*rh, (i+1)*rw, (j+1)*rh-1, 10, 10, 50, 255);
            }
        }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    SDL_Event event;
    SDL_Surface *screen;
    SDL_TimerID id;

    int mX, mY,                 /**< mouse X és Y koordinátái */
    tX, tY,                     /**< mouseX és mouseY megfeleltetése a játéktábla tX, tY elemeinek */
//    i, j,                       /**< ciklusváltozók */
    w = 800, h = 600,           /**< width, height */
    db_w = 50, db_h = 50;       /**< rows, coloumns */

    bool ** jatek;
    kep_letrehoz(&jatek, db_w, db_h);

    bool vege = false, szunet = true; /**< a játék állapotát jelző logikai változók */

    /* SDL inicializálása és ablak megnyitása */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(1080, h, 0, SDL_ANYFORMAT);
    if (!screen)
    {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Conway's game of life", "Conway's game of life");

    /* játék rajzolása*/
    jatek = kov_kep(jatek, db_w, db_h);
    tabla_rajzol(jatek, db_w, db_h, w, h, screen);

    /* menü */
    stringRGBA(screen, 930, 20, "MENU", 4, 123, 93, 255);
    stringRGBA(screen, 930, 70, "PAUSE", 4, 123, 93, 255);
    stringRGBA(screen, 930, 120, "NEXT STEP", 4, 123, 93, 255);
    stringRGBA(screen, 930, 170, "QUIT", 4, 123, 93, 255);

    /* eddig elvegzett rajzolasok a kepernyore */
    SDL_Flip(screen);
    /* idozito hozzaadasa: 500 ms; 1000 ms / 500 ms -> 2 fps */
    id = SDL_AddTimer(500, idozit, NULL);
    /* event loop */
    while (!vege)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        /* felhasznaloi esemeny: ilyeneket general az idozito fuggveny */
        case SDL_USEREVENT:
            if (!szunet){
                jatek = kov_kep(jatek, db_w, db_h);
                tabla_rajzol(jatek, db_w, db_h, w, h, screen);
                SDL_Flip(screen);
            }
            break;
        case SDL_QUIT:
            vege = true;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_p)
                szunet = !szunet;
            else if (event.key.keysym.sym == SDLK_ESCAPE)
                vege = true;
            else if ((event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_KP_ENTER) && szunet == true)
                jatek = kov_kep(jatek, db_w, db_h);
                tabla_rajzol(jatek, db_w, db_h, w, h, screen);
                SDL_Flip(screen);
            break;
        case SDL_MOUSEBUTTONUP: // kétfélét kezelünk, jobbklikk feléleszt, balklikk megöl
            mX = event.button.x;
            mY = event.button.y;
            if (mX > w)
            {
                if (mX > w + 130 && mX < 1000){
                    if (mY > 70 && mY < 90)
                        szunet = !szunet;
                    else if (mY > 120 && mY < 140){
                        jatek = kov_kep(jatek, db_w, db_h);
                        tabla_rajzol(jatek, db_w, db_h, w, h, screen);
                        SDL_Flip(screen);
                    }
                    else if (mY > 170 && mY < 190)
                        vege = true;
                }
            }
            else if (mX <= w && szunet == true)
            {
                tX = 1 + mX / (w/db_w);
                tY = 1 + mY / (h/db_h);
                if (event.button.button == SDL_BUTTON_LEFT)
                    jatek[tX-1][tY-1] = false;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    jatek[tX-1][tY-1] = true;
            }
            tabla_rajzol(jatek, db_w, db_h, w, h, screen);
            SDL_Flip(screen);
            break;
        }
    }

    /* ablak bezarasa */
    free(jatek);
    SDL_RemoveTimer(id);
    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}
