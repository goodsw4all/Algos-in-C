#include <criterion/criterion.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

void printRecursiveForward(node_t *node)
{
    if (node == NULL) {
        printf("NULL\n");
        return;
    }

    printf("%d -> ", node->data);
    printRecursiveForward(node->next);
}

void printRecursiveBackward(node_t *node)
{
    if (node == NULL) {
        printf("NULL");
        return;
    }

    printRecursiveBackward(node->next);
    printf(" <- %d", node->data);
}

/* sub-functions for generic traverse */
void _printAll(node_t *p, void *arg)
{
    char *fmt;

    fmt = (char*) arg;
    printf(fmt, p->data, p);

    if (p->next == NULL)
        printf("NULL\n");
}

void _nodeCount(node_t *p, void *arg)
{
    int *count = (int *) arg; // arg 는 generic traverse 를 호출할 때 준다
    (*count)++;
}
/* sub-functions --> */

/* generic traverse learned from the practice of programming */
void traverse(node_t *head, void (*func)(node_t *, void *), void *arg)
{
    node_t *p = head;
    for (; p != NULL; p=p->next)
        (*func)(p, arg);
}

node_t* newNode(int data)
{
    node_t* node = (node_t *) malloc(sizeof(node_t));
    if (!node) {
        printf("Cannot allocate memory\n");
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

void insertNode(node_t **phead, node_t* newNode)
{
    if (newNode == NULL)
        return;

    newNode->next = *phead;
    *phead = newNode;
}

bool insertNodeNth(node_t **phead, node_t* new, int nth)
{
    if (new == NULL)
        return false;

    if (nth==1) { // Head 가 변경 되는 경우
        new->next = *phead;
        *phead = new;
        return true;
    }

    node_t *prev = *phead;
    for(int i=0; i<nth-2; i++) { // 이전 노드를 찾아서
        prev = prev->next;
        if (prev == NULL)
            return false;
    }

    new->next = prev->next;
    prev->next = new;

    return true;
}

void removeNode(node_t **phead)
{
    if (*phead == NULL) // empty
        return;

    node_t *temp = *phead;
    *phead = temp->next;
    free(temp);
}

bool removeNodeNth(node_t **phead, int nth)
{
    if (*phead == NULL) // empty
        return false;

    node_t *temp = *phead;
    if (nth == 1) { // Head 값이 변경되어야 하는 경우
        *phead = temp->next;
        free(temp);
        return true;
    }

    node_t *prev = *phead;
    for (int i=0; i<nth-2; i++) {
        prev = prev->next;
        if (prev == NULL)
            return false;
    }

    temp = prev->next;
    prev->next = prev->next->next;
    free(temp);

    return true;
}

void reverseRecursive(node_t **phead, node_t *node)
{
    if (node->next == NULL) {
        *phead = node;
        return;
    }

    reverseRecursive(phead, node->next);
    node_t *nextNode = node->next;
    nextNode->next = node;
    node->next = NULL;
}

void reverseIterative(node_t **phead)
{
    node_t *curNode = *phead;
    node_t *prevNode = NULL;
    node_t *nextNode = NULL;

    while (curNode != NULL) {
        nextNode = curNode->next; // 다음 노드로 이동하기 위해 임시저장
        curNode->next = prevNode;
        prevNode = curNode;
        curNode = nextNode;
    }

    *phead = prevNode;
}

bool removeData(node_t **phead, int data)
{
    if (*phead == NULL) // empty
        return false;

    node_t *curNode = *phead;

    if (curNode->data == data) {
        *phead = curNode->next;
        free(curNode);
        return true;
    }

    node_t *prev = curNode;
    curNode = curNode->next;
    while (curNode != NULL) {
        if (curNode->data == data) {
            // remove it
            prev->next = curNode->next;
            free(curNode);
            return true;
        }
        prev = curNode;
        curNode = curNode->next;
    }

    return false;
}

/* Test w/ criterion framework below */
void setup(void)
{
    cr_log_info("%s()\n", __FUNCTION__);

}

void teardown(void)
{
    cr_log_info("%s()\n", __FUNCTION__);

}

TestSuite(SinglyLinkedList, .init = setup, .fini = teardown);

Test(SinglyLinkedList, insert, .disabled = false) {
    node_t *head = NULL;

    for(int i=0; i<3; i++) {
        insertNode(&head, newNode(i));
    }

    printf("Linked List \n");
    traverse(head, _printAll, "%d(0x%p) -> ");
    reverseRecursive(&head, head);
    traverse(head, _printAll, "%d(0x%p) -> ");
    reverseIterative(&head);
    traverse(head, _printAll, "%d(0x%p) -> ");

    int count = 0;
    traverse(head, _nodeCount, &count);
    printf("\nTotal %d elements in the list\n", count);
    printRecursiveForward(head);
    insertNodeNth(&head, newNode(7), 4);
    printRecursiveForward(head);
    removeData(&head, 7);
    printRecursiveForward(head);

    removeNodeNth(&head, count);
    printRecursiveForward(head);
    removeNodeNth(&head, 1);
    printRecursiveForward(head);
    removeNodeNth(&head, 1);
    printRecursiveForward(head);
    removeNode(&head);
    printRecursiveForward(head);
}

