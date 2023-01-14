#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i = 0;
int isCpfValid = 0;

typedef struct {
    char Cpf[15];
    char Name[120];
    char Sex[4];
    int MonthBorn;
    int DayBorn;
    int yearBorn;
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


// VALIDATIONS

int validateCpf(char cpf[])
{
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0; ///se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}


void registerPerson(){
    Person pw;
    fflush(stdin);

    printf("-------------------- REGISTRO DE PESSOA --------------------\n");
    printf("Digite o CPF da pessoa: ");
    scanf("%s", pw.Cpf);

    isCpfValid = validateCpf(pw.Cpf);
    if(isCpfValid == 1){
        printf("CPF inválido, favor reiniciar cadastro\n");
        return;
    }
    
    fflush(stdin);

    printf("Digite o nome da pessoa: ");
    scanf("%[^\n]s", pw.Name);
    fflush(stdin);

    printf("Digite o Sexo da pessoa: ");
    scanf("%s", pw.Sex);
    fflush(stdin);

    // //FUNCTION TO VALIDATE DATAAA!!!!!
    printf("Dia Nascimento: ");
    scanf("%d", &pw.DayBorn);
    fflush(stdin);

    printf("Mês Nascimento: ");
    scanf("%d", &pw.MonthBorn);
    fflush(stdin);

    printf("Ano Nascimento: ");
    scanf("%d", &pw.yearBorn);
    fflush(stdin);

    printf("Digite a cidade da pessoa: ");
    scanf("%[^\n]s", pw.City);
    fflush(stdin);

    printf("Digite a UF/Estado da pessoa: ");
    scanf("%s", pw.Uf);
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
    fprintf(fp, "%d%d%d\n", pw.DayBorn, pw.MonthBorn, pw.yearBorn);
    fprintf(fp, "%s\n", pw.City);
    fprintf(fp, "%s\n", pw.Uf);
    printf("Pessoa cadastrada com sucesso! \n");

    // FILE - Close file
    fclose(fp);
}
