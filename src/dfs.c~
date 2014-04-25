//#include "dataStructures.h"
#include "motor.h"
#include "dfs.h"

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

void init_Dfs()
{
  initStack(&spine);
  init();
  int nextNodeID = -1;
}

void addNeigbourNodesToFrontier(int id){
    vertexNode* v = searchNode(id);
    //Found the vertex node

    //Create a temp head edgeNode
    edgeNode* temp_head = v->head; 
    while(temp_head!=NULL)  //Traverse and add all ids into the frontier
    {

        /*if(markedNodes.find(temp_head->astPosid) != markedNodes.end())
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
            //lastTurn = direction;
		//lastPositionSeen = lastTurn;
            distanceToNextNode = temp_head->distance;
            break;
    }

        temp_head = temp_head->next;
    }   

    moveCar(direction, distanceToNextNode);
	lastTurn  = direction;
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
    init_Dfs();
    init_motors();
    run();
    int nextNodeID;
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





