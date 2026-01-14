#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if(s->element == NULL){
	    return 0;
    }
    return 1;
}

int isIntegerStackFull(stack *s)
{
    if (s==NULL || s->count + 1 == s->maxSize)
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
    if (s==NULL || s->count == -1)
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
    if (s == NULL||s->element == NULL)
    {
        return 0;
    }
    else
    {
        free(s->element);
        s->element = NULL;
        return 1;
    }
}

int checkParenthesis(char *exp)
{
    stack s;
    if (!initIntegerStack(&s, strlen(exp)))
    {
        return 0;
    }
    for (int i = 0; exp[i] != '\0'; i++)
    {
        char ch = exp[i];
        if (ch == '(' || ch == '[' || ch == '{')
        {
            pushIntegerStack(&s, (int)ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            int topChar;
            if (!popIntegerStack(&s, &topChar))
            {
                freeIntegerStack(&s);
                return 0;
            }
            if ((ch == ')' && topChar != '(') || (ch == '}' && topChar != '{') || (ch == ']' && topChar != '['))
            {
                freeIntegerStack(&s);
                return 0;
            }
        }
    }
    int valid = isIntegerStackEmpty(&s);
    freeIntegerStack(&s);
    return valid;
}

int main()
{
    int N, M;
    int num;
    stack s1;
    stack s2;
    printf("Enter size of the first stack: ");
    scanf("%d", &N);
    printf("Enter size of the second stack: ");
    scanf("%d", &M);
    initIntegerStack(&s1, N);
    initIntegerStack(&s2, M);
    printf("Pushing elements in Stack 1.\n");
    while (isIntegerStackFull(&s1) != 1)
    {
        printf("Enter element to push in Stack 1: ");
        scanf("%d", &num);
        pushIntegerStack(&s1, num);
        printf("Pushed element %d.\n", num);
    }
    printf("Stack 1 is full.\n");
    printf("Pushing elements in Stack 2.\n");
    while (isIntegerStackFull(&s2) != 1)
    {
        printf("Enter element to push in Stack 2: ");
        scanf("%d", &num);
        pushIntegerStack(&s2, num);
        printf("Pushed element %d.\n", num);
    }
    printf("Both the stacks are full now.\n");
    printf("Popping elements from Stack 2.\n");
    while (!isIntegerStackEmpty(&s2))
    {
        popIntegerStack(&s2, &num);
        printf("Popped element %d.\n", num);
    }
    printf("Stack 2 is empty now. Popping elements from Stack 1.\n");
    while (!isIntegerStackEmpty(&s1))
    {
        popIntegerStack(&s1, &num);
        printf("Popped element %d.\n", num);
    }
    printf("Both the stacks are empty now.\n");

    char expression[100];
    getchar();
    printf("Enter a mathematical expression to check it's sanity with different kinds of parenthesis:");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';
    if (checkParenthesis(expression))
    {
        printf("Expression is correct.\n");
    }
    else
    {
        printf("Expression is incorrect.\n");
    }

    freeIntegerStack(&s1);
    freeIntegerStack(&s2);

    return 0;
}
