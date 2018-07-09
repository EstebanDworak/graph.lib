#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"


typedef struct strNode{
	int id;
	Type data;
	List chain;
};

typedef struct strNode Node;

struct strGraph{
	Node **arr;
	unsigned long vertex;
	unsigned long edge;
//	Comparator cmpFunction;
//	Print myPrint;
};



Graph graph_create()
{
    Graph new = (Graph)malloc(sizeof(struct strGraph));
    if(new == NULL)
        return NULL;
	new->arr = (Node**)malloc(sizeof(Node));
	new->edge = 0;
	new->vertex = 0;
}


boolean graph_addVertex(Graph who, Type data)
{
    printf("Size: %d",who->vertex);
	Node *new = (Node*)malloc(sizeof(Node));
	new->data = data;
	new->id = (who->vertex)+1;
	new->chain=list_create();

	*(who)arr)=realloc(*(who->arr),sizeof(Node)*(who->vertex+1));
	who->arr[who->vertex] = new;
	who->vertex++;

	printf("\n%p\n",who->arr[who->vertex]);
	printf("%p\n",new);
}
/*
bool add_edge(Graph who, int id_source, int id_dest)
{
	Node *SOURCE = (Node*)malloc(sizeof(Node));
	Node *DEST = (Node*)malloc(sizeof(Node));
	//Verificar si existe SOURCE Y DEST
	SOURCE = who->arr[id_source-1];
	DEST = who->arr[id_dest-1];

	list_add(SOURCE->chain, DEST);
	free(SOURCE);
	free(DEST);
}

int graph_vertexCount(Graph who)
	return who->vertex;

int graph_edgeCount(Graph who)
	return who->edge;

int graph_outDegree(Graph who, int id)
{
	Node *SOURCE = (Node*)malloc(sizeof(Node));
	//Verificar si existe SOURCE Y DEST
	SOURCE = who->arr[id_source-1];
	return size_list(SOURCE->chain);
}

int graph_hasEdge(Graph who, int id_source, int id_sink)
{
	Node *SOURCE = (Node*)malloc(sizeof(Node));
	//Verificar si existe SOURCE Y DEST
	SOURCE = who->arr[id_sink-1];
	Node *SINK = (Node*)malloc(sizeof(Node));
	//Verificar si existe SOURCE Y DEST
	SINK = who->arr[id_sink-1];

	Node *p=(Node*)malloc(sizeof(Node));
	for(int x=0; x<size_list(SOURCE->chain); x++)
	{
		p=SOURCE->chain[x];
		if(p == SINK)
			return true;
	}
	return false;
}

void graph_print(Graph who, Print p)
{
	for (int x = 0; x<who->size_vertex; x++)
		printf("%d\n || %d", who->arr[x]->ID, who->arr[x]->data);
}*/
