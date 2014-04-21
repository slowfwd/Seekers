#include "interface.h"
int endofList;
pathNode * insert(pathNode * head,int d){
  pathNode * newNode = (pathNode *) malloc(sizeof(pathNode));
  pathNode * currentNode= head;
  
  if(head==NULL){
    head = newNode;
    newNode->next = NULL;
  newNode->id= d;
  return head;
  }
  else{
    while(currentNode->next!=NULL){
      currentNode = currentNode->next;
    }
    currentNode->next = newNode;
  }
  
  newNode->next = NULL;
  newNode->id= d;
  return head;
}
