#include <stdio.h>
#include <time.h>
#include "fonction.h"

void printMenu (int choice ) {

    unsigned char HORIZONTALBODY;
    gotoxy (5, 11);
    fprintf (stdout,"Bienvenue dans le projet snake, faites un choix :");

    if (choice == 1)
    {
        gotoxy (10, 13);
        fprintf (stdout,"%s%s%s%s> - Jouer !\n",lig,lig,lig,lig);
        gotoxy (10, 14);
        fprintf (stdout,"- Mode\n");
        gotoxy (10, 15);
        fprintf (stdout,"- HighScore\n");
        gotoxy (10, 16);
        fprintf (stdout,"- Instructions\n");
        gotoxy (10, 17);
        fprintf (stdout,"- Quitter\n");
    }

    if (choice == 2)
    {
        gotoxy (10, 13);
        fprintf (stdout,"- Jouer !\n");
        gotoxy (10, 14);
        fprintf (stdout,"%s%s%s%s> - Mode!\n",lig,lig,lig,lig);
        gotoxy (10, 15);
        fprintf (stdout,"- HighScore\n");
        gotoxy (10, 16);
        fprintf (stdout,"- Instructions\n");
        gotoxy (10, 17);
        fprintf (stdout,"- Quitter\n");
    }

    if (choice == 3)
    {
        gotoxy (10, 13);
        fprintf (stdout,"- Jouer !\n");
        gotoxy (10, 14);
        fprintf (stdout,"- Mode!\n");
        gotoxy (10, 15);
        fprintf (stdout,"%s%s%s%s> HighScore\n",lig,lig,lig,lig);
        gotoxy (10, 16);
        fprintf (stdout,"- Instructions\n");
        gotoxy (10, 17);
        fprintf (stdout,"- Quitter\n");
    }

    if (choice == 4)
    {
        gotoxy (10, 13);
        fprintf (stdout,"- Jouer !\n");
        gotoxy (10, 14);
        fprintf (stdout,"- Mode!\n");
        gotoxy (10, 15);
        fprintf (stdout,"- HighScore\n");
        gotoxy (10, 16);
        fprintf (stdout,"%s%s%s%s> Instructions\n",lig,lig,lig,lig);
        gotoxy (10, 17);
        fprintf (stdout,"- Quitter\n");
    }
    if (choice == 5)
    {
        gotoxy (10, 13);
        fprintf (stdout,"- Jouer !\n");
        gotoxy (10, 14);
        fprintf (stdout,"- Mode!\n");
        gotoxy (10, 15);
        fprintf (stdout,"- HighScore\n");
        gotoxy (10, 16);
        fprintf (stdout,"- Instructions\n");
        gotoxy (10, 17);
        fprintf (stdout,"%s%s%s%s>  Quitter\n",lig,lig,lig,lig);
    }
}

void printMenuColor (int choice, int* couleur) {

unsigned char HORIZONTALBODY;

    if (choice == 1)
    {
        gotoxy (15,6);
        writeInColor("",NOIR,0); fprintf (stdout,"%s%s%s%s> - Noir\n",lig,lig,lig,lig); writeInColor("",NOIR,1);
        gotoxy (15, 7);
        writeInColor("",ROUGE,0); fprintf (stdout,"- ROUGE\n"); writeInColor("",ROUGE,1);
        gotoxy (15, 8);
        writeInColor("",VERT,0); fprintf (stdout,"- VERT\n"); writeInColor("",VERT,1);
        gotoxy (15, 9);
        writeInColor("",JAUNE,0); fprintf (stdout,"- JAUNE\n"); writeInColor("",JAUNE,1);
        gotoxy (15, 10);
        writeInColor("",BLEU,0); fprintf (stdout,"- BLEU\n"); writeInColor("",BLEU,1);
        gotoxy (15, 11);
        writeInColor("",MAGENTA,0); fprintf (stdout,"- MAGENTA\n"); writeInColor("",MAGENTA,1);
        gotoxy (15, 12);
        writeInColor("",CYAN,0); fprintf (stdout,"- CYAN\n"); writeInColor("",CYAN,1);
    *couleur=NOIR;
    }

    if (choice == 2)
    {
        gotoxy (15,6);
        writeInColor("",NOIR,0); fprintf (stdout,"- Noir\n"); writeInColor("",NOIR,1);
        gotoxy (15, 7);
        writeInColor("",ROUGE,0); fprintf (stdout,"%s%s%s%s> - ROUGE\n",lig,lig,lig,lig); writeInColor("",ROUGE,1);
        gotoxy (15, 8);
        writeInColor("",VERT,0); fprintf (stdout,"- VERT\n"); writeInColor("",VERT,1);
        gotoxy (15, 9);
        writeInColor("",JAUNE,0); fprintf (stdout,"- JAUNE\n"); writeInColor("",JAUNE,1);
        gotoxy (15, 10);
        writeInColor("",BLEU,0); fprintf (stdout,"- BLEU\n"); writeInColor("",BLEU,1);
        gotoxy (15, 11);
        writeInColor("",MAGENTA,0); fprintf (stdout,"- MAGENTA\n"); writeInColor("",MAGENTA,1);
        gotoxy (15, 12);
        writeInColor("",CYAN,0); fprintf (stdout,"- CYAN\n"); writeInColor("",CYAN,1);
    *couleur=ROUGE;
    }

    if (choice == 3)
    {
        gotoxy (15,6);
        writeInColor("",NOIR,0); fprintf (stdout,"- Noir\n"); writeInColor("",NOIR,1);
        gotoxy (15, 7);
        writeInColor("",ROUGE,0); fprintf (stdout,"- ROUGE\n"); writeInColor("",ROUGE,1);
        gotoxy (15, 8);
        writeInColor("",VERT,0); fprintf (stdout,"%s%s%s%s> - VERT\n",lig,lig,lig,lig); writeInColor("",VERT,1);
        gotoxy (15, 9);
        writeInColor("",JAUNE,0); fprintf (stdout,"- JAUNE\n"); writeInColor("",JAUNE,1);
        gotoxy (15, 10);
        writeInColor("",BLEU,0); fprintf (stdout,"- BLEU\n"); writeInColor("",BLEU,1);
        gotoxy (15, 11);
        writeInColor("",MAGENTA,0); fprintf (stdout,"- MAGENTA\n"); writeInColor("",MAGENTA,1);
        gotoxy (15, 12);
        writeInColor("",CYAN,0); fprintf (stdout,"- CYAN\n"); writeInColor("",CYAN,1);
    *couleur=VERT;
    }

    if (choice == 4)
    {
        gotoxy (15,6);
        writeInColor("",NOIR,0); fprintf (stdout,"- Noir\n"); writeInColor("",NOIR,1);
        gotoxy (15, 7);
        writeInColor("",ROUGE,0); fprintf (stdout,"- ROUGE\n"); writeInColor("",ROUGE,1);
        gotoxy (15, 8);
        writeInColor("",VERT,0); fprintf (stdout,"- VERT\n"); writeInColor("",VERT,1);
        gotoxy (15, 9);
        writeInColor("",JAUNE,0); fprintf (stdout,"%s%s%s%s> - JAUNE\n",lig,lig,lig,lig); writeInColor("",JAUNE,1);
        gotoxy (15, 10);
        writeInColor("",BLEU,0); fprintf (stdout,"- BLEU\n"); writeInColor("",BLEU,1);
        gotoxy (15, 11);
        writeInColor("",MAGENTA,0); fprintf (stdout,"- MAGENTA\n"); writeInColor("",MAGENTA,1);
        gotoxy (15, 12);
        writeInColor("",CYAN,0); fprintf (stdout,"- CYAN\n"); writeInColor("",CYAN,1);
    *couleur=JAUNE;
    }
    if (choice == 5)
    {
        gotoxy (15,6);
        writeInColor("",NOIR,0); fprintf (stdout,"- Noir\n"); writeInColor("",NOIR,1);
        gotoxy (15, 7);
        writeInColor("",ROUGE,0); fprintf (stdout,"- ROUGE\n"); writeInColor("",ROUGE,1);
        gotoxy (15, 8);
        writeInColor("",VERT,0); fprintf (stdout,"- VERT\n"); writeInColor("",VERT,1);
        gotoxy (15, 9);
        writeInColor("",JAUNE,0); fprintf (stdout,"- JAUNE\n"); writeInColor("",JAUNE,1);
        gotoxy (15, 10);
        writeInColor("",BLEU,0); fprintf (stdout,"%s%s%s%s> - BLEU\n",lig,lig,lig,lig); writeInColor("",BLEU,1);
        gotoxy (15, 11);
        writeInColor("",MAGENTA,0); fprintf (stdout,"- MAGENTA\n"); writeInColor("",MAGENTA,1);
        gotoxy (15, 12);
        writeInColor("",CYAN,0); fprintf (stdout,"- CYAN\n"); writeInColor("",CYAN,1);
    *couleur=BLEU;
    }
    if (choice == 6)
    {
        gotoxy (15,6);
        writeInColor("",NOIR,0); fprintf (stdout,"- Noir\n"); writeInColor("",NOIR,1);
        gotoxy (15, 7);
        writeInColor("",ROUGE,0); fprintf (stdout,"- ROUGE\n"); writeInColor("",ROUGE,1);
        gotoxy (15, 8);
        writeInColor("",VERT,0); fprintf (stdout,"- VERT\n"); writeInColor("",VERT,1);
        gotoxy (15, 9);
        writeInColor("",JAUNE,0); fprintf (stdout,"- JAUNE\n"); writeInColor("",JAUNE,1);
        gotoxy (15, 10);
        writeInColor("",BLEU,0); fprintf (stdout,"- BLEU\n"); writeInColor("",BLEU,1);
        gotoxy (15, 11);
        writeInColor("",MAGENTA,0); fprintf (stdout,"%s%s%s%s> - MAGENTA\n",lig,lig,lig,lig); writeInColor("",MAGENTA,1);
        gotoxy (15, 12);
        writeInColor("",CYAN,0); fprintf (stdout,"- CYAN\n"); writeInColor("",CYAN,1);
    *couleur=MAGENTA;
    }
    if (choice == 7)
    {
        gotoxy (15,6);
        writeInColor("",NOIR,0); fprintf (stdout,"- Noir\n"); writeInColor("",NOIR,1);
        gotoxy (15, 7);
        writeInColor("",ROUGE,0); fprintf (stdout,"- ROUGE\n"); writeInColor("",ROUGE,1);
        gotoxy (15, 8);
        writeInColor("",VERT,0); fprintf (stdout,"- VERT\n"); writeInColor("",VERT,1);
        gotoxy (15, 9);
        writeInColor("",JAUNE,0); fprintf (stdout,"- JAUNE\n"); writeInColor("",JAUNE,1);
        gotoxy (15, 10);
        writeInColor("",BLEU,0); fprintf (stdout,"- BLEU\n"); writeInColor("",BLEU,1);
        gotoxy (15, 11);
        writeInColor("",MAGENTA,0); fprintf (stdout,"- MAGENTA\n"); writeInColor("",MAGENTA,1);
        gotoxy (15, 12);
        writeInColor("",CYAN,0); fprintf (stdout,"%s%s%s%s> - CYAN\n",lig,lig,lig,lig); writeInColor("",CYAN,1);
    *couleur=CYAN;
    }
}

void printMenuMode(int choice, int *mode) {

unsigned char HORIZONTALBODY;

    if (choice == 1)
    {
    	gotoxy (8,6);
    	writeInColor("",NOIR,0); fprintf (stdout,"%s%s%s%s> - Classique\n",lig,lig,lig,lig); writeInColor("",NOIR,1);
        gotoxy (8,8);
        writeInColor("",ROUGE,0); fprintf (stdout,"- Chercher un aiguille dans une botte de Foin\n"); writeInColor("",ROUGE,1);
        gotoxy (8,10);
        writeInColor("",BLEU,0); fprintf (stdout,"-  SmartSnake, le serpend malin, ou pas\n"); writeInColor("",BLEU,1);
    *mode=1;
    }

    if (choice == 2)
    {
    	gotoxy (8,6);
    	writeInColor("",NOIR,0); fprintf (stdout,"- Classique\n"); writeInColor("",NOIR,1);
        gotoxy (8,8);
        writeInColor("",ROUGE,0); fprintf (stdout,"%s%s%s%s> - Chercher un aiguille dans une botte de Foin\n",lig,lig,lig,lig); writeInColor("",ROUGE,1);
        gotoxy (8,10);
        writeInColor("",BLEU,0); fprintf (stdout,"-  SmartSnake, le serpend malin, ou pas\n"); writeInColor("",BLEU,1);
    *mode=2;
    }

    if (choice == 3)
    {
		gotoxy (8,6);
    	writeInColor("",NOIR,0); fprintf (stdout,"- Classique\n"); writeInColor("",NOIR,1);
        gotoxy (8,8);
        writeInColor("",ROUGE,0); fprintf (stdout,"- Chercher un aiguille dans une botte de Foin\n"); writeInColor("",ROUGE,1);
        gotoxy (8,10);
        writeInColor("",BLEU,0); fprintf (stdout,"%s%s%s%s> - SmartSnake, le serpend malin, ou pas\n",lig,lig,lig,lig); writeInColor("",BLEU,1);
    *mode=3;
    }
}

// Fonction pour choisir le mode de jeu
void chooseMode (int *mode) {

    #define YMAXMODE 13
    #define YMINMODE 3
    #define XMAXMODE 75
    #define XMINMODE 6

    int x = XMINMODE;
    int y = YMINMODE;

    int choice = 1;
    int touche = 0;

    gotoxy(x,y);
    printAirMenu(XMINMODE, YMINMODE, XMAXMODE, YMAXMODE);

    gotoxy((XMAXMODE)/2-8,YMINMODE+1);
    fprintf (stdout, "Choose Your Mode !");
    printMenuMode(choice, &(*mode));

    mode_raw(1);
    while (touche != 13) {

        if (kbhit()) { // CAPTURE TOUCHE FRAPPE AU CLAVIER

            do {
                touche=getchar();
            } while (touche != 91 && touche != 13);

            if (touche != 13) // SI LA TOUCHE APPUYE EST "ENTER", c'est que le choix est définitif donc on sort du while
            {                 // Sinon c'est qu'on souhaite parcourir le menu
                touche=getchar();
                yourChoice(touche, &choice, MENU_MODE );

                if (choice != 13) { cleartoxy (15, 6, 5); cleartoxy (35, 6, 5); } // ON CLEAR SEULEMENT CETTE PARTIE DE L'ECRAN !

                printMenuMode(choice, &(*mode));
            }
        }
    }
    mode_raw(0);
}

// Fonction pour choisir la couleur du Snake en début de jeu
void chooseColor (int *couleur) {

    #define YMAXCOLOR 15
    #define YMINCOLOR 3
    #define XMAXCOLOR 48
    #define XMINCOLOR 6

    int x = XMINCOLOR;
    int y = YMINCOLOR;

    int choice = 1;
    int touche = 0;

    gotoxy(x,y);
    printAirMenu(XMINCOLOR, YMINCOLOR, XMAXCOLOR, YMAXCOLOR);

    gotoxy((XMAXCOLOR)/2-11,YMINCOLOR+1);
    fprintf (stdout, "Choose Your Favorite Color !");
    printMenuColor(choice, &(*couleur));

    mode_raw(1);
    while (touche != 13) {

        if (kbhit()) { // CAPTURE TOUCHE FRAPPE AU CLAVIER

            do {
                touche=getchar();
            } while (touche != 91 && touche != 13);

            if (touche != 13) // SI LA TOUCHE APPUYE EST "ENTER", c'est que le choix est définitif donc on sort du while
            {                 // Sinon c'est qu'on souhaite parcourir le menu
                touche=getchar();
                yourChoice(touche, &choice, MENU_COLOR );

                if (choice != 13) cleartoxy (15, 6, 8);   // ON CLEAR SEULEMENT CETTE PARTIE DE L'ECRAN !

                printMenuColor(choice, &(*couleur));
            }
        }
    }
    mode_raw(0);
}

// Fonction gerant les déplacements dans les menus
void yourChoice (int touche, int* choice, int menu) {

    switch(touche) {

    case TOUCH_TOP :    *choice=*choice-1;
                        if (*choice == 0)
                        {
                            if (menu == MENU_START) *choice=5;
                            if (menu == MENU_COLOR) *choice=7;
                            if (menu == MENU_MODE)  *choice=3;
                        }
                        break;

    case TOUCH_BOTTOM : *choice=*choice+1;
                        if (menu == MENU_START) {
                            if (*choice == 6)
                            {
                                *choice=1;
                            }
                            break;
                        }
                        if (menu == MENU_COLOR) {
                            if (*choice == 8)
                            {
                            *choice=1;
                            }
                        break;
                        }
                        if (menu == MENU_MODE) {
                            if (*choice == 4)
                            {
                            *choice=1;
                            }
                        break;
                        }
    }
}
