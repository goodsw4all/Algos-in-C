#include <criterion/criterion.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

//<----------------------------- Q for BFS
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
//----------------------------> Q for BFS

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

node_t* searchNode(node_t *root, int data)
{
    if (root == NULL)
        return NULL;

    if (root->data == data)
        return root;

    if (root->data >= data)
        return searchNode(root->left, data);
    else
        return searchNode(root->right, data);
}

void removeTree(node_t *root)
{
    if (root == NULL)
        return;

    if (root->left) removeTree(root->left);
    if (root->right) removeTree(root->right);
    free(root);
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

/* SIZE : 총 노드의 숫자 */
int getTreeSize(node_t *root)
{
    if (root == NULL)
        return 0;
    return getTreeSize(root->left) + getTreeSize(root->right)  + 1; // 1은 Root 자신
}

#define MAX(x,y) ((x)>(y) ? (x) : (y))

/* MAX Depth : 최대 경로(Edge) 구하기 */
int getTreeMaxDepth(node_t *root)
{
    if (root == NULL) // empty
        return 0;

    int leftDepth = getTreeMaxDepth(root->left);
    int rightDepth = getTreeMaxDepth(root->right);

    return MAX(leftDepth, rightDepth) + 1;
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

bool isBST(node_t *root, int minValue, int maxValue)
{
    if (root == NULL)
        return true;

    if (root->data > minValue
            && root->data < maxValue
            && isBST(root->left, minValue, root->data)
            && isBST(root->right, root->data, maxValue)) {
        return true;

    } else {
        return false;
    }
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
    // Traversal

    printf("    Tree Structure\n"
           "          8\n"
           "       /     \\\n"
           "     3        10\n"
           "   /   \\        \\\n"
           "  1     6        14\n"
           "      /   \\     /\n"
           "     4     7   13""\n");
    BFS(root);
    puts("Level-Order (BFS)");
    preorderDFS(root);
    puts("Pre-Order   (DFS)");
    inorderDFS(root);
    puts("In-Order    (DFS)");
    postorderDFS(root);
    puts("Post-Order  (DFS)");

    // Tree Info
    printf("Tree Info\n");
    printf(" - Size      (How many nodes?)                 : %d\n", getTreeSize(root));
    printf(" - Max Depth (# of nodes in the longest Path?) : %d\n", getTreeMaxDepth(root));
    printf(" - Min       (follow left)                     : %d\n", findMinRecursive(root));
    printf(" - Max       (follow right)                    : %d\n", findMaxRecursive(root));
    printf("%s BST\n", (isBST(root, INT32_MIN, INT32_MAX) ? "It's" : "It's not"));
    node_t *node = searchNode(root, 14);
    printf("Get %d, and swap left(%d), right(NULL)\n", node->data, node->left->data);
    node->right = node->left;
    node->left = NULL;
    printf("%s BST\n", (isBST(root, INT32_MIN, INT32_MAX) ? "It's" : "It's not"));
    printf("\n");

}