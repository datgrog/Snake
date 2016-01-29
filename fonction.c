#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>    // mode raw
#include <unistd.h>     // fonction system
#include <time.h>
#include <sys/time.h>   // kbhit
#include <unistd.h>
#include "fonction.h"   // .h de ce fichier

    ////////////////////
    // FONCTION PRIMAIRE
    ////////////////////

// Fonction qui fait a x 0.01s d'arrêt du programme.
void sleepa (unsigned int a)
{
    int i;
    for(i=0; i<a; i++) {
                        usleep(100);
    }
}

// Fonction activant le mode RAW du terminal, ou mode BRUT.
void mode_raw (int activer)
{
    static struct termios cooked;
    static int raw_actif = 0;

    if (raw_actif  ==  activer) return;
    if (activer) {
        struct termios raw;
        tcgetattr(STDIN_FILENO, &cooked);
        raw = cooked;
        cfmakeraw(&raw);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }
    else tcsetattr(STDIN_FILENO, TCSANOW, &cooked);

    raw_actif = activer;
}

// Fonction vérifiant si une touche est appuyée
int kbhit (void)
{
    struct timeval tv = {0, 0};
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv)  ==  1;
}

// LA fonction magique qui positionne le curseur à (x,y) dans la console.
// AXE X : de la gauche vers la droite.
// AXE Y : du haut vers le bas.
void gotoxy (int x, int y) {
    fprintf (stdout, "%c[%d;%df", 0x1B, y, x);
}

// Fonction "nettoyant" une position ( ou plutôt remplacant par des espaces )
void cleartoxy (int x, int y, int stop) {
    int i=0;
    for (i=0; i<stop ; i++) {
        gotoxy(x,(y+i)); fprintf (stdout,"                           ");
    }
}

// Génère un nombre aléatoire entre a - inclus - et b - exclus.
int rand_ab (int a, int b) {
                           return rand()%(b-a) +a;
}

/* Renvoie un nombre aléatoire entre 0 et 1 */
double rand_0_1(){  return rand()/(double)RAND_MAX; }

/*Génère un entier entre 1 et taille suivant la loi modélisée par le tableau
passé en paramètre */
int alea_perso(double loi[], int taille) {
    int i=0;
    double x=rand_0_1();
    double somme=0;
    /* Dans le premier passage dans la boucle, on testera
           si x est inférieur à somme, c'est à dire loi[0]. Si ce n'est pas le cas
           on relance la boucle : somme vaudra alors loi[0] + loi[1]
           ... et ainsi de suite.
        */
    do{
        somme += loi[i];
        i++;
    }while( somme < x && i < taille  );
    return i;
}

// Fonction affichant l'aire de jeu
void afficheArea (int ligne, int colonne)
{
    int l = 0;
    int c = 0;

    unsigned char COLONNE;
    unsigned char LIGNE;

    unsigned char  HAUTGAUCHE;
    unsigned char  BASGAUCHE;
    unsigned char  HAUTDROIT;
    unsigned char  BASDROIT;

    unsigned char  LIGNEPLUSBAS;
    unsigned char  LIGNEPLUSHAUT;

    gotoxy(0, 0);


    for (l = 0; l < HEIGTH_AREA_GAME; l++) {

        for (c = 0; c < WIDTH_AREA_GAME + 16 ; c++) { // +15 POUR AFFICHAGE DES TIMES & SCORE EN LARGEUR

            if (l == 0 && c == 0) fprintf (stdout, "%s", HG); // Coin haut gauche AireJeu
            else
                if (l == 0  && c > 0 && c != WIDTH_AREA_GAME-1 && c < WIDTH_AREA_GAME+15 ) fprintf (stdout, "%s", lig); // Première ligne SANS le coin droit AireJeu
                else
                    if (l == 0 && c == WIDTH_AREA_GAME + 15 ) fprintf (stdout, "%s", HD);
                    else
                        if (l == HEIGTH_AREA_GAME-1 && c > 0 && c != WIDTH_AREA_GAME-1 && c < WIDTH_AREA_GAME+15) fprintf (stdout, "%s", lig); // Dernière ligne SANS le coin bas droit AireJeu
                        else
                            if (l == 0 && c == WIDTH_AREA_GAME-1) fprintf (stdout, "%s", hd);
                            else
                                if ( l == HEIGTH_AREA_GAME-1 && c == WIDTH_AREA_GAME + 15 ) fprintf (stdout, "%s", BD);
                                else
                                    if ( c == 0  && l > 0 && l < HEIGTH_AREA_GAME-1 ) fprintf (stdout, "%s", col); // 1ère colonne
                                    else
                                        if ( c == WIDTH_AREA_GAME-1  && l > 0 && l < HEIGTH_AREA_GAME-1 ) fprintf (stdout, "%s", col); // colonne du milieu
                                        else
                                            if ( c == WIDTH_AREA_GAME+15  && l > 0 && l < HEIGTH_AREA_GAME+15 ) fprintf (stdout, "%s", col); // dernière colonne
                                            else
                                                if (l == HEIGTH_AREA_GAME-1 && c == 0) fprintf (stdout, "%s", BG);
                                                else
                                                    if (l == HEIGTH_AREA_GAME-1 && c == WIDTH_AREA_GAME-1) fprintf (stdout, "%s", bd);
                                                    else fprintf (stdout, " ");
        }
        fprintf(stdout,"\n");
    }
}

// Fonction gérant l'écriture en couleur
void writeInColor(char texte[], int C_texte, int init) {
    if (init)
        fprintf (stdout,"\033[%dm%s\033[0m", C_texte, texte);
    else
        fprintf (stdout,"\033[%dm%s", C_texte, texte);
}

    /////////////////////////////
    // FONCTION AFFICHAGE GENERAL
    /////////////////////////////

// Fonction affichant le temps de jeu
int printTime (clock_t *start, clock_t *stop)
{
    time(stop);
    int timeMin = (int)difftime(*stop, *start)/60;
    int timeSec = (int)difftime(*stop, *start)%60;

    if (difftime(*stop, *start) >60 ) {
        gotoxy(42,2); writeInColor("",ROUGE,0); fprintf(stdout,"TIME  :  %d:%2d\n",timeMin,timeSec); writeInColor("",ROUGE,1);
    }
    else {
        gotoxy(42,2); writeInColor("",ROUGE,0); fprintf(stdout,"TIME  :   %.0f\n",difftime(*stop, *start)); writeInColor("",ROUGE,1);
    }

    return ( int )difftime(*stop, *start);

}

// Fonction affichant le score
void printScore (int score) {
    gotoxy(42,3);
    writeInColor("",ROUGE,0); fprintf(stdout,"SCORE :   %d\n",score); writeInColor("",ROUGE,1);
}

// Fonction affichant le panneau de compteur de food à droite de l'aire de jeu,
// mettant à jour le tableau associé à ce panneau
// et aussi changeant le score actuel du joueur ( en haut à droite )
int differentFood (int *score, int luckFood, int *compteurFood) {

    unsigned char STAR;                // ★    BLACK STAR
    unsigned char COMET;              //  ☄    COMET
    unsigned char SUNSHINE;          //   ☀    BLACK SUN WITH RAYS
    unsigned char CLOUD;            //    ☁    CLOUD
    unsigned char SHAMROCK;        //     ☘    SHAMROCK
    unsigned char CIRCLE;         //      ●    BLACK CIRCLE
    unsigned char DIAMOND;       //       ◆    BLACK DIAMOND
    unsigned char TRIANGLE;     //        ▲    BLACK UP-POINTING TRIANGLE
    unsigned char RECTANGLE;   //         ▬    BLACK RECTANGLE
    unsigned char SQUARE;     //          ▪    BLACK SMALL SQUARE

    int x=42;
    int y=HEIGTH_ACTIVE_AREA/2-1;
    int i=0;
    int returnScore;

    if (luckFood==0) {

        for ( i= 0; i < 8; i++)
        {
            gotoxy(x,y);
            if (i==0) { writeInColor("",JAUNE,0);   fprintf(stdout,  "%s : \n", star);     writeInColor("",JAUNE,1);    }
            if (i==1) { writeInColor("",ROUGE,0);   fprintf (stdout, "%s : \n", comet);    writeInColor("",ROUGE,1);    }
            if (i==2) { writeInColor("",JAUNE,0);   fprintf (stdout, "%s : \n", sunshine); writeInColor("",JAUNE,1);    }
            if (i==3) { writeInColor("",BLANC,0);   fprintf (stdout, "%s : \n", cloud);    writeInColor("",BLANC,1);    }
            if (i==4) { writeInColor("",VERT,0);    fprintf (stdout, "%s : \n", shamrock); writeInColor("",VERT,1);     }
            if (i==5) { writeInColor("",CYAN,0);    fprintf (stdout, "%s : \n", circle);   writeInColor("",CYAN,1);     }
            if (i==6) { writeInColor("",BLEU,0);    fprintf (stdout, "%s : \n", diamond);  writeInColor("",BLEU,1);     }
            if (i==7) { writeInColor("",MAGENTA,0); fprintf (stdout, "%s : \n", triangle); writeInColor("",MAGENTA,1);  }
            y++;
        }
        gotoxy(x,16); fprintf (stdout, "%s : \n", rectangle);
        gotoxy(x,17); fprintf (stdout, "%s : \n", square);
    }

    if (luckFood == 10) { *score += 1024;   returnScore=1024; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2-1);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 9 ) { *score += 512;    returnScore=512; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 8 ) { *score += 256;    returnScore=256; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2+1);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 7 ) { *score += 128;    returnScore=128; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2+2);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 6 ) { *score += 64;     returnScore=64; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2+3);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 5 ) { *score += 32;     returnScore=32; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2+4);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 4 ) { *score += 16;     returnScore=16; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2+5);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 3 ) { *score += 8;      returnScore=8; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2+6);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 2 ) { *score += 4;      returnScore=4; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2+7);      fprintf(stdout, "%d",compteurFood[luckFood]); }
    if (luckFood == 1 ) { *score += 2;      returnScore=2; compteurFood[luckFood]++;   gotoxy(47,HEIGTH_ACTIVE_AREA/2+8);      fprintf(stdout, "%d",compteurFood[luckFood]); }

    return returnScore;
}

// Fonction affichant l'aire du menu.
void printAirMenu (int xmin, int ymin, int xmax, int ymax) {

    unsigned char COLONNE;
    unsigned char LIGNE;

    unsigned char  HAUTGAUCHE;
    unsigned char  BASGAUCHE;
    unsigned char  HAUTDROIT;
    unsigned char  BASDROIT;

    int x = xmin;
    int y = ymin;

    for (y=ymin ; y < ymax ; y++) {

        for (x=xmin ; x < xmax  ; x++) {
            gotoxy(x,y);
            if (y == ymin && x == xmin) fprintf (stdout, "%s", HG);
            else
                if (y == ymin  && x > xmin && x < xmax-1 ) fprintf (stdout, "%s", lig);
                else
                    if (y == ymax-1 && x > xmin && x < xmax-1) fprintf (stdout, "%s", lig);
                    else
                        if (y == ymin && x == xmax-1) fprintf (stdout, "%s", HD);
                        else
                            if ( x == xmin  && y > 0 && y < ymax-1 ) fprintf (stdout, "%s", col);
                            else
                                if ( x == xmax-1  && y > ymin && y < ymax-1 ) fprintf (stdout, "%s", col);
                                else
                                    if (y == ymax-1 && x == xmin) fprintf (stdout, "%s", BG);
                                    else
                                        if (y == ymax-1 && x == xmax-1) fprintf (stdout, "%s", BD);
                                        else fprintf (stdout, " ");
        }
    }
}

    /////////////////////
    // FONCTION HIGHSCORE
    /////////////////////

// Fonction chargeant les highscores à partir du fichier highscores et placant les highscores fichiers dans des tableaux.
void loadhighscore(HIGHSCORE* joueur,char* fileScore) {
    int n=3, i;

    FILE* fileName;

    for (i = 0; i < 3; ++i)
    {
        joueur[i].score=0;
        joueur[i].tabNom[0]=0;
        joueur[i].timePlay=0;
        joueur[i].couleur=0;
    }

    if(!(fileName=fopen(fileScore, "r"))){
    fprintf(stdout,"erreur d'ouverture de fichier\n");
    return;
}
    for (i=0;i<n;i++){

    fscanf(fileName, "%d ",&(joueur[i].score));
    fscanf(fileName, "%s ",joueur[i].tabNom);
    fscanf(fileName, "%d ",&(joueur[i].timePlay));
    fscanf(fileName, "%d",&(joueur[i].couleur));

    }
    fclose(fileName);
}

// Fonction affichant les highscores.
void printHighScore (HIGHSCORE* joueur, int message) {

#define YMAX 14
#define YMIN 3
#define XMAX 48
#define XMIN 6

    int i;
    int x = XMIN;
    int y = YMIN;

    unsigned char TOP;
    unsigned char MID;
    unsigned char BOT;

    gotoxy(x,y);

    printAirMenu(XMIN, YMIN, XMAX, YMAX);

    gotoxy((XMAX)/2-2,YMIN+1);
    fprintf (stdout, "HIGHSCORE");

    if (message == 2)
    {
        gotoxy(10,11); fprintf(stdout, "Dernier ! C'est pas trop mal ...");
    }
    if (message == 1)
    {
        gotoxy(7,11); fprintf(stdout, "Deuxieme ! Good mais pas encore premier!");
    }
    if (message == 0)
    {
        gotoxy(10,11); fprintf(stdout, "PREMIER ! Ok sa carry vener");
    }

    for (i=0;i<3;i++) {

        gotoxy(XMIN+2,7+i);
        if (i==0)       { writeInColor("",joueur[i].couleur,0); fprintf(stdout,"%s",top);    writeInColor("",joueur[i].couleur,1); }
        else if (i==1)  { writeInColor("",joueur[i].couleur,0); fprintf(stdout,"%s",mid);    writeInColor("",joueur[i].couleur,1); }
        else            { writeInColor("",joueur[i].couleur,0); fprintf(stdout,"%s",bot);    writeInColor("",joueur[i].couleur,1); }

        gotoxy(15,7+i);
        writeInColor("",joueur[i].couleur,0); fprintf(stdout,"%s ",joueur[i].tabNom);     writeInColor("",joueur[i].couleur,1);
        gotoxy(27,7+i);
        writeInColor("",joueur[i].couleur,0); fprintf(stdout," %3d   ",joueur[i].score);  writeInColor("",joueur[i].couleur,1);
        gotoxy(XMAX-6,7+i);
        writeInColor("",joueur[i].couleur,0); fprintf(stdout,"%d:%d",joueur[i].timePlay/60,joueur[i].timePlay%60); writeInColor("",joueur[i].couleur,1);

        gotoxy(XMAX/2-3,YMAX+1);
        printf("Press Enter");

    }
}

// Fonction mettant à jouer le fichier HIGHSCORE
int majHighScore(char* fileScore, HIGHSCORE* joueur , int scoreJoueur, int timeGame, int couleur) {
    int i, ligne=-1, n=3;
    char nomJoueur[11];

    for(i=2; i>=0; i--) {

        if (scoreJoueur>=joueur[i].score)
        {
            ligne=i;
        }
    }

    if(ligne>=0) {

        gotoxy(10,5);
        fprintf(stdout,"Nouveau HighScore !");
        gotoxy(10,6);
        fprintf(stdout,"Entrez votre nom : ");
        scanf("%s", nomJoueur);
        system("clear");

        // CHANGEMENT DANS LA STRUCTURE HIGHSCORE

        joueur[ligne].score = scoreJoueur;
        strcpy (joueur[ligne].tabNom, nomJoueur);
        joueur[ligne].timePlay = timeGame;
        joueur[ligne].couleur = couleur;
    }

    // REECRITURE DU FICHIER HIGHSCORE
    FILE* fichier=fopen(fileScore, "w");
    for (i=0;i<n;i++){
        fprintf(fichier, "%d %s %d %d\n", joueur[i].score, joueur[i].tabNom, joueur[i].timePlay, joueur[i].couleur);
    }
    fclose(fichier);

    return ligne; // pour le message à afficher si new highscore
}

    /////////////////
    // FONCTION SNAKE
    /////////////////

/////////////////////////////////////////////////////
// smartSnake : le serpent part se nourrir tout seul
// Fonction créant un bot - limité - pour le Snake
/////////////////////////////////////////////////////
void smartSnake (COORD *theSnake, COORD *theFood, int *touche, int *dir) {

    int  goSnake;

    goSnake = *dir;

    if (goSnake == TOLEFT) {
        ///////////////////////
        // DEPLACEMENT A GAUCHE
        ///////////////////////
        if (theSnake[THEHEAD].x > theFood->x)  // LA NOURRITURE EST DEVANT
            if (theSnake[THEHEAD].x == theFood->x && theSnake[THEHEAD].y>theFood->y) *touche = TOUCH_TOP;
            else
                if (theSnake[THEHEAD].x == theFood->x && theSnake[THEHEAD].y<theFood->y) *touche = TOUCH_BOTTOM;
                else
                    if (theSnake[THEHEAD].y == HEIGTH_ACTIVE_AREA && theFood->y == HEIGTH_ACTIVE_AREA) *touche = TOUCH_TOP; // SAME 4 QUAND LA NOURRITURE EST SUR LA MEME LIGNE DERRIERE HEIGTH_ACTIVE_AREA = LIGNE -1 !!!!!!!!
                    else *touche = TOUCH_LEFT;
        else    // QUAND LA NOURRITURE EST DERRIERE
            if (theSnake[THEHEAD].y>theFood->y) *touche = TOUCH_TOP;
            else
                if (theSnake[THEHEAD].y == HEIGTH_ACTIVE_AREA && theFood->y == HEIGTH_ACTIVE_AREA) *touche = TOUCH_TOP;
                else *touche = TOUCH_BOTTOM;
    }

    if (*dir == TORIGHT) {
        ///////////////////////
        // DEPLACEMENT A DROITE
        ///////////////////////
        if (theSnake[THEHEAD].x<theFood->x) // QUAND LA NOURRITURE EST DEVANT
            if (theSnake[THEHEAD].x == theFood->x && theSnake[THEHEAD].y > theFood->y) *touche = TOUCH_TOP;
            else
                if (theSnake[THEHEAD].x == theFood->x && theSnake[THEHEAD].y<theFood->y) *touche = TOUCH_BOTTOM;
                else
                    if (theSnake[THEHEAD].y == HEIGTH_ACTIVE_AREA && theFood->y == HEIGTH_ACTIVE_AREA) *touche = TOUCH_TOP; // SAME 3
                    else *touche = TOUCH_RIGHT;
        else     // QUAND LA NOURRITURE EST DERRIERE
            if (theSnake[THEHEAD].y>theFood->y) *touche = TOUCH_TOP;
            else
                if (theSnake[THEHEAD].y == HEIGTH_ACTIVE_AREA && theFood->y == HEIGTH_ACTIVE_AREA) *touche = TOUCH_TOP; // SAME 3
                else *touche = TOUCH_BOTTOM;
    }
    // DANS DIR 3 & 4 ON A SOUS-ENTENDU (theSnake[THEHEAD].y == 2 && theFood->y == 2) A CAUSE DU IDKW
    // DANS DIR 1 & 2 C'EST BIZARRE JE PREFERE METTRE LES CONDITIONS POUR ETRE SUR

    if (*dir == TOTOP) {
        ///////////////////////////
        // DEPLACEMENT VERS LA HAUT
        ///////////////////////////
        if (theSnake[THEHEAD].y > theFood->y)        // QUAND LA NOURRITURE EST DEVANT
            if (theSnake[THEHEAD].y == theFood->y && theSnake[THEHEAD].x>theFood->x) *touche = TOUCH_LEFT;
            else
                if (theSnake[THEHEAD].y == theFood->y && theSnake[THEHEAD].x<theFood->x) *touche = TOUCH_RIGHT;
                else
                    if (theSnake[THEHEAD].x == TOBOTTOM && theFood->x == TOBOTTOM) *touche = TOUCH_RIGHT;  // SAME 1
                    else
                        if (theSnake[THEHEAD].x == WIDTH_ACTIVE_AREA && theFood->x == WIDTH_ACTIVE_AREA) *touche = TOUCH_LEFT; // SAME 1
                        else    *touche = TOUCH_TOP;
        else    // QUAND LA NOURRITURE EST DERRIERE
            if (theSnake[THEHEAD].x>theFood->x) *touche = TOUCH_LEFT;
            else
                if (theSnake[THEHEAD].x == TOBOTTOM && theFood->x == TOBOTTOM) *touche = TOUCH_RIGHT;  // SAME 1
                else
                    if (theSnake[THEHEAD].x == WIDTH_ACTIVE_AREA && theFood->x == WIDTH_ACTIVE_AREA) *touche = TOUCH_LEFT; // SAME 1
                    else *touche = TOUCH_RIGHT;
    }

    if (*dir == TOBOTTOM) {
        ///////////////////////////
        // DEPLACEMENT VERS LE BAS
        ///////////////////////////
        if (theSnake[THEHEAD].y<theFood->y) // QUAND LA NOURRITURE EST DEVANT
            if (theSnake[THEHEAD].y == theFood->y && theSnake[THEHEAD].x>theFood->x) *touche = TOUCH_LEFT;
            else
                if(theSnake[THEHEAD].y == theFood->y && theSnake[THEHEAD].x<theFood->x) *touche = TOUCH_RIGHT;
                else
                    if (theSnake[THEHEAD].x == TOBOTTOM && theFood->x == TOBOTTOM) *touche = TOUCH_RIGHT;  // SAME 2
                    else
                        if (theSnake[THEHEAD].x == WIDTH_ACTIVE_AREA && theFood->x == WIDTH_ACTIVE_AREA) *touche = TOUCH_LEFT; // SAME 2
                        else *touche = TOUCH_BOTTOM;
            else    // QUAND LA NOURRITURE EST DERRIERE
                if (theSnake[THEHEAD].x>theFood->x) *touche = TOUCH_LEFT;
                else
                    if (theSnake[THEHEAD].x == TOBOTTOM && theFood->x == TOBOTTOM) *touche = TOUCH_RIGHT;  // SAME 2
                    else
                        if (theSnake[THEHEAD].x == WIDTH_ACTIVE_AREA && theFood->x == WIDTH_ACTIVE_AREA) *touche = TOUCH_LEFT;  // SAME 2
                        else *touche = TOUCH_RIGHT;
    }
}

// Fonction intialisant le snake.
void initheSnake (int nbSectionSnake, COORD *theSnake, int colonne, int ligne) {

    int i;

    for (i = 0; i < nbSectionSnake; i++) {   // On initialise le COORD

        if (i == 0) {
                    theSnake[i].x = (colonne/2);
                    theSnake[i].y = (ligne/2);
        }
        else {
             theSnake[i].x = theSnake[i-1].x + 1;
             theSnake[i].y = theSnake[i-1].y;
        }
    }
}

// Tri le tableau de COORD du Snake
void trietheSnake (int nbSectionSnake, COORD *theSnake, COORD headPosPrec) {

    int i;
    COORD ThirdSection;
    COORD TMP;

    ThirdSection = theSnake[AFTER_HEAD];
    theSnake[AFTER_HEAD] = headPosPrec;

    for (i = AFTER_HEAD + 1; i < nbSectionSnake; i++)   {

        TMP = theSnake[i];
        theSnake[i] = ThirdSection;
        ThirdSection = TMP;
    }
}

// Fonction d'affichage réduite :
// - affiche la nouvelle tête
// - affiche le "cou"
// - efface la dernière partie du corps
void printSnake (COORD *theSnake, int *dir, int nbSectionSnake, int couleur) {

    unsigned char VERTICALBODY;
    unsigned char HORIZONTALBODY;

    gotoxy (theSnake[THEHEAD].x, theSnake[THEHEAD].y);

    switch (*dir) {
    case TOTOP    : writeInColor("",couleur,0); fprintf (stdout, "%c", '^'); writeInColor("",couleur,1); break;
    case TOBOTTOM : writeInColor("",couleur,0); fprintf (stdout, "%c", 'v'); writeInColor("",couleur,1); break;
    case TORIGHT  : writeInColor("",couleur,0); fprintf (stdout, "%c", '>'); writeInColor("",couleur,1); break;
    case TOLEFT   : writeInColor("",couleur,0); fprintf (stdout, "%c", '<'); writeInColor("",couleur,1); break;
    }

    gotoxy (theSnake[AFTER_HEAD].x, theSnake[AFTER_HEAD].y); // headTmp.x, headTmp.y

    if (*dir == TOTOP || *dir == TOBOTTOM) { writeInColor("",couleur,0); fprintf (stdout, "%s", col); writeInColor("",couleur,1);  } // Corps
    else                                   { writeInColor("",couleur,0); fprintf (stdout, "%s", lig); writeInColor("",couleur,1);  }  // Corps

    gotoxy (theSnake[nbSectionSnake - 1].x, theSnake[nbSectionSnake - 1].y); // theSnake[nbSectionSnake-1] tailTmp.x, tailTmp.y
    fprintf (stdout, "%c", ' ');
}

// DIR : 1 = HAUT ; 2 = BAS ; 3 = DROITE ; 4 =  GAUCHE
// Fonction changeant la direction du snake.
void changeDirSnake (int touche, COORD *theSnake, int *dir) {


    if (*dir == TOLEFT && touche == TOUCH_RIGHT) touche = TOUCH_LEFT;
    if (*dir == TORIGHT && touche == TOUCH_LEFT) touche = TOUCH_RIGHT;
    if (*dir == TOTOP && touche == TOUCH_BOTTOM) touche = TOUCH_TOP;
    if (*dir == TOBOTTOM && touche == TOUCH_TOP) touche = TOUCH_BOTTOM;

    switch(touche) {

    case TOUCH_TOP :    theSnake[THEHEAD].y = (theSnake[THEHEAD].y) - 1;
                        *dir = TOTOP;
                        break;
    case TOUCH_BOTTOM : theSnake[THEHEAD].y = theSnake[THEHEAD].y + 1;
                        *dir = TOBOTTOM;
                        break;
    case TOUCH_RIGHT :  theSnake[THEHEAD].x = theSnake[THEHEAD].x + 1;
                        *dir = TORIGHT;
                        break;
    case TOUCH_LEFT :   theSnake[THEHEAD].x = (theSnake[THEHEAD].x) - 1;
                        *dir = TOLEFT;
                        break;
    }

}

// Fonction affichant lors d'un virage du snake le bon caractère spécial.
void theSnakeCurve (int *dir, int *dirTmp, COORD *theSnake, int nbSectionSnake, int couleur) {

    unsigned char LEFT_TO_UP; // gauche VERS le haut
    unsigned char LEFT_TO_DOWN; // gauche VERS le bas
    unsigned char RIGHT_TO_UP; // droite VERS le haut
    unsigned char RIGHT_TO_DOWN;  // droite VERS le bas

    gotoxy(theSnake[1].x, theSnake[1].y);

    if ((*dir == TOTOP && *dirTmp == TOLEFT) || (*dir == TORIGHT && *dirTmp == TOBOTTOM)) { writeInColor("",couleur,0); fprintf (stdout, "%s\n", gauchevhaut); writeInColor("",couleur,1); }
    if ((*dir == TOBOTTOM && *dirTmp == TOLEFT) || (*dir == TORIGHT && *dirTmp == TOTOP)) { writeInColor("",couleur,0); fprintf (stdout, "%s\n", gauchevbas);  writeInColor("",couleur,1); }
    if ((*dir == TOTOP && *dirTmp == TORIGHT) || (*dir == TOLEFT && *dirTmp == TOBOTTOM)) { writeInColor("",couleur,0); fprintf (stdout, "%s\n", droitevhaut); writeInColor("",couleur,1); }
    if ((*dir == TOBOTTOM && *dirTmp == TORIGHT) || (*dir == TOLEFT && *dirTmp == TOTOP)) { writeInColor("",couleur,0); fprintf (stdout, "%s\n", droitevbas);  writeInColor("",couleur,1); }

}

// Affiche le Snake en entier.
void printFullSnake (COORD *theSnake, int *dir, int nbSectionSnake, int couleur) {
    int i;
    unsigned char VERTICALBODY;
    unsigned char HORIZONTALBODY;

    unsigned char LEFT_TO_UP; // ╰
    unsigned char LEFT_TO_DOWN; // ╭
    unsigned char RIGHT_TO_DOWN; // ╮
    unsigned char RIGHT_TO_UP; // ╯

    COORD sectionPrecedente={0,0};
    COORD sectionActuelle={theSnake[THEHEAD].x,theSnake[THEHEAD].y};
    COORD sectionSuivante={theSnake[AFTER_HEAD].x,theSnake[AFTER_HEAD].y};

    gotoxy (sectionActuelle.x, sectionActuelle.y);

    // On affiche la tête dans le bon sens
    switch (*dir) {
        case TOTOP    : writeInColor("",couleur,0); fprintf (stdout, "%c", '^'); writeInColor("",couleur,1); break;
        case TOBOTTOM : writeInColor("",couleur,0); fprintf (stdout, "%c", 'v'); writeInColor("",couleur,1); break;
        case TORIGHT  : writeInColor("",couleur,0); fprintf (stdout, "%c", '>'); writeInColor("",couleur,1); break;
        case TOLEFT   : writeInColor("",couleur,0); fprintf (stdout, "%c", '<'); writeInColor("",couleur,1); break;
    }

    // On affiche toutes les parties du corps ( à partir du cou jusqu'à la queue puisque la tête a déjà été affiché séparément ).
    for (i=1;i<nbSectionSnake;i++) {
        sectionPrecedente.x=sectionActuelle.x;
        sectionPrecedente.y=sectionActuelle.y;
        sectionActuelle.x=sectionSuivante.x;
        sectionActuelle.y=sectionSuivante.y;

        gotoxy (sectionActuelle.x, sectionActuelle.y);
        // Si ce n'est pas la dernière section du Snake, on a aussi sectionSuivante
        if (i!=nbSectionSnake-1) {
            sectionSuivante.x=theSnake[i].x;
            sectionSuivante.y=theSnake[i].y;

            // si le char est │
            if (sectionPrecedente.x == sectionActuelle.x && sectionActuelle.x == sectionSuivante.x) {
                writeInColor("",couleur,0); fprintf (stdout, "%s", col); writeInColor("",couleur,1); }
            // si le char est ─
                if (sectionPrecedente.y == sectionActuelle.y && sectionActuelle.y == sectionSuivante.y) {
                writeInColor("",couleur,0); fprintf (stdout, "%s", lig); writeInColor("",couleur,1); }
            // si le char est ╮
            if ((sectionPrecedente.y > sectionActuelle.y && sectionPrecedente.x == sectionActuelle.x && sectionSuivante.x < sectionActuelle.x && sectionSuivante.y == sectionActuelle.y) || (sectionSuivante.y > sectionActuelle.y && sectionSuivante.x == sectionActuelle.x && sectionPrecedente.y == sectionActuelle.y && sectionPrecedente.x < sectionActuelle.x)) {
                writeInColor("",couleur,0); fprintf (stdout, "%s", droitevbas); writeInColor("",couleur,1); }
            // si le char est ╭
            if ((sectionPrecedente.y == sectionActuelle.y && sectionPrecedente.x > sectionActuelle.x && sectionSuivante.y > sectionActuelle.y && sectionSuivante.x == sectionActuelle.x) || (sectionSuivante.y == sectionActuelle.y && sectionSuivante.x > sectionActuelle.x && sectionPrecedente.x == sectionActuelle.x && sectionPrecedente.y > sectionActuelle.y)) {
                writeInColor("",couleur,0); fprintf (stdout, "%s", gauchevbas); writeInColor("",couleur,1); }
            // si le char est ╰
            if ((sectionPrecedente.y < sectionActuelle.y && sectionPrecedente.x == sectionActuelle.x && sectionSuivante.y == sectionActuelle.y && sectionSuivante.x > sectionActuelle.x) || (sectionSuivante.y < sectionActuelle.y && sectionSuivante.x == sectionActuelle.x && sectionPrecedente.y == sectionActuelle.y && sectionPrecedente.x > sectionActuelle.x)) {
                writeInColor("",couleur,0); fprintf (stdout, "%s", gauchevhaut); writeInColor("",couleur,1); }
            // si le char est ╯
            if ((sectionPrecedente.y == sectionActuelle.y && sectionPrecedente.x < sectionActuelle.x && sectionSuivante.y < sectionActuelle.y && sectionSuivante.x == sectionActuelle.x) || (sectionSuivante.y == sectionActuelle.y && sectionSuivante.x < sectionActuelle.x && sectionPrecedente.y < sectionActuelle.y && sectionPrecedente.x == sectionActuelle.x)) {
                writeInColor("",couleur,0); fprintf (stdout, "%s", droitevhaut); writeInColor("",couleur,1); }
        }
        else {
            if (sectionPrecedente.x == sectionActuelle.x) {
                    writeInColor("",couleur,0); fprintf (stdout, "%s", col); writeInColor("",couleur,1); }
                if (sectionPrecedente.y == sectionActuelle.y) {
                    writeInColor("",couleur,0); fprintf (stdout, "%s", lig); writeInColor("",couleur,1);
                }
        }
    }
}


    ////////////////
    // FONCTION FOOD
    ////////////////

// Affiche la nourriture.
void printFood(COORD *theFood, int luckFood) {

    unsigned char STAR;                // ★    BLACK STAR
    unsigned char COMET;              //  ☄    COMET
    unsigned char SUNSHINE;          //   ☀    BLACK SUN WITH RAYS
    unsigned char CLOUD;            //    ☁    CLOUD
    unsigned char SHAMROCK;        //     ☘    SHAMROCK
    unsigned char CIRCLE;         //      ●    BLACK CIRCLE
    unsigned char DIAMOND;       //       ◆    BLACK DIAMOND
    unsigned char TRIANGLE;     //        ▲    BLACK UP-POINTING TRIANGLE
    unsigned char RECTANGLE;   //         ▬    BLACK RECTANGLE
    unsigned char SQUARE;     //          ▪    BLACK SMALL SQUARE

    gotoxy(theFood->x, theFood->y);
    if (luckFood == 10) { writeInColor("",JAUNE,0);   fprintf(stdout,  "%s \n", star);     writeInColor("",JAUNE,1);    }
    if (luckFood == 9 ) { writeInColor("",ROUGE,0);   fprintf (stdout, "%s \n", comet);    writeInColor("",ROUGE,1);    }
    if (luckFood == 8 ) { writeInColor("",JAUNE,0);   fprintf (stdout, "%s \n", sunshine); writeInColor("",JAUNE,1);    }
    if (luckFood == 7 ) { writeInColor("",BLANC,0);   fprintf (stdout, "%s \n", cloud);    writeInColor("",BLANC,1);    }
    if (luckFood == 6 ) { writeInColor("",VERT,0);    fprintf (stdout, "%s \n", shamrock); writeInColor("",VERT,1);     }
    if (luckFood == 5 ) { writeInColor("",CYAN,0);    fprintf (stdout, "%s \n", circle);   writeInColor("",CYAN,1);     }
    if (luckFood == 4 ) { writeInColor("",BLEU,0);    fprintf (stdout, "%s \n", diamond);  writeInColor("",BLEU,1);     }
    if (luckFood == 3 ) { writeInColor("",MAGENTA,0); fprintf (stdout, "%s \n", triangle); writeInColor("",MAGENTA,1);  }
    if (luckFood == 2 ) fprintf (stdout, "%s", rectangle);
    if (luckFood == 1 ) fprintf (stdout, "%s", square);
}

// Fonction initialisant la nourriture, vérifiant si ses coordonnées sont valides, et l'affichant.
void initCheckAndPrinttheFood (COORD *theFood, COORD *theSnake, int nbSectionSnake, int luckFood, int y, int x)
{
   int a, b, i;

   int resCheck; // XXX

   do {
        a = rand_ab(2, x-1); /* -1 car les Foods prennent l'espace de 2 caractères pour s'affiche
                                donc si un food apparait si la ligne verticale précédent la colonne du terrain celle-ci sera "mangé" */
        b = rand_ab(2, y);
        resCheck = TRUE;    // On part du principe que la coord générée par a et b est tel qu'on le souhaite
        for (i = 0; i<nbSectionSnake; i++) {
                if (a == theSnake[i].x && b == theSnake[i].y ) resCheck = FALSE;
           }
    } while (resCheck == FALSE);

    theFood->x = a;
    theFood->y = b;

    printFood(theFood, luckFood);
}

    ////////////////////////
    // FONCTION VERIFICATION
    ////////////////////////

// Fonction vérifiant si la tête du Snake n'est pas sur un bord de l'aire de jeu.
int checktheSnakePosition (COORD *theSnake, int ligne, int colonne)
{
    if (theSnake[THEHEAD].x <= 1 || theSnake[THEHEAD].y <= 1 || theSnake[THEHEAD].x>= colonne || theSnake[THEHEAD].y >= ligne) return FALSE;

    return TRUE;
}

// Fonction vérifiant si la tête du snake n'est pas sur une partie du corps.
int checktheSnakeEatHimself (COORD *theSnake, int nbSectionSnake)
{
    int i;

    for (i = 1; i<nbSectionSnake; i++)
    {
        if ((theSnake[THEHEAD].x == theSnake[i].x) && (theSnake[THEHEAD].y == theSnake[i].y)) return FALSE;
    }
    return TRUE;
}

    ///////////////////////////
    // FONCTION ANIMATION
    ///////////////////////////

// Fonction d'animation du Score.
void fAnimScore(COORD* coordAnim, int* animScore, int scoreValue, COORD *theSnake, int *dir, int nbSectionSnake, int couleur) {
	int scoreLength, i;
	// On détermine le nombre de caractère du score.

	if (scoreValue < 10)
		scoreLength=1;
	if (scoreValue > 9 && scoreValue < 100)
		scoreLength=2;
	if (scoreValue > 99 && scoreValue < 1000)
		scoreLength=3;
	if (scoreValue > 999 && scoreValue < 9999)
		scoreLength=4;

	if (*animScore != 1) { // Si c'est la première fois que l'animation se fait on n'a rien à effacer
		gotoxy(coordAnim->x, coordAnim->y);
		for (i=0;i<scoreLength+1;i++) // Scorelength +1 car il y a un "+" et le score à effacer !
			printf(" ");
	}

    printFullSnake (theSnake, dir, nbSectionSnake, couleur); // on réaffiche le snake ( l'animation peut avoir été placée SUR des parties du snake donc après effacage de l'animation on ré-affiche le snake )

	if (*animScore != 4) {
		if (coordAnim->x>WIDTH_ACTIVE_AREA-scoreLength) // Si l'animation va déborder sur le bord droit du terrain, on la décale.
			coordAnim->x-=scoreLength;
		if (coordAnim->y>2) { // Si il n'y a pas collision avec la bordure d'en haut
			coordAnim->y-=1;
			gotoxy(coordAnim->x, coordAnim->y);
			printf("+%d", scoreValue);
		}
		else { // Collision avec la bordue du haut, on arrête l'animation.
			*animScore=4;
		}
	}
    *animScore=*animScore+1;
}
