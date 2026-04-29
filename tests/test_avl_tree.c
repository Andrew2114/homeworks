#include "../src/avl_tree.h"
#include "test_utils.h"

TEST(test_avl_insert_and_find) {
    Node* root = NULL;
    root = avl_insert(root, "SVO", "Sheremetyevo");
    root = avl_insert(root, "JFK", "Kennedy");
    root = avl_insert(root, "LED", "Pulkovo");
    
    Node* found = avl_find(root, "SVO");
    ASSERT(found != NULL);
    ASSERT_STR_EQ("SVO", found->code);
    ASSERT_STR_EQ("Sheremetyevo", found->name);
    
    found = avl_find(root, "ZZZ");
    ASSERT(found == NULL);
    
    avl_free(root);
}

TEST(test_avl_delete) {
    Node* root = NULL;
    root = avl_insert(root, "SVO", "Sheremetyevo");
    root = avl_insert(root, "JFK", "Kennedy");
    root = avl_insert(root, "LED", "Pulkovo");
    
    root = avl_delete(root, "JFK");
    ASSERT(avl_find(root, "JFK") == NULL);
    ASSERT(avl_find(root, "SVO") != NULL);
    ASSERT(avl_find(root, "LED") != NULL);
    ASSERT(avl_count(root) == 2);
    
    avl_free(root);
}

TEST(test_avl_count) {
    Node* root = NULL;
    ASSERT(avl_count(root) == 0);
    
    root = avl_insert(root, "A", "Airport A");
    root = avl_insert(root, "B", "Airport B");
    root = avl_insert(root, "C", "Airport C");
    ASSERT(avl_count(root) == 3);
    
    avl_free(root);
}

TEST(test_avl_contains) {
    Node* root = NULL;
    root = avl_insert(root, "SVO", "Sheremetyevo");
    
    ASSERT(avl_contains(root, "SVO") == 1);
    ASSERT(avl_contains(root, "JFK") == 0);
    
    avl_free(root);
}
