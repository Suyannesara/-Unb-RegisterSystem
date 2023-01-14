#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <ctype.h>

int i = 0;
int isCpfValid, isInputValid = 0;
int isElementPresentInGroup = 0;
char reset[] = {"-------------Reinicie a Aplicação ------------"};
char locationsRows[10];
int ufExists;

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

typedef struct
{
    char Uf[3];
    char Name[120];
    
} Locations;

Locations locations[1000];


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

    // check if string is 11 characters long
    if (strlen(cpf) != 11)
    {
        printf("Invalid CPF: Must be 11 digits long.\n");
        return 0;
    }

    // check if string contains only digits
    for (i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i]))
        {
            printf("Invalid CPF: Must contain only digits.\n");
            return 0;
        }
        digits[i] = cpf[i] - '0';
    }

    // check for invalid CPF numbers according to the Ministry of Agriculture in Brazil
    // check if all digits are the same
    for (i = 1; i < 11; i++) {
        if (digits[i] != digits[0]) {
            break;
        }
    }
    if (i == 11) {
        printf("Invalid CPF: All digits are the same.\n");
        return 0;
    }

    // calculate first verification digit
    d1 = 0;
    for (i = 0; i < 9; i++)
    {
        d1 += digits[i] * (10 - i);
    }
    r = 11 - (d1 % 11);
    if (r == 10 || r == 11)
    {
        r = 0;
    }
    if (r != digits[9])
    {
        printf("Invalid CPF: Incorrect first verification digit.\n");
        return 0;
    }

    // calculate second verification digit
    d2 = 0;
    for (i = 0; i < 10; i++)
    {
        d2 += digits[i] * (11 - i);
    }
    r = 11 - (d2 % 11);
    if (r == 10 || r == 11)
    {
        r = 0;
    }
    if (r != digits[10])
    {
        printf("Invalid CPF: Incorrect second verification digit.\n");
        return 0;
    }

    printf("Valid CPF number!\n");
    return 1;
}


int checkIfInputIsValid(char input[], int maxChar){  
    // strlen(input <= maxChar) ? (continue) : (return 0);
    int inputLen = strlen(input);

    // Checks if maximum length is attendend
    if (!(inputLen < maxChar) || (inputLen == 0))
    {
        printf("Voce ultrapassou o limite de caracteres para esse campo!\n %s", reset);
        exit(0);
    }

    // issspace - check if it is a blank space
    for (int i=0; i < inputLen; i++) {
        if(!(input[i] >= 'A' && input[i] <= 'Z' || input[i] >= 'a' && input[i] <= 'z' || input[i] == ' '))
        {
            printf("Os inputs conter apenas letras ou espaços!\n %s", reset);
            exit(0);
        }
    }

    return 1;
}


int checkIfLocationExists(char userInput[], int locationType){

    int size = 0;
    char line[5572];
    char *ufToken;
    char *cityTokenNoAccent;
    char *cityToken;

    FILE *fp2 = fopen("locations.csv", "r");
    if (fp2 == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    if (locationType == 1)
    {
        size = 0;
        // VERRIFY UF
        while (fgets(line, sizeof(line), fp2)) {
        ufToken = strtok(line, ",");
        ufToken = strtok(NULL, ",");
        // strcpy(locations[size].Uf, token);

        // VERIFICAR SE O TOKEN == INPUT - SES IM, UF EXISTE
        if(strcmp(userInput, ufToken) == 0){
            return 1;
        }
        size++;
        }
    }
       
    if (locationType == 0)
    {
        // VERIFY CITY
        while (fgets(line, sizeof(line), fp2)) {
        cityToken = strtok(line, ","); // ignore the first column
        cityToken = strtok(NULL, ","); // ignore the second column
        cityToken = strtok(NULL, ",");
        cityTokenNoAccent = strtok(NULL, ",");;

        // VERIFICAR SE O TOKEN == INPUT - SES IM, UF EXISTE
        if((strcmp(userInput, cityToken) == 0) || (strcmp(userInput, cityTokenNoAccent) == 0)){
            return 1;
        }
        size++;
        }
    }
    
    // Close the file
    fclose(fp2);

    return 0;
}

void registerPerson(){
    Person pw;
    fflush(stdin);

    printf("-------------------- REGISTRO DE PESSOA --------------------\n");
    printf("CPF: ");
    fgets(pw.Cpf, 15, stdin);
    pw.Cpf[strcspn(pw.Cpf, "\n")] = '\0';
    isCpfValid = validateCpf(pw.Cpf);
    if (isCpfValid == 0)
    {
        exit(0);
    }
    

    printf("Nome: ");
    scanf("%[^\n]s", pw.Name);
    checkIfInputIsValid(pw.Name, sizeof(pw.Name));

    printf("Sexo (F - Feminino, M - Masculino): ");
    scanf("%s", pw.Sex);
    if (!pw.Sex == "F" ||pw.Sex == 'M'){
        printf("O sexo digitado deve ser F ou M\n %s", reset);
        exit(0);
    }
    
    checkIfInputIsValid(pw.Sex, sizeof(pw.Sex));

    //FUNCTION TO VALIDATE DATAAA!!!!!
    printf("Dia Nascimento: ");
    scanf("%d", &pw.DayBorn);

    printf("Mês Nascimento: ");
    scanf("%d", &pw.MonthBorn);

    printf("Ano Nascimento: ");
    scanf("%d", &pw.yearBorn);
    fflush(stdin);

    printf("Cidade: ");
    fgets(pw.City, sizeof(pw.City), stdin);
    pw.City[strcspn(pw.City, "\n")] = '\0';
    // checkIfInputIsValid(pw.City, sizeof(pw.City));

    if(checkIfLocationExists(pw.City, 0) == 0){
        printf("Cidade inexistente\n %s", reset);
        exit(0);
    }

    printf("UF/Estado: ");
    // verificar se a UF digitada tem somente 2 digitos?
    scanf("%s", pw.Uf);
    checkIfInputIsValid(pw.Uf, sizeof(pw.Uf));

    if(checkIfLocationExists(pw.Uf, 1) == 0){
        printf("UF inexistente\n %s", reset);
        exit(0);
    }

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
    fprintf(fp, "%d/%d/%d\n", pw.DayBorn, pw.MonthBorn, pw.yearBorn);
    fprintf(fp, "%s\n", pw.City);
    fprintf(fp, "%s\n", pw.Uf);
    printf("Pessoa cadastrada com sucesso! \n");

    // FILE - Close file
    fclose(fp);
}
