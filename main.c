#include <stdio.h>
#define PERSON_ATTRIBUTES 6;

int main()
{
    char *personAttributes[6] = {"cpf", "nome", "sexo", "data de nascimento", "cidade", "UF"};
    int i;
    int alreadyRegistered = 0;

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

    for (i = 0; i < 6; i++)
    {
        printf("Digite o %s da pessoa: \n", personAttributes[i]);
        // "%[^\n]" - Read all until user press enter
        scanf("%[^\n]", &pw.personAttributes[i]);

        // //Open file for writing
        // fp = fopen("person.txt", "a");

        // //printFile
        // fprintf(fp, "%s\n", pw.Cpf);
        // fclose(fp);
    }

    // vERIFY IF THERES A PERSON WITH A REGISTER CPF ALREADY ON FILE
    //Open file for reading
    fp = fopen("person.txt", "r");

    for (i = 0; i < 6; i++)
    {
        if (!feof(fp))
        {
            return;
        }

        fscanf(fp, "%^\n", pr.Cpf);

        if (strcmp(pw.Cpf, pr.Cpf) != 0)
        {
            fp = fopen("person.txt", "a");
            printf("Pessoa cadastrada com sucesso");
            // alreadyRegistered += 1;
        }else {
            printf("Nao eh possivel cadastrar, ja tem esse cpf");
        }

    }

    
    /* code */
    return 0;
}

void registerPerson(){

}
