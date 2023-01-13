#include<time.h>
#include "main.h"
#include "sandq.h"

#define max 10
#define D (24*60*60)
#define H (60*60)
#define M (60)


chain_stack *initialize_stack()    //Initialize the stack
{
     chain_stack *S=(chain_stack*)malloc(sizeof(chain_stack));
     S->bottom=NULL;
     S->top=NULL;
     return S;
}

int full_stack(chain_stack *S)   //full stack
{
    return S->top==max;
}

int push_stack(chain_stack *S,node data) // Into the stack
{
    if(full_stack(S)) // (S)-> max
     {
       return 0;  //Full stack
     }
      S->top=S->top+1 ;
      strcpy((S->stack_array[S->top]).car_no,data.car_no);
      (S->stack_array[S->top]).initial_time=data.initial_time;
      return 1;
}

int pop_stack(chain_stack *S,node *data)  //Pop top element
{
     if(S->top==0)
     {
        return 0;  // Empty stack
     }

     strcpy((*data).car_no,(S->stack_array[S->top]).car_no);
     (*data).initial_time=(S->stack_array[S->top]).initial_time;
     S->top--;

     return 1;
}

int search_stack(chain_stack *S,node data) // Search for elements in the stack data
{
     int i;
     if(S->top==0)
     {
        return 0;  //Empty stackk
     }
     for(i=1;i<=S->top;i++)
     {
        if(strcmp(S->stack_array[i].car_no , data.car_no)==0)
      {
        return 1;
      }
     }
     return 0;
}


linked_queue* initial_queue (void)  //Initialize queue
{
     linked_queue *Q=( linked_queue * ) malloc( sizeof ( linked_queue ) );
     Q->rear=Q->front=NULL;
     return Q;
}

int empty_queue(linked_queue *Q) //An empty queue
{
    return Q->front == NULL;
}


int front_queue ( linked_queue *Q, node *data ) //Take the team first
{
     if (empty_queue (Q))
     {
         return 0;
     }
     strcpy((*data).car_no , (Q->front->data).initial_time);
     return 1;
}


int enqueue ( linked_queue **Q, node data)
{
     queue *p = ( queue * ) malloc( sizeof ( queue ) );
     strcpy((p->data).car_no , data.car_no);
     (p->data).initial_time = data.initial_time;
     p->next = NULL;

     if ( (*Q)->front == NULL )
     {
        (*Q)->front = (*Q)->rear = p;
     }
     else
     {
        (*Q)->rear = (*Q)->rear->next = p;
     }
     return 1;
}


int dequeue ( linked_queue **Q, node *data)
{
     if ( empty_queue (*Q) )
     {
      return 0;
     }

     queue *p = (*Q)->front;
     strcpy((*data).car_no ,p->data.car_no);
     (*data).initial_time = p->data.initial_time;
     (*Q)->front = (*Q)->front->next;

     if ((*Q)->front == NULL)
        (*Q)->rear = NULL;
        free (p);
     return 1;
}


int now_time(void)
{
     time_t t1;
     time(&t1);
     int time=t1%D;
     return time;
}
