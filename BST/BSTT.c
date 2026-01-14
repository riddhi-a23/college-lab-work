#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
    struct node *parent;
} treenode;

treenode *createNode(int val)
{
    treenode *newNode = (treenode *)malloc(sizeof(treenode));
    newNode->data = val;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    newNode->parent = NULL;
    return newNode;
}

int isEmpty(treenode *t)
{
    if (t == NULL)
    {
        return 1;
    }
    return 0;
}

treenode *insertNode(treenode *t, int val)
{
    if (isEmpty(t))
    {
        t = createNode(val);
        return t;
    }
    if (t->data > val)
    {
        treenode *child = insertNode(t->lchild, val);
        t->lchild = child;
        child->parent = t;
    }
    else
    {
        treenode *child = insertNode(t->rchild, val);
        t->rchild = child;
        child->parent = t;
    }
    return t;
}

int getCount(treenode *t)
{
    if (t == NULL)
    {
        return 0;
    }
    return 1 + getCount(t->lchild) + getCount(t->rchild);
}

int inorder(treenode *t)
{
    if (t == NULL)
    {
        return 0;
    }
    inorder(t->lchild);
    printf("%d ", t->data);
    inorder(t->rchild);
    return 1;
}

int preorder(treenode *t)
{
    if (t == NULL)
    {
        return 0;
    }
    printf("%d ", t->data);
    preorder(t->lchild);
    preorder(t->rchild);
    return 1;
}

int postorder(treenode *t)
{
    if (t == NULL)
    {
        return 0;
    }
    postorder(t->lchild);
    postorder(t->rchild);
    printf("%d ", t->data);
    return 1;
}

int height(treenode *t)
{
    if (t == NULL)
    {
        return -1; // height of empty tree is -1
    }
    int lh = height(t->lchild);
    int rh = height(t->rchild);
    if (lh > rh)
    {
        return lh + 1;
    }
    else
    {
        return rh + 1;
    }
}

int max(treenode *t)
{ // extreme right
    if (t == NULL)
    {
        printf("Tree is empty.\n");
        return -1;
    }
    while (t->rchild != NULL)
    {
        t = t->rchild;
    }
    return t->data;
}

int min(treenode *t)
{ // extreme left
    if (t == NULL)
    {
        printf("Tree is empty.\n");
        return -1;
    }
    while (t->lchild != NULL)
    {
        t = t->lchild;
    }
    return t->data;
}

int equal(treenode *t1, treenode *t2)
{
    if (t1 == NULL && t2 == NULL)
    {
        return 1;
    }
    if (t1 == NULL || t2 == NULL)
    {
        return 0;
    }
    if (t1->data != t2->data)
    {
        return 0;
    }

    int leftEqual = equal(t1->lchild, t2->lchild);
    int rightEqual = equal(t1->rchild, t2->rchild);

    if (leftEqual && rightEqual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

treenode *search(treenode *t, int key)
{
    if (t == NULL || t->data == key)
        return t;
    if (key < t->data)
        return search(t->lchild, key);
    return search(t->rchild, key);
}

treenode *insucc(treenode *t, int key)
{
    treenode *curr = search(t, key);
    if (curr == NULL)
        return NULL;

    // case 1: right subtree exists
    if (curr->rchild != NULL)
    {
        treenode *temp = curr->rchild;
        while (temp->lchild != NULL)
            temp = temp->lchild;
        return temp;
    }

    // case 2: no right subtree — go up till node is left child
    treenode *p = curr->parent;
    while (p != NULL && curr == p->rchild)
    {
        curr = p;
        p = p->parent;
    }
    return p;
}

int deleteNodeHelper(treenode **rootRef, int val)
{
    treenode *t = *rootRef;
    if (t == NULL)
        return 0;

    if (val < t->data)
        return deleteNodeHelper(&(t->lchild), val);
    else if (val > t->data)
        return deleteNodeHelper(&(t->rchild), val);
    else
    {
        if (t->lchild == NULL && t->rchild == NULL)
        {
            free(t);
            *rootRef = NULL;
        }
        else if (t->lchild == NULL)
        {
            treenode *temp = t->rchild;
            temp->parent = t->parent;
            free(t);
            *rootRef = temp;
        }
        else if (t->rchild == NULL)
        {
            treenode *temp = t->lchild;
            temp->parent = t->parent;
            free(t);
            *rootRef = temp;
        }
        else
        {
            treenode *succ = t->rchild;
            while (succ->lchild != NULL)
                succ = succ->lchild;
            t->data = succ->data;
            return deleteNodeHelper(&(t->rchild), succ->data);
        }
        return 1;
    }
}

int deleteNode(treenode *t, int val)
{
    return deleteNodeHelper(&t, val);
}

int main()
{
    treenode *t = NULL;
    treenode *t2 = NULL;
    int flag = 1;
    int ch = -1;
    int num = 0;

    do
    {
        printf("1. Insert a node in the tree.\n"
               "2. Check if the tree is empty or not.\n"
               "3. Get the count of nodes in the tree.\n"
               "4. Get the inorder traversal.\n"
               "5. Get the preorder traversal.\n"
               "6. Get the postorder traversal.\n"
               "7. Get the height. \n"
               "8. Get the minimum node.\n"
               "9. Get the maximum node. \n"
               "10. Delete a node from the tree.\n"
               "11. Find the inorder successor of a node.\n"
               "12. Check if two trees are equal or not.\n"
               "0. Exit the program\n"
               "Enter your choice : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the node to be inserted: ");
            scanf("%d", &num);
            t = insertNode(t, num);
            break;
        case 2:
            if (isEmpty(t))
            {
                printf("Tree is empty.\n");
            }
            else
            {
                printf("Tree isn't empty.\n");
            }
            break;
        case 3:
            printf("There are %d nodes in the tree.\n", getCount(t));
            break;
        case 4:
            printf("Inorder sequence: ");
            if (inorder(t) == 0)
            {
                printf("Tree is empty.\n");
            }
            break;
        case 5:
            printf("Preorder sequence: ");
            if (preorder(t) == 0)
            {
                printf("Tree is empty.\n");
            }
            break;
        case 6:
            printf("Postorder sequence: ");
            if (postorder(t) == 0)
            {
                printf("Tree is empty.\n");
            }
            break;
        case 7:
            printf("Height of the tree is %d.\n", height(t));
            break;
        case 8:
            printf("Minimum node in the tree is %d.\n", min(t));
            break;
        case 9:
            printf("Maximum node in the tree is %d.\n", max(t));
            break;
        case 10:
            if (isEmpty(t))
            {
                printf("Tree is empty. Cannot delete.\n");
                break;
            }
            printf("Enter the node to be deleted: ");
            scanf("%d", &num);
            if (deleteNodeHelper(&t, num))
                printf("%d deleted successfully.\n", num);
            else
                printf("Node %d not found in the tree.\n", num);
            break;
        case 11:
            printf("Enter key to find successor: ");
            scanf("%d", &num);
            treenode *succ = insucc(t, num);
            if (succ)
            {
                printf("Inorder successor of %d is %d\n", num, succ->data);
            }
            else
            {
                printf("No inorder successor found for %d\n", num);
            }
            break;
        case 12:
            printf("Build Tree 2 (enter -1 to stop):\n");
            while (1)
            {
                printf("Enter node value: ");
                scanf("%d", &num);
                if (num == -1)
                    break;
                t2 = insertNode(t2, num);
            }
            if (equal(t, t2))
            {
                printf("Tree 1 and Tree 2 are equal.\n");
            }
            else
            {
                printf("Tree 1 and Tree 2 are NOT equal.\n");
            }
            break;
        case 0:
            flag = 0;
            printf("Exited the program.\n");
            break;
        default:
            printf("Wrong choice!!!");
        }
    } while (flag);
    return 0;
}
