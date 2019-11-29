//
// Created by lemikhovalex on 28.11.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b-tree.h"

btree init_BTree(void)
/* firstly let's create tree */
{
    btree b = (btree) malloc(sizeof(*b));
    // if it is created firstly - it is a leaf, empty leaf
    b->is_leaf = 1;
    b->size = 0;
    return b;
}


void free_BTree(btree b)
/* if i made it, i can kill it
 * of courese destroy not only one nide, but all of them recursively */
{
    if (!(b->is_leaf))
    /* if there are more nodes, let's make them free */
    {
        for (int i = 0; i < b->size + 1; i++)
        {
            free_BTree(b->child[i]);
        }
    }
    /*let's free dad */
    free (b);
}


int array_searchhigh_key(int size, const struct Data *array, uint64_t key)
// in array of fixed size we need to find key with binary search in already sorted array
{
    int a  = -1;
    int b = 0;
    int c = size;
    // classics
    while (a + 1 < c) {
        b = (a + c) / 2;
        if (array[b].key == key)
            return b;
        else if (array[b].key < key)
            a = b;
        else
            c = b;
    }

    return c;
}


static btree btree_insert(btree b, struct Data elem, struct Data *median)
// whoo, inserting
{
    // calulating position to insert
    int position = array_searchhigh_key(b->size, b->data, elem.key);

    if (position < b->size && b->data[position].key == elem.key)
    // the simpliest case - there is already such element in tree
    {
        b->data[position] = elem;
        return NULL;
    }

    // for better understanding follow points
    if (b->is_leaf)
    // 1) no way, we got a leaf, let's just add to data, about overflow later
    {
        memmove(&b->data[position + 1], &b->data[position], sizeof(struct Data) * (b->size - position));
        b->data[position] = elem;
        b->size++;
    }
    else
    // 6) wait, if we are not in leaf
    {
        struct Data child_median;
        // no way, insert to child
        // b->child[position] due to algorithm
        btree B_tree_child = btree_insert(b->child[position], elem, &child_median);

        if (B_tree_child)
        // if it goes down and we have a separated tree by point (3)
        {
            // we just insert median into our node as median
            memmove(&b->data[position + 1], &b->data[position], sizeof(struct Data) * (b->size - position));
            b->data[position] = child_median;
            // and creating child for this median
            memmove(&b->child[position + 2], &b->child[position + 1], sizeof(struct Node) * (b->size - position));
            b->child[position + 1] = B_tree_child;
            // ok finally dont forget to take into account that there is a new child
            b->size++;
            // now our tree is ready to be checked for over size, go to point (3)
        }
    }

    if (b->size >= MAX_SIZE)
    // 3) if we are oversize
    {
        // creating new node
        btree b_new = (btree) malloc(sizeof(struct Node));
        // median value is special one, it is to be returned
        int mid = b->size / 2;
        *median = b->data[mid];
        // new node
        b_new->size = b->size - mid - 1;
        // shorting node, data we ignore will be passed to new node
        b->size = mid;
        b_new->is_leaf = b->is_leaf;
        // data from old node to new one
        memmove(b_new->data, &b->data[mid + 1], sizeof(struct Data) * b_new->size);

        if (!(b->is_leaf))
        // if not leaf we shold copy not only data, but childre too
        {
            memmove(b_new->child, &b->child[mid + 1], sizeof(btree) * (b_new->size + 1));
        }

        // passing new node. next point is in other function
        return b_new;
    } else
    // 2 if we are not over sized let's go do nothing and this is the end
    {
        return NULL;
    }
}

void B_tree_insert(btree b, struct Data elem)
/* if we got a tree, let's put smth in! */
{
    // data-struct for data we want to insert
    struct Data median;
    // wow, we need to insert in only one direction(not like binary tree), so may be there is no direction
    btree b_new = btree_insert(b, elem, &median);
    // so we got a
    if (b_new)
    // 5) we got a new tree with data to be reconstructed. we need to unite them
    {
        // we copy data to new tree
        btree b_final = (btree) malloc(sizeof(*b_final));
        memmove(b_final, b, sizeof(*b));

        // and now final has 2 children
        b->size = 1;
        b->is_leaf = 0;
        // and median value to the top
        b->data[0] = median;
        b->child[0] = b_final;
        b->child[1] = b_new;
    }
}


uint64_t B_tree_search(btree b, uint64_t key)
// seems to be easy.
{

    if (b->size == 0)
    //empty tree doestn seems to be good
    {
        printf("no data in tree\n");
        return -1;
    }

    // search for position
    int position = array_searchhigh_key(b->size, b->data, key);
    //if key is founded
    if (position < b->size && b->data[position].key == key)
    {
        return b->data[position].value;
    } else if (b->is_leaf)
    // we need to go down, but can we?
    {
        return -1;
    }
    // if we can let's go down
    return B_tree_search(b->child[position], key);
}


void B_tree_delete(btree b, uint64_t key)
//if we only have to insert del marker, ok
{
    struct Data elem;
    elem.key = key; elem.value = -1;
    B_tree_insert(b, elem);
}
