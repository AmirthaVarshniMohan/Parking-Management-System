#include<stdio.h>
#include "main.h"
#include "data.h"
#include "sandq.h"
#define max 10
#define D (24*60*60)
#define H (60*60)
#define M (60)


char buffer[200];

int Parking(linked_queue **Q,chain_stack *S) //parking
{
     //char* car_no = (char *)malloc(20 * sizeof(char));
     int i,time_now;
     node data;

     printf("\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
     printf("\n\t\t\t\t\t|VEHICLE INFORMATION|");
     printf("\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");

     set_color(0);printf("\n\n\n\t\t\t\tEnter the car number : ");
     fflush(stdin);
     scanf("%[^\n]%*c",data.car_no);
     //printf("%s",data.car_no);

     printf("\n\t\t\t\tEnter your name      : ");
     scanf(" %s",data.name);

     time_t t;
     time(&t);
     printf("\n\t\t\t\tThe time of entry    : %s", ctime(&t));


      strcat(buffer,"\n ");
      strcat(buffer," ");
      strcpy(buffer,data.name);
      strcat(buffer," \n");
      strcat(buffer," ");
      strcat(buffer,data.car_no);
      strcat(buffer," \n");
      strcat(buffer," ");
      strcat(buffer,ctime(&t));


     for(i=1;i<=S->top;i++)
     {
        if(strcmp(S->stack_array[i].car_no , data.car_no)==0)//car number already exists
        {
             printf("The Car already exist\n");
             return 0;
        }
     }

     enqueue(Q,data); //Go in and wait in line

     while(!empty_queue(*Q))
     {
       if(full_stack(S)) //Park stack full
         {
             printf("PLEASE WAIT...\n");
             break;
         }
       else // Parking stack not full
         {
             dequeue(Q,&data);// Wait for the car to leave
             data.initial_time=now_time();// Record current time
             push_stack(S,data);// Enter the parking stack
             fflush(stdin);
             printf("\n\n\t\t\t\tCAR SUCCESSFULLY PARKED!!!\n");
         }
     }
     return ;
}

int departure(chain_stack *S,chain_stack *B,linked_queue **Q)
{
       // char* car_no = (char *)malloc(20 * sizeof(char));
        printf("\n\t\t\t\t\t VEHICLE DEPARTURE");
        printf("\n\t\t\t\t\t-------------------");

     if(S->bottom == S->top)/*  Park stack is empty */
     {
        printf("PARKING IS EMPTY!!\n");
     }

     else
     {
         node data;
         char *i;
         i=(char *)malloc(20 * sizeof(char));
         int h,m,s;
         float charge;
         int time_now,parking_time;

         printf("\n\t\t\t\tDeparture Vehicle Number: ");
         fflush(stdin);
         scanf("%[^\n]%*c",i);
        // printf("%s",i);

         time_t t;
         time(&t);
         printf("\n\t\t\t\tThe time of departure   : %s", ctime(&t));

          FILE *ptr=fopen("logs.txt","a");
          strcat(buffer," ");
          strcat(buffer,ctime(&t));
          strcat(buffer,"___________________________________________________________________________");
          strcat(buffer,"\n");
          fprintf(ptr,"%s",buffer);
          fclose(ptr);

          strcpy(data.car_no,i);
         //data.car_no=i;
         if(!search_stack(S,data))//  There is no such car in the parking lot
             {
                 printf("\n\t\t\t\tDID NOT FIND THE CAR!\n");
                 getch();
                 return ;
             }
         else// The car is in the parking lot
          {

             while(strcmp(S->stack_array[S->top].car_no , i)!=0)//  The cars behind the car in turn go out of the yield stack
             {
             	//printf("%s",S->stack_array[S->top].car_no);
             	if(S->top==0)
             		break;
                 pop_stack(S,&data);
                 push_stack(B,data);
             }

             pop_stack(S,&data);//  The car is out of the parking lot
             time_now=now_time();
             parking_time=time_now-data.initial_time;//  Calculate stop time

             h = parking_time/H;
             parking_time = parking_time%H;
             m = parking_time/M;
             s = parking_time%M;
             charge = 6*h+0.1*(m+1);//  Calculate parking charges

            // strcpy(data.car_no,"");

             printf("\n\t\t\t\tThe departure vehicle   : %s",data.car_no);
             printf("\n\n\t\t\t\tParking time            : %d:%d:%d",h,m,s);
             printf("\n\n\t\t\t\tCharge(Rs.6/h)          : Rs.%g\n",charge);


            int c;
 			printf("\n\tDo you want the bill? (1/0): ");
 			scanf("%d",&c);

             if (c==1)
 			{
 				FILE *ptr;
			    ptr=fopen("bill.txt","w+");
                set_color(1);
				fprintf(ptr,"\t\t\t\t----------------------------------------------\n");
			    fprintf(ptr,"\t\t\t\t               FLORA PARK'IN                \n");
				fprintf(ptr,"\t\t\t\t----------------------------------------------\n");
				fprintf(ptr,"\t\t\t\tDATE : 29/09/2021\n\n");
			    fprintf(ptr,"\t\t\t\tVEHICLE NUMBER     : %s\n",data.car_no);
			    fprintf(ptr,"\t\t\t\tTOTAL PARKING TIME : %d:%d:%d\n\n",h,m,s);
			    fprintf(ptr,"\t\t\t\t----------------------------------------------\n");
			    fprintf(ptr,"\t\t\t\tParking Charge     :Rs. %g\n",charge);
			    fprintf(ptr,"\t\t\t\tTax                :Rs. 3\n");
			    fprintf(ptr,"\t\t\t\t----------------------------------------------\n");
			    fprintf(ptr,"\n\t\t\t\t Payable Amount : RS. %g /- \n",charge+3);
			    fprintf(ptr,"\t\t\t\t----------------------------------------------\n");
			    fprintf(ptr,"\t\t\t\t                   THANK YOU                  \n");
			    fprintf(ptr,"\t\t\t\t\----------------------------------------------\n");
			    fclose(ptr);
			    printf("\n\t\t\t\t\tHERE IS YOUR BILL!!\n");


                FILE *ptr1;
                ptr1=fopen("bill.txt","r");
                if(ptr1==NULL)
                {
                    printf("The file is not available!");
                    return;
                }
                char c1;
                while((c1=fgetc(ptr1))!=EOF)
                {
                    printf("%c",c1);
                }
                fclose(ptr1);
                getch();
                }
         }


             while(B->bottom != B->top)/*  The cars in the yield stack go out of the parking stack in turn */
             {
                 pop_stack(B,&data);
                 push_stack(S,data);
             }

             while(!full_stack(S)&&(!empty_queue(*Q)))/*  The parking stack is not full and the waiting queue is not empty */
             {
                 dequeue(Q,&data); /*  Wait for the train to leave */
                 data.initial_time=now_time();
                 push_stack(S,data);/*  The outgoing cars were parked in the parking lot */
             }
     }


}



int waiting_list(chain_stack *S,linked_queue **Q)// Check the current condition of the parking lot
{
     node data;
     int i;
     int time_now,parking_time;
     int h,m,s;
     struct queue *p;
     int wait_count=0;

     fflush(stdin);
     p=(*Q)->front;

     printf("\n\t\t\t\t\tCAR WAITING LIST");
     printf("\n\t\t\t\t\t-----------------");
     if(p == 0)// Waiting queue empty
     {
        printf("\n\t\t\t\tWaiting car       :0\n");
     }
     else// The wait queue is not empty
     {
         do
         {
              wait_count++;
              p=p->next;
         }while(p!=0);// Count the number of cars in the waiting queue

         printf("\n\t\t\t\tWaiting car       :%d\n",wait_count);
     }


     printf("\n\t\t\t\tVehicle Number    : ");
     for(i=1;i<=S->top;i++)
     {
         printf("%-10s/ ",S->stack_array[i].car_no);

         if(strcmp(S->stack_array[i].car_no , data.car_no)==0)
         {
           return 1;
         }
     }

     printf("\n\n\t\t\t\tParking time      :");
     for(i=1;i<=S->top;i++)
     {
         time_now = now_time();
         parking_time = time_now - S->stack_array[i].initial_time;// Calculating the current stop time
         h = parking_time/H;
         parking_time = parking_time%H;
         m = parking_time/M;
         s = parking_time%M;
         printf("%02d:%02d:%02d/ ",h,m,s);
     }
     printf("\n");

}

int display(chain_stack *S,linked_queue **Q)
{
    node data;
    int i,j;
    fflush(stdin);
    system("COLOR B");

    if(S->top==NULL)
	{
		set_color(14);printf("\n PARKING LOT - FLOOR ONE\n");
		 printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		 for(i=1;i<=5;i++)
		{
		 	printf(" /          / ");
		}
		 printf("\n\n----------------------------------------------------------------------\n");
		 for(i=1;i<=5;i++)
		{
		 	printf(" /          / ");
		}
        printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
	   	set_color(14);printf("\n PARKING LOT - FLOOR TWO\n");
		printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		printf("\n");
		for(i=1;i<=5;i++)
		{
		 	printf(" /          / ");
		}
		printf("\n----------------------------------------------------------------------\n\n");
		for(i=1;i<=5;i++)
		{
		 	printf(" /          / ");
		}
		printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
	}

    else if(S->top==1)
		{
			printf("\n PARKING LOT - FLOOR ONE\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		 	printf("/%-10s/  ",S->stack_array[1].car_no);

			 printf("\n\n----------------------------------------------------------------------\n");

			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		   	printf("\n PARKING LOT - FLOOR TWO\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
			printf("\n");

			printf("\n----------------------------------------------------------------------\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		}

		else if(S->top==2)
		{
			printf("\n PARKING LOT - FLOOR ONE\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		 	printf("/%-10s/ /%-10s/   ",S->stack_array[1].car_no,S->stack_array[2].car_no);

			 printf("\n\n----------------------------------------------------------------------\n");

			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		   	printf("\n PARKING LOT - FLOOR TWO\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
			printf("\n");

			printf("\n----------------------------------------------------------------------\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		}

		else if(S->top==3)
		{
			printf("\n PARKING LOT - FLOOR ONE\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		 	printf("/%-10s/ /%-10s/ /%-10s/  ",S->stack_array[1].car_no,S->stack_array[2].car_no,S->stack_array[3].car_no);

			 printf("\n\n----------------------------------------------------------------------\n");

			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		   	printf("\n PARKING LOT - FLOOR TWO\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
			printf("\n");

			printf("\n----------------------------------------------------------------------\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		}

		else if(S->top==4)
		{
			printf("\n PARKING LOT - FLOOR ONE\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		 	printf("/%-10s/ /%-10s/ /%-10s/ /%-10s/ ",S->stack_array[1].car_no,S->stack_array[2].car_no,S->stack_array[3].car_no,S->stack_array[4].car_no);

			 printf("\n\n----------------------------------------------------------------------\n");

			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		   	printf("\n PARKING LOT - FLOOR TWO\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
			printf("\n");

			printf("\n----------------------------------------------------------------------\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		}

		else if(S->top==5)
		{
			printf("\n PARKING LOT - FLOOR ONE\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		 	printf("/%-10s/ /%-10s/ /%-10s/ /%-10s/ /%-10s/",S->stack_array[1].car_no,S->stack_array[2].car_no,S->stack_array[3].car_no,S->stack_array[4].car_no,S->stack_array[5].car_no);

			 printf("\n\n----------------------------------------------------------------------\n");

			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		   	printf("\n PARKING LOT - FLOOR TWO\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
			printf("\n");

			printf("\n----------------------------------------------------------------------\n\n");
			printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		}


	else
	{

		if(S->top<11)
		{

		printf("\n PARKING LOT - FLOOR ONE\n");

		printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");

	 	for(i=1;i<=S->top;i++)
		{
		 	printf("/%-10s/  ",S->stack_array[i].car_no);
		    if (i==5 )
		    {
		    	printf("\n\n--------------------------------------------------------------------\n");
		    	printf("\n");

			}

			//printf("|%-10d|  ",S->stack_array[j].No);
		 	if(strcmp(S->stack_array[i].car_no , data.car_no)==0)
		 	{
		  		return 1;
		 	}

		}
		printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		printf("\n PARKING LOT - FLOOR TWO\n");
		printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		printf("\n");
		for(i=1;i<=5;i++)
		{
		 	printf(" /          / ");
		}
		printf("\n----------------------------------------------------------------------\n\n");
		for(i=1;i<=5;i++)
		{
		 	printf(" /          / ");
		}
		printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		}

		else
		{
			printf("\n PARKING LOT -TWO FLOORS\n");

		printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");

	 	for(i=1;i<=S->top;i++)
		{
		 	printf("/%-10s/  ",S->stack_array[i].car_no);
		    if (i==5 || i==10  )
		    {
		    	printf("\n\n--------------------------------------------------------------------\n");
		    	printf("\n");
			}

			if ( i==15 )
		    {

		    	printf("\n\n--------------------------------------------------------------------\n");
		    	printf("/%-10s/  ",S->stack_array[i].car_no);
		    	printf("\n");
			}

			//printf("|%-10d|  ",S->stack_array[j].No);
		 	if(strcmp(S->stack_array[i].car_no, data.car_no)==0)
		 	{
		  		return 1;
		 	}
		}
		printf("\n\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
		}
}

}
