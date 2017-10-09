/*#include<stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>*/
#include "keystrokes.h"

//linked list node 
struct node
{
	double data;
	struct node* next;
};

//creates at new node
struct node *newNode(double data)
{
	struct node *new_node = (struct node *) malloc(sizeof (struct node));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void push (struct node ** head_ref, int new_data){
	struct node* new_node = newNode(new_data);
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void printList(struct node *node){
	while(node != NULL){
		printf("%lf ", node->data );
		node = node->next;
	}
}
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}
void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

timespec diff(timespec start, timespec end)
{
    timespec temp;

    if (end.tv_nsec-start.tv_nsec<0)
    {
            temp.tv_sec = end.tv_sec-start.tv_sec-1;
            temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    }
    else 
    {
            temp.tv_sec = end.tv_sec-start.tv_sec;
            temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

double convert_time(double nano, double sec){
	double milione, militwo, sum;
	
	milione=nano/1000000;
	militwo = sec *1000;
	sum=militwo + milione;
	return sum;

}

keyandData getInput()
{
   char strInput;
   char password[1024] = "";
   int iter = 0;
   timespec time1, time2,temp;
   long time_elapsed_nanos;
   double sum=0.0;
   struct node* diffList = NULL;


   while(1){
   		
        if(kbhit()){

        	strInput=getc(stdin);

        	if(strInput>32){
	        	if (iter == 0){
	        		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	        		iter++;
	        		//add the char to the array
	        		append(password, strInput);
	        	}

	        	else{
	        		//time_elapsed_nanos = timer_end(vartime,timer_stamp());
	        		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	        		
	        		append(password, strInput);
	        		temp=diff(time1,time2);
	        		sum=convert_time(temp.tv_nsec,temp.tv_sec);
	        		push(&diffList,sum);
	        		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	        	}
        	}else{
        		break;
        	}
		}
	}
	struct keyandData returnee;
	strncpy(returnee.password,password,1024);
	returnee.diffList=diffList;
    return returnee;
}



 
