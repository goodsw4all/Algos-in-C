#include <criterion/criterion.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

//<----------------------------- for BFS
typedef struct queue_node {
    struct node *data;
    struct queue_node *next;
} q_node_t;

q_node_t *front = NULL;
q_node_t *rear  = NULL;

bool isQueueEmpty()
{
    return (front == NULL && rear == NULL) ? true: false;
}

void enqueue(node_t* x)
{
    q_node_t *new = (q_node_t*) malloc(sizeof(q_node_t));
    new->data = x;
    new->next = NULL;

    if (front == NULL && rear == NULL) {
        front = rear = new;
        return;
    }

    rear->next = new;
    rear = new;
}

node_t *dequeue()
{
    if (front == NULL && rear == NULL)
        return NULL;

    node_t *data = front->data;
    q_node_t *remove = front;

    if (front == rear)
        front = rear = NULL;
    else
        front = front->next;
    free(remove);

    return data;
}
//----------------------------> for BFS

node_t *getNewNode(int data)
{
    node_t* node = (node_t*) malloc(sizeof(node_t));
    if(node == NULL) {
        printf("Cannot allocate memory\n");
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insertNode(node_t **proot, int data)
{
    if (*proot == NULL) {
        *proot = getNewNode(data);
        return;
    }

    if ((*proot)->data >= data) {
        insertNode(&(*proot)->left, data);
    } else {
        insertNode(&(*proot)->right, data);
    }

}

bool searchNode(node_t *root, int data)
{
    if (root == NULL)
        return false;

    if (root->data == data)
        return true;

    if (root->data >= data)
        return searchNode(root->left, data);
    else
        return searchNode(root->right, data);
}

int findMinIterative(node_t *root)
{
    if (root == NULL)
        return INT32_MIN;

    node_t *cur = root;

    while(cur->left != NULL) {
        cur = cur->left;
    }

    return cur->data;
}

int findMinRecursive(node_t *root)
{
    if (root == NULL)
        return INT32_MIN;

    if (root->left == NULL)
        return root->data;

    return findMinRecursive(root->left);

}

int findMaxIterative(node_t *root)
{
    if (root == NULL)
        return INT32_MAX;

    node_t *cur = root;
    while (cur->right != NULL) {
        cur = cur->right;
    }

    return cur->data;
}

int findMaxRecursive(node_t *root)
{
    if (root == NULL)
        return INT32_MAX;

    node_t *cur = root;
    if (cur->right == NULL)
        return cur->data;

    return findMaxRecursive(cur->right);
}

#define ROOT_VISIT(x) \
    do { \
        printf("%2d -> ", x); \
    }while(0)

void BFS(node_t *root)
{
    if (root == NULL)
        return;

    enqueue(root);

    while(!isQueueEmpty()) {
        node_t *cur = dequeue();
        ROOT_VISIT(cur->data);

        if (cur->left != NULL) {
            enqueue(cur->left);
        }
        if (cur->right != NULL) {
            enqueue(cur->right);
        }
    }
}

void preorderDFS(node_t *root)
{
    if (root == NULL)
        return;

    ROOT_VISIT(root->data);
    preorderDFS(root->left);
    preorderDFS(root->right);
}

void inorderDFS(node_t *root)
{
    if (root == NULL)
        return;

    inorderDFS(root->left);
    ROOT_VISIT(root->data);
    inorderDFS(root->right);

}
void postorderDFS(node_t *root)
{
    if (root == NULL)
        return;

    postorderDFS(root->left);
    postorderDFS(root->right);
    ROOT_VISIT(root->data);
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

//TODO : Valgrind Check
TestSuite(BST, .init = setup, .fini = teardown);
Test(BST, operations, .disabled = true) {
    node_t *root = NULL; //Empty

    insertNode(&root, 15);
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 25);
    insertNode(&root, 8);
    insertNode(&root, 12);

    cr_expect(searchNode(root, 15), "searchNode");
    cr_expect_not(searchNode(root, 21), "searchNode() which is not in tree");

    cr_expect_eq(findMinIterative(root), findMinRecursive(root), "Find Min 8");
    cr_expect_eq(findMaxIterative(root), findMaxRecursive(root), "Find Max 25");

    cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
}

/* BFS / DFS */
Test(BST, order, .disabled = false) {
    node_t *root = NULL; //Empty
    insertNode(&root, 8);

    insertNode(&root, 3);
    insertNode(&root, 10);

    insertNode(&root, 1);
    insertNode(&root, 6);
    insertNode(&root, 14);

    insertNode(&root, 4);
    insertNode(&root, 7);
    insertNode(&root, 13);

    /*
     *
     *            8
     *         /     \
     *       3        10
     *     /   \        \
     *    1     6        14
     *        /   \     /
     *       4     7   13
     *
     */

    BFS(root);
    puts("Level-Order");
    preorderDFS(root);
    puts("Pre-Order");
    inorderDFS(root);
    puts("In-Order");
    postorderDFS(root);
    puts("Post-Order");
}