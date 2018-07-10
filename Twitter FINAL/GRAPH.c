#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH.h"

//Estructura NODO (Lista)
struct strNode
{
	unsigned long id;
	Vertex *ptr_ver;        //Cada nodo de la lista tiene un apuntador a un vertice
	struct strNode *next;
	struct strNode *prior;
};

//LISTA
struct strList
{
	Node *first;
	Node *last;
	unsigned int size;
};

//Estructura VERTICES
struct strVertex
{
	int id;
	Type data;      //Contiene el codigo de cada tweet
	List chain;     //Esta lista contiene a los "re-tweets" de cada "tweet"
};

//GRAFO
struct strGraph
{
	Vertex **arr;           //Arreglo de apuntadores a cada elemento existente en el grafo
	int vertex;             //Num. total de vertices en el grafo
	int edge;               //Num. total de aristas en el grafo
	Comparator cmpFunction; //Apuntador a la funcion con quien compararemos
	Print myPrint;          //Como se va a imprimir todo el grafp
};


Graph create_graph(Comparator myCMP, Print myPrint)
{
	Graph new = (Graph)malloc(sizeof(struct strGraph));
	if(new!=NULL)
    {
        new->arr = malloc(sizeof(Vertex));  //Se hace espacio para la lista
        new->edge = 0;
        new->vertex = 0;
        new->cmpFunction = myCMP;           // Recibimos los formatos de
        new->myPrint = myPrint;             // comparacion y de impresion
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

bool graph_addVertex(Graph who, Type data)
{
	Vertex* new = (Vertex*)malloc(sizeof(struct strVertex));
	if(new!=NULL)
    {
		new->data = data;
        new->id = who->vertex;                                          //ID va ser conforme se van creando los vertices
        new->chain = list_create();                                     //Se utilice funciones de 'list.h' para crear la lista
        who->arr[who->vertex] = new;                                    //Se guarda el apuntador en el arreglo que tiene el grafo
        who->arr = realloc(who->arr, sizeof(Vertex)*(who->vertex+1));   //Se crea un nuevo espacio en el arreglo del grafo
        who->vertex++;                                                  //para poder siempre recibir un vertice nuevo
        return true;
    }
    else
        return false;
}

bool  graph_addEdge(Graph who, Type source, Type dest)
{
    //Primero buscamos el tweet y re-tweet dentro del arreglo del grafo y sacamos su id (source y dest)
    int id_source = -1, id_dest = -1;
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

void graph_PrintAll(Graph who, long long var)  //Imrpime todo el grafo
{
	for(int i=0; i<var;i++)
    {
        who->myPrint(who->arr[i]->id, (char*)who->arr[i]->data, list_size(who->arr[i]->chain));
/*		printf("\n(Tweet ID:%d - %s)", who->arr[i]->id, who->arr[i]->data);
		printf(" # of Re-Tweets: %d",list_size(who->arr[i]->chain));
		//printf("\n\tRe-Tweet: %s", who->arr[list_get(who->arr[i]->chain, x)]->data);

		for(int x=0; x<list_size(who->arr[i]->chain); x++){
			printf("\n\tRe-Tweet: %s", who->arr[list_get(who->arr[i]->chain, x)]->data);
		}*/
	}
}

void graph_printSingleUser(Graph who, long long var, singlePrint user, int id)  //Imprime los re-tweets que tiene un tweet
{
    printf("\n(Tweet ID:%d - %s)", who->arr[id]->id, who->arr[id]->data);
    for(int x=0; x<list_size(who->arr[id]->chain); x++)
    {
        user(who->arr[list_get(who->arr[id]->chain, x)]->data);
    }
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
