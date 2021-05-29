#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SIZE 100

int front, rear;
int cqueue[QUEUE_SIZE];
void print_queue();
void addcq(int item);
int deletecq();


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	int temp;
	front = rear = 0;
	
	addcq(11);
	addcq(13);
	addcq(17);
	addcq(19);
	temp = deletecq();
	print_queue();
	temp = deletecq();
	print_queue();
	temp = deletecq();
	print_queue();
	temp = deletecq();
	print_queue();
}

void print_queue()
{
	int i = front;
	while(i != rear)
	{
		i = ++i % QUEUE_SIZE;
		printf("%d ", cqueue[i]);
	}
	printf("\n");
}

void addcq(int item)
{
	//check if there is a room in the queue
	if(((rear+1) % QUEUE_SIZE) == front)
	{
		printf("Queue Full\n");
		return;
	}
	rear = (rear+1) % QUEUE_SIZE;
	cqueue[rear] = item;
	//print the queue
	print_queue();
}

int deletecq()
{
	if(front == rear) //empty queue
	{
		printf("empty queue\n");
		return -999;
	}
	front = (front+1) % QUEUE_SIZE;
	return cqueue[front]; //
}
