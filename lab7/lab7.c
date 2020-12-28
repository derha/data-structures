#include <stdio.h>
#include <stdlib.h>

struct node
{
    int num;
    int balance;
    struct node *left_child;
    struct node *right_child;
};

struct node* insert(struct node **current_node, struct node *new_node, struct node **root);
void print_nums(struct node *root);
void print_tree(struct node *root);
int print_level(struct node *root, int until_stop);
int update_balance(struct node *root);

//----------------------------------------------------------------------------------------------------------------------

int main()
{
    struct node *root = NULL;

    // input and AVL tree creation
    int exit_check;
    while (1)
    {
        scanf("%d", &exit_check);
        if (exit_check == -1)
            break;

        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->num = exit_check;
        new_node->balance = 0;
        new_node->left_child = NULL;
        new_node->right_child = NULL;

        insert(&root, new_node, &root);
    }

    print_nums(root);
    printf("\n");
    print_tree(root);

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

struct node* insert(struct node **current_node, struct node *new_node, struct node **root)
{
    // actual insertion of a new node as a leaf
    if (!(*current_node))
    {
        *current_node = new_node;
        update_balance(*root);
        return NULL;
    }

    struct node *new_child = NULL;
    if (new_node->num < (*current_node)->num)
        new_child = insert(&((*current_node)->left_child), new_node, root);
    else
        new_child = insert(&((*current_node)->right_child), new_node, root);
    if (new_child)
    {
        if (new_child->num < (*current_node)->num)
            (*current_node)->left_child = new_child;
        else
            (*current_node)->right_child = new_child;
        update_balance(*root);
    }

    struct node *new_root = NULL;
    // LL rotation
    if ((*current_node)->balance == 2 && ((*current_node)->left_child)->balance == 1)
    {
        new_root = (*current_node)->left_child;
        (*current_node)->left_child = new_root->right_child;
        new_root->right_child = *current_node;

        if ((*root)->num == (*current_node)->num)
        {
            *root = new_root;
            return NULL;
        }
    }

    // RR rotation
    else if ((*current_node)->balance == -2 && ((*current_node)->right_child)->balance == -1)
    {
        new_root = (*current_node)->right_child;
        (*current_node)->right_child = new_root->left_child;
        new_root->left_child = *current_node;

        if ((*root)->num == (*current_node)->num)
        {
            *root = new_root;
            return NULL;
        }
    }

    // LR rotation
    else if ((*current_node)->balance == 2 && ((*current_node)->left_child)->balance == -1)
    {
        new_root = (*current_node)->left_child->right_child;
        (*current_node)->left_child->right_child = new_root->left_child;
        new_root->left_child = (*current_node)->left_child;
        (*current_node)->left_child = new_root->right_child;
        new_root->right_child = *current_node;

        if ((*root)->num == (*current_node)->num)
        {
            *root = new_root;
            return NULL;
        }
    }

    // RL rotation
    else if ((*current_node)->balance == -2 && ((*current_node)->right_child)->balance == 1)
    {
        new_root = (*current_node)->right_child->left_child;
        (*current_node)->right_child->left_child = new_root->right_child;
        new_root->right_child = (*current_node)->right_child;
        (*current_node)->right_child = new_root->left_child;
        new_root->left_child = *current_node;

        if ((*root)->num == (*current_node)->num)
        {
            *root = new_root;
            return NULL;
        }
    }

    return new_root;
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
    printf("%d (%d B)\n", root->num, root->balance);

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
            printf("%d (%d L) (%d B) ", root->left_child->num, root->num, root->left_child->balance);

        if (root->right_child != NULL)
            printf("%d (%d R) (%d B) ", root->right_child->num, root->num, root->right_child->balance);

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

int update_balance(struct node *root)
{
    if (!(root->left_child) && !(root->right_child))
    {
        root->balance = 0;
        return 1;
    }

    int l_height = 0;
    int r_height = 0;

    if (root->left_child != NULL)
        l_height = update_balance(root->left_child);

    if (root->right_child != NULL)
        r_height = update_balance(root->right_child);

    root->balance = l_height - r_height;

    if (l_height > r_height)
        return l_height + 1;
    return r_height + 1;
}