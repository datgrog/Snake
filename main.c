#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // fonction system dont l'algo kbhit
#include <time.h>
#include "fonction.h"

void playGameSnake (HIGHSCORE *joueur, char *fileScore, int couleur, int mode);

int main (int argc, char *argv[])
{

    #define PLAYGAME             1
    #define MODEGAME             2
    #define HIGHSCORES           3
    #define HOWTOGAME            4
    #define ENDGAME              5

    //
    // INITIALISATION DE VARIABLES AVANT LA BOUCLE DE MENU !
    //

    int choice = PLAYGAME; // Afficher seulement si changement ---> choiceTmp;
    int touche = 0;

    // Initialisation de la fonction rand() grace à srand() once
    srand(time (NULL));

    fprintf(stdout,"\e[?25l"); // DESACTIVE L'AFFICHAGE DU CURSEUR

    char fileScore[]="highscore"; /* On créer fileScore qui contient le nom exact du fichier
    conservant les 3 plus grand score avec le nom du joueur ainsi que leurs temps en durant leurs parties. */

    HIGHSCORE joueur[3];  /* On initialise une variable de type HIGHSCORE qui servira en fin de partie de partie, lorsque la boucle principale est terminer
    autrement dit quand la varible continuer == 0 pour charger et afficher les meilleurs score voir modifier le fichier qui les sauvegarde si nécessaire. */
    loadhighscore(joueur, fileScore);

    //
    // DEBUT DU PROGRAMME SELON L'UTILISATEUR !
    //

    system("clear");
    system("head start"); // On affiche le fichier start
    gotoxy(12,12);
    printf("Press Enter");

    mode_raw(1);
    while (touche != 13) {
         touche=getchar();
    }
    cleartoxy(12,12,1); // On efface le "Press Enter"

    #define YMAXMENU 20
    #define YMINMENU 10
    #define XMAXMENU 57
    #define XMINMENU 1

    //
    // BOUCLE DU MENU !
    //

    for (; choice != ENDGAME; ) {

        fflush (stdin);
        fflush (stdout);
        printAirMenu (XMINMENU, YMINMENU, XMAXMENU, YMAXMENU);
        printMenu(choice);
        touche=0; // SINON LE MENUE N'APPARAIT PAS ET IL RELANCE EN BOUCLE LE DERNIER CHOIX ENREGISTRER ! ! ! (/!\)
        int couleur=0; // La couleur n'as pas encore été choisit
        int mode = 1; // Le mode Classique par défaut

        while (touche != 13) {

            if (kbhit()) { // CAPTURE TOUCHE FRAPPE AU CLAVIER

                do {
                    touche=getchar();
                    gotoxy (12, 12);
                } while (touche != 91 && touche != 13);

                if (touche != 13) // SI LA TOUCHE APPUYE EST "ENTER", c'est que le choix est définitif donc on sort du while
                {                 // Sinon c'est qu'on souhaite parcourir le menu
                    touche=getchar();
                    yourChoice(touche, &choice, MENU_START);

                    if (choice != 13) cleartoxy (5, 13, 5);            // ON CLEAR SEULEMENT CETTE PARTIE DE L'ECRAN !

                    printMenu(choice);
                }
            }
        }

       mode_raw(0); // NECESSAIRE ICI QU'IMPORTE LE CHOIX !

        //
        // LE CHOIX DANS LE MENU EST MAINTENANT INTERPRETE
        //

        switch (choice)
        {
            case PLAYGAME :     system("clear");
                                chooseColor (&couleur);
                                system("clear");
                                playGameSnake(joueur, fileScore, couleur, mode);
                                mode_raw(0);          // ON JOUE AVEC LE MODE RAW SINON L'AFFICHAGE du fichier "start" ne s'affiche pas correctement.
                                system("head start");
                                mode_raw(1);

                                break;

            case MODEGAME :     system("clear");
                                chooseMode(&mode);
                                system("clear");
                                system("clear");
                                chooseColor (&couleur);
                                system("clear");
                                playGameSnake(joueur, fileScore, couleur, mode);
                                mode_raw(0);
                                system("clear");
                                system("head start");
                                mode_raw(1);
                                break;

            case HIGHSCORES :   touche=0; // Sinon touche est toujours = à "entrer" et on sort de la boucle while donc on ne voit rien
                                system("clear");
                                loadhighscore(joueur, fileScore); // ON CHARGE LES MEILLEURS SCORES
                                printHighScore (joueur, -1); // ON AFFICHE LES MEILLEURS SCORES. La valeur-1 indique qu'il n'y a pas de message a afficher
                                mode_raw(1);
                                while (touche != 13) {
                                     touche=getchar();
                                }
                                mode_raw(0);
                                system("clear");
                                system("head start");
                                mode_raw(1);
                                break;

            case HOWTOGAME :    system("clear");
                                system ("more instructions");
                                system("clear");
                                system("head start");
                                mode_raw(1);
                                break;

            case ENDGAME :      printf("\e[?25h"); // REACTIVE L'AFFICHAGE DU CURSEUR
                                system("clear");
                                exit(0);

                                break;
        }
    }
return 0;
}

void playGameSnake (HIGHSCORE* joueur, char *fileScore, int couleur, int mode) {

    time_t start, stop;
    time(&start);
    /* On initialise les variables du temps afin de voir le temps qui passe en jeu (en haut à droite de la console)
    mais aussi pour stocker le temps d'une partie si celle-ci fait partie des 3 plus grand score. */

    int finalTime; // LE TEMPS A LA FIN DE LA PARTIE

    int ligne = HEIGTH_AREA_GAME, colonne = WIDTH_AREA_GAME;
    /* On définit les variables ligne et colonne (respectivement la hauteur et la largeur) à l'aide de deux define.
    Sachant qu'un caractère dans la console mesure 18 pixels de hauteur et 9 pixels en largeur,
    nous avons donc choisi arbitrairement la valeur de la variable colonne afin d'obtenir la valeur de la variable ligne tel que :
    Ligne=2Colonne
    pour homogénisé l'affichage afin de ne pas avoir l'impression que le snake se déplace plus vite lorsqu'il bouge verticalement. */

    int nbSectionSnake = SIZE_SNAKE;
    // On initialise le nombre de section de snake par défault à savoir 4.

    int continuer=TRUE;
    /* On initialise une variable bouléenne "continuer" qui permettra a la boucle principale d'être infinie
    tant que celle-ci est vrai, sinon la partie est terminé. */

    int touche=68; /* On initialise la variable touche à 68 qui réfère au caractère D : on choisie ici la direction par défault que prendra le snake au début de la partie,
    à savoir la gauche (cf la fonction changeDirSnake expliqué plus tard).*/

    int toucheEscape=FALSE;  // Permet de quitter la partie si l'on appuy sur 'q'
    int dir=TOLEFT, dirTmp=TOLEFT; // INDIQUE LA DIRECTION POUR CHANGER SA TETE CORRECTEMENT / TMP QUAND CHANGEDIR
    /*Les variables dir et dirTmp permettent de savoir la direction du snake respectivement aux instant t et t-1 sachant :
    #define TOTOP       1
    #define TOBOTTOM    2
    #define TORIGHT     3
    #define TOLEFT      4
    */

    int vitesse=175000; /* On initialise la variable "vitesse" qui sevira a ralentir le programme à l'aide de la fonction usleep pour voir le snake ce déplacer "lentement" au début. */

    int nbFood=0;
    // La variable "nbFood" permet de savoir si un aliment est afficher, si c'est le cas nbFood vaut 1, 0 sinon.

    const int NB_EVT=10; // Nombre d'evenement autrement dit le nombre de different food du jeu
    double loi[10]={0.200000, 0.160000, 0.134218, 0.128000, 0.102400, 0.081920, 0.065536, 0.052429, 0.041943, 0.033554}; // La loi de probabilité qu'on a définis pour chaque élément
    int luckFood=0; // Détermine le Food "aléatoirement"
    int compteurFood[11]={0};

    int score=0;

    // ANIMATION SCORE
    int phaseAnimScore=0; // Contient l'étape de l'animation
    int animScoreValue=0; // Valeur du score marqué
    COORD sAnimScore={0,0}; // Coordonnée de l'animation du score
    int animEnCours=0; // Y'a t-il une animation en cours ?

    system("clear");

    COORD theFood, headPosPrec, theSnake[684]; // ligne*colonne-(2*colonne+2*(ligne-2)) La taille maximum que peut prendre le snake;
    // - theFood pour afficher la nourriture à un endroit précis (cf initCheckAndPrinttheFood )
    // - headPosPrec permettant de savoir les coordonnées de la tête à l'instant t-1, pilier de la fonction déplacement (cf trietheSnake).
    // - theSnake[] de taille 684 correspondant à la formule : ligne*colonne-(2*colonne+2*(ligne-2))

    theFood.x=0;
    theFood.y=0;
    headPosPrec.x=0;
    headPosPrec.y=0;

    COORD aiguille; int nbAiguille=0; // Pour le mode 2
    aiguille.x=0;
    aiguille.y=0;

    initheSnake (nbSectionSnake, theSnake, colonne, ligne);
    afficheArea (ligne, colonne);
    mode_raw (1);
    /* Ensuite on initialise le snake au milieu du plateau de jeu de taille 4. On affiche la plateau de jeu et seulement après
    on active le mode brute pour ne pour voir les éléments lu au clavier par la fonction kbhit sans appuyer sur entrer
    sinon l'affichage ne fonctionne pas (caractère dans tous les sens). */

    differentFood (&score, luckFood, compteurFood); /* Le paramètre LuckFood ne sera égal à 0 uniquement ICI,
    ainsi dans la fonction on affichera qu'une seule fois les Foods différents en dessous du temps et du score */

    printSnake (theSnake, &dir, nbSectionSnake, couleur); // On affiche une première fois le snake.

    ////////////////////
    // BOUCLE PRINCIPALE
    ////////////////////

    while (continuer==1) { // boucle bouléen qui ne s'arrêtera uniquement lorsque la partie sera terminé

        fflush (stdin);
        fflush (stdout);

        if (dir != dirTmp) {
                            theSnakeCurve (&dir, &dirTmp, theSnake, nbSectionSnake, couleur);
                            dirTmp=dir;
        }
        /*
        Ensuite, on regarde si la direction du snake à changer par rapport à l'itération précédente en comparant dir et dirTmp,
        si oui alors pour créer l'illusion du virage on va utiliser theSnakeCurve,
        ensuite on affecte à dirTmp la direction du snake à l'instant t (qui sera utilisé comme une valeur de t-1 car la valeur de dir va changer).
        Sinon la snake continue horizontalement ou verticalement (dir==dirTmp).
        */
        /* Ainsi grâce à dir et dirTmp on connait la direction du snake à l'instant t et t-1 afin d'afficher des éléments différents en fonction de ses deux variables,
        notamment la tête du snake dans la fonction printSnake ainsi que le caractère qui permet de voir le snake faire un "virage" avec theSnakeCurve */

        if (mode == 3 ) smartSnake (theSnake, &theFood, &touche, &dir);

        fprintf (stdout, "\n"); // TEST POUR MOI

        usleep (vitesse); // TEMPORISATION
        /* Vient l'endormissement du programme pour permettre de voir le snake à l'oeil nu en fonction de la variable vitesse qui décrémente lorsqu'un aliment mangé
        (lorsque la variable vitesse décrémente l’endormissement du programme est moindre donc on voit le snake bouger plus rapidement). */

        headPosPrec = theSnake[THEHEAD];
        // On remarque ensuite la ligne suivante "headPosPrec = theSnake[THEHEAD];". Tout comme la variable dirTmp, headPosPrec servira comme une valeur de t-1.

        if (kbhit()) { // CAPTURE TOUCHE FRAPPE AU CLAVIER
            do {
               touche=getchar();
            } while (touche!=91 && touche!= 113);

            if (touche == 113) toucheEscape = TRUE; // REVENIR AU MENU
            else touche=getchar();
        }

        /* Lorsqu'on appuie sur une touche directionnel celle-ci renvoie 3 valeurs dans le buffer à savoir respectivement 27 91 X ( X dépend de la touche appuyé)
        Par exemple quand X == 68 cela correspond à la flèche directionnel gauche, c'est pourquoi au tout début nous avons initialisé la variable touche à 68.
        #define TOUCH_TOP       65
        #define TOUCH_BOTTOM    66
        #define TOUCH_RIGHT     67
        #define TOUCH_LEFT      68
        Donc on créer une boucle qui ne sort uniquement lorsque 91 est lu
        pour ensuite lire LA valeur qui nous intéresse qui permet d'indiquer la direction.
        Sinon on sort lorsque la valeur 113 est lu correspondant à la lettre q permettant de quitter la partie.
        */

        continuer = checktheSnakePosition(theSnake,ligne,colonne);
        if (toucheEscape==TRUE) continuer=FALSE;
        if (continuer) continuer= checktheSnakeEatHimself(theSnake,nbSectionSnake);
        if (continuer) {

            if (mode == 1 || mode == 3) {                                                                  // MODE CLASSIQUE OU SMARTSNAKE

                if ((theSnake[THEHEAD].x == theFood.x) && (theSnake[THEHEAD].y == theFood.y)) {

                    if (dir != TOLEFT ) { gotoxy(theFood.x+1,theFood.y); fprintf(stdout, " "); }
                    /* L'image d'un Food prend deux cases et le Food est généré sur la case de gauche,
                    donc quand theSnake[THEHEAD] viens par la gauche l'image de la case de droite est aussi mangé, sinon est "reste" dans l'air de jeu. */
                    nbSectionSnake++;
                    animScoreValue = differentFood (&score, luckFood, compteurFood); // MAJ SCORE
                    nbFood = 0;
                    // ANIMATION SCORE
                    phaseAnimScore=1;
		            sAnimScore.x=theSnake[THEHEAD].x+1;
		            sAnimScore.y=theSnake[THEHEAD].y;
		            animEnCours=2;
                    if (vitesse >= 100000) vitesse -= 1500;
                }

                finalTime = printTime (&start, &stop);
                printScore (score);

                changeDirSnake (touche, theSnake, &dir);
                trietheSnake (nbSectionSnake, theSnake, headPosPrec);

                if (nbFood == 0) {
                    luckFood=alea_perso(loi,NB_EVT);
                    initCheckAndPrinttheFood (&theFood, theSnake, nbSectionSnake, luckFood, ligne, colonne);
                    nbFood=1;
                }

                // ANIMATION SCORE
        	    // Si on a une animation en cours
        	    if ((phaseAnimScore > 0 && animEnCours==1) || animEnCours==2) {
            		if (animEnCours == 2) {
            			animEnCours=1;
            		}
            		fAnimScore(&sAnimScore, &phaseAnimScore, animScoreValue, theSnake, &dir, nbSectionSnake, couleur);
            		if (phaseAnimScore > 4) {
            			phaseAnimScore=0;
            			animEnCours=0;
            		}
            		printFood(&theFood, luckFood); // si la food généré est sous l'animation alors réaffiche le food pour éviter un bug d'affichage
        	    }

            }
            if (mode == 2) { // AIGUILLE DANS UNE BOTTE DE FOIN

                if ((theSnake[THEHEAD].x == aiguille.x) && (theSnake[THEHEAD].y == aiguille.y)) {
                if (dir != TOLEFT ) { gotoxy(theFood.x+1,theFood.y); fprintf(stdout, " "); }
                nbSectionSnake++;
                differentFood (&score, luckFood, compteurFood); // MAJ SCORE
                nbAiguille = 0;
                if (vitesse >= 100000) vitesse -= 1500;
                }

                finalTime = printTime (&start, &stop);
                printScore (score);

                changeDirSnake (touche, theSnake, &dir);
                trietheSnake (nbSectionSnake, theSnake, headPosPrec);

                luckFood=alea_perso(loi,NB_EVT);
                initCheckAndPrinttheFood (&theFood, theSnake, nbSectionSnake, luckFood, ligne, colonne);

                if (nbAiguille == 0) { aiguille.x=theFood.x; aiguille.y=theFood.y; nbAiguille=1; }
                }
             printSnake (theSnake, &dir, nbSectionSnake, couleur);
            }
        }
    // FIN BOUCLE PRINCIPALE ON PROCEDE MAINTENANT A L'AFFICHAGE DES HIGHSCORES
    int message=-1; // Dans la fonction majHighScore si nouveau score on renvoi 0, 1 ou 2 donc différent message -1 sinon donc on par du principe qu'il n'y a pas de nouveau highscore
    mode_raw(0);
    system("clear"); // CLEAN LE JEU
    system("head finish");
    mode_raw(1);
    gotoxy(12,12);
    printf("Press Enter");
    while (touche != 13) {
             touche=getchar();
    }
    system("clear"); // CLEAN LE GAME OVER
    mode_raw(0); // POUR VOIR CE QUE L'ON ECRIT (Si meilleur score)
    message = majHighScore(fileScore, joueur, score, finalTime, couleur);
    printHighScore (joueur, message); // ON AFFICHE LES MEILLEURS SCORES
    mode_raw(1);
    touche=0; // Sinon touche est toujours = à "entrer" et on sort de la boucle while donc on ne voit rien
    while (touche != 13) {
             touche=getchar();
    }
    system("clear");
}
