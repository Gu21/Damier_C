#include "main.h"

int main()
{
    int choix = 0;

    while(1)
    {
        choix = menu();

        switch(choix)
        {
            case 1:     // PvP
                game(0, 0, 0);
                break;

            case 2:     // PvE
                //game(0, 1);
                printf("Et bah nan, on a eu la flemme de faire une IA, bonne journee !\n");
                return 0;

            case 3:
                game(0, 0, 1);
                break;

            case 4:     // Quitter
                return 0;

            default:
                printf("Choix inconnu");
                break;
        }
    }
}
