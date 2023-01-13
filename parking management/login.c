#include "main.h"
#include "login.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void login()
{
   	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="user";
    char pass[10]="pass";

    do
    {

    set_color(3);printf("\n\t\t\t                                                                                             ");
    set_color(3);printf("\n\t\t\t                                                                       _.-=\"_-       _    ");
    set_color(3);printf("\n\t\t\t                                      _.-=\"   _-          | ||""""""\"---._______     __..   ");
    set_color(3);printf("\n\t\t\t                          ___.===""""-.______-,,,,,,,,,,,,`-''----" """""       \"""""  __'  ");
    set_color(3);printf("\n\t\t\t                   __.--""     __        ,'                   o \           __        [__|   ");
    set_color(3);printf("\n\t\t\t              __-""=======.--""  ""--.=================================.--""  ""--.=======:  ");
    set_color(3);printf("\n\t\t\t             ]       [w] : /         \\ : |========================|   : /       \\:  [w] :  ");
    set_color(3);printf("\n\t\t\t             V___________:|          |: |========================|    :|        |:   _-\"   ");
    set_color(3);printf("\n\t\t\t              V__________: \         / :_|=======================/_____:\         /:__-\"      ");
    set_color(3);printf("\n\t\t\t               -----------' \"-____-\"  `-------------------------------' \"-____-\"             ");


    set_color(14); printf("\n\n\n\n\n\n\n\t\t\t\t\t\t  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb  LOGIN FIRST  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb  ");
    set_color(14);printf(" \n\n\t\t\t\t\t\t                       ENTER USERNAME:- ");
	scanf("%s", &uname);
	set_color(14);printf(" \n\n\t\t\t\t\t\t                       ENTER PASSWORD:- ");

        while(i<10)
        {
            pword[i]=getch();
            c=pword[i];
            if(c==13) break;
            else printf("*");
            i++;
        }
        pword[i]='\0';
        //char code=pword;
        i=0;
        //scanf("%s",&pword);

        if(strcmp(uname,"user")==0 && strcmp(pword,"pass")==0)
        {
            set_color(7);printf("\n\n\n\t\t\t\t\t\t\t       WELCOME !! YOUR LOGIN IS SUCCESSFULL:)");
            set_color(7);printf("\n\n\n\t\t\t\t\t\t  Press any key to continue...");
            getch();//holds the screen
            break;
        }

        else
        {
            set_color(7);printf("\n\n\n\t\t\t\t\t\t\t       SORRY !!!!  LOGIN IS UNSUCESSFUL\n\n");
            a++;
            getch();

        }
    }while(a<=2);

        if (a>2)
        {
            printf("\nSorry you have entered the wrong username and password for four times!!!");
            getch();

        }
            system("cls");
}


