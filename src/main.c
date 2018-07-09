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
    /*
    graph_addVertex(g1,(void*)100,0, "Ricardo", "2018", "Diaz");
    graph_addVertex(g1,(void*)200,0, "Esteban", "1999", "Cervantez");
    graph_addVertex(g1,(void*)300,0, "Jorge", "2000", "Dong");
    graph_addVertex(g1,(void*)400,0, "Juan", "2414", "Perez");
    graph_addVertex(g1,(void*)500,0, "Alejandro", "3030", "Flores");
    printf("Vertex: %d\n",graph_vertexCount(g1));
    graph_addEdge(g1,2,0);
    graph_addEdge(g1,2,1);
    graph_addEdge(g1,3,2);
    printf("Edge: %d\n", graph_edgeCount(g1));
    printf("NEIGHTBORS: %li\n", graph_outDegree(g1,2));
    printf("HAS EDGE: %d\n", graph_hasEdge(g1,2,1));
    print(g1);*/

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

        graph_addVertex(g1,x,0, name, number, extra);

        x++;
    }
    fclose(stream);
    graph_addEdge(g1,4,0);
    graph_addEdge(g1,2,1);
    graph_addEdge(g1,20,10);
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
