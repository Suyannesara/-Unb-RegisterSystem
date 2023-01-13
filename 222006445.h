#include <stdio.h>
void showMenu() {
    int opt;
    printf("Escolha uma das opcoes a seguir: \n");
    printf("1) Cadastrar Pessoa \n");
    printf("2) Consultar Pessoa \n");
    printf("3) Listar pessoas por cidade \n");
    printf("4) Gerar relatório \n");
    printf("5) Excluir Pessoa \n");
    printf("6) Encerrar programa\n");

    scanf("%d", &opt);

    if (opt < 1 || opt > 6)
    {
        printf("Opcao invalida, digite um numero de 1 a 6 \n");
        return;
       
    }

    // Execute function according to option
    switch (opt)
    {
    case 1:
        registerPerson();
        break;
    
    default:
        break;
    }

}


void registerPerson(){
    typedef struct
    {
        char Name[120];
        //char Cpf[12];
    }Person;

    FILE *fp;
    Person pw;

    scanf("Nome %s", pw.Name);
    printf(pw.Name);

    
}