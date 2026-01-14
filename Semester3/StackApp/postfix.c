#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define M 100

typedef struct
{
    int maxSize;
    int count;
    int *element;
} stack;

int initIntegerStack(stack *s, int stackSize)
{
    s->maxSize = stackSize;
    s->count = -1;
    s->element = (int *)malloc(stackSize * sizeof(int));
}

int isIntegerStackFull(stack *s)
{
    if (!s || s->count + 1 == s->maxSize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isIntegerStackEmpty(stack *s)
{
    if (!s || s->count == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int pushIntegerStack(stack *s, int d)
{
    if (isIntegerStackFull(s) == 1)
    {
        return 0;
    }
    else
    {
	s->count++;
        s->element[s->count] = d;
        return 1;
    }
}

int popIntegerStack(stack *s, int *dp)
{
    if (isIntegerStackEmpty(s) == 1)
    {
        return 0;
    }
    else
    {
        *dp = s->element[s->count];
	s->count--;
        return 1;
    }
}

int freeIntegerStack(stack *s)
{
    if (s == NULL)
    {
        return 0;

    }
    else
    {
        free(s->element);
        return 1;
    }
}

int main()
{
    stack s;
    initIntegerStack(&s, M);
    char exp[M];    
    printf("Enter a postfix expression to evaluate it: ");
    scanf("%s",exp);

    for(int i=0; exp[i]!='\0';i++) {
	if(isdigit(exp[i])){
		pushIntegerStack(&s,exp[i]-'0');	
	} else {
		int operand1, operand2;
		popIntegerStack(&s, &operand2);
		popIntegerStack(&s, &operand1);
		char ch = exp[i];
		int ans=0;
		switch(ch) {
			case '+':
			ans = operand1 + operand2;
			break;
			case '-':
			ans = operand1 - operand2;
			break;
			case '*':
			ans = operand1 * operand2;
			break;
			case '/':
			ans = operand1 / operand2;
			break;
		}
		pushIntegerStack(&s, ans);
	}
    }
    int ans;
    popIntegerStack(&s, &ans);
    printf("Answer is: %d\n",ans);

    freeIntegerStack(&s);

    return 0;
}
