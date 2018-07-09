


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


struct strNode{
	Type Data;
	struct strNode *next;
	struct strNode *prior;
};

typedef struct strNode Node;

struct strList{
	Node *first;
	Node *last;
	unsigned int size;
};

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

Node * createNode(Type data){
	Node *new;
	new=(Node *)malloc(sizeof(Node));
	new->Data=(void *)malloc(sizeof(*data));
	memcpy(new->Data, data, sizeof(*data));
	new->next=NULL;
	new->prior=NULL;
	return new;
}

void list_add(List l, Type data){
	//Agrega un elemento al final de la lista
	//e incrementa el size
	if(l!=NULL){
		Node *new;
		new=createNode(data);
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

Type list_get(List l, int p){
	Type value=NULL;
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
			value=current->Data;
		}
	}
	return value;
}

void list_set(List l, Type data, int p){
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
			current->Data=data;
		}
	}
}

Type list_remove(List l, int p){
	Node *current=NULL;
	Type tmp;
	int i=0;
	int s=l->size;
	if(l!=NULL){
		//Buscar el nodo a remover
		if ((p>=0) && (p<s)){
			current=l->first;
			while(i<p){
				current=current->next;
				i++;
			}
		}
		if((p==0)&&(s==1)){
			tmp=current->Data;
			l->first=NULL;
			l->last=NULL;
			l->size=0;
			free(current);
			return tmp;
		}else{
			if(p==0) //Se va a eliminar el nodo inicial
			{
				tmp=current->Data;
				l->first=current->next;
				l->first->prior=NULL;
				l->size--;
				free(current);
				return tmp;
			}
			else{
				if(p==(s-1))//Se va a eliminar el nodo final
				{
					tmp=current->Data;
					l->last=current->prior;
					l->last->next=NULL;
					l->size--;
					free(current);
					return tmp;
				}
				else
				{//El elemento a remover esta en medio
					tmp=current->Data;
					current->prior->next=current->next;
					current->next->prior=current->prior;
					free(current);
					return tmp;
				}
			}
		}

	}
	return NULL;
}

void list_destroy(List l){
	while(list_size(l)>0)
		list_remove(l, 0);
	free(l);
}








































