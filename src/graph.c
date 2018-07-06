#include <stdio.h>
#include <stdlib.h>

struct strNode{
	int id;
	Type DATA;
	List chain;
} 

typedef struct strNode Node;

struct strGraph{
	Node *arr;
	int vertex;
	int edge;
	Comparator cmpFunction;
	Print myPrint;
}

typedef struct strGraph Graph;

Graph create_graph(Comparator myCMP, Print print)
{
	Graph new = (Graph)malloc(sizeof(Graph));
	//Verificamos si se creó
	new->arr = malloc(sizeof(Node));
	new->edge = 0;
	new->vertex = 0;
	new->cmpFunction = myCMP;
	new->myPrint = print;
}

void destroy_graph(Graph who)
{
	x=0;
	while(who->vertex != 0)
	{
		list_destroy(who->arr[x]->chain);
		free(who->arr[x]);
		x++;
	}
	free(who);
}

bool add_vertex(Graph who, Type data)
{
	Node new = (Node)malloc(sizeof(Node));
	new->data = data;
	new->id = (who->vertex)+1;
	new->chain=create_list();
	who->arr=(Node)realloc(who->arr,sizeof(Node)*(who->vertex+1));
	who->arr[who->vertex] = &new;
	who->vertex++;
}

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
}
