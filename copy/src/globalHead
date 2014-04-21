#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXNODES 10

typedef struct node {
	int ID;
	struct node * next; // a pointer to the next node
} graph_node;
graph_node * head =NULL;
int tempList[MAXNODES];

/**
 * no parameters
 * returns nothing
 * create a linked list
 */
graph_node * createList(){

	// graph_node * head = NULL;
	head =  malloc(sizeof(graph_node));//points to the start of dynamic memory allocated for the struct

	head->ID = 0;
	head->next = NULL;
	return head;
}

/**
 * @param- pointer to first element, node ID
 * returns nothing
 */
void add(int ID){

	graph_node * current = head;
	while(current->next != NULL){//traverse till the end of the list
		current = current->next;
		// printf("In while\n");
	}
	printf("new node added\n");
	current->next = malloc(sizeof(graph_node));
	current->next->ID = ID;
	current->next->next = NULL;
}

/**
 * prints out the list of nodes in the list
 */
int * list(){

	
	graph_node * current = head;
	if(current == NULL){
		printf("List Empty!");
		return NULL;
		// return -1;
	}
	int i=0;
	while(current != NULL){
		// printf("Node %d\n", current->ID);
		tempList[i] = current->ID;
		current = current->next;
		i++;
	}
	// return 1;
	return &tempList[0];
}

int removeNode(int ID){

	graph_node * current = head;
	graph_node * temp;

	if(head->next == NULL){//only one node in list
		if(head->ID == ID){
			free(head);
			head=NULL;
			return 1;
		}
	}
	else{//more than one node in list
		//if first one is the Required one!
		if(current->ID == ID){
			temp= current->next;
			free(head);
			head = temp;
			return 1;
		}
		while(current->next != NULL){//check rest of the nodes
				if(current->next->ID == ID){
					temp= current->next->next;
					free(current->next);
					current->next = temp;
					return 1;
				}
				current=current->next;
			}
		}
	return -1;
}

/**
 * returns the pointer to the node with given ID
 */
graph_node * searchNode(int ID){

	graph_node * current = head;

	while(current != NULL){
		if(current->ID == ID)
			return current;
		else{
			current = current->next;
		}
	}
	return NULL;
}

/**
 * @param pointer to first element
 * returns nothing
 * clears the entire list
 */
void clear(){

	// graph_node * current =head;
	graph_node * temp;
	while(head->next != NULL){//last node
		temp = head->next;
		free(head);
		head = temp;
	}
	if(head->next == NULL)//last element
		free(head);
		head=NULL;
}

/**
 * @param- node ID, pointer to first element of the list
 * returns true if the list contains the given ID
 * 			false otherwise
 */
bool contains(int ID){

	if(searchNode(ID) == NULL)
		return false;
	return true;
}

/**
 * 
 * returns number of nodes in the list
 */
int size(){

	graph_node * current = head;
	int len=0;
	if(current == NULL)
		return len;//empty list
	while(current != NULL){
		len++;
		current= current->next;
	}

	return len;
}

int main(){
	graph_node * tempPtr;
	// int list[MAXNODES];
	
	//create a linked list, return the pointer to first element
	head = createList();
	//add the node with given ID to the end of the list
	add(3);
	add(1);
	add(2);
	int *i;
	//print the list of all nodes in the list
	// i = list();
	// printf("i=%d\n",i);
	// i = removeNode(1);
	// printf("i=%d\n",i);

	// tempPtr = searchNode(0);
	// if(tempPtr == NULL)
	// 	printf("Node not found!\n");
	// else
	// 	printf("Node found!\n");
	// printf("List contains node 2:%d",contains(2));
	// printf("Length of the list = %d\n", size());
	// clear();
	int j,len;
	// j = list();
	i = list();
	// if(j == 0)
	// 	printf("List is Empty!\n");
	len = size();
	printf("Length of the list = %d\n", len);
	// for(j=0;j < len;j++){
	// 	printf("Node %d\n",tempList[j]);
	// 	// j++;
	// }
	while(len!=0){
		printf("Node %d\n",*i);
		i++;
		len--;
	}
	return 0;
}
