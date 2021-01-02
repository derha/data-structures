#include <stdio.h>
#include <stdlib.h>

struct node
{
    int num;
    char color;
    struct node *parent;
    struct node *left_child;
    struct node *right_child;
};

void insert(struct node **root, struct node *new_node);
void print_nums(struct node *root);
void print_tree(struct node *root);
int print_level(struct node *root, int until_stop);
struct node* grand_parent(struct node *n);
struct node* uncle(struct node *n);
void case1(struct node *n, struct node **root);
void case2(struct node *n, struct node **root);
void case3(struct node *n, struct node **root);
void case4(struct node *n, struct node **root);
void case5(struct node *n, struct node **root);
void rotate_right(struct node *n, struct node **root);
void rotate_left(struct node *n, struct node **root);

//----------------------------------------------------------------------------------------------------------------------

int main()
{
    struct node *root = NULL;

    // input and red-black tree creation
    int exit_check;
    while (1)
    {
        scanf("%d", &exit_check);
        if (exit_check == -1)
            break;

        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->num = exit_check;
        new_node->color = 'R';
        new_node->parent = NULL;
        new_node->left_child = NULL;
        new_node->right_child = NULL;

        insert(&root, new_node);
        case1(new_node, &root);
    }

    print_nums(root);
    printf("\n");
    print_tree(root);

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

void insert(struct node **root, struct node *new_node)
{
    if (!(*root))
    {
        *root = new_node;
        return;
    }

    if (new_node->num < (*root)->num)
    {
        insert(&((*root)->left_child), new_node);
        if ((*root)->left_child->num == new_node->num)
            new_node->parent = *root;
    }
    else
    {
        insert(&((*root)->right_child), new_node);
        if ((*root)->right_child->num == new_node->num)
            new_node->parent = *root;
    }
}

void print_nums(struct node *root)
{
    if (root->left_child != NULL)
        print_nums(root->left_child);

    printf("%d\n", root->num);

    if (root->right_child != NULL)
        print_nums(root->right_child);

    return;
}

void print_tree(struct node *root)
{
    printf("%d %c\n", root->num, root->color);

    for (int i = 0; ; ++i)
    {
        if (!print_level(root, i))
            break;
        printf("\n");
    }
}

int print_level(struct node *root, int until_stop)
{
    if (!until_stop)
    {
        if (root->left_child != NULL)
            printf("%d %c (%d L) ", root->left_child->num, root->left_child->color, root->num);

        if (root->right_child != NULL)
            printf("%d %c (%d R) ", root->right_child->num, root->right_child->color, root->num);

        return 1;
    }

    int flag = 0;

    if (root->left_child != NULL)
        if (print_level(root->left_child, until_stop - 1))
            flag = 1;

    if (root->right_child != NULL)
        if (print_level(root->right_child, until_stop - 1))
            flag = 1;

    return flag;
}

struct node* grand_parent(struct node *n)
{
    if ((n != NULL) && (n->parent != NULL))
        return n->parent->parent;
    else
        return NULL;
}

struct node* uncle(struct node *n)
{
    struct node *g = grand_parent(n);
    if (g == NULL)
        return NULL;
    if (n->parent == g->left_child)
        return g->right_child;
    else
        return g->left_child;
}

void case1(struct node *n, struct node **root)
{
    if (n->parent == NULL)
        n->color = 'B';
    else
        case2(n, root);
}

void case2(struct node *n, struct node **root)
{
    if (n->parent->color == 'B')
        return;
    else
        case3(n, root);
}

void case3(struct node *n, struct node **root)
{
    struct node *u = uncle(n);
    struct node *g = grand_parent(n);
    if ((u != NULL) && (u->color == 'R'))
    {
        n->parent->color = 'B';
        u->color = 'B';
        g->color = 'R';
        case1(g, root);
    }
    else
        case4(n, root);
}

void case4(struct node *n, struct node **root)
{
    struct node *g = grand_parent(n);
    if ((n == n->parent->right_child) && (n->parent == g->left_child))
    {
        rotate_left(n->parent, root);
        n = n->left_child;
    }
    else if ((n == n->parent->left_child) && (n->parent == g->right_child))
    {
        rotate_right(n->parent, root);
        n = n->right_child;
    }
    case5(n, root);
}

void case5(struct node *n, struct node **root)
{
    struct node *g = grand_parent(n);
    if ((n == n->parent->left_child) && (n->parent == g->left_child))
        rotate_right(g, root);
    else if ((n == n->parent->right_child) && (n->parent == g->right_child))
        rotate_left(g, root);
    n->parent->color = 'B';
    g->color = 'R';
}

void rotate_right(struct node *n, struct node **root)
{
    struct node *prev_parent = n->parent;
    struct node *local_root = n->left_child;

    n->left_child = local_root->right_child;
    n->parent = local_root;
    local_root->right_child = n;
    local_root->parent = prev_parent;

    if (*root == n)
        *root = local_root;
    else if (local_root->num < prev_parent->num)
        prev_parent->left_child = local_root;
    else
        prev_parent->right_child = local_root;
}

void rotate_left(struct node *n, struct node **root)
{
    struct node *prev_parent = n->parent;
    struct node *local_root = n->right_child;

    n->right_child = local_root->left_child;
    n->parent = local_root;
    local_root->left_child = n;
    local_root->parent = prev_parent;

    if (*root == n)
        *root = local_root;
    else if (local_root->num < prev_parent->num)
        prev_parent->left_child = local_root;
    else
        prev_parent->right_child = local_root;
}