#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i = 0;
int isCpfValid = 0;

typedef struct {
    char Cpf[16];
    char Name[120];
    char Sex[2];
    int MonthBorn;
    int DayBorn;
    int yearBorn;
    char City[40];
    char Uf[3];
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
    int i, d1, d2, r;
    int digits[11];

    if (strlen(cpf) != 11)
    {
        printf("O cpf deve ter 11 digitos sem '.' ou '-'");
        return 0;
    }
    
    // Check for invalid caracthers and repeated digits
    for (i = 0; i < 11; i++) {
        if (!isdigit(cpf[i]) || (digits[i] = cpf[i] - '0') == digits[i+1]) {
            return 0;
        }
    }

    // Calculate first digit
    d1 = 0;
    for (i = 0; i < 9; i++) {
        d1 += digits[i] * (10 - i);
    }
    r = 11 - (d1 % 11);
    if (r == 10 || r == 11) {
        r = 0;
    }
    if (r != digits[9]) {
        return 0;
    }

    // Calculate second digit
    d2 = 0;
    for (i = 0; i < 10; i++) {
        d2 += digits[i] * (11 - i);
    }
    r = 11 - (d2 % 11);
    if (r == 10 || r == 11) {
        r = 0;
    }
    if (r != digits[10]) {
        return 0;
    }

    return 1;
}


void registerPerson(){
    Person pw;
    fflush(stdin);

    printf("-------------------- REGISTRO DE PESSOA --------------------\n");
    printf("Digite o CPF da pessoa: ");
    fgets(pw.Cpf, 15, stdin);
    pw.Cpf[strcspn(pw.Cpf, "\n")] = '\0';

    isCpfValid = validateCpf(pw.Cpf);
    if(isCpfValid == 0){
        printf("CPF inválido, favor reiniciar cadastro\n");
        return;
    }

    printf("Digite o nome da pessoa: ");
    scanf("%[^\n]s", pw.Name);

    printf("Digite o Sexo da pessoa: ");
    scanf("%s", pw.Sex);

    // //FUNCTION TO VALIDATE DATAAA!!!!!
    printf("Dia Nascimento: ");
    scanf("%d", &pw.DayBorn);

    printf("Mês Nascimento: ");
    scanf("%d", &pw.MonthBorn);

    printf("Ano Nascimento: ");
    scanf("%d", &pw.yearBorn);
    fflush(stdin);

    printf("Digite a cidade da pessoa: ");
    fgets(pw.City, sizeof(pw.City), stdin);
    pw.City[strcspn(pw.City, "\n")] = '\0';

    printf("Digite a UF/Estado da pessoa: ");
    // verificar se a UF digitada tem somente 2 digitos?
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
