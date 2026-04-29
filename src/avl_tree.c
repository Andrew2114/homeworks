#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max(int a, int b)
{
    return a > b ? a : b;
}

static int get_height(Node* n)
{
    return n ? n->height : 0;
}

static void update_height(Node* n)
{
    if (n) {
        n->height = 1 + max(get_height(n->left), get_height(n->right));
    }
}

static Node* rotate_right(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);
    return x;
}

static Node* rotate_left(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);
    return y;
}

static Node* balance(Node* n)
{
    if (!n)
        return NULL;

    update_height(n);
    int balance_factor = get_height(n->left) - get_height(n->right);

    if (balance_factor > 1) {
        if (get_height(n->left->right) > get_height(n->left->left)) {
            n->left = rotate_left(n->left);
        }
        return rotate_right(n);
    }

    if (balance_factor < -1) {
        if (get_height(n->right->left) > get_height(n->right->right)) {
            n->right = rotate_right(n->right);
        }
        return rotate_left(n);
    }

    return n;
}

static Node* find_min(Node* root)
{
    while (root->left)
        root = root->left;
    return root;
}

Node* avl_create_node(const char* code, const char* name)
{
    Node* new = (Node*)malloc(sizeof(Node));
    if (!new)
        return NULL;
    strcpy(new->code, code);
    strcpy(new->name, name);
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    return new;
}

Node* avl_insert(Node* root, const char* code, const char* name)
{
    if (!root)
        return avl_create_node(code, name);

    int cmp = strcmp(code, root->code);

    if (cmp < 0) {
        root->left = avl_insert(root->left, code, name);
    } else if (cmp > 0) {
        root->right = avl_insert(root->right, code, name);
    } else {
        return root;
    }

    return balance(root);
}

Node* avl_find(Node* root, const char* code)
{
    if (!root)
        return NULL;

    int cmp = strcmp(code, root->code);
    if (cmp < 0)
        return avl_find(root->left, code);
    if (cmp > 0)
        return avl_find(root->right, code);
    return root;
}

int avl_contains(Node* root, const char* code)
{
    return avl_find(root, code) != NULL;
}

Node* avl_delete(Node* root, const char* code)
{
    if (!root)
        return NULL;

    int cmp = strcmp(code, root->code);

    if (cmp < 0) {
        root->left = avl_delete(root->left, code);
    } else if (cmp > 0) {
        root->right = avl_delete(root->right, code);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Node* temp = find_min(root->right);
            strcpy(root->code, temp->code);
            strcpy(root->name, temp->name);
            root->right = avl_delete(root->right, temp->code);
        }
    }

    return balance(root);
}

void avl_save(Node* root, FILE* f)
{
    if (!root)
        return;
    avl_save(root->left, f);
    fprintf(f, "%s:%s\n", root->code, root->name);
    avl_save(root->right, f);
}

void avl_free(Node* root)
{
    if (!root)
        return;
    avl_free(root->left);
    avl_free(root->right);
    free(root);
}

int avl_count(Node* root)
{
    if (!root)
        return 0;
    return 1 + avl_count(root->left) + avl_count(root->right);
}
