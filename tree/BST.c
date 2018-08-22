#include <criterion/criterion.h>

typedef struct tree_node {
    int data;
    struct tree_node *left;
    struct tree_node *right;
} node_t;

node_t * findMinIterative(node_t *root);

/* <- Q for levelOrderBFS */
typedef struct queue_node {
    struct tree_node *data;
    struct queue_node *next;
} q_node_t;

q_node_t *front = NULL;
q_node_t *rear  = NULL;

bool isQueueEmpty()
{
    return (front == NULL && rear == NULL) ? true : false;
}

void enqueue(node_t* x)
{
    q_node_t *new = (q_node_t*) malloc(sizeof(q_node_t));
    new->data = x; // Tree Node
    new->next = NULL;

    if (front == NULL && rear == NULL) {
        front = rear = new;
        return;
    }

    // 뒤에 새로운 노드 추가
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
        front = front->next; // 앞에서 노드를 꺼내와 제거
    free(remove);

    return data;
}
/* Q for levelOrderBFS -> */

/*
 * 새로운 Q Node를 할당
 */
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

/*
 *   Insert (the new node recursively)
 *
 *   현재 노드보다 작다면 왼쪽 트리로 재귀 호출
 *   현재 노드보다 크다면 오른쪽 트리로 재귀 호출
 *   삽입할 위치를 찾으면 새로운 노드를 생성해서 그 위치 삽입하고 return
 *
 */
void insertNode(node_t **proot, int data)
{
    if (*proot == NULL) {  // 삽입할 위치
        *proot = getNewNode(data);
        return;
    }

    if ((*proot)->data >= data) {
        insertNode(&(*proot)->left, data);
    } else {
        insertNode(&(*proot)->right, data);
    }
}

/*
 *   Search
 *   이진 탐색 트리의 성질을 이용하여 재귀 호출 (삽인과 유사한 방식)
 *   현재 노드보다 작다면 왼쪽 트리로 재귀 호출
 *   현재 노드보다 크다면 오른쪽 트리로 재귀 호출
 *   leaf node 까지 도달했으면 NULL return
 *   같은 데이터를 찾았으면 현재 노드 return
 */
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
/*
 *   Delete
 *   현재 노드보다 작다면 왼쪽 트리로 재귀 호출
 *   현재 노드보다 크다면 오른쪽 트리로 재귀 호출
 *   지울 노드를 찾으면
 *   case 1 : 자식 없는 경우 (무자식 상팔자)
 *            현재 노드를 지운다. 이 경우에는 여전히 현재 노드는 주소값을 가지고 있으므로 NULL 할당까지 한다.
 *   case 2 : 오른쪽 자식만 있는 경우
 *            현재 노드를 오른쪽 자식으로 교체하고, 현재 노드는 지운다.
 *   case 3 : 왼쪽 자식만 있는 경우
 *            현재 노드를 왼쪽 자식으로 교체하고, 현재 노드는 지운다.
 *   case 4 : 둘 다 있는 경우
 *            오른쪽 트리에서 가장 작은 값을 찾아 교체, 현재 노드의 오른쪽 노드에서 중복된 값을 지우는 재귀호출
 *            (왼쪽 트리에서 가장 큰값을 찾아 교체하는 방법으로 해되 된다)
 *
 */
node_t* deleteNode(node_t *root, int data)
{
    if (root == NULL)
        return root;

    if (root->data > data)
        root->left = deleteNode(root->left, data);
    else if (root->data < data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL && root->right == NULL) {
            node_t *temp = root;
            free(temp);
            root = NULL;
        } else if (root->left == NULL) {
            node_t *temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            node_t *temp = root;
            root = root->left;
            free(temp);
        } else {
            node_t *temp = findMinIterative(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
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

/*
 *   Level Order (Breadth First Search)
 *   1. Q 에 root node 를 enqueue
 *   2. Q 에서 node 를 하나 꺼내어 방문(data read)
 *   3. 꺼낸 노드의 자식들을 enqueue
 *   4. Q 가 완전히 비우질 때까지 2,3 반복
 */
void levelOrderBFS(node_t *root)
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

/*
 *   D - L - R
 */
void preorderDFS(node_t *root)
{
    if (root == NULL)
        return;

    ROOT_VISIT(root->data);
    preorderDFS(root->left);
    preorderDFS(root->right);
}
/*
 *   L - D - R
 */
void inorderDFS(node_t *root)
{
    if (root == NULL)
        return;

    inorderDFS(root->left);
    ROOT_VISIT(root->data);
    inorderDFS(root->right);

}

/*
 *   L - R - D
 */
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

/*
 *   Find minimum
 *   BST는 왼쪽으로 순회하면 작은 값들을 만남
 */
node_t * findMinIterative(node_t *root)
{
    if (root == NULL)
        return NULL;

    node_t *cur = root;

    while(cur->left != NULL) {
        cur = cur->left;
    }

    return cur;
}

int findMinRecursive(node_t *root)
{
    if (root == NULL)
        return INT32_MIN;

    if (root->left == NULL)
        return root->data;

    return findMinRecursive(root->left);
}

/*
 *   Find maximum
 *   오른쪽으로 가다보면 큰 값들을 만남 제일 끝에 있는 애
 */
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

/*
 *   BST check
 *   isBST(root, INT32_MIN, INT32_MAX);
 *   현재 값은 최소값보다 크고 최대값보다 작아야 함
 *   && 왼쪽 트리로는 최소값과 최대값(현재값으로, 왼쪽에는 부모 노드값이 최대값이므로)해서 재귀호출
 *   && 오른쪽 트리로는 최소값(현재값)과 최대값으로 하여 재귀호출
 */
bool isBST(node_t *root, int minValue, int maxValue)
{
    if (root == NULL)
        return true;

    if (root->data > minValue
            && root->data < maxValue )
        return false;

    if (isBST(root->left, minValue, root->data)
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

//    cr_expect_eq(findMinIterative(root), findMinRecursive(root), "Find Min 8");
//    cr_expect_eq(findMaxIterative(root), findMaxRecursive(root), "Find Max 25");

    cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
}

/* levelOrderBFS / DFS */
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

    /*  Binary Search Tree
     *  왼쪽 노드와 그 이하 child 는 핸재 노드보다 작아야 하고
     *  오른쪽 노드와 그 이하 child 는 현재 노드보다 커야 한다
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
    levelOrderBFS(root);
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
    printf("Find %d, and swap left(%d), right(NULL)\n", node->data, node->left->data);
    node->right = node->left;
    node->left = NULL;
    printf("%s BST\n", (isBST(root, INT32_MIN, INT32_MAX) ? "It's" : "It's not"));
    printf("\n");

}