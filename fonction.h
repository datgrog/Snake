#ifndef FONCTION_H
#define FONCTION_H

/// SENS DU SNAKE

#define TOTOP       1
#define TOBOTTOM    2
#define TORIGHT     3
#define TOLEFT      4
#define THEHEAD     0

/// SENS DU SNAKE AVEC LES TOUCHES DIRECTIONELLES

#define TOUCH_TOP       65
#define TOUCH_BOTTOM    66
#define TOUCH_RIGHT     67
#define TOUCH_LEFT      68

/// LA TETE DU SNAKE => theSnake[THEHEAD]

#define THEHEAD         0
#define AFTER_HEAD      1

/// AIRE DE JEU

#define WIDTH_AREA_GAME   40
#define HEIGTH_AREA_GAME  20
#define WIDTH_ACTIVE_AREA   39
#define HEIGTH_ACTIVE_AREA  19

/// TAILLE DE DEPART DU SNAKE

#define SIZE_SNAKE               4

/// VITESSE SNAKE

#define TEMPORISATION       100000

/// BOOL

#define TRUE     1
#define FALSE    0

/// CARACTERE SPECIAUX

// Pour le snake

#define    VERTICALBODY 	col[4] = {226, 148, 130, 0}; // Corps du Snake à la vertical │
#define    HORIZONTALBODY 	lig[4] = {226, 148, 128, 0}; // Corps du Snake à la l'honrizontal ─

#define    LEFT_TO_UP gauchevhaut[4] = {226, 149, 176, 0}; // gauche VERS le haut ╰

#define    LEFT_TO_DOWN  gauchevbas[4] = {226, 149, 173, 0}; // gauche VERS le bas ╭

#define    RIGHT_TO_DOWN  droitevbas[4] = {226, 149, 174, 0}; // droite VERS le bas ╮

#define    RIGHT_TO_UP droitevhaut[4] = {226, 149, 175, 0}; // droite VERS le haut ╯

// Pour les contours en Jeu & Highscore

#define    HAUTGAUCHE  	HG[4] = {226, 149, 148, 0}; // Le coin ╔

#define    BASGAUCHE 	BG[4] = {226, 149, 154, 0}; // Le coin ╚

#define    HAUTDROIT 	HD[4] = {226, 149, 151, 0}; // Le coin ╗

#define    BASDROIT 	BD[4] = {226, 149, 157, 0}; // Le coin ╝

#define    LIGNEPLUSBAS  	hd[4] =  {226, 149, 166, 0}; // Le coin ╦

#define    LIGNEPLUSHAUT  	bd[4] = {226, 149, 169, 0}; // Le coin ╩

#define    COLONNE 		col[4] = {226, 149, 145, 0}; // Les colonnes : ║
#define    LIGNE  		lig[4] = {226, 149, 144, 0}; // Les lignes : ═

// Caractères spéciaux pour Highscore ( smiley )

#define 	TOP top[5]={240, 159, 152, 129, 0}; // 😁 GRINNING FACE WITH SMILING EYES
#define 	MID mid[5]={240, 159, 152, 138, 0}; // 😊 SMILING FACE WITH SMILING EYES
#define 	BOT bot[5]={240, 159, 152, 146, 0}; // 😒 UNAMUSED FACE

// Caractères spéciaux pour le Food

#define    STAR star[4] = {226, 152, 133, 0}; //      		 ★    BLACK STAR
#define    COMET comet[4] = {226, 152, 132,0}; //     		 ☄    COMET
#define    SUNSHINE sunshine[4] = {226, 152, 128, 0}; // 	 ☀    BLACK SUN WITH RAYS
#define    CLOUD cloud[4] = {226, 152, 129, 0}; //     		 ☁    CLOUD
#define    SHAMROCK shamrock[4] = {226, 152, 152, 0}; //  	 ☘    SHAMROCK
#define    CIRCLE circle[4] = {226, 151, 143, 0}; //    	 ●    BLACK CIRCLE
#define    DIAMOND diamond[4] = {226, 151, 134, 0}; //   	 ◆    BLACK DIAMOND
#define    TRIANGLE triangle[4] = {226, 150, 178, 0}; //  	 ▲    BLACK UP-POINTING TRIANGLE
#define    RECTANGLE rectangle[4] = {226, 150, 172, 0}; // 	 ▬    BLACK RECTANGLE
#define    SQUARE square[4] = {226, 150, 170, 0}; //    	 ▪    BLACK SMALL SQUARE

// COORDONNEE

typedef struct {
    				int x; // Coord
    				int y; // Coord
} COORD;

// HIGHSCORE

typedef struct{
				    int score;
				    int timePlay;
				    int couleur;
				    char tabNom[11];
} HIGHSCORE;

// COULEUR

enum {NOIR = 30, ROUGE, VERT, JAUNE, BLEU, MAGENTA, CYAN, BLANC};   // ON DEFINIS DES COULEURS

// POUR LA FONCTION YOURCHOICE

#define MENU_START 1
#define MENU_COLOR 2
#define MENU_MODE  3

/// FONCTION PRIMAIRE

void sleepa (unsigned int a); // Endormir le programme
void mode_raw (int activer); // Mode BRUT du terminal
int kbhit (void);
void gotoxy (int x, int y); // Aller à la position (x;y)
void cleartoxy (int x, int y, int stop); // Remplace par des espaces une partie de l'écran
int rand_ab (int a, int b); // Random entre a et b : renvoi entier
double rand_0_1(); // Random entre 0 et 1 : renvoy réel
int alea_perso(double loi[], int taille); // Probabilité : en fonction de la loi[] et du nombre d'evenement (NB_EVT = Nombre d'aliment different)
void writeInColor(char texte[], int C_texte, int init); // Afficher en couleur suivant le deuxieme parametre

/// FONCTION DU FICHIER MENU.C
void printMenu (int choice ); // Affiche le Menu en fonction du choix lu au clavier
void printMenuColor (int choice, int *couleur); // Fonction complémentaire à chooseColor
void printMenuMode (int choice, int* mode); // Fonction complémentaire à chooseMode
void printAirMenu (int xmin, int ymin, int xmax, int ymax); // Affiche les bordures d'un menu par rapport à ses paramètres
void yourChoice (int touche, int* choice, int menu); // Joue avec les touches directionnels en complément de l'affichage du Menu
void chooseColor (int *couleur); // Permet au joueur de choisir une couleur
void chooseMode (int *mode); // Permet au joueur de choisir un mode

/// FONCTION AFFICHAGE GENERAL
void afficheArea (int ligne, int colonne); // On affiche l'air de jeu
int printTime (clock_t* start, clock_t* end); // Calcule et initialise le temps
void printScore (int score); // Affiche le score
int differentFood (int *score, int luckFood, int *compteurFood); // Affiche les differentes Foods en dessous de TIME et SCORE en jeu, met à jours la variable score ainsi que le tableau compteurFood

/// FONCTION HIGHSCORE
void loadhighscore(HIGHSCORE* test,char* fileScore); // Charge les highscores ( fichier vers tableau )
void printHighScore (HIGHSCORE* highScore, int message); // Affiche les highscores
int majHighScore(char* fileScore, HIGHSCORE* test , int scoreJoueur, int timeGame, int couleur); // Met à jour le fichier highscore

/// FONCTION ANIMATION SCORE
void fAnimScore(COORD* coordAnim, int* animScore, int scoreValue, COORD *theSnake, int *dir, int nbSectionSnake, int couleur); // Gere l'animation

/// FONCTION SNAKE

void smartSnake (COORD *theSnake, COORD *theFood, int *touche, int *dir); // SO SMART !
void initheSnake (int nbSectionSnake, COORD *theSnake, int colonne, int ligne);
void trietheSnake (int nbSectionSnake, COORD *theSnake, COORD headPosPrec);
void printSnake (COORD *theSnake, int *dir, int nbSectionSnake, int couleur);   // Fonction qui : affiche tête, affiche caractère corps entre la pos de la new head et du "cou", delete pose queue
void printFullSnake (COORD *theSnake, int *dir, int nbSectionSnake, int couleur); // Affiche le snake en ENTIER
void changeDirSnake (int touche, COORD *theSnake, int *dir);
void theSnakeCurve (int *dir, int *dirTmp, COORD *theSnake, int nbSectionSnake, int couleur);

/// FONCTION FOOD
void initCheckAndPrinttheFood (COORD *theFood, COORD *theSnake, int nbSectionSnake, int luckFood, int y, int x); // Init Verifie et Affiche
void printFood(COORD *theFood, int luckFood); // Affiche la food seulement

/// FONCTION VERIFICATION
int checktheSnakePosition (COORD *theSnake, int ligne, int colonne);
int checktheSnakeEatHimself (COORD *theSnake, int nbSectionSnake);

#endif
