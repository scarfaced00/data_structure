#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 100
int queue[QUEUE_SIZE];
int rear = -1;
int front = -1;
void print_queue();
void addq(int item);
int deleteq();


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void main() {
	
	int temp;
	
	addq(3);
	addq(5);
	addq(7);
	temp = deleteq();
	print_queue();
}

void print_queue()
{
	int i;
	for(i = front+1; i <= rear; i++)
		printf("%d ", queue[i]);
}

void addq(int item)
{
	if(rear == QUEUE_SIZE-1)
	{
		printf("Queue is full\n");
		return;
	}
	queue[++rear] = item;
}

int deleteq()
{
	if(front == rear) //empty queue
	{
		printf("empty queue\n");
		return -999;
	}
	return queue[++front]; //now the front is empty
}
