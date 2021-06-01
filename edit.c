#define NUMBER '0'
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getop(char s[]);
void push(int item);
int top = -1;
int ov_size = -1;
int oo_size = -1;
int opstack[MAX]; //연산자 스택
void print_stack();
int Prec(char ch);
int pop();
char expr[MAX] ="";
//char * expr = malloc(MAX * sizeof(char));

int main(void)
{
    int i;
    int prec_incom;
    int output_val[MAX];
    char output_op[MAX];
    char output_expr[MAX];
    int type, op2;
    char s[MAX];
    char ch;
    printf("Input an infix notation to convert : ");
    while ((type = getop(s)) != '\n')
    {
        switch (type)
        {
        case NUMBER:
        	strcat(expr, s);
            if (ov_size < MAX)
            {
                output_val[++ov_size] = atoi(s);
                output_op[++oo_size] = NUMBER;
            }

            else
                printf("error: stack full, can't push %i\n", atoi(s));
            break;
        case '(':
            push(type);
            print_stack();
            break;
        case ')':
            while (opstack[top] != '(')
            {
                //output_op[++oo_size] = pop();
                ch = pop();
                strncat(expr, &ch, 1);
                output_val[++ov_size] = -999;
            }
            top--; //remove '(' from the opstack
            break;
        case '+': case '-': case '*': case '/': case '^':
            if (top > -1 && opstack[top] != '(')
            {
                prec_incom = Prec(type);
                //when the operator at the top has higher precedence
                while (Prec(opstack[top]) > prec_incom)
                {
                    //output_op[++oo_size] = pop();
                    ch = pop();
                	strncat(expr, &ch, 1);
                    output_val[++ov_size] = -999;
                }
                //when the operator at the top has equal precedence
                if (Prec(opstack[top]) == prec_incom)
                {
                    if (prec_incom != '^')
                    {
                        //output_op[++oo_size] = pop();
                        ch = pop();
                		strncat(expr, &ch, 1);
                        output_val[++ov_size] = -999;
                    }
                    push(type);
                    print_stack();
                }
                //when the operator at the top has lower precedence
                if (Prec(opstack[top]) < prec_incom)
                {
                    push(type);
                    print_stack();
                }
            }
            else
            {
                push(type);
                print_stack();
            }
        }
    }
    //when the input expression has been completely processed
    while (top > -1)
    {
        //output_op[++oo_size] = pop();
        ch = pop();
        strncat(expr, &ch, 1);
        output_val[++ov_size] = -999;
    }

    printf("Corresponding Postfix notation is\npostfix = ");
	printf("%s", expr);/*
    for (i = 0; i <= ov_size; i++)
    {
        if ((output_val[i]) != -999)
            printf("%d ", output_val[i]);
        else
            printf("%c ", output_op[i]);
    }
    printf("\n");
    printf("Evaluation : ");*/
    top = -1;
    //evaluation
    for (i = 0; i <= ov_size; i++)
    {
        if ((output_val[i]) != -999)//if it's an operand
            push(output_val[i]);
        else //if it's an operator
        {
            char op = output_op[i];
            switch (op) {
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
        }
    printf("%d", pop());
            

    }

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getchar()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;   	/* not a number */
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetc(c, stdin);
    return NUMBER;
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

int Prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }
    return -1;
}

