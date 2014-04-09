#include "dataStructures.h"
#include "list.h"

struct param
{
	orientation turn;
	int timer;
};

typedef struct param param;
param* res_params;
void getParam(pathNode*);
