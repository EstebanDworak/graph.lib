#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH.h"

#define M 19

long long var = 0;                          //Guarda el total de tweets unicos
int cmpSTR(Type d1, Type d2);               //Nuestra funcion comparar
void PrintAll(int, char*, int);             //Funcion que determina como imprimir el grafo
void Print_reTweets(char* who);             //Funcion que imprime los re-tweets en un formato
const char* getfield(char* line, int num);  //Funcion que devuelve un elemento del archivo .CSV

int main()
{
    char *number, line[1024], temp[M]="000000", *src, *dst;

    Graph g1 = create_graph(cmpSTR, PrintAll);//Crea un grafo y se pasan funciones

    //Leemos el archivo y sus datos lo pasamos vertices del grafo
    //Aqui leeremos los tweets que se reenvian (tweet origen, columna 2)
    FILE *stream = fopen("RETWEETS.csv", "r");
    if(stream!=NULL)
    {   while (fgets(line, 1024, stream))
        {   char* tmp = strdup(line);
            number = malloc(sizeof(char)*M);
            strcpy(number,getfield(tmp, 2)); //Guardamos el valor que estaba en la columna '2' del .csv

            //Si el valor que sacamos no es igual al temp, lo añadimos al grafo
            if(strcmp(temp,number)!=0){
                 graph_addVertex(g1,number);
                 strcpy(temp,number);//Ahora este valor sera el nuevo temp
            }
            free(tmp);
        }
        fclose(stream);
        var = graph_vertexCount(g1);//Guardamos el total de tweets unicos que se reenvian
    }
    else
        printf("No se pudo leer el archivo\n");

    //Leemos el archivo y sus datos lo pasamos vertices del grafo
    //Aqui leeremos todos los re-tweets en el dataset (columna 1)
    stream = fopen("RETWEETS.csv", "r");
    if(stream!=NULL)
    {   while (fgets(line, 1024, stream))
        {   char* tmp = strdup(line);
            number = malloc(sizeof(char)*M);
            strcpy(number,getfield(tmp, 1)); //Recibimos el valor de la columna 1 y
            free(tmp);                       // lo pasamos al grafo
            graph_addVertex(g1,number);
        }
        fclose(stream);
    }
    else
        printf("No se pudo leer el archivo\n");

    //Aqui se va conectar el re-tweet con el tweet origen
    stream = fopen("RETWEETS.csv", "r");
    if(stream!=NULL)
    {   while (fgets(line, 1024, stream))
        {   char* tmp = strdup(line);
            src = malloc(sizeof(char)*M); //src = re-tweet
            strcpy(src, getfield(tmp, 2));
            free(tmp);

            tmp = strdup(line);
            dst = malloc(sizeof(char)*M); //dst = tweet origen
            strcpy(dst, getfield(tmp, 1));
            free(tmp);

            graph_addEdge(g1, src, dst); //Se pasan al grafo para unirlos
        }
        fclose(stream);
    }
    else
        printf("No se pudo abrir el archivo\n");

    graph_PrintAll(g1,var); //Si todo sale bien, se imprime el grafo completo, conforme al formato dado
    printf("\nTotal Tweets: %li\n", var); //Da el total de tweets unicos

    graph_printSingleUser(g1,var,Print_reTweets,19);     //Ejemplo de printSingleUser: imprime los retweets que recibio el tweet 19.


    graph_destroy(g1); //Se libera el espacio
}

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

int cmpSTR(Type d1, Type d2)
{
    if(strcmp(d1,d2)==0)
        return 0;
    else
        return 1;
}

void PrintAll(int id, char* account, int size)
{
    printf("\n(Tweet ID:%d - %s) | # of Re-Tweets: %d", id, account, size);
}

void Print_reTweets(char* who)
{
    printf("\n\tRe-Tweet: %s", who);
}
