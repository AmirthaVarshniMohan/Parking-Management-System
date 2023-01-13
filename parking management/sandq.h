
#ifndef SANDQ_H
#define SANDQ_H

#include "main.h"
#define max 10



/*typedef int stack_data;
typedef int queue_data;
typedef int element_type;
*/
typedef struct node
{
     char car_no[30];  // Car number
     char name[20];
     int initial_time;
     int parking_time;
     float charge;

// Time to enter the parking lot
}node;


typedef struct queue //  Queue node
{
     struct node data;
     struct queue *next;
}queue;

typedef struct linked_queue // Chain queue structure
{
     struct queue *front,*rear;
     struct node b ;
}linked_queue;


typedef struct chain_stack // Chain stack structure
{
     int top;
     int bottom;
     struct node b ;
     struct node stack_array[max+1] ;
}chain_stack ;

chain_stack* initialize_stack();
int full_stack(chain_stack *S) ;
int push_stack(chain_stack *S,node data);
int pop_stack(chain_stack *S,node *data);
int search_stack(chain_stack *S,node data);

linked_queue* initial_queue (void); //initialize queue
int empty_queue(linked_queue *Q) ;
int front_queue ( linked_queue *Q, node *data );
int enqueue ( linked_queue **Q, node data);
int dequeue ( linked_queue **Q, node *data);
int now_time(void);

#endif
