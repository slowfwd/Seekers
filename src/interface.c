#include "interface.h"
vectorNode currGraph;

param * getParam(pathNode * curr)
{
	edgeNode current;
	param res;
	int id = curr -> id;
	
	if(id == 0)
	{
		currGraph = head;
	}
	
	current = searchEdge(currGraph, id));
	if (current)
	{
		res.turn = current.turn;
		res.timer = current.distance;
	}
	else
	{
		res.turn = 0;
		res.timer = 0;
	}
	return res;
 }
	