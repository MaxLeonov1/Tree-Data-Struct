#include <stdio.h>
#include <time.h>

#include "tree.h"



int main() {

    TREE_INIT(tree_1)

    TreeCtor(&tree_1);

    FillTree(&tree_1);
    TreeDump(&tree_1, TreeErr_t::MEM_ALLOC_ERR );
    CheckSortTime(&tree_1);


    TreeDtor(&tree_1);

    return 0;
}



void FillTree ( Tree_t* tree ) {

    const size_t test_elem_num = 1000;

    for ( size_t idx = 0; idx < test_elem_num; idx++ ) {

        double rand_num = (double)(rand() % test_elem_num);
        InsertNode ( tree, rand_num );

    }

}



void CheckSortTime ( Tree_t* tree ) {

    time_t start = 0, end = 0;
    double delta = 0;

    time(&start);
    SortTree(tree->root);
    time(&end);

    delta = difftime(start, end);
    printf("[SORT TIME]:%lf\n", delta);

}


 
void SortTree ( TreeNode_t* node ) {

    if (node->left != nullptr)
        SortTree (node->left);

    printf("%lf\n", node->data);

    if (node->right != nullptr)
        SortTree (node->right);

}