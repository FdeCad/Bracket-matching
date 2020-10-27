#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

#define TRUE 1               
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef  char SElemtype;
typedef int Status;

typedef struct{
    SElemtype *base;
    SElemtype *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack *S)
{
    S->base = (SElemtype *)malloc(STACK_INIT_SIZE*sizeof(SElemtype));
    if(!S->base) exit(-2);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return 1;
}

SElemtype GetTop(SqStack S)
{
    SElemtype e;
    if(S.top==S.base)   return ERROR;
    e = *(S.top-1);
    return e;
}

Status Push(SqStack *S,SElemtype e)
{
    if(S->top - S->base>=S->stacksize)
    {
        S->base = (SElemtype *)realloc(S->base,(S->stacksize+STACK_INIT_SIZE)*sizeof(SElemtype));
        S->top = S->base + S->stacksize;
        S->stacksize += STACK_INIT_SIZE;
    }
    *(S->top++) = e;
    return OK;
}

Status Pop(SqStack *S,SElemtype *e)
{
    if(S->top == S->base) return ERROR;
    e = (--S->top);
    return OK;
}

Status StackClear(SqStack *S)
{
    S->top=S->base;
}

Status MatchBracket(SqStack S)   
{
    SElemtype ch,e;
    printf("Please enter the bracket string to match:");
    do
    {
        ch = getchar();
        if(ch=='('||ch=='{'||ch=='[')
            Push(&S,ch);
        else if((ch==')'&&(GetTop(S)=='('))||(ch=='}'&&(GetTop(S)=='{'))||(ch==']'&&(GetTop(S)=='[')))
            Pop(&S,&e); 
        else
            break;
    } while (ch!='\n');
    if(S.top==S.base&&ch=='\n') 
        return OK;
    else 
        return ERROR;
}

void main()
{
    SqStack S;
    InitStack(&S);
    if(MatchBracket(S))
        printf("Successfully match!\n");
    else
        printf("Fairly match!\n");
}
