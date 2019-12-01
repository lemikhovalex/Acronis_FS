#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "b-tree.h"

int main(int argc, char **argv)
{
    uint64_t test_size = TEST_SIZE;
    struct Data d;



    // creating tree
    /*
    btree b0 = init_BTree();
    d.key = 3; d.value = 3;
    B_tree_insert(b0, d);
    d.key = 6; d.value = 6;
    B_tree_insert(b0, d);
    d.key = 1; d.value = 1;
    B_tree_insert(b0, d);
    d.key = 2; d.value = 2;
    B_tree_insert(b0, d);
    d.key = 4; d.value = 4;
    B_tree_insert(b0, d);
    d.key = 5; d.value = 5;
    B_tree_insert(b0, d);
    d.key = 7; d.value = 7;
    B_tree_insert(b0, d);
    d.key = 8; d.value = 8;
    B_tree_insert(b0, d);
    d.key = 9; d.value = 9;
    B_tree_insert(b0, d);
    d.key = 10; d.value = 10;
    B_tree_insert(b0, d);

    uint64_t l0 = 0;
    get_number_of_elems(b0, &l0);
    printf("len of d1 = %lu\n", l0);



*/
    // creating smth to push

    btree b = init_BTree();
    printf("Ok now let's push a ton(%lu) of data to tree\n\n", test_size);
    for (uint64_t i = 1; i <= test_size; i++)
    {
        d.key = i;
        d.value = i*i;
        // printf("gonna push key  : %u\n", d.key);
        // printf("gonna push value: %u\n", d.value);
        B_tree_insert(b, d);
    }
    printf("We'v pushed a ton(%lu) of data to tree. Let's find each piece of data\n", test_size);
    int ok_flag = 0;
    for (uint64_t i = 1; i <= test_size; i++)
    {
        if(B_tree_search(b, i) == -1    )
        {
            printf("FUUUUU, cant find key %lu in tree\n", i);
            ok_flag = 1;
        }
    }
    if (ok_flag == 0)
    {
        printf("I found all i've inserted\n");
    }
    printf("Let's try to merge trees\n");

    btree b1 = init_BTree();
    btree b2 = init_BTree();

    for(uint64_t i = 1; i <= test_size; i ++)
    {
        d.key = i;
        d.value = i;
        B_tree_insert(b1, d);

        d.key = i + 2 * test_size;
        d.value = i + 100;
        B_tree_insert(b2, d);
    }

    //uint64_t l1 = 0;
    //get_number_of_elems(b1, &l1);
    //printf("len of d1 = %lu\n", l1);

    btree merged_tree = merge(b1, b2);

    printf("Merge done\n");
    // ok then let's check if we lost smth
    ok_flag = 0;
    for(uint64_t i = 1; i <= test_size; i ++)
    {
        if(B_tree_search(merged_tree, i) == -1)
        {
            printf("FUUUUU in MERGED, cant find key %lu in tree\n", i);
            ok_flag = 1;
        }

        if(B_tree_search(merged_tree, i + 2 * test_size) == -1)
        {
            printf("FUUUUU in MERGED, cant find key %lu in tree\n", i + 2 * test_size);
            ok_flag = 1;
        }
    }
    if (ok_flag == 0)
    {
        printf("I found all i've inserted in MERGEDED tree\n");
    }

    free_BTree(merged_tree);
    free_BTree(b1);
    free_BTree(b2);
    free_BTree(b);
    printf("Trees are freed\n");


    return 0;
}
