#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "structures.h"
#include "fonctions.h"


void draw_invaders(SDL_Surface *ecran, Invader *invader)
{
    int i, j, MOB_NB_X = invader[0].nbx, MOB_NB_Y = invader[0].nby;
    for (i = 0; i < MOB_NB_X; ++i)
        for (j = 0; j < MOB_NB_Y; ++j)
        { 
        	if( invader[i + MOB_NB_X*j].is_alive)
          		SDL_BlitSurface(invader[i + MOB_NB_X*j].surface, NULL, ecran, &invader[i+MOB_NB_X*j].pos);
          	if( invader[i + MOB_NB_X*j].tir->load)
          		SDL_BlitSurface(invader[i + MOB_NB_X*j].tir->surface, NULL, ecran, &invader[i+MOB_NB_X*j].tir->pos);
        }
}


void draw_infos_top(SDL_Surface *ecran, Joueur* joueur, Invader* invader)
{
    char texte[] = "";

    snprintf(texte, 100, "Score : %d", joueur->score + update_score(invader));
    draw_texte(ecran, texte, 10, 10, 10, BLANC);

    snprintf(texte, 100, "Vies : %d", joueur->nb_live);
    draw_texte(ecran, texte, 10, 1125, 10, BLANC);
}

void draw_texte( SDL_Surface *ecran, char* chaine, int taille_police, int x, int y, int couleur)
{
	TTF_Font *police = TTF_OpenFont("fonts/8-bit.ttf", taille_police);
    SDL_Color color[2] = { {255, 255, 255, 255}, {255, 0, 0, 255}};
    SDL_Surface *texte = TTF_RenderText_Blended(police, chaine, color[couleur]);
    SDL_Rect pos;
	
	if( x == -1)
		pos.x = TAILLE_X/2 - texte->w/2;
	else
		pos.x = x;
	if( y == -1)
		pos.y = TAILLE_Y/2 - texte->h/2;
	else
		pos.y = y;
	
	SDL_BlitSurface(texte, NULL, ecran, &pos);

	SDL_FreeSurface(texte);
    TTF_CloseFont(police);
}

void draw_joueur(SDL_Surface *ecran, Joueur* joueur)
{
    SDL_BlitSurface(joueur->surface[joueur->orientation], NULL, ecran, &joueur->pos);

    if(joueur->tir->load)
        SDL_BlitSurface(joueur->tir->surface, NULL, ecran, &joueur->tir->pos);
}

void draw_changement_niveau(SDL_Surface *ecran, Joueur* joueur, int niveau)
{
    int i;
    char texte_niveau[100];

    SDL_Surface *fond = IMG_Load("pics/fond_5.png");
    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;

    snprintf(texte_niveau, 100, "Niveau %d !", niveau+1);

    for( i = 0; i < 64; ++i)
    {
        SDL_BlitSurface(fond, NULL, ecran, &pos_fond);
        draw_texte(ecran, texte_niveau, i, -1, -1, BLANC);
        draw_joueur(ecran, joueur);
        SDL_Flip(ecran);
        SDL_Delay(12);
    }
}