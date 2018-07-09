#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define M 10000
long long var =0;
int cmpInt(Type d1, Type d2);
void printInt(Type d);

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
    Graph g1 = create_graph(cmpInt, printInt);
    FILE* stream = fopen("prueba.csv", "r");
    if(stream==NULL)
        printf("ERROR\n");

    char *number;
    char line[1024];

    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        number = malloc(sizeof(char)*M);
        strcpy(number,getfield(tmp, 1));
        free(tmp);
        graph_addVertex(g1,number);
    }

    var = graph_vertexCount(g1);
    fclose(stream);


    stream = fopen("prueba.csv", "r");
    if(stream==NULL)
        printf("ERROR\n");

    char temp[25]="000000";

    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        number = malloc(sizeof(char)*M);
        strcpy(number,getfield(tmp, 2));

        if(strcmp(temp,number)!=0){
             graph_addVertex(g1,number);
             strcpy(temp,number);
        }
        free(tmp);
    }
    fclose(stream);




    char *src, *dst;
    stream = fopen("prueba.csv", "r");
    if(stream==NULL)
        printf("ERROR\n");

    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        src = malloc(sizeof(char)*M);
        strcpy(src, getfield(tmp, 2));
        free(tmp);

        tmp = strdup(line);
        dst = malloc(sizeof(char)*M);
        strcpy(dst, getfield(tmp, 1));
        free(tmp);

        graph_addEdge(g1, src, dst);
    }
    fclose(stream);
    print(g1,var);
}

/*TODAVIA NO USO ESTAS FUNCIONES,  SOLO LO DECLARÉ AQUI POR EL MOMENTO*/
int cmpInt(Type d1, Type d2)
{
    //int *v1 = (int *)d1;
    int v1 = *(int *)d1;
    int v2 = *(int *)d2;
    return v1-v2;
}

void printInt(Type d)
{
    printf(" %d ", *(int*)d);
}
