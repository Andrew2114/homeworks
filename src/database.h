#pragma once

#include "avl_tree.h"
#include <stdio.h>

typedef struct {
    Node* root;
    char filename[256];
    int count;
} Database;

Database* db_create(const char* filename);
int db_load(Database* db);
int db_save(Database* db);
int db_add(Database* db, const char* code, const char* name);
int db_delete(Database* db, const char* code);
const char* db_find(Database* db, const char* code);
void db_destroy(Database* db);
int db_get_count(Database* db);
