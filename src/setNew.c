#include "set.h"

// void initSet(set * head){

// 	head->listHead = NULL;
// }

void addToSet(set * head, int ID){

	//check if the node exists, don't add
	// graph_node * current = head;
	// printf("Inside addToSet \n");
	// printf("Pointer to Spine: %d\n",head);

	if(head == NULL){//first element of the set
		// printf("Inside addToset first element loop\n");
		head = malloc(sizeof(set));
		head->listHead = NULL;
	}
	if(!setContains(head, ID)){// if the set doesn't contain the given ID
		addToLinkedList(head,head->listHead, ID);

	}
}


/**
 * @param- pointer to first element, node ID
 * returns nothing
 */
void addToLinkedList(set* setHead, graph_node * head, int ID){

	// printf("the head before malloc %d\n",head);

	// if(current == NULL){//first node of the list
	// 	current = malloc(sizeof(graph_node));
	// 	current->ID = ID;
	// 	current->next = NULL;
	// 	printf("Inside addToLinkedList\n");
	// 	return;
	// }
	if(head == NULL){//first node of the list
		head = malloc(sizeof(graph_node));
		// printf("the head after malloc %d\n",head);
		head->ID = ID;
		head->next = NULL;
		// printf(" Inside addToLinkedList\n");
		setHead->listHead = head;
		return;
	}
	graph_node * current = head;
	while(current->next != NULL){//traverse till the end of the list
		current = current->next;
		// printf("In while\n");
	}
	// printf("new node added\n");
	current->next = malloc(sizeof(graph_node));
	current->next->ID = ID;
	current->next->next = NULL;
	setHead->listHead = head;
}

/**
 * prints out the list of nodes in the list
 */
// 

void listLinkedList(graph_node * head){

	
	graph_node * current = head;
	if(current == NULL){
		printf("List Empty!");
		return;
		// return -1;
	}
	int i=0;
	while(current != NULL){
		printf("Node %d\n", current->ID);
		current = current->next;
		// printf("Is it here?\n");
	}
	// return 1;
}


void listSet(set * head){

	if(head == NULL)
		return;
	listLinkedList(head->listHead);
	// printf("Is it here?\n");
}

int removeNodeFromList(set * setHead, graph_node * head, int ID){

	graph_node * current = head;
	graph_node * temp;

	if(head->next == NULL){//only one node in list
		if(head->ID == ID){
			free(head);
			head=NULL;
			setHead->listHead = NULL;
			return 1;
		}
	}
	else{//more than one node in list
		//if first one is the Required one!
		if(current->ID == ID){
			temp= current->next;
			free(head);
			// head = temp;
			setHead->listHead = temp;
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

int removeNodeFromSet(set * head, int ID){

	return removeNodeFromList(head, head->listHead, ID);	
}

/**
 * returns the pointer to the node with given ID
 */
graph_node * searchNodeInLinkedList(graph_node * head, int ID){

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
void clearLinkedList(set * setHead, graph_node * head){

	// graph_node * current =head;
	graph_node * temp;
	while(head->next != NULL){//last node
		temp = head->next;
		free(head);
		head = temp;
		setHead->listHead = temp;

	}
	if(head->next == NULL)//last element
		free(head);
		head=NULL;
		setHead->listHead = NULL;
}

void clearSet(set * head){

	clearLinkedList(head, head->listHead);
}

/**
 * @param- node ID, pointer to first element of the list
 * returns true if the list contains the given ID
 * 			false otherwise
 */
bool listContains(graph_node * head, int ID){

	if(searchNodeInLinkedList(head, ID) == NULL)
		return false;
	return true;
}

bool setContains(set * head, int ID){

	return listContains(head->listHead,ID);
}

/**
 * 
 * returns number of nodes in the list
 */
int sizeOfLinkedList(graph_node * head){

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

/**
*
*/
int sizeOfSet(set * head){

	return sizeOfLinkedList(head->listHead);
}

/**
* @param - 
* returns 1 if the list is empty
* 		  0 otherwise
*/
int isLinkedListEmpty(graph_node * head){

	if(sizeOfLinkedList(head)!=0)
		return 0;
	return 1;
}

int isSetEmpty(set * head){

	return isLinkedListEmpty(head->listHead);
}