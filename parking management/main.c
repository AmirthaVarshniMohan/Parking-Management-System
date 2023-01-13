#include<stdio.h>
#include<stdlib.h>

#include "main.h"
#include "sandq.h"
#include "data.h"

#define max 10

void display_logs();
int main()
{

     login();
     node data;
     int i;
     struct chain_stack *park;//  Park stack
     struct chain_stack *back;// Make way for the stack
     struct linked_queue *wait;// Waiting queue

     park=initialize_stack();
     back=initialize_stack();
     wait=initial_queue();

     while(1)
     {
      system("cls");
      system("COLOR FC");
      	set_color(0);printf("\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
        set_color(0);printf("\t\t\t\t\t\xdb                                               \xdb\n");
        set_color(4);printf("\t\t\t\t\t\xdb        =============================          \xdb\n");
        set_color(4);printf("\t\t\t\t\t\xdb             PARKING MANAGEMENT                \xdb\n");
        set_color(4);printf("\t\t\t\t\t\xdb        =============================          \xdb\n");
        set_color(0);printf("\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
      set_color(16);
      printf("\n\t\t\t\t  1 -->PARKING \n");
      printf("\t\t\t\t  2 -->DEPARTURE \n");
      printf("\t\t\t\t  3 -->SITUATION\n");
      printf("\t\t\t\t  4 -->DISPLAY   \n");
      printf("\t\t\t\t  5 -->HISTORY\n");
      printf("\t\t\t\t  6 -->EXIT \n");
      printf("\n\t\t\t\t\t Enter your choice: ");
      scanf(" %d",&i);

      switch(i)
      {
       case 1://  parking
       {
        system("cls");
        Parking(&wait,park);

        //setbuf(stdin,NULL);
        getchar();
        break;
       }

       case 2:
       {
        system("cls");
        departure(park,back,&wait);
        //setbuf(stdin,NULL);
        getchar();
        break;
       }

       case 3:
       {
        system("cls");
        waiting_list(park,&wait);
        //setbuf(stdin,NULL);
        getchar();
        break;
       }

       case 4:
        {
             system("cls");
             {
                display(park,&wait);
                //setbuf(stdin,NULL);
                getchar();
                 break;
		      }
        break;
        }
       case 5:
        {
            display_logs();
            break;
        }

       case 6:
       {
        return 0;
       }

       default:
              printf("\nEnter the correct choice ! ");
              break;
       }
      }
     return 0;
}

void set_color(int sample)
{
 WORD w_color;
 HANDLE h_std_out=GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_SCREEN_BUFFER_INFO csbi;
 if(GetConsoleScreenBufferInfo(h_std_out,&csbi))
 {
  w_color=(csbi.wAttributes&0xF0)+(sample&0x0F);
  SetConsoleTextAttribute(h_std_out,w_color);
 }
 return;
}



void display_logs()
{
    system("cls");
    FILE *ptr;
    ptr=fopen("logs.txt","r");
    if(ptr==NULL)
    {
        printf("The file is not available!");
        return;
    }
    char c;
    while((c=fgetc(ptr))!=EOF)
    {
        printf("%c",c);
    }
    fclose(ptr);
    getch();

}
