#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "structures.h"
#include "fonctions.h"


void load_invaders(Invader *invader, int ORG_Y, int MOB_NB_X, int MOB_NB_Y)
{

    SDL_Surface* SPRITE_INVADERS[6] = {
        IMG_Load("pics/mobs/sprite_mob_0_36x36.png"),
        IMG_Load("pics/mobs/sprite_mob_1_36x36.png"),
        IMG_Load("pics/mobs/sprite_mob_2_36x36.png"),
        IMG_Load("pics/mobs/sprite_mob_3_36x36.png"),
        IMG_Load("pics/mobs/sprite_mob_4_36x36.png"),
        IMG_Load("pics/mobs/sprite_mob_5_36x36.png"),
    };

    SDL_Surface* SPRITE_TIRS[6] = {
        IMG_Load("pics/mobs/sprite_tir_0_16x24.png"),
        IMG_Load("pics/mobs/sprite_tir_1_16x24.png"),
        IMG_Load("pics/mobs/sprite_tir_2_16x24.png"),
        IMG_Load("pics/mobs/sprite_tir_3_16x24.png"),
        IMG_Load("pics/mobs/sprite_tir_4_16x24.png"),
        IMG_Load("pics/mobs/sprite_tir_5_16x24.png"),        
    };

    int i, j;
    int rand[6] = {0, 1, 2, 3, 4, 5};
    randomisation(rand,6);


    for (i = 0; i < MOB_NB_X; ++i)
    {
    	for (j = 0; j < MOB_NB_Y; ++j)
    	{
    		invader[i + MOB_NB_X*j].surface = SPRITE_INVADERS[rand[j]];
    		invader[i + MOB_NB_X*j].is_alive = 1;
    		invader[i + MOB_NB_X*j].pos.x = MOB_ORG_X + i * MOB_ESP_X;
    		invader[i + MOB_NB_X*j].pos.y = MOB_ORG_X + j * MOB_ESP_Y + ORG_Y;
            invader[i + MOB_NB_X*j].pos.w = invader[i + MOB_NB_X*j].surface->w;
            invader[i + MOB_NB_X*j].pos.h = invader[i + MOB_NB_X*j].surface->h;
            invader[i + MOB_NB_X*j].vit_x = MOB_VIT_X;
            invader[i + MOB_NB_X*j].nbx = MOB_NB_X;
            invader[i + MOB_NB_X*j].nby = MOB_NB_Y;

            invader[i + MOB_NB_X*j].tir = (Tir*) malloc(sizeof(Tir));
            invader[i + MOB_NB_X*j].tir->surface = SPRITE_TIRS[rand[j]];
            invader[i + MOB_NB_X*j].tir->load = 0;
            invader[i + MOB_NB_X*j].tir->vit_y = - JOUEUR_TIR_VIT_Y;
    	}
    }
}

Joueur* load_joueur(SDL_Surface *ecran)
{
    Joueur* joueur = (Joueur*) malloc(sizeof(Joueur));

    joueur->surface[TOP] = IMG_Load("pics/perso/sprite_perso_top_48x48.png"); 
    joueur->surface[RIGHT] = IMG_Load("pics/perso/sprite_perso_right_48x48.png");
    joueur->surface[LEFT] = IMG_Load("pics/perso/sprite_perso_left_48x48.png");

    joueur->pos.x = ecran->w/2 - joueur->surface[0]->w/2;
    joueur->pos.y = ecran->h - joueur->surface[0]->h - 10;
    joueur->pos.w = joueur->surface[0]->w;
    joueur->pos.h = joueur->surface[0]->h;

    joueur->nb_live = JOUEUR_NB_VIE;
    joueur->score = 0;
    joueur->orientation = TOP;
    joueur->vit_x = JOUEUR_VIT_X;
    joueur->last_move = SDL_GetTicks();

    joueur->tir = (Tir*) malloc(sizeof(Tir));
    joueur->tir->surface = IMG_Load("pics/arduino.png");
    joueur->tir->load = 0;
    joueur->tir->vit_y = JOUEUR_TIR_VIT_Y;

    return joueur;
}

void load_tir_joueur( Joueur* joueur)
{
    joueur->tir->load = 1;
    joueur->tir->pos.w = joueur->tir->surface->w;
    joueur->tir->pos.h = joueur->tir->surface->h;
    joueur->tir->pos.x = joueur->pos.x + joueur->pos.w/2 - joueur->tir->pos.w/2;
    joueur->tir->pos.y = joueur->pos.y - joueur->tir->pos.h - 10;
}

void load_tir_invaders( Invader *invader)
{
    invader->tir->load = 1;
    invader->tir->pos.w = invader->tir->surface->w;
    invader->tir->pos.h = invader->tir->surface->h;
    invader->tir->pos.x = invader->pos.x + invader->pos.w/2 - invader->tir->pos.w/2;
    invader->tir->pos.y = invader->pos.y + invader->tir->pos.h + 10;
}
