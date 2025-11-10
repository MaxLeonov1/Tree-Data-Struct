#include <stdio.h>

#include "tree.h"
#include "akinator.h"



int main() {

    TREE_INIT(tree_1)

    TreeCtor(&tree_1);

    InsertNode(&tree_1.root, "animal");
    InsertNodeAfter(tree_1.root, "hooman", _left_);
    InsertNodeAfter(tree_1.root, "cat", _right_);

    FindSubject(&tree_1);

    TreeDump( &tree_1, TreeErr_t::MEM_ALLOC_ERR );

    SaveToDisk( &tree_1, NULL );

    TreeDtor(&tree_1);

    return 0;
}
 