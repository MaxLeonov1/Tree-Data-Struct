#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "akinator.h"
#include "sup_func.h"



int main() {

    TREE_INIT(tree_1)

    TreeCtor(&tree_1);

    InsertNode(&tree_1.root, "animal", tree_1.root);
    InsertNodeAfter(tree_1.root, "cat", _left_);
    InsertNodeAfter(tree_1.root, "teaching matan", _right_);
    InsertNodeAfter(tree_1.root->right, "prof", _right_);
    InsertNodeAfter(tree_1.root->right, "student", _left_);

    //TreeDump( &tree_1, TreeErr_t::TREE_OK, NULL );
    
    // GuessSubject(&tree_1);
    // FindSubject(&tree_1);

    //TreeDump( &tree_1, TreeErr_t::TREE_OK, "[%s]", "aboba prime" );

    SaveToDisk( &tree_1, NULL );

    TreeDtor(&tree_1);

    return 0;
}
 