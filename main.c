#include <stdio.h>
#include "222006445.h"
#define PERSON_ATTRIBUTES 6;


int menuOption = 0;


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
    
    default:
        printf("Opcao invalida, digite um numero de 1 a 6 \n");
        break;
    }

    fflush(stdin);
    
    return 0;
}
