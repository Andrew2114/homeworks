#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char code[4];
    char name[256];
    struct Node* left;
    struct Node* right;
    int height;
} Node;

Node* avl_create_node(const char* code, const char* name);

Node* avl_insert(Node* root, const char* code, const char* name);

Node* avl_find(Node* root, const char* code);

Node* avl_delete(Node* root, const char* code);

void avl_save(Node* root, FILE* f);

void avl_free(Node* root);

int avl_count(Node* root);

int avl_contains(Node* root, const char* code);
