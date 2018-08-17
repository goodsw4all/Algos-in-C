#include <criterion/criterion.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} node_t;

void printAll(node_t **head)
{
    node_t *p = *head;

    while(p) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

node_t* newNode(int data)
{
    node_t* node = (node_t *) malloc(sizeof(node_t));
    if (!node) {
        printf("Cannot allocate memory\n");
        return NULL;
    }

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void insertFirst(node_t **phead, node_t *newNode)
{
    if (*phead == NULL) {
        *phead = newNode;
        return;
    }

    (*phead)->prev = newNode;
    newNode->next = *phead;
    *phead = newNode;
}

void removeFirst(node_t **phead)
{
    if (*phead == NULL) {
        return;
    }

    node_t *temp = *phead;
    *phead = temp->next;
    free(temp);
}

/*
 * function insertAfter(List list, Node node, Node newNode)
 * function insertAfter(List list, Node node, Node newNode)
 */
/* Test w/ criterion framework below */
void setup(void)
{
    cr_log_info("%s()\n", __FUNCTION__);

}

void teardown(void)
{
    cr_log_info("%s()\n", __FUNCTION__);

}

TestSuite(DoublyLinkedList, .init = setup, .fini = teardown);

Test(DoublyLinkedList, operations, .disabled = false) {
    node_t *head = NULL;

    printf("Insert First\n");
    for(int i=0; i<5; i++) {
        insertFirst(&head, newNode(i));
        printAll(&head);
    }

    printf("Remove First\n");
    for(int i=0; i<5; i++) {
        removeFirst(&head);
        printAll(&head);
    }
}

