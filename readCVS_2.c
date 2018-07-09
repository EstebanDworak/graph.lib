#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 1024


const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

struct data
{
    char *name;
    char *age;
    char *extra;
};

typedef struct data DATA;

int main()
{
    //Usando el archivo vertex_person.csv
    FILE* stream = fopen("vertex_person.csv", "r");
    if(stream==NULL)
        printf("ERROR\n");

    DATA users[200];
    char line[1024];

    //Recibir parametro 1 y ponerlo en NAME
    int x = 0;
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        users[x].name = malloc(sizeof(char)*M);
        strcpy(users[x].name,getfield(tmp, 1));
        free(tmp);
        x++;
    }
    fclose(stream);

    //Recibir parametro 2 y ponerlo en AGE
    x=0;
    stream = fopen("vertex_person.csv", "r");
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        users[x].age = malloc(sizeof(char)*5);
        strcpy(users[x].age,getfield(tmp, 2));
        free(tmp);
        x++;
    }
    fclose(stream);

    //Recibir parametro 3 y ponerlo en EXTRA
    x=0;
    stream = fopen("vertex_person.csv", "r");
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        users[x].extra = malloc(sizeof(char)*M);
        strcpy(users[x].extra,getfield(tmp, 3));
        free(tmp);
        x++;
    }

    //Imprimir cierto rango
    for (int i = 10; i<20; i++)
    {
        printf("%d: %s | %s | %s \n", i, users[i].name, users[i].age, users[i].extra);
    }
}
