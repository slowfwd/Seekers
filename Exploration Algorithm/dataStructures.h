#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
  Straight,
  Right,
  Back,
  Left
} orientation;

struct edgeNode {
  struct edgeNode * next;
  int id;
  int distance;
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
void createEdgeNode(int);
void deleteEdgeAtoB(vertexNode *, vertexNode *);
void deleteEdge(vertexNode *, vertexNode *);
void deleteVertexNode(vertexNode *);
bool addEdge(vertexNode *,vertexNode *, float, orientation, orientation);
void search(int);
vertexNode* searchNode(int );
void searchEdge(vertexNode*, int );
void init();
void print();
void edgeInit(vertexNode *, edgeNode *);


vertexNode *head;
vertexNode *tail;
vertexNode *foundNode;
edgeNode *foundEdge;



