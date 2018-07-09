#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

typedef void* Type;
typedef struct strGraph *Graph;
typedef enum {false,true} boolean;



//CREATE GRAPH OBJECT
Graph graph_create();
//CLEAR MEMORY
void graph_destroy(Graph*);
//ADD NODE
boolean graph_addVertex(Graph, Type);
//ADD EDGE
boolean graph_addEdge(Graph, unsigned long, unsigned long);
//GET NUMBER OF NODES ON GRAPH
unsigned long graph_vertexCount(Graph);
//GET NUMBER OF EDGES ON GRAPH
unsigned long graph_edgeCount(Graph);
//GET NUMBER OF NEIGHTBORS FROM NODE
unsigned long graph_outDegree(Graph, unsigned long);
//CHEK IF NODES ARE LINKED
boolean graph_hasEdge(Graph, unsigned long, unsigned long);



#endif
