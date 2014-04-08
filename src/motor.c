
#include <stdio.h>
#include <bcm2835.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include "interface.h"

#define FORWARD 1
#define RIGHT 2
#define LEFT 3
#define MOTORA RPI_GPIO_P1_12
#define MOTORB RPI_GPIO_P1_11



struct motor_params{
  int pin;
  float duty;
  };

pathNode *headList;


void printPath ()
{
pathNode * iter;
iter = headList;
while (iter)
{
	//printf("%p\t",iter);
	printf("%d \n", iter -> id) ;
	iter = iter -> next;
}
//printf("%p\t",iter);
}

void run ()
{   init(); 
    int i = 0;
    while(i<7){
        createVertexNode();
        i++;
    }
    addEdge(search(0),search(1), 3, Right, Right );
    addEdge(search(0),search(2), 3, Right, Right );
    addEdge(search(1),search(2), 3, Right, Right );
    addEdge(search(2),search(4), 3, Right, Right );
    addEdge(search(2),search(5), 3, Right, Right );
    addEdge(search(2),search(3), 3, Right, Right );
    addEdge(search(1),search(3), 3, Right, Right );
    addEdge(search(3),search(6), 3, Right, Right );
    
    
    headList = insert(headList,0);
    insert(headList,2);
    insert(headList,1);
    insert(headList,0);
    //insert(headList,0);
    printPath();
    //print();
  }



void *drivemotors(void *arg){

 struct  motor_params* motor = (struct motor_params*)arg;
 
 //printf("VALUE: %d\n",value);
 
 while(1){
   bcm2835_gpio_write(motor->pin,HIGH);
   bcm2835_delayMicroseconds(motor->duty*200);
   bcm2835_gpio_write(motor->pin,LOW);
   bcm2835_delayMicroseconds((100-motor->duty)*200);
 
  } 
}


int main(int argc,char **argv){ 
  param*  moveParams;
  struct motor_params motorleft,motorright;
  pthread_t lth ,rth;
  run();

  motorleft.pin = MOTORA;
  motorright.pin = MOTORB;
  int direction = 3;
  
 
   
  if(!bcm2835_init())
    return 1;

  bcm2835_gpio_fsel(MOTORA, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(MOTORB, BCM2835_GPIO_FSEL_OUTP);
  
 
  
  while(headList){

       moveParams = getParam(headList);
       direction =  moveParams->turn;
       
       printf("Headlist id : %d",headList->id);
      
      //scanf("%d",&direction);
      switch(direction){
      	case FORWARD:
      	  motorright.duty = 3.75;
      	  motorleft.duty = 11.25;
      	  break;
      	case RIGHT:
      	  motorright.duty = 7.25;
      	  motorleft.duty = 11.25;
      	  break;
      	case LEFT:
      	  motorright.duty = 3.75;
      	  motorleft.duty = 7.25;
      	  break;
      	default:
      	  motorright.duty = 7.25;
      	  motorleft.duty = 7.25;
      	  break; 
      }
      
      //starting motor thread   
      pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
      pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
      //sleep(3);
      sleep(moveParams->timer);
      /*if(direction == FORWARD)
    	sleep(3);
      else{ 
	sleep(1);
	}*/	 
      pthread_cancel(rth);
      pthread_cancel(lth);
      pthread_join(rth,NULL);
      pthread_join(lth,NULL);
      headList = headList->next;
      
    
  }
  
  bcm2835_close();

  return 0;
}
