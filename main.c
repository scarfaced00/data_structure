#define NUMBER '0'
#define OPERATOR -999 
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getop(char s[]); //�Է� infix ���ĺκ��� �ǿ����� ���� �ƴ��� ���� 
void push(int item);
int pop();
int top = -1;
int ov_size = -1; //output_value�� ũ�� 
int oo_size = -1; //output_op�� ũ��
int opstack[MAX]; //������ ����
void print_stack(); //���û��� ��� 
int Prec(char ch); //������ �켱���� ��ȯ 

int main(void)
{
    int i;
    int prec_incom;
    int output_val[MAX]; //postfix������ �ǿ����� ����迭 
    char output_op[MAX]; //postfix������ ������ ����迭 
    int type, op2;
    char s[MAX]; //�Էµ� infix���� ��ū 
    printf("Input an infix notation to convert : ");
    //infix�����Է¹޾� postfix�� ��ȯ 
    while ((type = getop(s)) != '\n')
    {
        switch (type)
        {
        case NUMBER:
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
                output_op[++oo_size] = pop();
                output_val[++ov_size] = OPERATOR;
            }
            top--; //�����ڽ��ÿ��� '(' ����
            break;
        case '+': case '-': case '*': case '/': case '%':
            if (top > -1 && opstack[top] != '(')
            {
                prec_incom = Prec(type);
                //opstack�� top�� �켱���� > input������(type)�� �켱���� 
                while (Prec(opstack[top]) > prec_incom)
                {
                    output_op[++oo_size] = pop();
                    output_val[++ov_size] = OPERATOR;
                }
                //opstack�� top�� �켱���� = input������(type)�� �켱���� 
                if (Prec(opstack[top]) == prec_incom)
                {
                    output_op[++oo_size] = pop();
                    output_val[++ov_size] = OPERATOR;
                    push(type);
                    print_stack();
                }
                //opstack�� top�� �켱���� < input������(type)�� �켱���� 
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
    //�Էµ� infix ������ ��� ó�������� opstack�� �����ִ� ������ ��� pop() 
    while (top > -1)
    {
        output_op[++oo_size] = pop();
        output_val[++ov_size] = OPERATOR;
    }

    printf("Corresponding Postfix notation is\npostfix = ");
	//postfix���� ���
    for (i = 0; i <= ov_size; i++)
    {
        if ((output_val[i]) != OPERATOR)
            printf("%d ", output_val[i]);
        else
            printf("%c ", output_op[i]);
    }
    printf("\n");
    printf("Evaluation : ");
    top = -1; //opstack�ٽ� ����� ���� 
    
    //Postfix ���� ��
    for (i = 0; i <= ov_size; i++)
    {
        if ((output_val[i]) != OPERATOR)//postfix�� �ǿ����ںκ� 
            push(output_val[i]);
        else //postfix�� �����ںκ�
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
            case '%':
                op2 = pop();
                if (op2 != 0)
                    push(pop() % op2);
                else
                    printf("error: zero divisor\n");
                break;
            defualt:
                printf("error: unknown command\n");
                break;
            }
            }
        }
    //������ ����� ��� 
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
    case '%':
        return 2;
    }
    return -1;
}

