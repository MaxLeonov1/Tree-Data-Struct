#include <stdlib.h>
#include <stdio.h>

#include "tree.h"



void TreeCtor ( Tree_t* tree ) {

    tree->node_0.data = 0;
    tree->node_0.left = nullptr;
    tree->node_0.right = nullptr;

    tree->cpcty = 1;

}

