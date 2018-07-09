#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    //Usando el archivo vertex_person.csv
    FILE* stream = fopen("vertex_person.csv", "r");
    if(stream==NULL)
        printf("ERROR\n");

    char line[1024];
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        printf("%s\n", getfield(tmp, 1)); //El numero '1' da nombres, el '2' da años y '3' da si es adulto
        // NOTE strtok clobbers tmp
        free(tmp);
    }
}
