/*
    author @ Utsav Mehta and Shallav Varma
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*    
    Orientation gives the direction of motion of the bot
    with respect to reference. 
*/
typedef enum{
  Straight,
  Right,
  Back,
  Left
} orientation;

/*
Represents an edge between two nodes in the graph. For each node in the graph there is a list of edgeNodes which represent the nodes directly connected with that particular node.
*/
struct edgeNode {
  struct edgeNode * next; //pointer to the next node connected to the vertexNode 
  int id;                           //id of the node to which the vertexNode is connected to 
  int distance;                 //distance  from the node to the vertexNode 
  orientation turn;            //orientation of the node wrt the vertexNode
};

/*
		    It  represents all the nodes in my graph structure.
*/ 
struct vertexNode {
int id;    //  used for identification of the node.
struct edgeNode *head,*tail;    // Head and tail of the list of nodes to which a particular
                                          // node is connected to in graph.
struct vertexNode *next; // Pointer to the next vertex node
};

typedef struct edgeNode edgeNode;
typedef struct vertexNode vertexNode;

/*
    Allocates a new node  in the graph.
    @return
    True if memory allocated successfully, false otherwise.
*/
bool createVertexNode();

/*
    Allocates an edge node.
    @param
     ID of new node.
*/
void createEdgeNode(int);

/* 
deletes an edge from node A to B. 
Note: it only deletes the edge from A to B not from B to A
*/ 
void deleteEdgeAtoB(vertexNode *, vertexNode *);

/*
Completely deletes the edge from node A to node B i.e both from A to B and B to A.
*/
void deleteEdge(vertexNode *, vertexNode *);

/*
    Deletes the vertex node and all its edges from the graph.
    @param
    Pointer to vertex node which is to be deleted
*/
void deleteVertexNode(vertexNode *);

/*
    Adds an edge between two nodes.
    @param: 
    vertexNode 1 ,vertexNode2 ,orietntation of vertexNode 1 wrt vertexNode 2,orietntation of      vertexNode 2 wrt vertexNode 1
    Returns true if the adge is succesfully added and false otherwise.
*/
bool addEdge(vertexNode *,vertexNode *, float, orientation, orientation);

/*
    Searches a vertex node. 
    This method is used internally by graph.c when no return value is expected.
    @param
    ID of the node to be searched.
    
*/
void search(int);

/*
    Searches a vertex node.
    This method is called by other files in project when a pointer return type is expected.
    @param
    ID of the node to be searched.
    @return
    Pointer to the vertex node if found, else NULL.
*/
vertexNode* searchNode(int );

/*
    Searches an edge between a vertexNode to another node in the list of edgeNodes corresponding to a vertexNode.
    @param
    vertexNode whose edges have to be searched.
    id of the edgeNode to be searched.
*/
void searchEdge(vertexNode*, int );

/*
   allocates the first node in the graph and initialises its ID to 0
*/
void init();

/*
  prints out the entire graph with all the nodes along side the nodes that are directly connected to it.
*/
void print();

/*
  Adds an edgenode to the list of edgeNodes of a vertexNode
  @param 
  vertexNode whose edgeNode list needs to be updated.
  edgeNode which needs to be added to the list.
*/
void edgeInit(vertexNode *, edgeNode *);


vertexNode *head;  // head of the vertexNode List
vertexNode *tail;  // tail of the vertexNode List
vertexNode *foundNode;
edgeNode *foundEdge; //found edgeNode


