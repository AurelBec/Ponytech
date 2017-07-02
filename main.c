/*********************************\
*Descrption :                     *
*                                 *
*Lancement initial, menu principal*
*                                 *
\*********************************/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "structures.h"
#include "fonctions.h"

int main()
{
/*INITIALISATION SDL, TTF ET FENETRE DE JEU*/
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_WM_SetCaption("ROBinvader", NULL);
    SDL_Surface *ecran = SDL_SetVideoMode(TAILLE_X, TAILLE_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_Event event;

/*DEFINITION VARIABLES*/
    int continuer = 1, selection = 0, score = 0, i;
    char name[100] = "";


/*LOADING DU MENU*/
    char texte_menu[][100] = {"Jouer", "Score", "Options", "Quitter"};
    SDL_Surface	*menu = IMG_Load("pics/menu/menu_fond.png");
    SDL_Rect pos_menu;
    pos_menu.x = 0; pos_menu.y = 0;
    SDL_BlitSurface(menu, NULL, ecran, &pos_menu);

/*BOUCLE DE MENU*/
	while (continuer)
    {

    /*UPDATE ITEMS MENU*/
        SDL_BlitSurface(menu, NULL, ecran, &pos_menu);
        draw_texte(ecran, "- ROBINVADER -", 64, -1, 15, BLANC);
        for( i = 0; i < MENU_MAX_SELECTION; ++i)
            draw_texte(ecran, texte_menu[i], 32, -1, TAILLE_Y/2 + 90 + 55*i, selection == i);
        SDL_Flip(ecran);

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        selection = (selection == 0)? MENU_MAX_SELECTION - 1 : selection - 1;
                        break;
                    case SDLK_DOWN:
                        selection = (selection == MENU_MAX_SELECTION - 1)? 0 : selection + 1;
                        break;
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_RETURN:
                        switch(selection)
                        {
                            case 0:
                                score = menu_jeu(ecran);

                                for( i = 0; i < 100; ++i)
                                    name[i] = '\0';
                                menu_entrer_nom(ecran, name);
                                update_fichier_score(score, name);

                                continuer = 1;
                                break;

                            case 1:
                                menu_score(ecran);
                                break;

                            case 2:
                                menu_option(ecran);
                                break;

                            case 3:
                                continuer = 0;
                                break;
                            default: break;
                        }
                        break;
                    default: break;
                }
                break;
        }
    }

/*FIN DU JEU*/
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    for(i = 50; i >= 0; --i, SDL_Delay(2))
    {
        SDL_BlitSurface(menu, NULL, ecran, &pos_menu);
        draw_texte(ecran, "Merci d'avoir joue !", i, -1, 500, 0);
        SDL_Flip(ecran);
    }

/*LIBERATIONS DE MEMOIRE*/
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
