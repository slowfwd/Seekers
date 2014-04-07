#include "list.h"

void insert(pathNode * head,int d){
  pathNode * newNode = (pathNode *) malloc(sizeof(pathNode));
  pathNode * currentNode= head;
  
  if(head==NULL){
    head = newNode;
  }
  else{
    while(currentNode->next!=NULL){
      currentNode=currentNode->next;
    }
    currentNode->next = newNode;
  }
  
  newNode->next = NULL;
  newNode->data= d;
}