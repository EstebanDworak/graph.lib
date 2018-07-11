#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


//Estructura NODO (Lista)
struct strNode{
	unsigned long id;
	Vertex *ptr_ver; //El contenido de cada NODE es un apuntador a un VERTEX
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

// Esta estructura va ser donde pondremos los datos de la persona y pelicula
struct info
{
    char *name;
    char *number;
    char *extra;
};
typedef struct info Content;

//Estructura VERTICES
struct strVertex{
	int id;         //Es un id unico dependiendo del tamaño del grafo
	bool type;      //Este dato nos va a indicar si es una pelicula o persona
	Content data;   //Aqui es donde guardaremos los datos
	List chain;     //Aqui donde se guardaran los vecinos
};

//GRAFO
struct strGraph{
	Vertex **arr; //Arreglo de apuntadores a todos los vertices del grafo
	int vertex;
	int edge;
	Comparator cmpFunction;
	Print printFunction;
};


Graph create_graph(Comparator myCMP, Print myPrint)
{
	Graph new = (Graph)malloc(sizeof(struct strGraph));
	if(new!=NULL)
    {
        new->arr = malloc(sizeof(Vertex));
        new->edge = 0;
        new->vertex = 0;
        new->cmpFunction = myCMP;
        new->printFunction = myPrint;
        return new;
    }
}

void graph_destroy(Graph who)
{
    int i=0;
    while(who->vertex>0) //Hasta que no tengamos vertices
    {
        list_destroy(who->arr[i]->chain);   //Primero destruimos la lista de cada vertice
        free(who->arr[i]);                  //Despues liberamos la memoria del vertice
        who->vertex--;
    }
}

void print(Graph who)
{
	for(int i=0; i<102;i++)
    {   printf("\n(%d - %s)", who->arr[i]->id, who->arr[i]->data.name);
		for(int x=0; x<list_size(who->arr[i]->chain); x++)
            who->printFunction(who->arr[list_get(who->arr[i]->chain, x)]->data.name);
	}
}

bool graph_addVertex(Graph who, bool type, char *name, char *number, char *extra)
{
	Vertex* new = (Vertex*)malloc(sizeof(struct strVertex));
	if(new!=NULL)
    {
		new->type = type;
		/*Aqui guardamos cada dato en un elemento de la estructura Content*/
        new->data.name = malloc(sizeof(char)*1024);
        strcpy(new->data.name, name);
        new->data.number = malloc(sizeof(char)*10);
        strcpy(new->data.number, number);
        new->data.extra = malloc(sizeof(char)*1024);
        strcpy(new->data.extra, extra);
        new->id = who->vertex; //ID va ser el numero del ultimo vertice creado

        new->chain = list_create();
        who->arr[who->vertex] = new;    //Se guarda el apuntador en el arreglo del grafo
        who->arr = realloc(who->arr, sizeof(Vertex)*(who->vertex+1));
        who->vertex++;
        return true;
    }
    else
        return false;
}


bool  graph_addEdge(Graph who, char *source, char *dest)
{
    //Aqui buscamos si 'source' y 'dest' existen dentro del grafo
    //y agarramos el id donde se encuentran
    int id_source, id_dest;
    for (int i=0; i<who->vertex; i++)
    {
        if (strcmp(who->arr[i]->data.name, source)==0)
        {
            id_source = i;
            break;
        }
    }
    for (int i=0; i<who->vertex; i++)
    {
        if (strcmp(who->arr[i]->data.name, dest)==0)
        {
            id_dest = i;
            break;
        }
    }
    //Comprobamos que si estan los vertices
    if (who->arr[id_source]!=NULL && who->arr[id_dest]!=NULL)
    {
        //Guardamos la direccion de los vertices a unir
        Vertex *SOURCE = (Vertex*)malloc(sizeof(Vertex));
        Vertex *DEST = (Vertex*)malloc(sizeof(Vertex));
        SOURCE = who->arr[id_source];
        DEST = who->arr[id_dest];
        //Agregamos 'dest' a la lista del 'source'
        list_add(SOURCE->chain, DEST, id_dest);
        who->edge++;
        return true;
    }
    else
        return false;
}

int graph_vertexCount(Graph who)    //Contar el numero de vertices en el grafo
{
    return who->vertex;
}

int graph_edgeCount(Graph who)      //Contar el numero de aristas en el grafo
{
    return who->edge;
}

unsigned long graph_outDegree(Graph who, unsigned long id) //Sacar el numero de "vecinos" que tiene el vertices
{
    return list_size(who->arr[id]->chain);
}

bool graph_hasEdge(Graph who, unsigned long id_source, unsigned long id_sink) //Comprobar si hay union entre dos vertices
{
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


List list_create()
{
	List l;
	l=(List)malloc(sizeof(struct strList));
	l->size=0;
	l->last=NULL;
	l->first=NULL;
	return l;
}

int list_size(List l)
{
	if(l!=NULL)
		return l->size;
	else
		return -1;
}

void list_add(List l, Vertex* ptr, unsigned long id)
{
	if(l!=NULL){
		Node *new = (Node*)malloc(sizeof(Node));
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

unsigned long list_get(List l, int p)
{
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

int list_remove(List l, int p)
{
	Node *current=NULL;
	Vertex* tmp;
	int i=0;
	int s=l->size;
	if(l!=NULL){
		//Finding the node in the position 'p'
		if ((p>=0) && (p<s)){
			current=l->first;
			while(i<p){
				current=current->next;
				i++;
			}
		}
		if((p==0)&&(s==1)){ // If the list have just one element inside (position 0)
			tmp=current->ptr_ver;
			l->first=NULL;
			l->last=NULL;
			l->size=0;
			free(current);
			return 1;
		}else{
			if(p==0) //If 'p' is the fir
			{
				tmp=current->ptr_ver;
				l->first=current->next;
				l->first->prior=NULL;
				l->size--;
				free(current);
				return 1;
			}
			else{
				if(p==(s-1))//Se va a eliminar el nodo final
				{
					tmp=current->ptr_ver;
					l->last=current->prior;
					l->last->next=NULL;
					l->size--;
					free(current);
					return 1;
				}
				else
				{//El elemento a remover esta en medio
					tmp=current->ptr_ver;
					//Node *tempNext, *tempPrior;
					current->prior->next=current->next;
					current->next->prior=current->prior;
					free(current);
					return 1;
				}
			}
		}

	}
	return NULL;
}

void list_destroy(List l)
{
	while(list_size(l)>0)
		list_remove(l, 0);
	free(l);
}
