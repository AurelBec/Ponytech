#ifndef CONSTANTES_H
#define CONSTANTES_H


enum {HAUT, BAS, GAUCHE, DROITE};
enum {TOP, RIGHT, LEFT};
enum {BLANC, ROUGE};
//enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

/* FENETRE DE JEU */
#define TAILLE_X 			1200
#define TAILLE_Y 			675

/* MENU */
#define MENU_MAX_SELECTION 	4
#define OPTION_MAX			4
#define SCORE_MAX          5
#define TAILLE_NOM	9

/* JEU */
#define MOB_ESP_X        	50
#define MOB_ESP_Y        	40
#define MOB_ORG_X			MOB_ESP_X
#define MOB_ORG_Y			20
#define MOB_NB_TOT			(MOB_NB_X * MOB_NB_Y)
#define MOB_VIT_X			8
#define MOB_ACC_X  			1.04
#define MOB_VIT_Y			10
#define MOB_DELAI_UPDATE	100

#define JOUEUR_NB_VIE		3
#define JOUEUR_VIT_X		10
#define JOUEUR_TIR_VIT_Y	-10

#define JOUEUR_DELAI_TIR	1000

#endif