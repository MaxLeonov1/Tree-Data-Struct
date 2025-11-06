#include <stdio.h>

#include "tree.h"



int main() {

    TREE_INIT( tree_1 )

    TreeCtor ( &tree_1 );

    InsertNode( &tree_1, "15_str" );
    InsertNode( &tree_1, "10_str" );
    InsertNode( &tree_1, "20_str" );
    InsertNode( &tree_1, "10_str" );
    InsertNode( &tree_1, "8_str" );
    InsertNode( &tree_1, "25_str" );
    InsertNode( &tree_1, "12_str" );
    InsertNode( &tree_1, "18_str" );

    TreeDump( &tree_1, TreeErr_t::MEM_ALLOC_ERR );

    TreeDtor(&tree_1);

    return 0;
}
 