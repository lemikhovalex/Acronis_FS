#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "b-tree.h"

int main(int argc, char **argv)
{
    uint64_t test_size = TEST_SIZE;
    // creating tree
    btree b = init_BTree();
    // creating smth to push
    struct Data d;

    printf("Ok now let's push a ton(%lu)(and a one in the very beginning) of data to tree\n\n", test_size);
    for (uint64_t i = 0; i < test_size; i++)
    {
        d.key = i;
        d.value = i*i;
        // printf("gonna push key  : %u\n", d.key);
        // printf("gonna push value: %u\n", d.value);
        B_tree_insert(b, d);
    }
    printf("We'v pushed a ton(%lu)(and a one in the very beginning) of data to tree. Let's find each piece of data\n", test_size);
    int ok_flag = 0;
    for (uint64_t i = 0; i < test_size; i++) {
        // printf("Gonna find key %u\n", i);
        if(B_tree_search(b, i) != i*i)
        {
            printf("FUUUUU, found find key %lu wrong in tree\n", i);
            ok_flag = 1;
        }
    }
    if (ok_flag == 0)
    {
        printf("Everything is alright\n");
    }
    uint64_t sum = 0;
    get_number_of_elems(b, &sum);
    printf("number of elements = %lu\n", sum);
    printf("Let's try to merge trees\n");

    btree b1 = init_BTree();
    btree b2 = init_BTree();

    for(uint64_t i = 0; i < test_size; i ++)
    {
        d.key = i;
        d.value = i;
        B_tree_insert(b1, d);

        d.key = i + test_size;
        d.value = i + 100;
        B_tree_insert(b2, d);
    }
    btree merged_tree = merge(b1, b2);

    free_BTree(merged_tree);
    printf("Merge is done\n");
    free_BTree(b1);
    free_BTree(b2);
    free_BTree(b);
    printf("Trees are freed\n");


    return 0;
}
