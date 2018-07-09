#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


//Estructura NODO (Lista)
struct strNode{
	unsigned long id; //El contenido de cada NODE es un apuntador a un VERTEX
	Veretex *ptr_ver;
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
	bool type;
	Type data;
	List chain;
};

//GRAFO
struct strGraph{
	Veretex **arr;
	int vertex;
	int edge;
	Comparator cmpFunction;
	Print printFunction;
};


Graph create_graph(Comparator myCMP, Print myPrint)
{
	Graph new = (Graph)malloc(sizeof(struct strGraph));
	new->arr = malloc(sizeof(Veretex));
	new->edge = 0;
	new->vertex = 0;
	new->cmpFunction = myCMP;
	new->printFunction = myPrint;
	return new;
}

void print(Graph who){
	for(int i=0; i<graph_vertexCount(who);i++){
		printf("\n(%d - %d)", who->arr[i]->id, who->arr[i]->data);

		for(int x=0; x<list_size(who->arr[i]->chain); x++){

			printf(" (%d - %d)",who->arr[i]->id,list_get(who->arr[i]->chain, x) );
		}
	}
}

bool graph_addVertex(Graph who, Type data, bool type)
{
	Veretex* new = (Veretex*)malloc(sizeof(struct strVertex));
	if(new!=NULL)
    {
		new->type = type;
        new->data = data;
        new->id = who->vertex;
        new->chain = list_create();

        who->arr[who->vertex] = new;
        who->arr = realloc(who->arr, sizeof(Veretex)*(who->vertex+1));
        who->vertex++;
        return true;
    }
    else
        return false;
}


bool  graph_addEdge(Graph who, int id_source, int id_dest)
{
    if (who->arr[id_source]!=NULL && who->arr[id_dest]!=NULL)
    {

        Veretex *SOURCE = (Veretex*)malloc(sizeof(Veretex));
        Veretex *DEST = (Veretex*)malloc(sizeof(Veretex));
        SOURCE = who->arr[id_source];
        DEST = who->arr[id_dest];
        /* Probe los apuntadores SOURCE y DEST y si funcionan */
        printf("VALOR EN SOURCE: %d\n", (int)SOURCE->data);
        printf("VALOR EN DEST: %d\n", (int)DEST->data);
        /* Entonces aqui esta el problema */
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
    Veretex *SOURCE = (Veretex*)malloc(sizeof(Veretex));
    Veretex *SINK = (Veretex*)malloc(sizeof(Veretex));

	//Verificar si existe SOURCE Y DEST
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
void list_add(List l, Veretex* ptr, unsigned long id){
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
