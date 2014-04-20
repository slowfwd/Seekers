
#include "dataStructures.h"
int xx;

#define ASSIGN_ID() ((xx) = (xx) + 1)

edgeNode *n;

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
vertexNode* searchNode(int nodeID){
  search(nodeID);
  return foundNode; 
}

void search(int nodeID)
{
    foundNode = head;
    if (nodeID > tail -> id)
    {
        return ;
    }
    else if (nodeID == tail -> id)
    {
        foundNode = tail;
        return;
    }
    else
    {
        while (foundNode -> id != nodeID)
        {
            foundNode = foundNode -> next;
        }
     
    }     
} 


/* @author Utsav 
adds an edge between two vertex nodes
*/  
bool addEdge(vertexNode* nodeA, vertexNode* nodeB, float distance, orientation turntoA, orientation turntoB ){
    edgeNode *EdgeAToB,*EdgeBToA;
    createEdgeNode(nodeB->id);
    EdgeAToB = foundEdge;
    createEdgeNode(nodeA->id);
    EdgeBToA = foundEdge;
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
        	searchEdge(iter,nodeA -> id);
        	if (foundEdge)
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


void searchEdge(vertexNode* vnode, int id){
	 foundEdge = vnode->head;
	 //printf("%p\n",foundEdge);
	 //printf("%d\t%d",foundEdge->id, id);
	while(foundEdge){
		if(foundEdge->id == id)
			return ;
		foundEdge = foundEdge->next;
	}
	
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
void createEdgeNode (int id)
{
    n = (edgeNode *)malloc(sizeof(edgeNode));
    if ( n != NULL)
    {
        n -> id = id;
    }
   foundEdge = n;
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

/*
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
}*/
