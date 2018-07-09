#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define M 1024

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
    //Usando el archivo vertex_person.csv
    FILE* stream = fopen("vertex_person.csv", "r");
    if(stream==NULL)
        printf("ERROR\n");

    char *name, *number, *extra;
    char line[1024];

    //Recibir parametro 1 y ponerlo en NAME
    int x = 0;
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        name = malloc(sizeof(char)*M);
        strcpy(name,getfield(tmp, 1));
        free(tmp);
        tmp = strdup(line);
        number = malloc(sizeof(char)*5);
        strcpy(number,getfield(tmp, 2));
        free(tmp);
        tmp = strdup(line);
        extra = malloc(sizeof(char)*M);
        strcpy(extra,getfield(tmp, 3));
        free(tmp);

        graph_addVertex(g1,0, name, number, extra);

        x++;
    }
    fclose(stream);
    //print(g1);

    //printf("\n    MOVIES\n");
    stream = fopen("vertex_movies.csv", "r");
    if(stream==NULL)
        printf("ERROR\n");

    x = 0;
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        name = malloc(sizeof(char)*M);
        strcpy(name,getfield(tmp, 1));
        free(tmp);
        tmp = strdup(line);
        number = malloc(sizeof(char)*5);
        strcpy(number,getfield(tmp, 2));
        free(tmp);
        tmp = strdup(line);
        extra = malloc(sizeof(char)*M);
        strcpy(extra,getfield(tmp, 3));
        free(tmp);

        graph_addVertex(g1,1, name, number, extra);

        x++;
    }
    fclose(stream);

    char *person, *movie;
    stream = fopen("edges_PersonMovies.csv", "r");
    if(stream==NULL)
        printf("ERROR3\n");
    x = 0;
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        person = malloc(sizeof(char)*M);
        strcpy(person, getfield(tmp, 1));
        free(tmp);

        tmp = strdup(line);
        movie = malloc(sizeof(char)*M);
        strcpy(movie, getfield(tmp, 2));
        free(tmp);

        graph_addEdge(g1, person, movie);
    }
    fclose(stream);
    print(g1);
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
