/* Вид дерева сверху */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct tree
{
    int key;
    struct tree *left, *right;
} tree;



void left(tree *tree)
{
    if(tree->left)
        left(tree->left);
    printf("%d ", tree->key);
}

void right(tree *tree)
{
    printf("%d ", tree->key);
    if(tree->right)
        left(tree->right);
}

void btUpView(tree *tree)
{
    left(tree);
    if(tree->right) 
        right(tree->right);
    printf("\n");
}

void add_tree(tree **my_tree,int key) 
{
    if(!*my_tree) 
	{
        *my_tree = (tree *) calloc(1, sizeof(tree));
        (*my_tree)->key = key;
    }
    else if((*my_tree)->key < key) 
        add_tree(&(*my_tree)->right, key);
    else 
        add_tree(&(*my_tree)->left, key);
}

int main() {
    tree *tree = NULL;
    add_tree(&tree, 10);
    add_tree(&tree, 5);
    add_tree(&tree, 15);
    add_tree(&tree, 3);
    add_tree(&tree, 7);
    add_tree(&tree, 13);
    add_tree(&tree, 18);
    add_tree(&tree, 1);
    add_tree(&tree, 6);
    btUpView(tree);
    return 0;
}


