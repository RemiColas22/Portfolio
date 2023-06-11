// Programme qui permer de jouer au Puissance 4

//-----------------------------definition---------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

const char PION_A = 'R';
const char PION_B = 'J';
const char VIDE = ' ';
const char INCONNU = ' ';
#define NB_LIG 6
#define NB_COL 7
typedef char Grille[NB_LIG][NB_COL];

void initGrille (Grille);
void afficher(Grille,char,int,int);
bool grillePleine(Grille);
void jouer(Grille,char,int*,int*);
int choisirColonne(Grille,char);
int trouveLigne(Grille,int);
bool estVainqueur(Grille,int,int,char);
void finDePartie(char);
char joueur_aleatoire();
void sauvegarde(int,int);

// ------------------------------programme-----------------------------

int main(){
    char stop;
    char poubelle;  // empeche le retour chariot
    char vainqueur;
    char pion;
    char sauv;
    int ligne;
    int colonne;
    int score_a;
    int score_b;
    bool partie;

    Grille g;
    score_a = 0;
    score_b = 0;
    
    printf("Bienvenues sur puissance4, les règles sont simples, le premier qui arrive à aligner 4 cases de sa couleur gagne.\nVoulez-vous jouer? (O pour Oui)\n") ;
    scanf("%c%c",&stop,&poubelle);
    while(stop == 'O'){
        partie = true;
        pion = joueur_aleatoire();
        printf("Le premier joueur est le joueur %c (choisie aléatoirement)\n",pion);
        initGrille(g);
        vainqueur = INCONNU;
        while(vainqueur == INCONNU && !grillePleine(g)){
            jouer(g,pion,&ligne,&colonne);
            afficher(g,pion,score_a,score_b);
            if (estVainqueur(g,ligne,colonne,pion)){
                vainqueur = pion;
                if (pion == PION_A ){ // Le vainqueur voit son score augemener de 1
                    score_a++;
                }
                else {
                    score_b++;
                }
            }
            if (pion == PION_A ){       // changement de joueur
                pion = PION_B;
            }
            else{
                pion = PION_A;
            }
        }
        finDePartie(vainqueur);
        printf("Voulez-vous recommencer une partie? (O pour Oui)\n");
        scanf("%c%c",&poubelle,&stop);
    }
    if(partie == true){
        printf("Le score final est donc de %d a %d.\nVoulez-vous sauvegarder les résultats dans un fichier score.txt?(O pour Oui)\n",score_a,score_b);
        scanf("%c%c",&poubelle,&sauv);
        if (sauv == 'O'){
            sauvegarde(score_a,score_b);
        }
    }
    printf("A plus tard!\n");
    return EXIT_SUCCESS;
}   


//----------------------------------fonction et procedure-----------------------------

void initGrille(Grille g){

    //Initialise la grille en affectant la constante VIDE à chacun de ses éléments.
    
    int colonne;
    int ligne;
    for (ligne = 0;ligne < NB_LIG;ligne++){
        for(colonne = 0;colonne < NB_COL;colonne++){
            g[ligne][colonne] = VIDE;
        }
    }
}

void afficher(Grille g,char pion,int score_a,int score_b){

    //Réalise l’affichage à l’écran du contenu de la grille avec les pions déjà joués et le score actuel
    
    int aff_col;
    int aff_lig;
    system("clear");
    printf("Nombres victoires: R:%d / J:%d\n",score_a,score_b);
    printf("au jouer %c de jouer\n",pion);
    printf(":0:1:2:3:4:5:6:\n");
    for (aff_lig = 0;aff_lig < NB_LIG;aff_lig++){
        printf(":");
        for(aff_col = 0;aff_col < NB_COL;aff_col++){
            printf("%c",g[aff_lig][aff_col]);
            if (aff_col == 6){
                printf(":");
            }
            else{
                printf("|");
            }
        }
        printf("\n");
    }
    printf(":::::::::::::::\n");
}

bool grillePleine(Grille g){

    //Teste si toutes les cases de la grille sont occupées ou non
    
    int lig;
    int col;
    bool res;
    res=true;
    for (lig = 0;lig < NB_LIG;lig++){
        for(col = 0;col < NB_COL;col++){
            if(g[lig][col] == VIDE){
                res=false;
            }
        }
    }
    return res;
}

void jouer(Grille g,char pion,int* ligne,int* colonne){

    // permet à un joueur de jouer son pion appelle des fonction trouveLigne et choisirColonne
    
    *colonne = choisirColonne(g,pion);
    *ligne = trouveLigne(g,*colonne);
    while (*ligne <= -1){
        printf("Impossible sur la colonne %d joueurs %c, plus de place.Veuillez choisir une autre colonne.\n",*colonne,pion);
        *colonne = choisirColonne(g,pion);
        *ligne = trouveLigne(g,*colonne);
    }
    g[*ligne][*colonne] = pion;
    
}

int choisirColonne(Grille g,char pion){

    // Le joueur choisit la colonne où il souhaite faire tomber son pion
    
    int position;
    printf("Joueur %c, inscrivez un chiffre entre 0 et 6(inclut)\n",pion);
    scanf("%d",&position);
    while(position < 0 || position > 6 ){
        printf("Colonne entre 0 et 6 pour le pion %c svp\n",pion);
        scanf("%d",&position);
    }
    return position;
}


int trouveLigne(Grille g,int colonne){
    //  trouver la première case non occupée de la colonne Si la colonne est pleine, la fonction retourne -1.

    int ligne;
    ligne = NB_LIG;
    while (g[ligne][colonne] != VIDE && ligne >= 0){
        ligne--;
    }
    return ligne;
}

bool estVainqueur(Grille g,int ligne,int colonne,char pion){

    // renvoie s’il y a une ligne, une colonne ou une diagonale formée d’au moins 4 pions identiques 
    
    int boucle;
    bool gagner;
    int aligne;
    int colonne_2;
    int ligne_2;
    
    gagner = false;

    //regarde ligne
    boucle = 0;
    aligne = 0;
    while(!gagner && aligne < 4 && boucle < NB_COL ){
        if(g[ligne][boucle] == pion){
            aligne++;
        }
        else{
            aligne=0;
        }
        boucle++;
    }
    if( aligne >= 4){
        gagner = true;
    }

    // regarde colonne
    boucle=0;
    aligne =0;
    while(!gagner && aligne < 4 && boucle < NB_LIG ){
        if(g[boucle][colonne] == pion){
            aligne++;
        }
        else{
            aligne=0;
        }
        boucle++;
    }
    if( aligne >= 4){
        gagner = true;
    }
    
    //regarde diagonale Nord-Ouest vers Sud-Est
    aligne = 0;
    ligne_2 = ligne; // conservation de la position du pion pour la seconde diagonal
    colonne_2 = colonne;
    while(ligne > 0 && colonne > 0){
        ligne--;
        colonne--;
    }
    while(!gagner && aligne < 4 && ligne < NB_LIG && colonne < NB_COL){
        if(g[ligne][colonne] == pion){
            aligne++;
        }
        else{
            aligne = 0;
        }
        ligne++;
        colonne++;
    }
    if( aligne >= 4){
        gagner = true;
    }
    
    //regarde diagonale Nord-Est vers Sud-Ouest
    aligne = 0;
    while(ligne_2 > 0 && colonne_2 < 6){
        ligne_2--;
        colonne_2++;
    }
    while(!gagner && aligne < 4 && ligne_2 < NB_LIG && colonne_2 >= 0){
        
        if(g[ligne_2][colonne_2] == pion){
            aligne++;
        }
        else{
            aligne = 0;
        }
        ligne_2++;
        colonne_2--;

    }
    if( aligne >= 4){
        gagner = true;
    }
   
    return gagner;
}

void finDePartie(char pion){

    // Affiche le résultat d’une partie lorsqu’elle est terminée.

    if (pion == PION_A){
        printf("bravo joueur R, vous avez gagner\n");
    }
    else if(pion == PION_B){
        printf("Bravo joueur J, vous avez gagner\n");
    }
    else {
        printf("Vous venez de finir la partie, plus de place dans le tableau.Il n'y a pas de gagnant\n");
    }
}

char joueur_aleatoire(){

    // choisis "aléatoirement" le premier joueur

    int nb;
    char joueur ;
    joueur = PION_B;;
    srand(time(NULL));     // création nb par rapport à l'heure systeme        
    nb = rand() % 2;
    if (nb == 0){
        joueur = PION_A;
    }
    return joueur;
}
void sauvegarde(int score_a,int score_b){

    // permet de sauvegarder les score de la partie dans un fichier .txt

    FILE* score = NULL;  //création de la variable score en tant que fichier
    score = fopen("score.txt", "a"); // ouverture du fichier   on choisit "a" pour que les anciennes valeurs du fichier reste et pour que si le fichier n'existe pas il soit créer
    if (score != NULL){ // si le fichier existe bien 
        fprintf(score,"Nombres victoires: R:%d / J:%d\n",score_a,score_b); // ecrire dans le fichiier
        fclose(score); // fermer le fichier
        printf("Sauvegarde effectuer.\n");
    }
}