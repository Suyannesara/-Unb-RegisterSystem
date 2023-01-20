#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CREATE AND DEFINE VARIABLES VALUES
#define LOCATIONS_LINES 5572
#define N_CPF_DIGITS 11
#define MAX_DAYS_IN_MONTH 31

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

int i = 0;
int isCpfValid, 
isInputValid, 
isDateValid, 
ufExists, 
isElementPresentInGroup = 0;

// MESSAGES
char RESET[] = {"\n------------- REINICIANDO O SISTEMA ------------"};
char ERRORCPF[] = {"CPF invalido\n"};
char ERROR_CPF_EXISTS[] = {"CPF ja cadastrado no sistema!\n"};
char ERRORDATE[] = {"Data de nascimento invalida\n"};
char ERRORFILE[] = {"Erro ao abrir a base de dados\n"};
char SUCCESSFILE[] = {"\nAbrindo base de dados . . .\n"};


// INIT CODE FUNCTION
int executeMenu() {
    int option;
    printf("Escolha uma das opcoes a seguir: \n");
    printf("1) Cadastrar Pessoa \n");
    printf("2) Consultar Pessoa \n");
    printf("3) Listar pessoas por cidade \n");
    printf("4) Gerar relatório \n");
    printf("5) Excluir Pessoa \n");
    printf("6) Encerrar programa\n");

    scanf("%d", &option);
    return option;
}

// VALIDATIONS AND AUXILIAR FUNCTIONS
int validateCpf(char cpf[])
{
    int i, d1, d2, r;
    int cpfDigits[N_CPF_DIGITS];

    // Check if CPF has at least and at maximum 11 digits
    if (strlen(cpf) != N_CPF_DIGITS)
    {
        printf("O CPF precisa ter 11 digitos, sem traços ou pontos.\n");
        return 0;
    }

    // Check if input has only NUMBERS 0-9
    for (i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i]))
        {
            printf("O CPF deve ser composto apenas de números, sem traços ou pontos.\n");
            return 0;
        }
        cpfDigits[i] = cpf[i] - '0';
    }

    // Check if CPF inputed is composed of the SAME NUMBER. Eg: 000000000000
    for (i = 1; i < 11; i++) {
        if (cpfDigits[i] != cpfDigits[0]) {
            break;
        }
    }
    if (i == N_CPF_DIGITS) {
        return 0;
    }

    // Verify second CPF digit
    d1 = 0;
    for (i = 0; i < 9; i++)
    {
        d1 += cpfDigits[i] * (10 - i);
    }
    r = 11 - (d1 % 11);
    if (r == 10 || r == 11)
    {
        r = 0;
    }
    if (r != cpfDigits[9])
    {
        return 0;
    }

    // Verify second CPF digit
    d2 = 0;
    for (i = 0; i < 10; i++)
    {
        d2 += cpfDigits[i] * (11 - i);
    }
    r = 11 - (d2 % 11);
    if (r == 10 || r == 11)
    {
        r = 0;
    }
    if (r != cpfDigits[10])
    {
        return 0;
    }

    return 1;
}

void isFileOpen(readFile){

    if (readFile == NULL)
    {
        printf("%s%s", ERRORFILE, RESET);
        exit(0);
    }
    printf("%s", SUCCESSFILE);

    return;
}

int checkIfDateValid(int d, int m, int y){
    int leapYear = 0;
    int monthMaxDays = MAX_DAYS_IN_MONTH;

    if (y < 0) {
        return 0;
    };

    if (m < 1 || m > 12) {
        return 0;
    };

    if (d < 1) {
        return 0;
    };


    if (m == 2) {
        if((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)){
            leapYear = 1;
        };

        if (leapYear == 1) {
            monthMaxDays = 29;
        } else {
            monthMaxDays = 28;
        };

    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        monthMaxDays = 30;
    };

    if (d > monthMaxDays) {
        return 0;
    };

    return 1;
}

int checkIfInputIsValid(char input[], int maxChar){  
    int inputLen = strlen(input);

    // Check if maximum length is attendend
    if (inputLen > maxChar || (inputLen == 0))
    {
        printf("Voce ultrapassou o limite de caracteres para esse campo!\n %s", RESET);
        return 0;
    }

    // issspace - check if it is a blank space
    for (int i=0; i < inputLen; i++) {
        if(!(input[i] >= 'A' && input[i] <= 'Z' || input[i] >= 'a' && input[i] <= 'z' || input[i] == ' '))
        {
            printf("Os inputs conter apenas letras ou espaços!\n %s", RESET);
            return 0;
        }
    }

    return 1;
}

int checkIfLocationExists(char userInput[], int locationType){

    int size = 0;
    char locationLine[LOCATIONS_LINES];
    char *ufToken;
    char *cityTokenNoAccent;

    FILE *fp2 = fopen("locations.csv", "r");
    if (fp2 == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    if (locationType == 1)
    {
        size = 0;
        // VERRIFY UF
        while (fgets(locationLine, sizeof(locationLine), fp2)) {
            ufToken = strtok(locationLine, ",");
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
        while (fgets(locationLine, sizeof(locationLine), fp2)) {
            cityTokenNoAccent = strtok(locationLine, ",");
            cityTokenNoAccent = strtok(NULL, ",");
            cityTokenNoAccent = strtok(NULL, ",");
            cityTokenNoAccent = strtok(NULL, ",");

            // VERIFICAR SE O TOKEN == INPUT - SES IM, UF EXISTE
            if(strcmp(userInput, cityTokenNoAccent) == 0){
                return 1;
            }
            size++;
        }
    }
    
    // Close the file
    fclose(fp2);

    return 0;
}

int orderPeopleInAlphabet(const void *p1, const void *p2){
    Person *pa = (Person *)p1;
    Person *pb = (Person *)p2;
    return strcmp(pa->Name, pb->Name);
}

// CORE CODE FUNCTIONS
void registerPerson(){
    FILE *writeFile = fopen("person.txt", "a");
    Person pw = {0};
    fflush(stdin);

    // Getting people`s data
    printf("-------------------- REGISTRO DE PESSOA --------------------\n");
    printf("CPF: ");
    fgets(pw.Cpf, 15, stdin);
    pw.Cpf[strcspn(pw.Cpf, "\n")] = '\0';
    isCpfValid = validateCpf(pw.Cpf);
    if (isCpfValid == 0)
    {
        printf("\n%s", ERRORCPF);
        exit(0);
    }
    // checkIfCpfIsRegistered(pw.Cpf);
    
    printf("Nome: ");
    scanf("%[^\n]s", pw.Name);
    isInputValid = checkIfInputIsValid(pw.Name, sizeof(pw.Name));
    if (isInputValid != 1){exit(0);}

    printf("Sexo (F - Feminino, M - Masculino): ");
    scanf("%s", pw.Sex);
    if (strcmp(pw.Sex, "F") != 0 && strcmp(pw.Sex, "M") != 0){
        printf("O sexo digitado deve ser F ou M\n %s", RESET);
        exit(0);
    }

    printf("Dia Nascimento: ");
    scanf("%d", &pw.DayBorn);

    printf("Mês Nascimento: ");
    scanf("%d", &pw.MonthBorn);

    printf("Ano Nascimento: ");
    scanf("%d", &pw.yearBorn);
    isDateValid = checkIfDateValid(pw.DayBorn, pw.MonthBorn, pw.yearBorn);
    if (isDateValid != 1)
    {
        printf("%s%s", ERRORDATE, RESET);
        exit(0);
    }
    
    fflush(stdin);

    printf("Cidade: ");
    fgets(pw.City, sizeof(pw.City), stdin);
    pw.City[strcspn(pw.City, "\n")] = '\0';
    isInputValid = checkIfInputIsValid(pw.City, sizeof(pw.City));
    if (isInputValid != 1){exit(0);}

    if(checkIfLocationExists(pw.City, 0) == 0){
        printf("Cidade inexistente\n %s", RESET);
        exit(0);
    }

    printf("UF/Estado: ");
    // verificar se a UF digitada tem somente 2 digitos?
    scanf("%s", pw.Uf);
    isInputValid = checkIfInputIsValid(pw.Uf, sizeof(pw.Uf));
    if (isInputValid != 1){exit(0);}

    if(checkIfLocationExists(pw.Uf, 1) == 0){
        printf("UF inexistente\n %s", RESET);
        exit(0);
    }

    fflush(stdin);

    // FILE - Check if it was successfully opened
    if (!writeFile)
    {
        printf("%s%s", ERRORFILE, RESET);
        exit(0);
    }
    
    //FILE - If it was ok - print on file
    fprintf(writeFile, "%s\n", pw.Cpf);
    fprintf(writeFile, "%s\n", pw.Name);
    fprintf(writeFile, "%s\n", pw.Sex);
    fprintf(writeFile, "%02d/%02d/%02d\n", pw.DayBorn, pw.MonthBorn, pw.yearBorn);
    fprintf(writeFile, "%s\n", pw.City);
    fprintf(writeFile, "%s\n", pw.Uf);
    printf("Pessoa cadastrada com sucesso! \n");

    // FILE - Close file
    fclose(writeFile);
}

void consultPerson(){
    Person pr = {0};
    char cpf[16];
    char buffer[1000];

    printf("-------------------- CONSULTA DE PESSOA --------------------\n");
    FILE *readFile = fopen("person.txt", "r");

    isFileOpen(readFile);

    printf("Digite o CPF para consulta: ");
    fflush(stdin);
    fgets(cpf, 12, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    while(fscanf(readFile, 
    "%s\n%[^\n]\n%s\n%d/%d/%d\n%[^\n]\n%[^\n]", 
    pr.Cpf, pr.Name, pr.Sex, &pr.DayBorn, &pr.MonthBorn, &pr.yearBorn, pr.City, pr.Uf) != EOF){
        if (strcmp(pr.Cpf, cpf) == 0)
        {
            printf("---- DADOS DE: %s ----\n", pr.Name);
            printf("---- CPF:               %s \n", pr.Cpf);
            printf("---- SEXO:              %s \n", pr.Sex);
            printf("---- DT. NASCIMENTO:    %0.2d/%0.2d/%d \n", pr.DayBorn, pr.MonthBorn, pr.yearBorn);
            printf("---- CIDADE:            %s \n", pr.City);
            printf("---- ESTADO/UF          %s \n", pr.Uf);
            exit(0);
        }
        
    };

    fclose(readFile);
}


void listPeopleByCity(){
    int j = 0;
    int numberOfPeople = 0;
    Person personByCityStruct;
    Person listOfPeople[200];

    printf("----------------- LISTAGEM POR CIDADE -----------------\n");

    FILE *readFile = fopen("person.txt", "r");
    isFileOpen(readFile);

    printf("Busque pelo nome da cidade: ");
    fflush(stdin);

    Locations city;
    // Receive input
    fgets(city.Name, sizeof(city.Name), stdin);
    city.Name[strcspn(city.Name, "\n")] = '\0';
    isInputValid = checkIfInputIsValid(city.Name, sizeof(city.Name));

    // Check if input is valid // Check if city Name exists
    if ((isInputValid != 1) || checkIfLocationExists(city.Name, 0) != 1){
        printf("%s\n", RESET);
        exit(0);
    }
    

    // Search on person file. Compare each city line with Name, see the ones that are compatible and insert in a array;
    // Read each line on file
    while(fscanf(readFile, 
        "%s\n%[^\n]\n%s\n%d/%d/%d\n%[^\n]\n%[^\n]", 
        personByCityStruct.Cpf, 
        personByCityStruct.Name, 
        personByCityStruct.Sex, 
        &personByCityStruct.DayBorn, 
        &personByCityStruct.MonthBorn, 
        &personByCityStruct.yearBorn, 
        personByCityStruct.City, 
        personByCityStruct.Uf) != EOF){

        if (strcmp(city.Name, personByCityStruct.City) == 0)
        {
            listOfPeople[numberOfPeople] = personByCityStruct;
            numberOfPeople++;
        }
    }

    // Sort people by name from A to Z
    qsort(listOfPeople, numberOfPeople, sizeof(Person), orderPeopleInAlphabet);

    for (j = 0; j < numberOfPeople; j++)
    {
        printf("\n%s   |   %s", listOfPeople[j].Cpf, listOfPeople[j].Name);
    }

    fclose(readFile);
    exit(0);
}


// ARRUMAR COMENTARIOS
// CRIAR FILE DE TESTES
// CHECK IF CPF IS VALID
// REMOVE PRINTFS IN ENGLISH