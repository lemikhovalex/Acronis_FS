//
// Created by lemikhovalex on 28.11.2019.
//

#include <stdint.h>
#define MAX_SIZE 5 // care full, only 2n -1 kind of value
#define TEST_SIZE 401
typedef struct Node *btree;

//data structure
struct Data
{
    uint64_t key;
    uint64_t value;
};

//node structure
struct Node
{
    int size;
    int is_leaf;
    struct Data data[MAX_SIZE + 1]; // dont ask why, just read how 'insert' works
    btree child[MAX_SIZE + 2]; // dont ask why, just read how 'insert' works
};

btree init_BTree(void);
void free_BTree(btree t);
uint64_t B_tree_search(btree t, uint64_t key);
void B_tree_insert(btree t, struct Data elem);
void B_tree_delete(btree t, uint64_t key);
void get_number_of_elems(btree, uint64_t*);
btree merge(btree, btree);
