#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode
{
    int data;
    struct listNode *next;
} node;

// node *createNode(int data){
//     node *temp = (node*)malloc(sizeof(node));
//     temp->data = data;
//     temp->next = NULL;
//     return temp;
// }

node *createLargeNumber(const char *str)
{ // Representation of a large number using Linked List(storing digits in reverse order)
    node *head = NULL;
    for (int i = 0; i < strlen(str); i++)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->data = str[i] - '0';
        temp->next = head;
        head = temp;
    }
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

node *reverseLinkedList(node *ptr)
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

void printNumberinDecimal(node *ptr)
{
    while (ptr != NULL)
    {
        printf("%d", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

node *addNumbers(node *ptrX, node *ptrY)
{
    node *ptrS = NULL;
    node *tail = NULL;
    int carry = 0;
    while (ptrX || ptrY || carry)
    {
        int sum = carry;
        if (ptrX)
        {
            sum += ptrX->data;
            ptrX = ptrX->next;
        }
        if (ptrY)
        {
            sum += ptrY->data;
            ptrY = ptrY->next;
        }
        node *temp = (node *)malloc(sizeof(node)); 
        temp->data = sum % 10;
        temp->next = NULL;
        if(ptrS==NULL){
            ptrS = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
        carry = sum / 10;
    }
    // ptrS = reverseLinkedList(ptrS);
    return ptrS;
}

int main()
{
    char s1[100], s2[100];
    printf("Enter first number:");
    scanf("%s", s1);
    node *num1 = createLargeNumber(s1);
    printf("Enter second number:");
    scanf("%s", s2);
    node *num2 = createLargeNumber(s2);
    node *sum = addNumbers(num1, num2);
    printLinkedList(sum);
    printNumberinDecimal(reverseLinkedList(sum));
    return 0;
}
