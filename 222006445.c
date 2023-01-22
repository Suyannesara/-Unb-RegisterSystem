#include <stdio.h>
#include "222006445.h"

int menuOption = 0;
char LOADING_OPTION[] = {"\nOpcao em construcao . . .\n"};
char INVALID_OPTION[] = {"\nOpcao invalida, digite um numero de 1 a 6\n"};
char FINISH_PROGRAM[] = {"\n-------------- FINALIZANDO PROGRAMA -------------\n"};
char INIT_APP[] = {"\n-------------------------- ATENCAO -----------------------\nCaro usuario, para funcionamento correto do programa:\n - Insira textos e caracteres em sua totalidade em letras MAIUSCULAS\n - O CPF digitado para consulta, cadastro ou outros, deve ser composto apenas de numeros\n - Os nomes das cidades e UFS devem ser escritos sem acento e em MAIUSCULO\n - A UF/ESTADO digita deve ser composta apenas de DOIS caracteres\n\n DIGITE ENTER PARA PROSSEGUIR:"};

int main()
{
    printf("%s", INIT_APP);
    scanf("%[^\n]s");
    printf("\n\n");
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
