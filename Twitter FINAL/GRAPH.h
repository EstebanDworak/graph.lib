#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef char* Type;
typedef enum {false,true} bool;

//Como llamaremos a cada estructura
typedef struct strGraph *Graph;
typedef struct strList *List;
typedef struct strVertex Vertex;
typedef struct strNode Node;

//Apuntadores a funcion
typedef int (*Comparator)(Type , Type);
typedef void (*Print)(int, char*, int);
typedef void (*singlePrint) (char*);

//===================================================/
/***********************GRAPH************************/
//===================================================/
Graph create_graph(Comparator, Print);									//CREATE GRAPH OBJECT
void graph_destroy(Graph);												//CLEAR MEMORY
bool graph_addVertex(Graph, Type);										//ADD NODE
bool  graph_addEdge(Graph, Type, Type);									//ADD EDGE
int graph_vertexCount(Graph);											//GET NUMBER OF NODES ON GRAPH
int graph_edgeCount(Graph);												//GET NUMBER OF EDGES ON GRAPH
unsigned long graph_outDegree(Graph, unsigned long);					//GET NUMBER OF NEIGHTBORS FROM NODE
bool graph_hasEdge(Graph, unsigned long, unsigned long);				//CHECK IF NODES ARE LINKED
void graph_PrintAll(Graph, long long);                                  //PRINT GRAPH
void graph_printSingleUser(Graph, long long, singlePrint, int);         //PRINT SINGLE USER

//===================================================/
/************************LIST************************/
//===================================================/
List list_create();														//RETURNS A NEW LIST CONTAINER
void list_destroy(List);												//CLEAR MEMORY
int list_size(List);													//RETURN LIST SIZE
void list_add(List ,Vertex*, unsigned long);							//ADD ELEMENT TO EXISTING LIST
unsigned long list_get(List, int);										//RETURNS NODE ID OF INDEX
int list_remove(List, int);											    //REMOVE ELEMENT FROM LIST

#endif // GRAPH_H_INCLUDED
