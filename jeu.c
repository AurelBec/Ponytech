/*********************************\
*Descrption :                     *
*                                 *
*Lancement du jeu                 *
*                                 *
\*********************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "structures.h"
#include "fonctions.h"

int menu_jeu(SDL_Surface *ecran)
{

/*INITIALISATION SDL*/
	srand(time(NULL));
    SDL_Event event;
    srand(time(NULL));
    SDL_EnableKeyRepeat(1000, 1000);

    SDL_Surface *fond = IMG_Load("pics/fond_5.png");
    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    SDL_BlitSurface(fond, NULL, ecran, &pos_fond);

/*DEFINTION VARIABLES*/
    int temps_update_invaders = SDL_GetTicks();
    int niveau = 0;
    int i;

/*DEFINITION PARAMETRES*/
    int MOB_NB_X, MOB_NB_Y;
    definition_parametres(&MOB_NB_X, &MOB_NB_Y);

/*CHARGEMENT DES ENTITES*/
//TODO : ameliorer loading des invaders (pointeur sur structures)
    Invader* invader = (Invader*) malloc(sizeof(Invader) * MOB_NB_TOT);
    load_invaders(invader, 0, MOB_NB_X, MOB_NB_Y);
    Joueur* joueur = load_joueur(ecran);

/*BOUCLE DE JEU*/
    SDL_Flip(ecran);
    //draw_changement_niveau(niveau, ecran, joueur);
    int continuer = 1;
    
	while (continuer && joueur->nb_live)
    {

    /*EVENT*/
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                /*FLECHE DU HAUT : ON TIRE*/
                    case SDLK_UP:
                        joueur->orientation = TOP;
                        if( !joueur->tir->load)
                        {
                            load_tir_joueur(joueur);
                            //printf("TJ : %d %d\n", joueur->tir->pos.w, joueur->tir->pos.h);
                        }
                        break;

                /*FLECHE DE DROITE : ON BOUGE VERS LA DROITE*/
                    case SDLK_RIGHT:
                        joueur->pos.x += (joueur->pos.x >= TAILLE_X - joueur->surface[TOP]->w - 50)? 0 : joueur->vit_x;
                        joueur->orientation = RIGHT;
                        joueur->last_move = SDL_GetTicks();
                        break;

                /*FLECHE DE GAUCHE : ON BOUGE VERS LA GAUCHE*/
                    case SDLK_LEFT:
                        joueur->pos.x -= (joueur->pos.x <= 50)? 0 : joueur->vit_x;
                        joueur->orientation = LEFT;
                        joueur->last_move = SDL_GetTicks();
                        break;

                    default: 
                        joueur->orientation = TOP;
                        break;
                }
                break;
        }

    /*UPDATE*/
        update_invaders(invader, &temps_update_invaders);
        update_tir_invaders(invader);
        update_tir_joueur(joueur);
        update_collision(joueur, invader);

        /*FIN DE NIVEAU*/
        if( update_score(invader) == MOB_NB_TOT )
        {    
            joueur->score += MOB_NB_TOT;
            niveau ++;

            MOB_NB_X += (niveau%3 == 0);
            MOB_NB_Y += (niveau%5 == 0);
            if(MOB_NB_Y > 6)  MOB_NB_Y = 6;
            if(MOB_NB_X > 15) MOB_NB_X = 15;

            free(invader);
            invader = (Invader*) malloc(sizeof(Invader) * MOB_NB_TOT);
            load_invaders(invader, (niveau > 20)? 100:(niveau*5), MOB_NB_X, MOB_NB_Y);

            draw_changement_niveau(ecran, joueur, niveau);
        }

        if( update_is_invaded( invader))
            continuer = 0;

        if( joueur->nb_live == 0)
            continuer = 0;

        if( !continuer )
            break;

        if( SDL_GetTicks() - joueur->last_move > 150)
            joueur->orientation = TOP;

    /*DRAW*/
        SDL_BlitSurface(fond, NULL, ecran, &pos_fond);
        draw_invaders(ecran, invader);
        draw_joueur(ecran, joueur);
        draw_infos_top(ecran, joueur, invader);
        SDL_Flip(ecran);
    }

/*FIN DU JEU*/
    int score_fin = joueur->score + update_score(invader);

/*LIBERATIONS DE MEMOIRE*/
    for (i = 0; i < 3; ++i)
        SDL_FreeSurface(joueur->surface[i]);
    SDL_FreeSurface(joueur->tir->surface);
    free(joueur->tir);

    for( i = 0; i < MOB_NB_Y; ++i)
    {
        SDL_FreeSurface(invader[MOB_NB_X*i].surface);
        SDL_FreeSurface(invader[MOB_NB_X*i].tir->surface);
        free(invader[MOB_NB_X*i].tir);
    }

    free(joueur);
    free(invader);
    //SDL_Quit();

    return score_fin;
}