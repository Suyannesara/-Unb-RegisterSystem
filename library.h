#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
char ERROR_CPF_NOT_EXISTS[] = {"CPF nao encontrado na base de dados\n"};
char ERRORDATE[] = {"Data de nascimento invalida\n"};
char ERRORFILE[] = {"Erro ao abrir a base de dados\n"};
// char SUCCESSFILE[] = {"\nAbrindo base de dados . . .\n"};
char ERRORSEX[] = {"O sexo digitado deve ser F ou M\n"};
char ERROR_UF[] = {"UF inexistente\n"};
char ERROR_CITY[] = {"CIDADE inexistente\n"};
char SUCCESS_REGISTERED[] = {"Pessoa cadastrada com sucesso!\n"};
char ERROR_NOBODY_IN_CITY[] = {"Nenhum registro correspondente a cidade digitada!\n"};


// INIT CODE FUNCTION
int executeMenu() {
    int option;
    printf("Escolha uma das opcoes a seguir: \n");
    printf("1) Cadastrar Pessoa \n");
    printf("2) Consultar Pessoa \n");
    printf("3) Listar pessoas por cidade \n");
    printf("4) Gerar relatorio \n");
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

    // Verify first CPF digit
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

void isFileOpen(file){
    // check if file has been succesfuly opened
    if (!file)
    {
        printf("%s%s", ERRORFILE, RESET);
        exit(1);
    }
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
        if(!(input[i] >= 'A' && input[i] <= 'Z' || input[i] == ' '))
        {
            printf("Os inputs conter apenas letras ou espaços!\n %s", RESET);
            return 0;
        }
    }

    return 1;
}

void checkIfCpfIsRegistered(char cpf[]){
    FILE *readFile = fopen("person.txt", "r");
    isFileOpen(readFile);

    Person personData;

    // Read data
    while(fscanf(readFile, 
        "%s\n%[^\n]\n%s\n%d/%d/%d\n%[^\n]\n%[^\n]", 
        personData.Cpf, 
        personData.Name, 
        personData.Sex, 
        &personData.DayBorn, 
        &personData.MonthBorn, 
        &personData.yearBorn, 
        personData.City, 
        personData.Uf) != EOF){

            if (strcmp(cpf, personData.Cpf) == 0)
            {
                printf("%s%s", ERROR_CPF_EXISTS, RESET);
                exit(1);
            }
            
        }
}

int checkIfLocationExists(char userInput[], int locationType){

    int size = 0;
    char locationLine[LOCATIONS_LINES];
    char *ufToken;
    char *cityTokenNoAccent;

    FILE *fp2 = fopen("locations.csv", "r");
    isFileOpen(fp2);

    if (locationType == 1)
    {
        size = 0;
        // VERRIFY UF
        while (fgets(locationLine, sizeof(locationLine), fp2)) {
            ufToken = strtok(locationLine, ",");
            ufToken = strtok(NULL, ",");

            // Verify if TOKEN == INPUT - If so, UF EXISTS
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
            cityTokenNoAccent = strtok(NULL, ","); // Receive second line
            cityTokenNoAccent = strtok(NULL, ","); // Receive third line
            cityTokenNoAccent = strtok(NULL, ","); // Receive forth file line

            // Verify if TOKEN == INPUT - If so, CITY EXISTS
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

// Using reference to upperString
void tranformStringToUpper(char *string){
    char caracter;
    int i;

    for (i = 0; i < strlen(string); i++)
    {
        caracter = string[i];
        string[i] = toupper(caracter);
    }
}

// CORE CODE FUNCTIONS
void registerPerson(){
    Person pw = {0};
    FILE *writeFile = fopen("person.txt", "a");
    isFileOpen(writeFile);
    fflush(stdin);

    // Getting people`s data
    printf("-------------------- REGISTRO DE PESSOA --------------------\n");
    printf("CPF: ");
    fgets(pw.Cpf, 15, stdin);
    pw.Cpf[strcspn(pw.Cpf, "\n")] = '\0';
    isCpfValid = validateCpf(pw.Cpf);
    if (isCpfValid == 0)
    {
        printf("\n%s%s", ERRORCPF,RESET);
        exit(1);
    }
    checkIfCpfIsRegistered(pw.Cpf);
    
    printf("Nome: ");
    scanf("%[^\n]s", pw.Name);
    tranformStringToUpper(&pw.Name);
    isInputValid = checkIfInputIsValid(pw.Name, sizeof(pw.Name));
    if (isInputValid != 1){exit(1);}

    printf("Sexo (F - Feminino, M - Masculino): ");
    scanf("%s", pw.Sex);
    tranformStringToUpper(&pw.Sex);
    if (strcmp(pw.Sex, "F") != 0 && strcmp(pw.Sex, "M") != 0){
        printf("%s%s", ERRORSEX, RESET);
        exit(1);
    }

    printf("Dia Nascimento: ");
    scanf("%d", &pw.DayBorn);

    printf("Mes Nascimento: ");
    scanf("%d", &pw.MonthBorn);

    printf("Ano Nascimento: ");
    scanf("%d", &pw.yearBorn);
    isDateValid = checkIfDateValid(pw.DayBorn, pw.MonthBorn, pw.yearBorn);
    if (isDateValid != 1)
    {
        printf("%s%s", ERRORDATE, RESET);
        exit(1);
    }
    
    fflush(stdin);

    printf("Cidade: ");
    fgets(pw.City, sizeof(pw.City), stdin);
    pw.City[strcspn(pw.City, "\n")] = '\0';
    tranformStringToUpper(&pw.City);
    isInputValid = checkIfInputIsValid(pw.City, sizeof(pw.City));
    if (isInputValid != 1){exit(1);}

    if(checkIfLocationExists(pw.City, 0) == 0){
        printf("%s%s", ERROR_CITY, RESET);
        exit(1);
    }

    printf("UF/Estado: ");
    // Verify if USER UF has only 2 digits
    scanf("%s", pw.Uf);
    tranformStringToUpper(&pw.Uf);
    isInputValid = checkIfInputIsValid(pw.Uf, sizeof(pw.Uf));
    if (isInputValid != 1){exit(1);}

    if(checkIfLocationExists(pw.Uf, 1) == 0){
        printf("%s%s", ERROR_UF, RESET);
        exit(1);
    }

    fflush(stdin);

    // FILE - Check if it was successfully opened
    if (!writeFile)
    {
        printf("%s%s", ERRORFILE, RESET);
        exit(1);
    }
    
    //FILE - If it was ok - print on file
    fprintf(writeFile, "%s\n", pw.Cpf);
    fprintf(writeFile, "%s\n", pw.Name);
    fprintf(writeFile, "%s\n", pw.Sex);
    fprintf(writeFile, "%02d/%02d/%02d\n", pw.DayBorn, pw.MonthBorn, pw.yearBorn);
    fprintf(writeFile, "%s\n", pw.City);
    fprintf(writeFile, "%s\n", pw.Uf);
    printf("%s\n", SUCCESS_REGISTERED);

    // FILE - Close file
    fclose(writeFile);
}

void consultPerson(){
    Person pr = {0};
    char cpf[16];
    int cpfExists = 0;

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
            cpfExists = 1;
            printf("---- DADOS DE: %s ----\n", pr.Name);
            printf("---- CPF:               %s \n", pr.Cpf);
            printf("---- SEXO:              %s \n", pr.Sex);
            printf("---- DT. NASCIMENTO:    %0.2d/%0.2d/%d \n", pr.DayBorn, pr.MonthBorn, pr.yearBorn);
            printf("---- CIDADE:            %s \n", pr.City);
            printf("---- ESTADO/UF          %s \n", pr.Uf);
            exit(1);
        }
        
    };

    if (cpfExists == 0)
    {
        printf("%s", ERROR_CPF_NOT_EXISTS);
    }
    

    fclose(readFile);
}


void listPeopleByCity(){
    int j = 0;
    int numberOfPeople = 0;
    int hasSomeoneInCity = 0;
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
    tranformStringToUpper(&city.Name);
    isInputValid = checkIfInputIsValid(city.Name, sizeof(city.Name));

    // Check if input is valid // Check if city Name exists
    if ((isInputValid != 1) || checkIfLocationExists(city.Name, 0) != 1){
        printf("%s\n", RESET);
        exit(1);
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
            int hasSomeoneInCity = 1;
            listOfPeople[numberOfPeople] = personByCityStruct;
            numberOfPeople++;
        }
    }

    if (hasSomeoneInCity == 0)
    {
        printf("%s", ERROR_NOBODY_IN_CITY);
        exit(1);
    }
    

    // Sort people by name from A to Z
    qsort(listOfPeople, numberOfPeople, sizeof(Person), orderPeopleInAlphabet);

    for (j = 0; j < numberOfPeople; j++)
    {
        printf("\n%s   |   %s", listOfPeople[j].Cpf, listOfPeople[j].Name);
    }

    fclose(readFile);
}


int calcAge(int yearBorn, int monthBorn){
    // Take actual date and time
    time_t actualTime = time(NULL);
    struct tm date = *localtime(&actualTime);

    int age = (date.tm_year) - yearBorn;

    if (monthBorn > date.tm_mon + 1){age--;}
    
    return age;
}

// int calcPercentByAge(int personAge, int totPeople){
//     int et15, et16, et30, et50, et60 = 0;
//     int p15, p16, p30, p50, p60 = 0;

//     if (personAge <= 15)
//     {
//         et15++;
//     }

//     if (personAge >= 16 && personAge <= 29)
//     {
//         et16++;
//     }

//     if (personAge >= 30 && personAge <= 49)
//     {
//         et30++;
//     }

//     if (personAge >= 50 && personAge <= 60)
//     {
//         et50++;
//     }

//     if (personAge > 60)
//     {
//         et60++;
//     }

//     // CALC PERCENT
//     p15 += (et15/totPeople) * 100;
//     return p15;
// }

void generateReport(){
    Person personData;

    FILE *readFile = fopen("person.txt", "r");
    isFileOpen(readFile);

    int registeredPeople = 0;
    int personAge = 0;
    int et15, et16, et30, et50, et60 = 0;
    int p15, p16, p30, p50, p60 = 0;
    
    int percentPerAge, percentPerSex = 0;

    while(fscanf(readFile, 
    "%s\n%[^\n]\n%s\n%d/%d/%d\n%[^\n]\n%[^\n]", 
    personData.Cpf, 
    personData.Name, 
    personData.Sex, 
    &personData.DayBorn, 
    &personData.MonthBorn, 
    &personData.yearBorn, 
    personData.City, 
    personData.Uf) != EOF){
        // CLASSIFY BY AGE
        personAge  = calcAge(personData.yearBorn - 1900, personData.MonthBorn);
        if (personAge <= 15)
        {
            et15++;
        }

        if (personAge >= 16 && personAge <= 29)
        {
            et16++;
            // printf("%d", et16);
        }

        if (personAge >= 30 && personAge <= 49)
        {
            et30++;
        }

        if (personAge >= 50 && personAge <= 60)
        {
            et50++;
        }

        if (personAge > 60)
        {
            et60++;
        }

        
        // Count people on file
        registeredPeople ++;
    }

    // printf("%d", &et16);
    p16 = ((float)et16/registeredPeople) * 100;

    printf("%.2f%%", p16);

    fclose(readFile);
}