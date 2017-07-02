#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "structures.h"
#include "fonctions.h"


void update_invaders(Invader *invader, int* temps_update_invaders)
{
    int id_first_x, id_last_x, is_colomn_alive, MOB_NB_X = invader[0].nbx, MOB_NB_Y = invader[0].nby;
    int i, j;

/*CALCUL DE LA 1ERE COLONNE ENCORE VIVANTE*/
    for( i = 0, is_colomn_alive = 0; i < MOB_NB_X && is_colomn_alive == 0; ++i)
    {
        for( j = 0; j < MOB_NB_Y; ++j)
            if( invader[MOB_NB_X*j + i].is_alive)
                is_colomn_alive = 1;
        if(is_colomn_alive)
            id_first_x = i;
    }
/*CALCUL DE LA DERNIERE COLONNE ENCORE VIVANTE*/
    for( i = MOB_NB_X-1, is_colomn_alive = 0; i >= 0 && is_colomn_alive == 0; --i)
    {
        for( j = 0; j < MOB_NB_Y; ++j)
            if( invader[MOB_NB_X*j + i].is_alive)
                is_colomn_alive = 1;
        if(is_colomn_alive)
            id_last_x = i;
    }

/*UPDATE POSITION INVADER*/
    if( SDL_GetTicks() - *temps_update_invaders > MOB_DELAI_UPDATE)
    {
        *temps_update_invaders = SDL_GetTicks();

        /*UPDATE POS REFERENCE*/
		invader[0].pos.x += invader[0].vit_x;
	    if( invader[id_first_x].pos.x + invader[0].vit_x < 10 || invader[id_last_x].pos.x + invader[0].vit_x + invader[0].surface->w > TAILLE_X - 10)
	    {
	    	invader[0].pos.y += MOB_VIT_Y;
			invader[0].pos.x -= invader[0].vit_x;
	    	invader[0].vit_x *= - MOB_ACC_X;
	    }

        /*UPDATE DES INVADERS*/
        for (i = 0; i < MOB_NB_X; ++i)
            for (j = 0; j < MOB_NB_Y; ++j)
            {
                invader[i + MOB_NB_X*j].pos.x = invader[0].pos.x + i*MOB_ESP_X;
                invader[i + MOB_NB_X*j].pos.y = invader[0].pos.y + j*MOB_ESP_Y;
            }
    }
}

/*int collision_tir_joueur(Tir* tir, Invader* invader)
{
    int i, MOB_NB_X = invader[0].nbx, MOB_NB_Y = invader[0].nby;

    for( i = 0; i < MOB_NB_TOT; ++i)
    {
        if( invader[i].is_alive == 1)
        if( ((tir->pos.x > invader[i].pos.x && tir->pos.x < invader[i].pos.x + invader[i].surface->w)
            || (tir->pos.x + tir->surface->w > invader[i].pos.x && tir->pos.x + tir->surface->w < invader[i].pos.x + invader[i].surface->w) )
            && (tir->pos.y > invader[i].pos.y && tir->pos.y < invader[i].pos.y + invader[i].surface->h) )
        {
            return i;
        }
    }

    return -1; // Pas de collision
}*/

/*int collision_tir_invader(Tir* tir, Joueur* joueur)
{
    if( (tir->pos.y + tir->surface->h > joueur->pos.y) && (tir->pos.y < joueur->pos.y + joueur->surface[0]->h) )
        if( (tir->pos.x > joueur->pos.x && tir->pos.x < joueur->pos.x + joueur->surface[0]->w) 
            || (tir->pos.x + tir->surface->w > joueur->pos.x && tir->pos.x + tir->surface->w < joueur->pos.x + joueur->surface[0]->w) )
            return 1;
    return -1; // Pas de collision
}*/

/*int collision_tirJ_tirI( Tir* tirJ, Tir* tirI)
{
    tirJ->pos.w = tirJ->pos.x + tirJ->surface->w;
    tirJ->pos.h = tirJ->pos.y + tirJ->surface->h;
    tirI->pos.w = tirI->pos.x + tirI->surface->w;
    tirI->pos.h = tirI->pos.y + tirI->surface->h;

    if( tirI->pos.h < tirJ->pos.y || tirI->pos.y > tirJ->pos.h || tirI->pos.w < tirJ->pos.x || tirI->pos.x > tirJ->pos.w)
        return -1; // Pas de collision
    else
        return 1;
}*/

int check_collision( SDL_Rect* pos1, SDL_Rect* pos2)
{
    if( (pos2->y + pos2->h <= pos1->y) || (pos2->y >= pos1->x + pos1->h) || (pos2->x + pos2->w <= pos1->x) || (pos2->x >= pos1->x + pos1->w) )
        return 0; // Pas de collision
    else
        return 1;
}

int update_score(Invader* invader)
{
    int score = 0, i, MOB_NB_X = invader[0].nbx, MOB_NB_Y = invader[0].nby;

    for( i = 0; i < MOB_NB_TOT; ++i)
        if( !invader[i].is_alive )
            score ++;

    return score;
}


void update_tir_joueur( Joueur* joueur)
{
    if(joueur->tir->load)
    {
        joueur->tir->pos.y += joueur->tir->vit_y;

        if(joueur->tir->pos.y < 0)
            joueur->tir->load = 0;
    }
}

void update_tir_invaders(Invader* invader)
{
    int i, j, MOB_NB_X = invader[0].nbx, MOB_NB_Y = invader[0].nby;
    int id_last_y[15];

/*RECUPERATION ID DERNIER MOB VIVANT DE LA COLONNE*/
    for(i = 0; i < MOB_NB_X; i++)
    {
        id_last_y[i] = -1;
        for( j = 0; j < MOB_NB_Y; j++)
            if(invader[i + MOB_NB_X*j].is_alive)
                id_last_y[i] = j;

    }

/*LOAD DES TIRS*/
    for ( i = 0; i < MOB_NB_X; ++i)
        if( id_last_y[i] != -1 && invader[i + MOB_NB_X*id_last_y[i]].tir->load == 0)
            if( (int)rand()%500 == 0)
                load_tir_invaders( &invader[i + MOB_NB_X*id_last_y[i]]);

/*UPDATE DES TIRS*/
    for( i = 0; i < MOB_NB_TOT; ++i)
        if(invader[i].tir->load)
        {
            invader[i].tir->pos.y += 1;

            if(invader[i].tir->pos.y > TAILLE_Y)
                invader[i].tir->load = 0;
        }

}

void update_collision( Joueur* joueur, Invader* invader)
{
    int i, MOB_NB_X = invader[0].nbx, MOB_NB_Y = invader[0].nby;

    for( i = 0; i < MOB_NB_TOT; ++i)
    {
        // COLLISION TIR - TIR //
        if( invader[i].tir->load && joueur->tir->load)
            if( check_collision(&joueur->tir->pos, &invader[i].tir->pos))
            {
                joueur->tir->load = 0;
                invader[i].tir->load = 0;
            }

        // COLLISION TIR - JOUEUR //
        if(invader[i].tir->load)    
        {
            if( check_collision(&joueur->pos, &invader[i].tir->pos) )
            {
                joueur->nb_live --;
                invader[i].tir->load = 0;
            }
        }

        // COLLISION TIR - INVADER //
        if( invader[i].is_alive && joueur->tir->load)
            if( check_collision(&joueur->tir->pos, &invader[i].pos) )
            {
                joueur->tir->load = 0;
                invader[i].is_alive = 0;
            }
    }
}

int update_is_invaded(Invader* invader)
{
    int i, j, MOB_NB_X = invader[0].nbx, MOB_NB_Y = invader[0].nby;
    int id_last_y[15];

/*RECUPERATION ID DERNIER MOB VIVANT DE LA COLONNE*/
    for(i = 0; i < MOB_NB_X; i++)
    {
        id_last_y[i] = -1;
        for( j = 0; j < MOB_NB_Y; j++)
            if(invader[i + MOB_NB_X*j].is_alive)
                id_last_y[i] = j;

    }

    for( i = 0; i < MOB_NB_X; ++i)
        if( id_last_y[i] != -1)
            if( invader[id_last_y[i]].pos.y + invader[id_last_y[i]].pos.h > TAILLE_Y - 50)
                return 1;

    return 0;
}

