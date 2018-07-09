#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH.h"


//Estructura NODO (Lista)
struct strNode{
	unsigned long id; //El contenido de cada NODE es un apuntador a un VERTEX
	Vertex *ptr_ver;
	struct strNode *next;
	struct strNode *prior;
};

typedef struct strNode Node;

//LISTA
struct strList{
	Node *first;
	Node *last;
	unsigned int size;
};



//Estructura VERTICES
struct strVertex{
	int id;
	Type data;
	List chain;
};

//GRAFO
struct strGraph{
	Vertex **arr;
	int vertex;
	int edge;
	Comparator cmpFunction;
	Print printFunction;
};


Graph create_graph(Comparator myCMP, Print myPrint)
{
	Graph new = (Graph)malloc(sizeof(struct strGraph));
	new->arr = malloc(sizeof(Vertex));
	new->edge = 0;
	new->vertex = 0;
	new->cmpFunction = myCMP;
	new->printFunction = myPrint;
	return new;
}

void print(Graph who, long long var){
	for(int i=var; i<who->vertex;i++){
		printf("\n(%d - %s)", who->arr[i]->id, who->arr[i]->data);

		for(int x=0; x<list_size(who->arr[i]->chain); x++){

			printf("\n\tRe-Tweet: %s", who->arr[list_get(who->arr[i]->chain, x)]->data);
		}
	}
}

bool graph_addVertex(Graph who, Type data)
{
	Vertex* new = (Vertex*)malloc(sizeof(struct strVertex));
	if(new!=NULL)
    {
		new->data = data;
        new->id = who->vertex;
        new->chain = list_create();
        who->arr[who->vertex] = new;
        who->arr = realloc(who->arr, sizeof(Vertex)*(who->vertex+1));
        who->vertex++;
        return true;
    }
    else
        return false;
}


bool  graph_addEdge(Graph who, Type source, Type dest)
{
    int id_source, id_dest;
    for (int i=0; i<who->vertex; i++)
    {
        if (strcmp(source,who->arr[i]->data)==0)
        {
            id_source = i;
            break;
        }
    }
    for (int i=0; i<who->vertex; i++)
    {
        if (strcmp(dest,who->arr[i]->data)==0)
        {
            id_dest = i;
            break;
        }
    }
    //printf("%d - %d\n", id_source, id_dest);
    if (who->arr[id_source]!=NULL && who->arr[id_dest]!=NULL)
    {
        Vertex *SOURCE = (Vertex*)malloc(sizeof(Vertex));
        Vertex *DEST = (Vertex*)malloc(sizeof(Vertex));
        SOURCE = who->arr[id_source];
        DEST = who->arr[id_dest];
        list_add(SOURCE->chain, DEST, id_dest);
        who->edge++;
        return true;
    }
    else
        return false;
}

int graph_vertexCount(Graph who)
{
    return who->vertex;
}

int graph_edgeCount(Graph who)
{
    return who->edge;
}

unsigned long graph_outDegree(Graph who, unsigned long id){
    return list_size(who->arr[id]->chain);
}

bool graph_hasEdge(Graph who, unsigned long id_source, unsigned long id_sink){
    Vertex *SOURCE = (Vertex*)malloc(sizeof(Vertex));
    Vertex *SINK = (Vertex*)malloc(sizeof(Vertex));

	SOURCE = who->arr[id_source];
	SINK = who->arr[id_sink];

	unsigned long p;
	for(int x=0; x<list_size(SOURCE->chain); x++)
	{
		p=list_get(who->arr[id_source]->chain,x);
		if(p == id_sink)
			return true;
	}
    return false;
}


List list_create(){
	List l;
	l=(List)malloc(sizeof(struct strList));
	l->size=0;
	l->last=NULL;
	l->first=NULL;
	return l;
}

int list_size(List l){
	if(l!=NULL)
		return l->size;
	else
		return -1;
}

/* Aqui le paso el apuntador DEST a la funcion*/
void list_add(List l, Vertex* ptr, unsigned long id){
	if(l!=NULL){
		Node *new = (Node*)malloc(sizeof(Node));
		/* Aqui hay problema: Creo que no es la manera correcta de
		pasar el apuntador y no se si es en la declaracion o ocmo paso DEST*/
		new->id = id;
		new->ptr_ver = ptr;
        new->next = NULL;
        new->prior = NULL;
		if(l->size==0)
		{
			l->first=new;
			l->last=new;
		}
		else{
			l->last->next=new;
			new->prior=l->last;
			l->last=new;
		}
		l->size++;
	}
}


unsigned long list_get(List l, int p){
	unsigned long value=NULL;
	Node *current=NULL;
	int i=0;
	int s=l->size;
	if(l!=NULL){
		if ((p>=0) && (p<s)){
			current=l->first;
			while(i<p){
				current=current->next;
				i++;
			}
			value=current->id;
		}
	}
	return value;
}
