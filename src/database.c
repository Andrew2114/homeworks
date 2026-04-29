#include "database.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Database* db_create(const char* filename) {
    Database* db = malloc(sizeof(Database));
    if (!db) return NULL;
    
    db->root = NULL;
    db->count = 0;
    strcpy(db->filename, filename);
    
    return db;
}

int db_load(Database* db) {
    FILE* f = fopen(db->filename, "r");
    if (!f) return -1;
    
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        
        char* colon = strchr(line, ':');
        if (!colon) continue;
        
        *colon = '\0';
        char* code = line;
        char* name = colon + 1;
        
        trim(code);
        trim(name);
        
        if (is_valid_iata_code(code) && strlen(name) > 0) {
            db->root = avl_insert(db->root, code, name);
            db->count++;
        }
    }
    
    fclose(f);
    return 0;
}

int db_save(Database* db) {
    FILE* f = fopen(db->filename, "w");
    if (!f) return -1;
    
    avl_save(db->root, f);
    fclose(f);
    return 0;
}

int db_add(Database* db, const char* code, const char* name) {
    if (!is_valid_iata_code(code) || strlen(name) == 0) return -1;
    if (avl_contains(db->root, code)) return -2; 
    
    db->root = avl_insert(db->root, code, name);
    db->count++;
    return 0;
}

int db_delete(Database* db, const char* code) {
    if (!avl_contains(db->root, code)) return -1;
    
    db->root = avl_delete(db->root, code);
    db->count--;
    return 0;
}

const char* db_find(Database* db, const char* code) {
    Node* found = avl_find(db->root, code);
    return found ? found->name : NULL;
}

void db_destroy(Database* db) {
    if (!db) return;
    avl_free(db->root);
    free(db);
}

int db_get_count(Database* db) {
    return db->count;
}
