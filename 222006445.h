#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char Cpf[30];
    char Name[120];
    char Sex[50];
    char DtBorn[12];
    char City[40];
    char Uf[4];
} Person;

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

    // Execute function according to option
    switch (opt)
    {
    case 1:
        registerPerson();
        break;
    
    default:
        printf("Opcao invalida, digite um numero de 1 a 6 \n");
        break;
    }

    fflush(stdin);
}

void registerPerson(){
    Person pw;
    fflush(stdin);

    printf("-------------------- REGISTRO DE PESSOA --------------------\n");
    printf("Digite o CPF da pessoa: ");
    fgets(pw.Cpf, 20, stdin);
    fflush(stdin);

    printf("Digite o nome da pessoa: ");
    fgets(pw.Name, 119, stdin);
    fflush(stdin);

    printf("Digite o Sexo da pessoa: ");
    fgets(pw.Sex, 2, stdin);
    fflush(stdin);

    //FUNCTION TO VALIDATE DATAAA!!!!!
    printf("Digite a data de nascimento da pessoa: ");
    fgets(pw.DtBorn, 11, stdin);
    fflush(stdin);

    printf("Digite a cidade da pessoa: ");
    fgets(pw.City, 39, stdin);
    fflush(stdin);

    printf("Digite a UF/Estado da pessoa: ");
    fgets(pw.Uf, 3, stdin);
    fflush(stdin);

    // FILE - Writing
    FILE *fp;
    fp = fopen("person.txt", "a");

    // FILE - Check if it was successfully opened
    if (fp == NULL)
    {
        printf("Erro ao criar base de registros, inicie novamente o cadastro!\n"); 
        return;
    }
    
    //FILE - If it was ok - print on file

    fprintf(fp, "%s\n", pw.Cpf);
    fprintf(fp, "%s\n", pw.Name);
    fprintf(fp, "%s\n", pw.Sex);
    fprintf(fp, "%s\n", pw.DtBorn);
    fprintf(fp, "%s\n", pw.City);
    fprintf(fp, "%s\n", pw.Uf);
    printf("Pessoa cadastrada com sucesso! \n");

    // FILE - Close file
    fclose(fp);
}
