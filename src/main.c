#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int cmpInt(Type d1, Type d2);
void printInt(Type d);

int main()
{
    Graph g1 = create_graph(cmpInt, printInt);
    graph_addVertex(g1,(void*)100);
    graph_addVertex(g1,(void*)200);
    graph_addVertex(g1,(void*)300);
    graph_addVertex(g1,(void*)400);
    graph_addVertex(g1,(void*)500);
    printf("Vertex: %d\n",graph_vertexCount(g1));
    graph_addEdge(g1,2,0);
    graph_addEdge(g1,2,1);
    printf("Edge: %d\n", graph_edgeCount(g1));
    printf("NEIGHTBORS: %li\n", graph_outDegree(g1,2));
    printf("HAS EDGE: %d\n", graph_hasEdge(g1,2,1));

    return 0;
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
