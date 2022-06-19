#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
/* donne un pointeur sur une case de la grille */
int * grille_case(int * grille_krusk, int x, int y, int largeur, int hauteur);
/* crée le labyrinthe avec algo kruskal*/
char * creer_grille_krusk(int largeur, int hauteur);
/* crée une grille de taille donnée */

void afficher_grille(char * grille, int largeur, int hauteur);

#pragma GCC diagnostic ignored "-Wformat-zero-length"
int main() {
    int largeur = 39, hauteur = 19;
	char * grille = creer_grille_krusk(largeur, hauteur);
    int x = 1, y = 1;
    initscr();
    noecho();
    cbreak();
    do {
        clear();
        afficher_grille(grille, largeur, hauteur);
        mvprintw(y, x-1, "@");
		mvprintw(hauteur - 2, largeur-1, "x");
		mvprintw(hauteur - 2, largeur+2, "<- sortie");
		mvprintw(y, x-1, "");
        refresh();
        getch();
        /* gestion des événements */
    } while(1);
    refresh();
    clrtoeol();
    refresh();
    endwin();
    free(grille);
    exit(EXIT_SUCCESS);
}
#pragma GCC diagnostic warning "-Wformat-zero-length"

int * grille_case(int * grille_krusk, int x, int y, int largeur, int hauteur) {
	if(grille_krusk == NULL || x < 0 || y < 0 || x >= largeur || y >= hauteur) {
		return NULL;
	}
	return grille_krusk + (x + y * largeur);
}

char * grille_case_char(char * grille, int x, int y, int largeur, int hauteur) {
	if(grille == NULL || x < 0 || y < 0 || x >= largeur || y >= hauteur) {
		return NULL;
	}
	return grille + (x + y * largeur);
}

char * creer_grille_krusk(int largeur, int hauteur) {
	int * grille_krusk = NULL;
	if((grille_krusk = (int *)malloc(sizeof(int) * largeur * hauteur)) == NULL) {
		printf("Allocation de la grille impossible.\n");
		exit(EXIT_FAILURE);
	}
	int x,y,i,j,k,l;
	// création des murs
	for(x = 0; x < largeur; ++x){
		for (y = 0; y < hauteur; ++y)
		{
			*grille_case(grille_krusk, 0, y, largeur, hauteur) = -1;
			if (y % 2 == 1){
				if(x % 2 == 1){
					*grille_case(grille_krusk, x, y, largeur, hauteur) = 0;
				}else{
					*grille_case(grille_krusk, x, y, largeur, hauteur) = -1;
				}
			}else{
				if(x % 2 == 1){
					*grille_case(grille_krusk, x, y, largeur, hauteur) = 0;
				}else{
					*grille_case(grille_krusk, x, y, largeur, hauteur) = -1;
				}
				*grille_case(grille_krusk, x, y, largeur, hauteur) = -1;
			}
			
		}
		
	}
	
	time_t t;
	srand((unsigned) time(&t));
	int nb = 0;
	//Algo Kruskal start

	//attribution des nombres aléatoires dans les cases vides
	for(i = 0; i < largeur; i++){
		for(j = 0; j < hauteur; j++){
			if(*grille_case(grille_krusk,i,j,largeur,hauteur) == 0){
				nb++;
				*grille_case(grille_krusk,i,j,largeur,hauteur) = nb;
						
			
			}
		}
	}
	//entrée sortie
	*grille_case(grille_krusk,0,1,largeur,hauteur) = 1;
	*grille_case(grille_krusk,largeur-1,hauteur-2,largeur,hauteur) = nb;

	int case1;
	int case2;
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	for(k = 1; k < hauteur - 1;k+=2){
			for(l=1; l< largeur - 1;l+=2){
				do{
					
					
					// choisir un mur
					int a = rand() % (largeur-2) +1;
					int b;

					if(a % 2 == 0){
						b = ((rand() % ((hauteur-1)/2)))* 2 + 1;
					}else{
						b = ((rand() % (((hauteur-2))/2)))* 2 + 2;
					}


					//vérifier que c'est un mur
					if(*grille_case(grille_krusk,a-1,b,largeur,hauteur)== -1){
						case1 = *grille_case(grille_krusk,a,b-1,largeur,hauteur);
						case2 = *grille_case(grille_krusk,a,b+1,largeur,hauteur);
					}else{//sinon prendre les cases à côté
						case1 = *grille_case(grille_krusk,a-1,b,largeur,hauteur);
						case2 = *grille_case(grille_krusk,a+1,b,largeur,hauteur);
					}

					if(case1 != case2){
						*grille_case(grille_krusk,a,b,largeur,hauteur) = 0;

						for(i = 1; i < largeur - 1; i+=2){
							for(j = 1; j< hauteur - 1; j+=2){
								if(*grille_case(grille_krusk,i,j,largeur,hauteur) == case2){
									*grille_case(grille_krusk,i,j,largeur,hauteur) = case1;
									
								}
							}
					}
					}

					
		
				}while(*grille_case(grille_krusk,l,k,largeur,hauteur) != case2);
				
			}
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	char * grille = NULL;
	if((grille = (char *)malloc(sizeof(char) * largeur * hauteur)) == NULL) {
		printf("Allocation de la grille impossible.\n");
		exit(EXIT_FAILURE);
	}
	int m,n;
	for(m = 0; m < largeur; m++){
		for(n = 0; n < hauteur; n++){
			if(*grille_case(grille_krusk,m,n,largeur,hauteur) == -1){
				*grille_case_char(grille,m,n,largeur,hauteur) = '#';			
			}else{
				*grille_case_char(grille,m,n,largeur,hauteur) = ' ';
			}
		}
	}
	/*
	for(y = 0; y < largeur;y++){
		for(x=0; x < hauteur ; x++){
			if(*grille_case(grille_krusk,x,y,largeur,hauteur) == -1){
				*grille_case_char(grille,x,y,largeur,hauteur) = '#';
			}else{
				*grille_case_char(grille,x,y,largeur,hauteur) = ' ';
			}
		}
	}*/

	free(grille_krusk);
	return grille;


	//return grille_krusk;
}

/*
char * creer_grille(int largeur, int hauteur) {
	int * grille_krusk = creer_grille_krusk(largeur, hauteur);
	char * grille = NULL;
	if((grille = (char *)malloc(sizeof(char) * largeur * hauteur)) == NULL) {
		printf("Allocation de la grille impossible.\n");
		exit(EXIT_FAILURE);
	}
	int m,n;
	for(m = 0; m < largeur; m++){
		for(n = 0; n < hauteur; n++){
			if(*grille_case(grille_krusk,m,n,largeur,hauteur) == -1){
				*grille_case_char(grille,m,n,largeur,hauteur) = '#';			
			}else{
				*grille_case_char(grille,m,n,largeur,hauteur) = ' ';
			}
		}
	}
	/*
	for(y = 0; y < largeur;y++){
		for(x=0; x < hauteur ; x++){
			if(*grille_case(grille_krusk,x,y,largeur,hauteur) == -1){
				*grille_case_char(grille,x,y,largeur,hauteur) = '#';
			}else{
				*grille_case_char(grille,x,y,largeur,hauteur) = ' ';
			}
		}
	}


	return grille;
}
*/
void afficher_grille(char * grille, int largeur, int hauteur) {
	int x, y;
	for(y = 0; y < hauteur; ++y) {
		for(x = 0; x < largeur; ++x) {
			mvprintw(y, x, "%c", *grille_case_char(grille, x, y, largeur, hauteur));
		}
	}
}
























