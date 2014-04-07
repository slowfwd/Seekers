
#include "dataStructures.h"
//int xx;
void init()
{ 	
	xx = 0;
	head = (vertexNode *)malloc(sizeof(vertexNode));
	head->id = xx;
	head->next = NULL;
	head -> head = NULL;
	head -> tail = NULL;
	tail = head;
}


// Search a node. 
/* @author Shallav 


*/    
vertexNode *search(int nodeID)
{
    vertexNode *iter = head;
    if (nodeID > tail -> id)
    {
        return NULL;
    }
    else if (nodeID == tail -> id)
    {
        return tail;
    }
    else
    {
        while (iter -> id != nodeID)
        {
            iter = iter -> next;
        }
        return iter;
    }     
} 


/* @author Utsav 
adds an edge between two vertex nodes
*/  
bool addEdge(vertexNode* nodeA, vertexNode* nodeB, float distance, orientation turntoA, orientation turntoB ){
    edgeNode *EdgeAToB,*EdgeBToA;
    EdgeAToB = createEdgeNode(nodeB->id);
    EdgeBToA = createEdgeNode(nodeA->id);
    if (EdgeAToB == NULL || EdgeBToA == NULL)
      return false;
    edgeInit(nodeA,EdgeAToB);
    edgeInit(nodeB,EdgeBToA);
    
    EdgeAToB->distance = distance;
    EdgeAToB->turn = turntoB;
    
    EdgeBToA->distance = distance;
    EdgeBToA->turn = turntoA;
    
    return true;
}
void edgeInit(vertexNode *vnode, edgeNode *enode){

    if(vnode->head == NULL){
      vnode->head = enode;
      vnode->tail = vnode->head;
      }
    else{
      vnode->tail->next = enode;
      vnode->tail = enode;
    }
    vnode->tail->next = NULL;

}
/* @author Shallav 
    deletes a node from graph
    First deletes all the edges emitting from graph, then deletes the node.*/
    
void deleteVertexNode ( vertexNode* nodeA)
{
    vertexNode * iter = head;
    vertexNode * temp = head;
    
    if (nodeA == NULL)
    {
        return;
    }
    //printf("Head ID: %d\n",iter -> id);
    while (iter)
    {
    	printf("ID: %d\n",iter -> id); 
        if (iter == nodeA)
        {
            edgeNode * head = nodeA -> head;
            edgeNode *delNode;
            while(head -> next)
            {
            	delNode = head -> next; 
            	head -> next = delNode -> next;
            	free(delNode);
            	//printf("NotReached\n"); 
            }	
            free(head);
            nodeA -> tail = NULL;       
        }
        else
        {
        	if (iter -> next == nodeA)
        	{
        		temp = iter;
        	}
        	if (searchEdge(iter,nodeA -> id))
        	{   printf("Searched Vertex Node %d\n",iter->id);
        		deleteEdgeAtoB(iter, nodeA);
        	}
        }
        iter = iter -> next;
    }    
    temp -> next = nodeA -> next;
    free(nodeA);
    printf("Done.\n");
}

edgeNode * searchEdge(vertexNode* vnode, int id){
	edgeNode* current = vnode->head;
	while(current){
		if(current->id == id)
			return current;
		current = current->next;
	}
	return current;
}
/* @author Utsav 
deletes all edges between two vertex nodes
*/ 
void deleteEdge(vertexNode* nodeA ,vertexNode* nodeB){
    deleteEdgeAtoB(nodeA, nodeB);
    deleteEdgeAtoB(nodeB, nodeA);
}

/* @author Utsav 
deletes an edge between vertexNode A and vertexNode B
*/ 
void deleteEdgeAtoB(vertexNode* nodeA, vertexNode* nodeB){
    edgeNode  * temp;
    edgeNode * currentNode;
    currentNode = nodeA->head;
    
    if (nodeA->head->id == nodeB->id){
    	temp = nodeA->head;
    	nodeA->head = temp->next;
    	free(temp);
    	return;
    }
      
    while(currentNode!= nodeA->tail)
    {
    	temp = currentNode;
    	if(currentNode->next->id == nodeB->id){
            temp = currentNode->next;
            currentNode->next = temp->next;
            free(temp);
            return;
        }
        currentNode = currentNode -> next;
    }   
    if(currentNode->id == nodeB->id)
    {
      	free(currentNode);
      	nodeA->tail = temp;      
    } 	
}

/* @author Shallav 
 */
edgeNode * createEdgeNode (int id)
{
    edgeNode *n = (edgeNode *)malloc(sizeof(edgeNode));
    if ( n != NULL)
    {
        n -> id = id;
    }
    return n;
}

/* @author Shallav */ 
bool createVertexNode ()
{
    vertexNode *n = (vertexNode *)malloc(sizeof(vertexNode));
    if (n == NULL)
    {
        return false;
    }
    else
    {    
        n -> id = ASSIGN_ID();
        n -> head = NULL;
        n -> tail = NULL;
        n -> next = NULL;
        tail -> next = n;
        tail = n;
  		
        return true;
    }
}

void printList ()
{
vertexNode * iter;
iter = head;
while (iter)
{
	printf("%p\t",iter);
	printf("%d \n", iter -> id) ;
	iter = iter -> next;
}
printf("%p\t",iter);
}

void print(){
	vertexNode *vertical = head;
	edgeNode *horizontal ; 
	while(vertical){
		printf("%d\t",vertical->id);
		horizontal = vertical->head;
		while(horizontal){
			printf("%d\t",horizontal->id);
			horizontal = horizontal->next;
		}
		vertical = vertical->next;
		printf("\n");
	}
}


int main()
{
    init();
    int i=0;
    while(i<7){
    	createVertexNode();
    	i++;
    }
    
    addEdge(search(0),search(1), 10, Left,Right );
    addEdge(search(0),search(4), 10, Left,Right );
    addEdge(search(1),search(2), 10, Left,Right );
    addEdge(search(2),search(3), 10, Left,Right );
    addEdge(search(2),search(4), 10, Left,Right );
    addEdge(search(4),search(5), 10, Left,Right );
    addEdge(search(4),search(6), 10, Left,Right );
    addEdge(search(5),search(6), 10, Left,Right );
    //deleteEdge(search(4),search(5));
    //deleteEdge(search(2),search(3));
    deleteVertexNode (search(4));
    print();
    return 0;
}
