#include <stdio.h>
#include "222006445.h"

int menuOption = 0;
char LOADING_OPTION[] = {"\nOpcao em construcao . . .\n"};
char INVALID_OPTION[] = {"\nOpcao invalida, digite um numero de 1 a 6\n"};
char FINISH_PROGRAM[] = {"\n-------------- FINALIZANDO PROGRAMA -------------\n"};

int main()
{
    menuOption = executeMenu();
    // Execute each function according to option
    switch (menuOption)
    {
    case 1:
        registerPerson();
        break;
    case 2:
        consultPerson();
        break;
    case 3:
        listPeopleByCity();
        break;
    case 4:
        printf("%s", LOADING_OPTION);
        break;
    case 5:
        printf("%s", LOADING_OPTION);
    case 6:
        printf("%s", FINISH_PROGRAM);
        break;
    default:
        printf("%s", INVALID_OPTION);
        break;
    }

    fflush(stdin);
    
    return 0;
}
