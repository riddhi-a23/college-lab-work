#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

typedef struct listNode
{
    int data;
    struct listNode *next;
} node;

node *addListNodeSorted(node *ptr, int element)
{
    node *temp = NULL;
    temp = (node *)malloc(sizeof(node));
    temp->next = NULL;
    temp->data = element;
    if (ptr == NULL)
    { // linked list is empty
        return temp;
    }
    if (element > ptr->data)
    {
        temp->next = ptr;
        return temp;
    }
    node *head = ptr; // holding head of list
    node *prev = NULL;
    while (ptr != NULL && element < ptr->data)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    temp->next = prev->next;
            curr->next = sorted;
            sorted = curr;
        }
    prev->next = temp;
    return head;
}

int isPresentListNodeSorted(node *ptr, int element)
{
    int pos = 1;
    while (ptr != NULL)
    {
        if (ptr->data == element)
        {
            return pos;
            curr->next = sorted;
            sorted = curr;
        }
        }
        ptr = ptr->next;
        pos++;
    }
    return 0; // such a node is not present
}
            curr->next = sorted;
            sorted = curr;
        }

node *deleteListNodeSorted(node *ptr, int element)
{
    if (ptr == NULL)
    { // linked list is empty
        return NULL;
    }
    if (ptr->data == element)
    {
        node *temp = ptr;
        ptr = ptr->next;
        free(temp);
        return ptr;
    }
    node *head = ptr; // holding head of list
    node *prev = NULL;
    while (ptr != NULL && element != ptr->data)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        return head;
    }
    node *temp = ptr;
    prev->next = ptr->next;
    free(temp);
    return head;
}

void printLinkedList(node *ptr)
{
    printf("Start -> ");
    while (ptr != NULL)
    {
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
}

node *freeListNodeSorted(node *ptr)
{
    node *temp;
    while (ptr != NULL)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    return NULL;
}

node *reverseListNodeSorted(node *ptr)
{
    node *prev = NULL;
    node *curr = ptr;
    node *next;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void updateListNode(node *ptr)
{
    while (ptr != NULL)
    {
        ptr->data += rand() % 10;
        ptr = ptr->next;
    }
}

node *sortListNode(node *ptr)
{
    node *sorted = NULL;
    node *curr = ptr;
    node *next;
    while (curr != NULL)
    {
        next = curr->next;
        if (sorted == NULL || curr->data >= sorted->data)
        { // insertion at the start
            curr->next = sorted;
            sorted = curr;
        }
        else
        { // insertion at the middle or end
            node *temp = sorted;
            while (temp->next != NULL && temp->next->data >= curr->data)
            {
                temp = temp->next;
            }
            curr->next = temp->next;
            temp->next = curr;
        }
        curr = next;
    }
    return sorted;
}

node *mergeListNodeSorted(node *ptr1, node *ptr2)
{
    node *merged = NULL;
    node *ptr = NULL;
    while (ptr1 != NULL && ptr2 != NULL)
    {
        node *temp;
        if (ptr1->data >= ptr2->data)
        {
            temp = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            temp = ptr2;
            ptr2 = ptr2->next;
        }
        if (merged == NULL)
        {
            merged = temp;
            ptr = temp;
        }
        else
        {
            ptr->next = temp;
            ptr = temp;
        }
    }
    if (ptr1 != NULL)
    {
        ptr->next = ptr1;
    }
    if (ptr2 != NULL)
    {
        ptr->next = ptr2;
    }
    return merged;
}

int main()
{
    node *s1 = NULL;
    node *s2 = NULL;
    node *s3 = NULL;
    int i = 0;
    int size;
    int ch = -1;
    int element = 0;
    do
    {
        printf("\n0. Exit program.\n"
               "1. Add node to the Linked list in sorted descending order.\n"
               "2. Check if an element is present in the Linked List or not.\n"
               "3. Delete target node from the Linked List.\n"
               "4. Print the Linked List.\n"
               "5. Free Linked List.\n"
               "6. Reverse the Linked List.\n"
               "7. Update the Linked List such that a random value from 0 to 9 is added to each element of the list.\n"
               "8. Sort the list in descending order.\n"
               "9. Merge two linked lists.\n"
               "Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            printf("Exited the program.\n");
            break;
        case 1:
            printf("Enter element to be added: ");
            scanf("%d", &element);
            s1 = addListNodeSorted(s1, element);
            printf("%d is added to the Linked List.\n", element);
            break;
        case 2:
            printf("Enter element to check if it is present not: ");
            scanf("%d", &element);
            if (isPresentListNodeSorted(s1, element) == 0)
            {
                printf("%d is not present in the Linked List.\n", element);
            }
            else
            {
                printf("%d is present at position %d of the Linked List.\n", element, isPresentListNodeSorted(s1, element));
            }
            break;
        case 3:
            printf("Enter targeted element to be deleted: ");
            scanf("%d", &element);
            s1 = deleteListNodeSorted(s1, element);
            printf("%d is deleted from the Linked List.\n", element);
            break;
        case 4:
            printf("Current Linked List: ");
            printLinkedList(s1);
            break;
        case 5:
            s1 = freeListNodeSorted(s1);
            if (s1 == NULL)
            {
                printf("Linked List has been freed successfully!\n");
            }
            curr->next = sorted;
            sorted = curr;
        }
            else
            {
                printf("Could not free Linked List.\n");
            }
            break;
        case 6:
            s1 = reverseListNodeSorted(s1);
            printf("Linked List has been reversed.\n");
            break;
        case 7:
            updateListNode(s1);
            printf("Linked List has been updated.\n");
            break;
        case 8:
            s1 = sortListNode(s1);
            printf("Linked List has been sorted in descending order.\n");
            break;
        case 9:
            printf("Enter the size of the first list: ");
            scanf("%d", &size);
            printf("Enter the elements of the first list: ");
            while (i < size)
            {
                scanf("%d", &element);
                s2 = addListNodeSorted(s2, element);
                i++;
            }
            i = 0;
            printf("Enter the size of the second list: ");
            scanf("%d", &size);
            printf("Enter the elements of the second list: ");
            while (i < size)
            {
                scanf("%d", &element);
                s3 = addListNodeSorted(s3, element);
                i++;
            }
            printLinkedList(mergeListNodeSorted(s2, s3));
            break;
        default:
            printf("Wrong Choice!!!\n");
        }
    } while (ch != 0);
    return 0;
}
