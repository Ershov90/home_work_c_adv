/* Найти брата */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef int datatype;

typedef struct tree {
    datatype key;
    struct tree *left, *right;
    struct tree *parent; 
} tree, br;

void add_tree(tree **root, datatype key, tree *pt) 
{
    if(!*root) {
        *root = (tree *) calloc(1, sizeof(tree));
        (*root)->key = key;
        (*root)->parent = pt;
    }
    else if((*root)->key < key) 
        add_tree(&(*root)->right, key, *root);
    else 
       add_tree(&(*root)->left, key, *root);
}

tree *findBrother(tree *root, datatype key)
{
    tree *target = NULL;
    tree *tmp[100];
    int top = -1;
    tmp[++top] = root;
    while (top >= 0) {
        tree *n = tmp[top--];
        if (n->key == key) {
            target = n;
            break;
        }
        if (n->right)
            tmp[++top] = n->right;
        if (n->left)
            tmp[++top] = n->left;
    }
    if (target == NULL)
        return NULL;
    if (target->parent == NULL)
        return 0;
    tree *parent = target->parent;
    if (parent->left == target)
        return parent->right;
    else
        return parent->left;
}

int main() {
    tree *m_tree = NULL;
    add_tree(&m_tree, 10, NULL);
    add_tree(&m_tree, 5, NULL);
    add_tree(&m_tree, 15,NULL);
    add_tree(&m_tree, 3, NULL);
    add_tree(&m_tree, 7, NULL);
    add_tree(&m_tree, 13, NULL);
    add_tree(&m_tree, 18, NULL);
    add_tree(&m_tree, 1, NULL);
    add_tree(&m_tree, 6, NULL);
    tree* br = findBrother(m_tree, 3);
    return 0;
}


