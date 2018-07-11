#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define M 1024

int cmpSTR(Type d1, Type d2); //Aqui estan nuestras funciones de
void printSTR(char*);        //comparacion y de impresion

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
    char *name, *number, *extra, *person, *movie;
    char line[1024];

    Graph g1 = create_graph(cmpSTR, printSTR);  //Se crea el grafo

    //Primero, se va a abrir el archivo de personas y se sacaran 3 datos
    //los cuales se pondrán en una estructura que representará un vertice
    FILE* stream = fopen("vertex_person.csv", "r");
    if(stream!=NULL)
    {
        while (fgets(line, 1024, stream))
        {
            char* tmp = strdup(line);
            name = malloc(sizeof(char)*M);
            strcpy(name,getfield(tmp, 1));  //El nombre
            free(tmp);
            tmp = strdup(line);
            number = malloc(sizeof(char)*5);
            strcpy(number,getfield(tmp, 2)); //La edad
            free(tmp);
            tmp = strdup(line);
            extra = malloc(sizeof(char)*M);
            strcpy(extra,getfield(tmp, 3)); //Mayor o Adulto
            free(tmp);

            graph_addVertex(g1,0, name, number, extra);

        }
        fclose(stream);
    }
    else
        printf("No se pudo leer el archivo\n");

    //Aqui leeremos el archivo con las peliculas y sacaremos 3 cosas:
    //donde lo pondremos en una estructura que será un vertice
    stream = fopen("vertex_movies.csv", "r");
    if(stream!=NULL)
    {
        while (fgets(line, 1024, stream))
        {
            char* tmp = strdup(line);
            name = malloc(sizeof(char)*M);
            strcpy(name,getfield(tmp, 1)); //Nombre
            free(tmp);
            tmp = strdup(line);
            number = malloc(sizeof(char)*5);
            strcpy(number,getfield(tmp, 2)); //Año de creacion
            free(tmp);
            tmp = strdup(line);
            extra = malloc(sizeof(char)*M);
            strcpy(extra,getfield(tmp, 3)); //Frase famosa
            free(tmp);

            graph_addVertex(g1,1, name, number, extra);

        }
        fclose(stream);
    }
    else
        printf("No se pudo leer el archivo\n");

    //AL final, se usará este archivo para unir cada actor(persona) con la
    //pelicula en donde participo. Estas uniones serán las aristas
    stream = fopen("edges_PersonMovies.csv", "r");
    if(stream!=NULL)
    {
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
    }
    else
        printf("No se pudo leer el archivo\n");

    print(g1); //Al final se imprime el grafo final
    graph_destroy(g1);
}

int cmpSTR(Type d1, Type d2)
{
    if(strcmp(d1,d2)==0)
        return 0;
    else
        return 1;
}

void printSTR(char* movie)
{
    printf("\n\tMOVIE: %s", movie);
}
