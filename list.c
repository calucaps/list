#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MAXDATA 64
#define INDEX_SIZE 1000

typedef struct _node {
	char data[MAXDATA];
	struct _node *next;
	struct _node *prev;
} NODE;

typedef struct _list {
	NODE *head;
	NODE *tail;
	NODE **index;
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
	list->index = calloc(INDEX_SIZE,sizeof(NODE *));
        return list;	
}

NODE ** indexList(LIST *list){
        NODE *node = list->head;
	memset(list->index,0,sizeof(NODE *) * INDEX_SIZE);
	int ii = 0;
	while(node != NULL) {
		list->index[ii] = node;
		node = node->next;
		ii++;
	}
	return list->index;
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

LIST *createListWithRandomElements(int size, int datasize){
	
	LIST *list = createList();

	char buff[MAXDATA];

	for(int jj = 0; jj < size; jj++) {
		memset(buff,0,MAXDATA);
		createRandomData(buff,datasize);
	    NODE *node = createNodeWithData(buff);
		appendNode(list,node);
	}

	return list;

}

LIST *createTestList(int size){
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

	for (int ii = 0; ii < size; ii++) {
		sprintf(buff,"node %d",ii);
		node = createNodeWithData(buff);
		pushNode(list,node);		
	}

	return list;

}

int main(int argc, char **argv) {


    LIST *list = createTestList(5);

	dumpList(list);

	NODE *node = popNode(list);

	free(node);

	printf("----------------\n");

	dumpList(list);

	node = findNode(list,"node 4");

	if (node != NULL) {
		printf("found %s\n", node->data);
	}
	else {
		printf("Not Found\n");
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

	
    LIST *list1 = createListWithRandomElements(3,15);

	dumpList(list1);



	printf("----------------\n");
	dumpListReverse(list1);
        printf("Printing index\n");
	
	NODE **index = indexList(list1);

	int kk = 0;
	while(index[kk] != NULL) {
		printf("idx %d %s\n", kk, index[kk]->data);
		kk++;
	}

	destroyList(list1);

	printf("the end\n");

} 



