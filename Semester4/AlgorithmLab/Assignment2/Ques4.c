#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *elements;
    int size;
    int capacity;
} Set;

void initSet(Set *s, int cap)
{
    s->elements = (int *)malloc(cap * sizeof(int));
    s->size = 0;
    s->capacity = cap;
}

bool exists(Set *s, int val)
{
    for (int i = 0; i < s->size; i++)
    {
        if (s->elements[i] == val)
            return true;
    }
    return false;
}

void add(Set *s, int val)
{
    if (!exists(s, val))
    {
        if (s->size < s->capacity)
        {
            s->elements[s->size++] = val;
        }
    }
}

void createSetFromInput(Set *s, char name)
{
    int n, val;
    printf("Enter number of elements for Set %c: ", name);
    scanf("%d", &n);

    initSet(s, n);

    printf("Enter %d integers for Set %c: ", n, name);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        add(s, val);
    }
}

bool isSubset(Set *A, Set *B)
{
    for (int i = 0; i < A->size; i++)
    {
        if (!exists(B, A->elements[i]))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    Set A, B;

    createSetFromInput(&A, 'A');
    createSetFromInput(&B, 'B');

    bool sub = isSubset(&A, &B);

    if (sub)
    {
        printf("\nSet A is a subset of Set B.\n");
        if (A.size < B.size)
        {
            printf("Set A is a proper subset of Set B.\n");
        }
        else
        {
            printf("Set A is not a proper subset of Set B (The sets are equal).\n");
        }
    }
    else
    {
        printf("\nSet A is not a subset of Set B.\n");
        printf("Set A is not a proper subset of Set B.\n");
    }

    free(A.elements);
    free(B.elements);

    return 0;
}