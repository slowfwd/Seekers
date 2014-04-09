#include "interface.h"


void getParam(pathNode * curr)
{       
	if(curr->next->next==NULL)
	{
        	endofList = 1;
		return;
	}
	search(curr->id);
	searchEdge(foundNode,curr->next->id);
	printf("%d ID found in Vertex Node %d.\n",foundEdge -> id, curr ->id);
	res_params->turn = foundEdge->turn;
	res_params->timer = foundEdge->distance;
	
 }
	
