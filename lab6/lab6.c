#include <stdio.h>
#include <stdlib.h>

struct node
{
    int id;
    int grade;
    struct node *left_child;
    struct node *right_child;
};

void insert(struct node **root, struct node *new_node);
void print_grades(struct node *root);
void print_tree(struct node *root);
int print_level(struct node *root, int until_stop);

//----------------------------------------------------------------------------------------------------------------------

int main()
{
    struct node *root = NULL;

    // input and binary search tree creation
    int exit_check;
    while (1)
    {
        scanf("%d", &exit_check);
        if (exit_check == -1)
            break;

        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->id = exit_check;
        scanf("%d", &(new_node->grade));
        new_node->left_child = NULL;
        new_node->right_child = NULL;

        insert(&root, new_node);
    }

    print_grades(root);
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

    if (new_node->grade < (*root)->grade)
        insert(&((*root)->left_child), new_node);
    else
        insert(&((*root)->right_child), new_node);
}

void print_grades(struct node *root)
{
    if (root->left_child != NULL)
        print_grades(root->left_child);

    printf("%d %d\n", root->id, root->grade);

    if (root->right_child != NULL)
        print_grades(root->right_child);

    return;
}

void print_tree(struct node *root)
{
    printf("%d %d\n", root->id, root->grade);

    for (int i = 0; ; ++i)
    {
        if (!print_level(root, i))
            break;
        printf("\n");
    }
}

int print_level(struct node *root, int until_stop)
{
    int flag = 0;

    if (!until_stop)
    {
        if (root->left_child != NULL)
        {
            printf("%d %d (%d L) ", root->left_child->id, root->left_child->grade, root->grade);
            flag = 1;
        }

        if (root->right_child != NULL)
        {
            printf("%d %d (%d R) ", root->right_child->id, root->right_child->grade, root->grade);
            flag = 1;
        }

        return flag;
    }

    if (root->left_child != NULL)
        if (print_level(root->left_child, until_stop - 1))
            flag = 1;

    if (root->right_child != NULL)
        if (print_level(root->right_child, until_stop - 1))
            flag = 1;

    return flag;
}