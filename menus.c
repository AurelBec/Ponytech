/************************************\
*Descrption :                        *
*                                    *
*Menus du jeu, mises a jour des menus*
*                                    *
\************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "structures.h"
#include "fonctions.h"

void menu_option(SDL_Surface *ecran)
{

/*INITIALISATION SDL*/
	srand(time(NULL));
    SDL_Event event;
    srand(time(NULL));
    SDL_EnableKeyRepeat(1000, 1000);
    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    
    SDL_Surface *fond = IMG_Load("pics/menu/menu_option_fond.png");
    SDL_Surface *line = IMG_Load("pics/menu/menu_option_line.png");
    SDL_Surface *curseur[2] = {IMG_Load("pics/menu/menu_option_curseur_0.png"), IMG_Load("pics/menu/menu_option_curseur_1.png")};
    SDL_Rect pos_fond, pos_curseur, pos_line;
    pos_fond.x = 0;
    pos_fond.y = 0;
    SDL_BlitSurface(fond, NULL, ecran, &pos_fond);

/*OUVERTURE FICHIER OPTION*/
    FILE* fichier = NULL;
    fichier = fopen("option.txt", "r+");

/*DEFINTION VARIABLES*/
    int i, j;
    char chaine[100] = "", texte_val[3] = "";
    char texte_menu[][100] = {"Nombre d'invaders en X", "Nombre d'invaders en Y", "Difficulte", "Son"};
    int option = 0;
    Option param_options[OPTION_MAX];
    for ( i = 0; i < OPTION_MAX; ++i)
    {
        fscanf(fichier, "%d\t%d \t%d" , &param_options[i].val, &param_options[i].val_min, &param_options[i].val_max);
        fgets(chaine, 100, fichier);
    }


    SDL_Flip(ecran);

/*BOUCLE DU MENU*/
    int continuer = 1;
	while (continuer)
    {

    /*EVENT*/
        SDL_WaitEvent(&event);
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
                    case SDLK_RETURN:
                        continuer = 0;
                        break;

                    case SDLK_UP:
                        option = (option == 0)? OPTION_MAX - 1 : option - 1;
                        break;
                    case SDLK_DOWN:
                        option = (option == OPTION_MAX - 1)? 0 : option + 1;
                        break;

                    case SDLK_RIGHT:
                            param_options[option].val ++;
                        break;

                    case SDLK_LEFT: 
                            param_options[option].val --;
                        break;

                    default: break;
                }
                break;
        }

    /*UPDATE*/
        if( param_options[option].val > param_options[option].val_max)
            param_options[option].val = param_options[option].val_max;
        if( param_options[option].val < param_options[option].val_min)
            param_options[option].val = param_options[option].val_min;

        SDL_BlitSurface(fond, NULL, ecran, &pos_fond);
        for ( i = 0; i < OPTION_MAX; ++i)
        {
        /*TEXTE*/
            draw_texte(ecran, texte_menu[i], 32, -1, 128*i + 64, BLANC);
        /*LIGNE*/
            for( j = 0; j < (param_options[i].val_max - param_options[i].val_min)*40; j+=8)
            {
                pos_line.x = TAILLE_X/2 - 20*(param_options[i].val_max - param_options[i].val_min) + j;
                pos_line.y = 128*i + 150;
                SDL_BlitSurface(line, NULL, ecran, &pos_line);
            }
        /*CURSEUR*/
            pos_curseur.x = TAILLE_X/2 - 20*(param_options[i].val_max - param_options[i].val_min) + 40*(param_options[i].val-param_options[i].val_min);
            pos_curseur.y = 128*i + 144;
            SDL_BlitSurface(curseur[i==option], NULL, ecran, &pos_curseur);
        /*VALEUR*/
            snprintf(texte_val, 3, "%d", param_options[i].val);
            draw_texte(ecran, texte_val, 24, TAILLE_X/2 + 20*(param_options[i].val_max - param_options[i].val_min) + 40, 128*(i+1), BLANC);
        }

        SDL_Flip(ecran);
    }

/*UPDATE FICHIER OPTION */
    rewind(fichier);
    fprintf(fichier, "%d\t%d\t%d\t#mob_nb_x\n", param_options[0].val, param_options[0].val_min, param_options[0].val_max);
    fprintf(fichier, "%d\t%d\t%d\t#mob_nb_y\n", param_options[1].val, param_options[1].val_min, param_options[1].val_max);
    fprintf(fichier, "%d\t%d\t%d\t#difficulte\n", param_options[2].val, param_options[2].val_min, param_options[2].val_max);
    fprintf(fichier, "%d\t%d\t%d\t#son\n", param_options[3].val, param_options[3].val_min, param_options[3].val_max);
    fclose(fichier);


/*LIBERATIONS DE MEMOIRE*/
    SDL_FreeSurface(curseur[0]);
    SDL_FreeSurface(curseur[1]);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(line);

    //SDL_Quit();

    return;
}

void menu_score(SDL_Surface *ecran)
{
    int i, nb_score, score;
    char line[100], nom[100], buffer[100];

    FILE* fichier = fopen("score.txt", "r+");
    fscanf(fichier, "%d", &nb_score);
    if(nb_score > 5) nb_score = 5;
    fgets(buffer, 100, fichier);


/*MEILLEUR SCORE*/
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    draw_texte(ecran, "Meilleur score", 64, 200, 50, 0);

    fscanf(fichier, "%d\t", &score);
    fgets(nom, 100, fichier);
    nom[strlen(nom) - 1] = '\0';
    snprintf(line, 100, "%s : %d", nom, score);
    draw_texte(ecran, line, 48, 200, 180, BLANC);

/*AFFICHAGE SCORES SUIVANTS*/
    for( i = 1; i < nb_score; ++i)
    {
        fscanf(fichier, "%d\t", &score);
        fgets(nom, 100, fichier);
        nom[strlen(nom) - 1] = '\0';
        snprintf(line, 100, "%s : %d", nom, score);
        draw_texte(ecran, line, 32, 250, 300 + 60*i, BLANC);
    }

    SDL_Flip(ecran);
    pause();

    fclose(fichier);
}

void update_fichier_score(int score, char* nom)
{
    int i, nb_score, tab_score[100], pos_score = -1;
    char **fichier_temp, buffer[100];

    FILE* fichier = fopen("score.txt", "r+");
    fscanf(fichier, "%d", &nb_score);
    fichier_temp = (char **) malloc( (nb_score + 2) * sizeof(char*));
    for( i = 0; i < nb_score + 2; ++i)
        fichier_temp[i] = (char*) malloc(100*sizeof(char));

/*Copie du fichier*/
    rewind(fichier);
    for (i = 0; i < nb_score + 2; ++i)
        fgets(fichier_temp[i], 100, fichier);
        //printf("%s", fichier_temp[i]);

    rewind(fichier);
    for ( i = 0; i < nb_score; ++i)
    {
        fgets(buffer, 100, fichier);
        fscanf(fichier, "%d\t", &tab_score[i]);

        if( score >= tab_score[i] && pos_score == -1)
            pos_score = i + 1;
    }

    //On ajoute un score au fichier
    if (pos_score != -1)
    {
    	rewind(fichier);
        for ( i = 0; i < pos_score; ++i)
            fprintf(fichier, "%s", fichier_temp[i]);

        fprintf(fichier, "%d\t%s\n", score, nom);
        //fprintf(fichier, "test\n" );

    	for ( i = pos_score; i < nb_score; ++i)
            fprintf(fichier, "%s", fichier_temp[i]);
    }

    rewind(fichier);
    fprintf(fichier, "%d", nb_score + 1);

    //affiche_tab(tab_score, 5);
    //printf("pos : %d\nval : %d\n", pos_score, debug);

    for ( i = 0; i < nb_score + 2; ++i)
        free(fichier_temp[i]);
    free(fichier_temp);
    fclose(fichier);
}

void menu_entrer_nom( SDL_Surface *ecran,  char* name)
{

    SDL_EnableUNICODE(1);
    SDL_Event event;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    draw_texte(ecran, "Entrer votre nom :", 32, 200, 50, 0);

    int continuer = 1, cursor_pos = 0;
    //char name_end[] = "__________";
	char name_extended[100];
    while (continuer)
    {        
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                    continuer = 0;
                    break;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
	                case SDLK_RETURN:
	                case SDLK_ESCAPE:
	                    continuer = 0;
	                    break;
	                case SDLK_BACKSPACE:
						/*if( cursor_pos != TAILLE_NOM)	*/cursor_pos--;
	                    if (cursor_pos < 0) 			cursor_pos = 0;
                        name[cursor_pos] = '\0';
	                    break;

	                default:
	                    if (event.key.keysym.unicode < 0x80 && event.key.keysym.unicode > 0)
	                    {
	                        name[cursor_pos] = (char) event.key.keysym.unicode;
	                        name[cursor_pos + 1] = '\0';
	                        cursor_pos++;
	                        /*if (cursor_pos > TAILLE_NOM) cursor_pos = TAILLE_NOM*/;
	                    }
	                    break;
                }
            }

        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        draw_texte(ecran, "Entrer votre nom :", 32, 200, 50, 0);
		snprintf(name_extended, 100, ">%s", name);
        draw_texte(ecran, name_extended, 24, 200, 200, BLANC);
        SDL_Flip(ecran);
        SDL_Delay(50);
    }

	name[cursor_pos+1] = '\0';

}