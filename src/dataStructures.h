#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

int xx ;

#define ASSIGN_ID() ((xx) = (xx) + 1)

typedef enum{
    false,
    true} bool;

typedef enum{
  Straight,
  Right,
  Back,
  Left
} orientation;



struct edgeNode {
  struct edgeNode * next;
  int id;
  float distance;
  orientation turn;
};

struct vertexNode {
int id;
struct edgeNode *head,*tail;
struct vertexNode *next;
};

typedef struct edgeNode edgeNode;
typedef struct vertexNode vertexNode;


bool createVertexNode();
edgeNode * createEdgeNode(int);
void deleteEdgeAtoB(vertexNode *, vertexNode *);
void deleteEdge(vertexNode *, vertexNode *);
void deleteVertexNode(vertexNode *);
bool addEdge(vertexNode *,vertexNode *, float, orientation, orientation);
vertexNode * search(int);
bool searchEdge(vertexNode*, int );
void init();
void print();
void edgeInit(vertexNode *, edgeNode *);
vertexNode *head;
vertexNode *tail;
