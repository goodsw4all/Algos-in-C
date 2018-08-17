#include <criterion/criterion.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

node_t *front = NULL;
node_t *rear  = NULL;

node_t *newNode(int data)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    if (!node) {
        printf("Cannot allocate memory\n");
    }
    node->data = data;
    node->next = NULL;

    return node;
}
void enqueue(int x)
{
    node_t *new = newNode(x);
    if (front == NULL && rear == NULL) {
        front = new;
        rear  = new;
        return;
    }

    rear->next = new;
    rear = new;
}

int dequeue()
{
    if (front == NULL && rear == NULL)
        return -1;

    int data = front->data;
    node_t *remove = front;
    front = front->next;
    free(remove);
}

void printList()
{
    if (front == NULL)
        return;

    node_t *p = front;
    printf("front ->");
    while (p) {
        printf(" | %d | ", p->data);
        p = p->next;
    }
    printf("<- rear\n");
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

TestSuite(Queue, .init = setup, .fini = teardown);

Test(Queue, operations, .disabled = false) {
    printf("Queue\n");
    printList();
    for(int i=0; i<5; i++) {
        enqueue(i);
        printList();
    }
    printf("\n");

    printf("Dequeue\n");
    for(int i=0; i<5; i++) {
        printList();
        int data = dequeue();
    }
    printList();
    printf("\n");
}
