//#include "dataStructures.h"
#include "motor.h"
#include "dfs.h"
#include "init.h"


extern bool objectFound;               //From opencv

orientation lastTurn;                          
orientation lastPostionSeen = Straight;     


int distanceToNextNode; //Distance to be travelled to the next node

static set* markedNodes;   // Set for storing nodes visited
static set* frontierNodes; // Set for storing frontier nodes to be explored
static stack spine;        // Spine for storing node IDs


/**
@description:
    initializes spine

*/

void init_Dfs()
{
  initStack(&spine);    //Initializes the stack     
}


/**
@description:
    Given a node id with reference to the graph,
    the neighbouring nodes are added to the frontier set
*/

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

/**
@description:
    The next node to be traversed is decided
    Incorporates the last position seen by the bot

@return : Returns the ID of the next node to be traversed

*/

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
    

/**
@description: Given the current node and next node
              to be traversed, the function returns only after 
              the bot has traversed to the next node

*/              

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

/**
@description: 
    Checks if neighbor node exists in the frontier
    Returns bool
*/
int checkIfNeighborExistsInFrontier(int nodeID) 
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

void startSearch()
{
    int currentNodeID = 0;  //Current node while starting is 0


    init_Dfs();         //Initialize the stack spine
    init_motors();      
    run();

    int nextNodeID;
    addNeigbourNodesToFrontier(currentNodeID);
    addToSet(&markedNodes,currentNodeID);  
    push(&spine, currentNodeID);
    nextNodeID = DecideNextNode(currentNodeID);
    int cnt = 0;
while(1)
{
    //scanAndSearch();    //openCV code 
    
    if(objectFound == true)
    {
        // Functionality here TBD 

    	printf("Obj found: %d",cnt);
	    cnt ++;
	    rotate360();
    	objectFound = false;	

       /* while(isObjectClose() == 0)
           moveForward(); // Provided by the motor library
    
            if(distanceTravelledFromPrevNode == distanceToNextNode)
                addToSet(&markedNodes,currentNodeID);
           //?? Who updates the current position of the object
	*/
        //Keep track of the distance so that obj position is known
        //Keep track of where we are in the graph

    }
    else
    {
        
  
        printf("Spine. \n");
        printStack(&spine);
        printf("\n\n");

        printf("Next node to be traversed: %d\n", nextNodeID);
     
        moveToNextNode(currentNodeID,nextNodeID); //Move to the next node
        currentNodeID = nextNodeID;             
        
        addToSet(&markedNodes,currentNodeID);   //Current Node has been traversed. Add to the set
        addNeigbourNodesToFrontier(currentNodeID);  //Adding frontier nodes from the new current node
        removeNodeFromSet(&frontierNodes,currentNodeID); //Removing the current node from frontier
     
        printf("Done nodes : \n");
        listSet(markedNodes);
        printf("Frontier Nodes : \n");
        listSet(frontierNodes);



        if (checkIfNeighborExistsInFrontier(currentNodeID)) //Check if neighbor exists in frontier
        {                                                   // If so visit there
         
            push(&spine, currentNodeID);  //Change
            nextNodeID = DecideNextNode(currentNodeID);
        }
        else
        { 
        if(isStackEmpty(&spine))
            return ; // Done traversing. Stop
        else
            {
                nextNodeID = pop(&spine);                
            }
        }
            
       }
        
}
}





