#define NUMBER '0'
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getev(char *expr[], char *s[]);
void push(int item);
int top = -1;
char whitespace = ' ';
int opstack[MAX]; //연산자 스택
void print_stack();
int pop();

int main()
{
	char s[MAX];
	int type, op2;
	char expr[] = "12 2 15 - * 13 4 2 * + 2 / +";
	
	while ((type = getev(expr, s)) != '\0')
	{
		switch (type) {
           case NUMBER : //if it's an operand
           		push(atoi(s));
           		break;
           case ' ' :
		   		break;
           case '+':
               push(pop() + pop());
               break;
           case '*':
               push(pop() * pop());
               break;
           case '-':
               op2 = pop();
               push(pop() - op2);
               break;
           case '/':
               op2 = pop();
               if (op2 != 0)
                   push(pop() / op2);
               else
                   printf("error: zero divisor\n");
               break;
           defualt:
               printf("error: unknown command\n");
               break;
           }
	}
	printf("%d", pop());
}
int getev(char *expr[], char *s[])
{
	char lttr;
	int i = 0;
	int j;
	while(expr[i] != '\0')
		printf("%c", expr[i++]);
	/*
	s[0] = lttr = expr[i];
	//sscanf( expr, "%c", &lttr);
	s[1] = '\0';
    if (!isdigit(lttr)) //not a number
        return lttr;
    j = 0;
    if (isdigit(lttr))
    {
        do
		{
			lttr = expr[++i];
			//sscanf( expr, "%c", &lttr);
		}
		while (isdigit(s[++j] = lttr));
	}	
    s[j] = '\0';
    return NUMBER;*/
}

void push(int item)
{
    if (top < MAX - 1)
    {
        opstack[++top] = item;
        return;
    }
    printf("Stack full\n");
    return;
}

int pop()
{
    if (top > -1)
    {
        return opstack[top--];
    }
    printf("Stack empty\n");
    return -999;
}

void print_stack()
{
    int i;
    for (i = 0; i <= top; i++)
    {
        printf("%c ", opstack[i]);
    }
    printf("\n");
}
