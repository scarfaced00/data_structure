#define NUMBER '0'
#define OPERATOR -999 
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getop(char s[]); //입력 infix 수식부분이 피연산자 인지 아닌지 구분 
void push(int item);
int pop();
int top = -1;
int ov_size = -1; //output_value의 크기 
int oo_size = -1; //output_op의 크기
int opstack[MAX]; //연산자 스택
void print_stack(); //스택상태 출력 
int Prec(char ch); //연산자 우선순위 반환 

int main(void)
{
    int i;
    int prec_incom;
    int output_val[MAX]; //postfix수식의 피연산자 저장배열 
    char output_op[MAX]; //postfix수식의 연산자 저장배열 
    int type, op2;
    char s[MAX]; //입력된 infix수식 토큰 
    printf("Input an infix notation to convert : ");
    //infix수식입력받아 postfix로 변환 
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
            top--; //연산자스택에서 '(' 제거
            break;
        case '+': case '-': case '*': case '/': case '%':
            if (top > -1 && opstack[top] != '(')
            {
                prec_incom = Prec(type);
                //opstack의 top의 우선순위 > input연산자(type)의 우선순위 
                while (Prec(opstack[top]) > prec_incom)
                {
                    output_op[++oo_size] = pop();
                    output_val[++ov_size] = OPERATOR;
                }
                //opstack의 top의 우선순위 = input연산자(type)의 우선순위 
                if (Prec(opstack[top]) == prec_incom)
                {
                    output_op[++oo_size] = pop();
                    output_val[++ov_size] = OPERATOR;
                    push(type);
                    print_stack();
                }
                //opstack의 top의 우선순위 < input연산자(type)의 우선순위 
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
    //입력된 infix 수식이 모두 처리됐으면 opstack에 남아있는 연산자 모두 pop() 
    while (top > -1)
    {
        output_op[++oo_size] = pop();
        output_val[++ov_size] = OPERATOR;
    }

    printf("Corresponding Postfix notation is\npostfix = ");
	//postfix수식 출력
    for (i = 0; i <= ov_size; i++)
    {
        if ((output_val[i]) != OPERATOR)
            printf("%d ", output_val[i]);
        else
            printf("%c ", output_op[i]);
    }
    printf("\n");
    printf("Evaluation : ");
    top = -1; //opstack다시 사용할 것임 
    
    //Postfix 수식 평가
    for (i = 0; i <= ov_size; i++)
    {
        if ((output_val[i]) != OPERATOR)//postfix의 피연산자부분 
            push(output_val[i]);
        else //postfix의 연산자부분
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
    //마지막 계산결과 출력 
    printf("%d", pop());
    getchar();
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

