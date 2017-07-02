/*********************************\
*Descrption :                     *
*                                 *
*Focntions utiles un peu partout  *
*                                 *
\*********************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "structures.h"
#include "fonctions.h"


void randomisation(int* tab, int taille)
{
	srand(time(NULL));

	int i = 0, n;
	int tab_present[] = {0, 0, 0, 0, 0, 0};

	do
	{
		n = (int)rand()%taille;
		if(tab_present[n] == 0)
		{
			tab[i] = n;
			i++;
			tab_present[n] = 1;
		}

	}while( i < taille);
}

void affiche_tab(int* tab, int taille)
{
	int i;
	for ( i = 0; i < taille; ++i)
		printf("%d\t", tab[i]);
	printf("\n");
}

void definition_parametres( int* param1, int *param2)
{
	FILE* fichier = fopen("option.txt", "r+");
	char chaine[100] = "";
	fscanf(fichier, "%d", param1);
	fgets(chaine, 100, fichier);
	fscanf(fichier, "%d", param2);
	fclose(fichier);
}

void pause()
{
	SDL_Event event;
	int continuer = 1;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
			continuer = 0;
			break;

			case SDL_KEYDOWN:
			continuer = 0;
			break;
		}
	}
}