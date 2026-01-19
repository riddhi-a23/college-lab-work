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

void createSetFromInput(Set *s, int index)
{
    int n, val;
    printf("Enter number of elements for Set %d: ", index);
    scanf("%d", &n);

    initSet(s, n);

    printf("Enter %d integers for Set %d: ", n, index);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        add(s, val);
    }
}

int main()
{
    int k;
    printf("Enter the number of sets (k): ");
    scanf("%d", &k);

    if (k < 1)
    {
        printf("k must be at least 1.\n");
        return 1;
    }

    Set *sets = (Set *)malloc(k * sizeof(Set));
    int total_capacity_needed = 0;

    for (int i = 0; i < k; i++)
    {
        createSetFromInput(&sets[i], i + 1);
        total_capacity_needed += sets[i].size;
    }

    Set unionSet;
    initSet(&unionSet, total_capacity_needed);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < sets[i].size; j++)
        {
            add(&unionSet, sets[i].elements[j]);
        }
    }

    printf("\nUnion of all %d sets: { ", k);
    for (int i = 0; i < unionSet.size; i++)
    {
        printf("%d ", unionSet.elements[i]);
    }
    printf("}\n");

    for (int i = 0; i < k; i++)
        free(sets[i].elements);
    free(sets);
    free(unionSet.elements);

    return 0;
}