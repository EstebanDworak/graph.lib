#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

typedef void* Type;
typedef enum {false,true} boolean;



struct strNode{
	int id;
	Type DATA;
	List chain;
};

typedef struct strNode Node;

struct strGraph{
	Node *arr;
	unsigned long vertex;
	unsigned long edge;
	Comparator cmpFunction;
	Print myPrint;
};

typedef struct strGraph Graph;



//CREATE GRAPH OBJECT
Graph graph_create(CMP, PRINT);

//CLEAR MEMORY
void graph_destroy(Graph);

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
