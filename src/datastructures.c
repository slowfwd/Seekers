#include <stdio.h>
#include <string.h>
#include <inttypes.h>

int xx = 0;

#define ASSIGN_ID() ((xx) = (xx) + 1)

enum bool{
    False,
    True};

enum orientation{
  Straight,
  Right,
  Back,
  Left
};

struct edgeNode {
  struct edgeNode * next;
  int id;
  float distance;
  orientation turn;
};

struct vertexNode {
int id;
struct edgeNode *p;
struct vertexNode *next;
};

typedef struct edgeNode edgeNode;
typedef struct vertexNode vertexNode;

vertexNode *head = (vertexNode *)malloc(sizeof(vertexNode));
vertexNode *tail;
head -> p = NULL;
tail = head;

// Search a node. 
/* @author Shallav 


*/    
vertexNode *search(int nodeID)
{
    vertexNode *iter = head;
    if (nodeID > tail.id)
    {
        return NULL;
    }
    else if (nodeID == tail.id)
    {
        return tail;
    }
    else
    {
        while (iter.id != nodeID)
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
    
    EdgeAToB->next = nodeA;
    EdgeAToB->distance = distance;
    EdgeAToB->turn = turntoB;
    
    EdgeBToA->next = nodeB;
    EdgeBToA->distance = distance;
    EdgeBToA->turn = turntoA;
    
    return true;
}

/* @author Shallav */ 
void deleteVertexNode ( vertexNode* nodeA)
{
    vertexNode * temp = head;
    vertexNode * iter = head;
    
    if (nodeA == NULL)
    {
        return;
    }
    
    while (iter)
    {
        if (iter == nodeA)
        {
            temp = iter;
            edgeNode * head = nodeA -> p;
            edgeNode * curr = head, *it;
            while(head -> next)
            {
                it = curr -> next;
                curr -> next = it -> next;
                if (it != NULL)
                {
                    free(it);
                }
                curr = curr -> next;
            }
            free(nodeA);       
        }
        deleteEdgeAtoB(iter, nodeA);
        iter = iter -> next;
    }    
    free(temp);
}
/* @author Utsav 
deletes all edges between two vertex nodes
*/ 
void deleteEdge(vetrexNode* nodeA ,vertexNode* nodeB){
    deleteEdgeAtoB(nodeA, nodeB);
    deleteEdgeAtoB(nodeB, nodeA);
}

/* @author Utsav 
deletes an edge between vertexNode A and vertexNode B
*/ 
void deleteEdgeAtoB(vertexNode* nodeA, vertexNode* nodeB){
    vertexNode* temp, currentNode;
    currentNode = nodeA;
    while(currentNode->next != NULL){
        if(currentNode->next->id == nodeB->id){
            temp = currentNode->next;
            currentNode->next = temp->next;
            free(temp);
        }
        current = current->next;
    }               
}

/* @author Shallav */ 
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
        n.id = ASSIGN_ID();
        n -> p = NULL;
        n -> next = NULL;
        tail -> next = n;
        n = tail;
        return true;
    }
}
