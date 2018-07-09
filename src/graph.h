#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef void* Type;
typedef enum {false,true} bool;

typedef struct strGraph *Graph;
typedef struct strList *List;
typedef struct strVertex Veretex;

typedef int (*Comparator)(Type , Type);
typedef void (*Print)(Type);



//===================================================/
/***********************GRAPH************************/
//===================================================/
Graph create_graph(Comparator, Print);									//CREATE GRAPH OBJECT
void graph_destroy(Graph);												//CLEAR MEMORY
bool graph_addVertex(Graph, Type, bool);										//ADD NODE
bool graph_addEdge(Graph, int, int);									//ADD EDGE
int graph_vertexCount(Graph);											//GET NUMBER OF NODES ON GRAPH
int graph_edgeCount(Graph);												//GET NUMBER OF EDGES ON GRAPH
unsigned long graph_outDegree(Graph, unsigned long);					//GET NUMBER OF NEIGHTBORS FROM NODE
bool graph_hasEdge(Graph, unsigned long, unsigned long);				//CHEK IF NODES ARE LINKED




//===================================================/
/************************LIST************************/
//===================================================/
List list_create();														//RETURNS A NEW LIST CONTAINER
void list_destroy(List);												//CLEAR MEMORY
int list_size(List);													//RETURN LIST SIZE
void list_add(List ,Veretex*, unsigned long);							//ADD ELEMENT TO EXISTING LIST
unsigned long list_get(List, int);										//RETURNS NODE ID OF INDEX
void list_set(List, Type, int);											//
Type list_remove(List, int);											//REMOVE ELEMENT FROM LIST



#endif // GRAPH_H_INCLUDED
