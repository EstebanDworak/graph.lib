#ifndef LIST_H_
#define LIST_H_

typedef void *Type;
typedef struct strList *List;

List list_create();

int list_size(List l);

void list_add(List l, Type data);

Type list_get(List l, int p);

void list_set(List l, Type data, int p);

Type list_remove(List l, int p);

void list_destroy(List l);

#endif /* LIST_H_ */

