#include <stdio.h>
#define PERSON_ATTRIBUTES 6;

int main()
{
    // char *personAttributes[6] = {"cpf", "nome", "sexo", "data de nascimento", "cidade", "UF"};
    // int i;
    // int alreadyRegistered = 0;

    typedef struct 
    {
        char Cpf;
        char Name;
        char Sex;
        int DtBorn;
        char City;
        char Uf;
    } Person;

    FILE *fp;
    Person pw;
    Person pr;
    // Limpar buffer


    printf("Digite o CPF da pessoa: \n");
    scanf("%[^\n]", &pw.Cpf);

    printf("Digite o nome da pessoa: \n");
    scanf("%[^\n]", &pw.Name);

    printf("Digite o Sexo da pessoa: \n");
    scanf("%[^\n]", &pw.Sex);

    printf("Digite a data de nascimento da pessoa: \n");
    scanf("%[^\n]", &pw.DtBorn);

    printf("Digite a cidade da pessoa: \n");
    scanf("%[^\n]", &pw.City);

    printf("Digite a UF/Estado da pessoa: \n");
    scanf("%[^\n]", &pw.Uf);

   
    //Open file for writing
    fp = fopen("person.txt", "a");

    if (fp != NULL)
    {
        //print ON File
        fprintf(fp, "%s\n", pw.Cpf);
        fprintf(fp, "%s\n", pw.Name);
        fprintf(fp, "%s\n", pw.Sex);
        fprintf(fp, "%s\n", pw.DtBorn);
        fprintf(fp, "%s\n", pw.City);
        fprintf(fp, "%s\n", pw.Uf);

        printf("Pessoa cadastrada com sucesso! \n");

        // Close file
        fclose(fp);
    }
    

    // vERIFY IF THERES A PERSON WITH A REGISTER CPF ALREADY ON FILE
    //Open file for reading
    fp = fopen("person.txt", "r");

    if (!feof(fp))
    {
        return;
    }else {
        // Insert data in PR variable
        fscanf(fp, "%^\n", &pr.Cpf);
        fscanf(fp, "%^\n", &pr.Name);
        fscanf(fp, "%^\n", &pr.Sex);
        fscanf(fp, "%^\n", pr.DtBorn);
        fscanf(fp, "%^\n", &pr.City);
        fscanf(fp, "%^\n", &pr.Uf);
    }


    if (strcmp(pw.Cpf, pr.Cpf) != 0)
    {
        fp = fopen("person.txt", "a");
        printf("Pessoa cadastrada com sucesso 22\n");
        // alreadyRegistered += 1;
    }else {
        printf("Nao eh possivel cadastrar, ja tem esse cpf");
    }

    return 0;
}

void registerPerson(){

}
