#include <stdio.h>

#include "tree.h"



int main() {

    TREE_INIT( tree_1 )

    TreeCtor ( &tree_1 );

    tree_1.node_0.data = 15;
    TreeNode_t node_1 = { 10, nullptr, nullptr };
    TreeNode_t node_2 = { 20, nullptr, nullptr };
    tree_1.node_0.left = &node_1;
    tree_1.node_0.right = &node_2;

    return 0;
}
 