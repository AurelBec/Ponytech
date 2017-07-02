#ifndef JEU_H
#define JEU_H

/*FONCTIONS COMMUNES*/
int menu_jeu(SDL_Surface *ecran);
void menu_option(SDL_Surface* ecran);
void menu_score(SDL_Surface *ecran);
void update_fichier_score( int score, char* nom);
void menu_entrer_nom( SDL_Surface *ecran, char *nom);
void definition_parametres( int* p1, int *p2);
void randomisation(int* tab, int taille);
void affiche_tab(int* tab, int taille);
void pause();

/*LOAD.c*/
Joueur* load_joueur(SDL_Surface *ecran);
void load_invaders(Invader *invader, int ORG_Y, int X, int Y);
void load_tir_joueur( Joueur* joueur);
void load_tir_invaders( Invader *invader);

/*UPDATE.c*/
void update_invaders(Invader *invader, int* temps_update_invaders);
void update_tir_invaders(Invader* invader);
void update_tir_joueur(Joueur* joueur);
int update_score(Invader* invader);
int check_collision( SDL_Rect* pos1, SDL_Rect* pos2);
void update_collision( Joueur* joueur, Invader* invader);
int update_is_invaded(Invader* invader);

/*DRAW.c*/
void draw_invaders(SDL_Surface *ecran, Invader *invader);
void draw_joueur(SDL_Surface* ecran, Joueur* joueur);
void draw_texte( SDL_Surface *ecran, char* chaine, int taille_police, int x, int y, int couleur);
void draw_infos_top(SDL_Surface* ecran, Joueur* joueur, Invader* invader);
void draw_changement_niveau(SDL_Surface *ecran, Joueur* joueur, int niveau);

#endif
