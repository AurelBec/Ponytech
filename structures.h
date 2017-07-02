#ifndef STRUCT_H
#define STRUCT_H

typedef struct tir
{
	SDL_Surface* surface;
	SDL_Rect pos;
	int vit_y;
	int load; //0 si pas afficher 1 sinon
} Tir;

typedef struct joueur
{
	SDL_Surface *surface[3];
	SDL_Rect pos;
	
	int nb_live;
	int score;
	int orientation;
	int last_move;
	int vit_x;

	Tir* tir;

} Joueur;


typedef struct invader
{
	SDL_Surface *surface;
	SDL_Rect pos;

	int nbx;
	int nby;

	int is_alive;
	float vit_x;

	Tir* tir;

} Invader;

typedef struct option
{
	int val;
	int val_min;
	int val_max;
	int pas;
} Option;

#endif
