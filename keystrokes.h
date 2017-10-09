#include<stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>




struct keyandData
{
	char password[1024];
	struct node* diffList;
	
};

void printList(struct node *node);
keyandData getInput();

