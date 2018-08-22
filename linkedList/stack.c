#include <criterion/criterion.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

node_t *top = NULL;

node_t *getNewNode(int data)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    if (!node) {
        printf("Cannot allocate memory\n");
    }
    node->data = data;
    node->next = NULL;

    return node;
}

void push(int data)
{
    node_t *new = getNewNode(data);
    if (top == NULL) { // Stack 이 비어 있으면
        top = new;
        return;
    }

    new->next = top;
    top = new;
}

int pop()
{
    if (top == NULL) { // Stack 이 비어 있으면
        printf("Empty!!!");
        return -1;
    }

    int ret = top->data;
    node_t *p = top;
    top = top->next;
    free(p);
    return ret;
}

void printList()
{
    node_t *temp = top; // Top은 Bottom 방향으로 next를 가지고 있다
    while(temp != NULL) {
        printf("| %d | ", temp->data);
        temp = temp->next;
    }
    printf("\n");
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

TestSuite(Stack, .init = setup, .fini = teardown);

Test(Stack, operations, .disabled = false) {
    printf("Push\ntop\n");
    for(int i=0; i<5; i++) {
        push(i);
        printList();
    }
    printf("\n");

    printf("Pop\ntop\n");
    for(int i=0; i<5; i++) {
        printList();
        int data = pop();
    }
    printf("\n");
}
