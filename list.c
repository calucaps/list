#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MAXDATA 64
typedef struct _node {
	char data[MAXDATA];
	struct _node *next;
	struct _node *prev;
} NODE;

typedef struct _list {
	NODE *head;
	NODE *tail;
} LIST;


NODE *createNode() { 
	NODE *new = calloc(1,sizeof(NODE));
	return new;
}


NODE *createNodeWithData(char *data) {
	NODE *new = createNode();
        strncpy(new->data,data,strlen(data));
	return new;
}

NODE *appendNode(LIST *list, NODE *node) {
	NODE *head = list->head;
	if (head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else {
	    
            NODE *tail  = list->tail;
	    tail->next = node;
	    node->prev = tail;
	    list->tail = node;
	}
	return list->tail;
}

NODE *pushNode(LIST *list, NODE *node){
	NODE *head = list->head;
	if (head == NULL) {
		appendNode(list, node);
	}
       	else {
            list->head = node;
	    node->next = head;
	    head->prev = node;
	}

	return node;
}

NODE *popNode(LIST *list) {
      NODE *node = list->head;
      if (node != NULL) {
 	  list->head = node->next;
	  list->head->prev = NULL;
      }
      return node;
}

LIST *createList() {

	LIST *list = calloc(1,sizeof(LIST));
        return list;	
}

void dumpList(LIST *list) {
        NODE *node = list->head;
	while(node != NULL) {
		printf("node.data -> %s\n", node->data);
		node = node->next;
	}
}


void dumpListReverse(LIST *list) {
        NODE *node = list->tail;
	while(node != NULL) {
		printf("node.data -> %s\n", node->data);
		node = node->prev;
	}
}

NODE *findNode(LIST *list, char *data) {
        NODE *node = list->head;
	while(node != NULL) {
                if (strncmp(data,node->data,MAXDATA) == 0) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

NODE *removeNode(LIST *list, char *data) {
        NODE *node = list->head;

	while(node != NULL) {
                if (strncmp(data,node->data,MAXDATA) == 0) {
			node->prev->next = node->next;
			node->next->prev = node->prev->prev;
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void destroyList(LIST *list) {
        NODE *node = list->head;
	while(node != NULL) {
		NODE *old = node;
		node = node->next;
		free(old);
	}
	free(list);
}

void createRandomData(char *data, size_t size){
	for (size_t ii = 0 ; ii < size ; ii++) {
		data[ii] = rand() % 95 + 33;
	}
}

int main(int argc, char **argv) {

	LIST *list = createList();

	NODE *head = createNodeWithData("head");
	
	NODE *node = appendNode(list, head);

	NODE *new = createNodeWithData("dddddaaaaa");

	node = appendNode(list,new);

	node = createNodeWithData("dafaadfa2");

	node = appendNode(list,node);

	node = createNodeWithData("new head");

        node = pushNode(list,node);

        
	char buff[MAXDATA];

	for (int ii = 0; ii < 10; ii++) {
		sprintf(buff,"node %d",ii);
		node = createNodeWithData(buff);
		pushNode(list,node);		
	}

	dumpList(list);

	node = popNode(list);

	free(node);

	printf("----------------\n");

	dumpList(list);

	node = findNode(list,"node 4");

	if (node != NULL) {
		printf("found %s\n", node->data);
	}

	printf("----------------\n");

	dumpListReverse(list);

	printf("----------------\n");

	removeNode(list,"node 4");

	dumpList(list);

	destroyList(list);


	printf("----------------\n");

	time_t t;
	srand((unsigned) time(&t));

	LIST *list1 = createList();

	for(int jj = 0; jj < 10; jj++) {
		memset(buff,0,MAXDATA);
		createRandomData(buff,10);
	        node = createNodeWithData(buff);
		appendNode(list1,node);
	}

	dumpList(list1);

	printf("----------------\n");
	dumpListReverse(list1);
	
	destroyList(list1);

	printf("the end\n");

} 



