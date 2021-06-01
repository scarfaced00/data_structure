#include <stdio.h>
#include <string.h>
#define STACK_SIZE 100
#define EXPR_SIZE 100


typedef enum
{
	open_b, close_b, plus, minus, times, divide, mod, eos, operand
} priority;

int stack[STACK_SIZE];
char expr[EXPR_SIZE];
int pos = 0;
char sym;
int sym_type;
int top = -1;

int eval_postfix();
void push(int item);
int pop();

char read_item();
void main()
{
	strcpy(expr, "57*9+34/-");
	strcpy(expr, "936+5-/7+64-*");
	eval_postfix();
}

int eval_postfix()
{
	char op2;
	while(read_item() != eos)
	{
		if (sym_type == operand)
		{
			sym = sym - '0'; //atoi
			push(sym);
		}
		else
			{
				switch (sym_type)
				{
					case (open_b) :
						push(sym);
						break;
					case (close_b) :
						while(expr[top] != '(')
							pop();
						break;						
					case (plus) :
						push(pop() + pop());
						break;
					case (minus) :
						op2 = pop();
						push(pop() - op2);
						break;					
					case (times) :
						push(pop() * pop());
						break;
					case (divide) :
						op2 = pop();
						if(op2 != 0)
							push(pop() / op2);
						else
							printf("error! zero divisor\n");
						break;
					case (mod) :
						op2 = pop();
						if(op2 != 0)
							push(pop() % op2);
						else
							printf("error! zero divisor\n");
						break;
				}

			}
		pos++;
	}
	printf("result: %d", pop());
}

void push(int item)
{
	//check if there is room for the item
	if(top == STACK_SIZE-1)
	{
		printf("stack full\n");
		return;
	}
	stack[++top] = item;
	return;
}

int pop()
{
	//check if stack is empty
	if(top < 0)
	{
		printf("Stack empty\n");
		return -999;
	}
	return stack[top--];
}

char read_item()
{
	int sym;
	sym = expr[pos];
	switch (sym)
	{
		case '(': 
			sym_type = open_b; 
			break;
		case ')' :
			sym_type = close_b; 
			break;
		case '\0' :
			sym_type = eos; 
			break;
		case '+' :
			sym_type = plus; 
			break;
		case '-' :
			sym_type = minus; 
			break;
		case '*' :
			sym_type = times; 
			break;
	    case '/' :
	    	sym_type = divide; 
			break;
		case '%' :
			sym_type = mod; 
			break;
		default :
			sym_type = operand;
	}
	return sym_type;
}

