#include <stdio.h>

#include "tree.h"



int main() {

    TREE_INIT( tree_1 )

    TreeCtor ( &tree_1 );

    InsertNode( &tree_1, 15 );
    InsertNode( &tree_1, 10 );
    InsertNode( &tree_1, 20 );
    InsertNode( &tree_1, 10 );
    InsertNode( &tree_1, 8 );
    InsertNode( &tree_1, 25 );
    InsertNode( &tree_1, 12 );
    InsertNode( &tree_1, 18 );

    TreeDump( &tree_1, TreeErr_t::TREE_OK );

    TreeDtor(&tree_1);

    return 0;
}
 