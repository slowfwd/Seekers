#include <stdio.h>
#include <bcm2835.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include "motor.h"

#define FORWARD 1
#define RIGHT 2
#define LEFT 3
#define MOTORA RPI_GPIO_P1_12
#define MOTORB RPI_GPIO_P1_11


extern orientation lastTurn;

struct motor_params{
  int pin;
  float duty;
  };

struct motor_params motorleft,motorright;

//pathNode *headList;
//extern param* res_params;
//extern int endofList;

void run ()
{   init();
	lastTurn = Straight;
   // endofList = 0;
    // memory allocation for recieved parameters from graph to drive the bot
    //res_params = (param*) malloc(sizeof(param)); 
    int i = 0;
    while(i<9){
    
        createVertexNode();
        
        i++;
    }
    addEdge(searchNode(0),searchNode(1), 3, Left, Right );
    addEdge(searchNode(1),searchNode(2), 3, Left, Right );
    addEdge(searchNode(2),searchNode(5), 3, Back, Straight );
    addEdge(searchNode(5),searchNode(4), 3, Right, Left );
    addEdge(searchNode(4),searchNode(3), 3, Right, Left );
    addEdge(searchNode(1),searchNode(4), 3, Back, Straight );
    addEdge(searchNode(0),searchNode(3), 3, Back, Straight );
    addEdge(searchNode(3),searchNode(6), 3, Back, Straight );
	addEdge(searchNode(6),searchNode(7), 3, Left, Right );
	addEdge(searchNode(7),searchNode(8), 3, Left, Right );
	addEdge(searchNode(4),searchNode(7), 3, Back, Straight );
	addEdge(searchNode(5),searchNode(8), 3, Back, Straight );    
    
   //print();
  }

void init_motors(){
   motorleft.pin = MOTORA;
   motorright.pin = MOTORB;
   if(!bcm2835_init())
    return ;

  bcm2835_gpio_fsel(MOTORA, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(MOTORB, BCM2835_GPIO_FSEL_OUTP);
}

void *drivemotors(void *arg){

 struct  motor_params* motor = (struct motor_params*)arg;

 
 while(1){
   bcm2835_gpio_write(motor->pin,HIGH);
   bcm2835_delayMicroseconds(motor->duty*200);
   bcm2835_gpio_write(motor->pin,LOW);
   bcm2835_delayMicroseconds((100-motor->duty)*200);
 
  } 
}

void driveStraight(int distance){
  printf("Going Straight\n");
  pthread_t lth ,rth;
  motorright.duty = 3.75;
  motorleft.duty = 11.25;
  
  //starting motor thread   
  pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
	printf("Threads created in drive straight.: %d \n",distance);  
  sleep(distance);
  
  pthread_cancel(rth);
  pthread_cancel(lth);
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
	printf("Threads cancelled in drive straight. \n");  
}

void turnRight(int distance){
  printf("Turning Right\n");
  pthread_t lth ,rth;
  motorright.duty = 7.25;
  motorleft.duty = 11.25;
  
  pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
  
  usleep(1370000);
//	sleep(1);
  
  pthread_cancel(rth);
  pthread_cancel(lth);
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
  
 // driveStraight(distance);
  
}

void turnLeft(int distance){
  printf("Turning Left\n");
  pthread_t lth ,rth;
  motorright.duty =7.25;// 3.75;
  motorleft.duty = 3.75;//7.25;
  
  pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
  
  usleep(1370000);
 // sleep(1);
  pthread_cancel(rth);
  pthread_cancel(lth);
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
  
 // driveStraight(distance);
}

void rotate360(){
   pthread_t lth ,rth;
  motorright.duty = 7.25;
  motorleft.duty = 11.25;
  
  pthread_create(&rth,NULL,drivemotors,(void*)&motorright);
  pthread_create(&lth,NULL,drivemotors,(void*)&motorleft);
  
  usleep(1330000*4);
  
  pthread_cancel(rth);
  pthread_cancel(lth);
  pthread_join(rth,NULL);
  pthread_join(lth,NULL);
   
}

void orient(int x)
{
	printf("\n Orienting itself.: %d \n",lastTurn); 
      sleep(1);
      switch(lastTurn)
      {
              case Right:
                      turnLeft(x);
                      sleep(1);
                      break;
              case Back:
                      turnRight(x);
			sleep(1);
                      turnRight(x);
                      sleep(1);
                      break;
              case Left:
                      turnRight(x);
                      sleep(1);
                      break;
              default:
                      break;
      }
}


void moveCar(orientation direction, int distance){
  orient(distance); 
  switch(direction){
  	case Straight:
  	  driveStraight(distance);
  	break;
  	case Right:
  	  turnRight(distance);
	driveStraight(distance);
  	break;
  	case Left:
  	  turnLeft(distance);
	driveStraight(distance);
  	break;
	case Back:
		turnRight(distance);
		sleep(1);
		turnRight(distance);
		driveStraight(distance);
		break;
  	default:
  	  motorright.duty = 7.25;
  	  motorleft.duty = 7.25;
  	  break; 
  }
  //bcm2835_close();
  return ;
}

