#ifndef DATA_H
#define DATA_H

#include "main.h"
#include "sandq.h"

int Parking(linked_queue **Q,chain_stack *S);
int departure(chain_stack *S,chain_stack *B,linked_queue **Q);
int waiting_list(chain_stack *S,linked_queue **Q);
void printbill(node *data);
int display(chain_stack *S,linked_queue **Q);
void set_color(int sample);


#endif
