#include <stdio.h>
#include "set.h"
#include "stack.h"

#include "dataStructures.h"

int currentDistanceTravelled;

orientation currentOrientation;

int objectFound = false;               //From opencv
                                        // Change
orientation lastPostionSeen = Straight;

int currentNodeID = 0;   
int distanceToNextNode;

set* markedNodes;
set* frontierNodes;
stack spine;


void addNeigbourNodesToFrontier(int id){
    vertexNode* v = searchNode(id);
    //Found the vertex node

    //Create a temp head edgeNode
    edgeNode* temp_head = v->head; 
    while(temp_head!=NULL)  //Traverse and add all ids into the frontier
    {

        /*if(markedNodes.find(temp_head->id) != markedNodes.end())
            frontierNodes.insert(temp_head->id);
        */
          //change
        if(setContains(markedNodes,temp_head->id) == 0)
            addToSet(&frontierNodes,temp_head->id);
        
        temp_head = temp_head-> next;
    }

}

int DecideNextNode(int currentNodeID){

    vertexNode* v = searchNode(currentNodeID);
    //Found the vertex node

    //Create a temp head edgeNode
    edgeNode* temp_head = v->head; 
    
    if(lastPostionSeen ==Left)
    {

        while(temp_head!=NULL)  //Traverse the edge nodes and check if the id matches
                                // and return true
        {
            if(temp_head->turn == lastPostionSeen)
                {
                    lastPostionSeen = Straight;
                    return temp_head->id;         
                }
            temp_head = temp_head->next;
        }
    }
    else if(lastPostionSeen == Right)
    {

        while(temp_head!=NULL)  //Traverse the edge nodes and check if the id matches
                                // and return true
        {
            if(temp_head->turn == lastPostionSeen)
                {
                    lastPostionSeen = Straight;
                    return temp_head->id;         
                }
            temp_head = temp_head->next;
        }
    }

    else
    {

        while(temp_head!=NULL)  //Traverse the edge nodes and check if the id matches
                                // and return true
        {
        /*    if(markedNodes.find(temp_head->id) !=markedNodes.end())
                return temp_head->id;
        */
           if(setContains(markedNodes,temp_head->id) == 0)
            {
                return temp_head->id;
            }
        
            temp_head = temp_head->next;
        }

    }  

    return 0;  
}
    



void moveToNextNode(int currentNodeID ,int nextNodeID)    //Decides on which  node to move to
{
    vertexNode* v = searchNode(currentNodeID);
    //Found the vertex node
    //Create a temp head edgeNode

    edgeNode* temp_head = v->head; 
    orientation direction ;
    while(temp_head!=NULL) 
    {
        if(temp_head-> id == nextNodeID){
            direction = temp_head->turn;
            distanceToNextNode = temp_head->distance;
            break;
        }
        temp_head = temp_head->next;
    }    
    printf("Node explored : %d \n", currentNodeID);
    // Rotate based on current orientation 
    // Set the timers

    // Actuate Motors
    // Keep updating currentDistanceTravelled

}

int checkIfNeighborExistsInFrontier(int nodeID) //Checks if neighbor node exists in the frontier
{
    vertexNode* v = searchNode(nodeID);
    //Found the vertex node

    //Create a temp head edgeNode
    edgeNode* temp_head = v->head; 

    while(temp_head!=NULL)  //Traverse the edge nodes and check if the id matches
                            // and return true
    {
        /*
        if(frontierNodes.find(temp_head->id) != frontierNodes.end())
            return 1;
       */
        if(setContains(frontierNodes,temp_head->id) == 1)
            return 1;
            
        temp_head = temp_head-> next;
    }
    return 0;

}



void scanAndSearch(void)
{


}

int main()
{


initStack(&spine);
init();
int nextNodeID = -1;

int i = 0;
    while(i<9){
    
        createVertexNode();
        
        i++;
    }
    addEdge(searchNode(0),searchNode(2), 3, Straight, Straight );
    addEdge(searchNode(0),searchNode(5), 3, Right, Right );
    addEdge(searchNode(0),searchNode(6), 4, Straight, Straight );
    addEdge(searchNode(2),searchNode(3), 3, Right, Right );
    addEdge(searchNode(3),searchNode(4), 3, Right, Right );
    addEdge(searchNode(6),searchNode(8), 6, Right, Right );
    addEdge(searchNode(5),searchNode(7), 3, Right, Right );
    addEdge(searchNode(7),searchNode(9), 3, Right, Right );
    addEdge(searchNode(8),searchNode(9), 3, Straight, Straight );

    print();
    addNeigbourNodesToFrontier(currentNodeID);
    addToSet(&markedNodes,currentNodeID);  
    push(&spine, currentNodeID);
    nextNodeID = DecideNextNode(currentNodeID);
while(1)
{
    //scanAndSearch();    //openCV code 
    
/*    if(objectFound == true)
    {
        while(isObjectClose() == 0)
           moveForward(); // Provided by the motor library
    
            if(distanceTravelledFromPrevNode == distanceToNextNode)
                addToSet(&markedNodes,currentNodeID);
           //?? Who updates the current position of the object

        //Keep track of the distance so that obj position is known
        //Keep track of where we are in the graph

    }
    else
    {
        
  */
        //lastPostionSeen = Straight;
        //nextNodeID = DecideNextNode(currentNodeID);
        printf("Spine. \n");
        printStack(&spine);
        printf("\n\n");

        printf("Next node to be traversed: %d\n", nextNodeID);
        moveToNextNode(currentNodeID,nextNodeID); //Add invariant
        currentNodeID = nextNodeID;
        
        addToSet(&markedNodes,currentNodeID);   //Change
        addNeigbourNodesToFrontier(currentNodeID);
        removeNodeFromSet(&frontierNodes,currentNodeID); //Change
        printf("Done nodes : \n");
        listSet(markedNodes);
        printf("Frontier Nodes : \n");
        listSet(frontierNodes);



        if (checkIfNeighborExistsInFrontier(currentNodeID)) //curr ID
        {
         
            push(&spine, currentNodeID);  //Change
            nextNodeID = DecideNextNode(currentNodeID);
        }
        else
        { 
        if(isStackEmpty(&spine))
            return 0; // Done traversing. Stop
        else
            {
                // nextNodeID = spine.top();
                nextNodeID = pop(&spine);                
            }
        }
            
       }
        return 0;
}





