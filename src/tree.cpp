#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree.h"

/*=====================================================================================*/

void TreeCtor ( Tree_t* tree ) {

    assert(tree);

    tree->root = nullptr;
    tree->cpcty = 1;

}

/*=====================================================================================*/

void TreeDtor ( Tree_t* tree ) {

    assert(tree);
    DeleteNode(tree->root);

}

/*=====================================================================================*/

TreeErr_t AllocNode ( TreeNode_t** node ) {

    assert(node);

    TreeNode_t* node_ptr = (TreeNode_t*)calloc(1, sizeof(node_ptr[0]));
    if ( node_ptr == nullptr ) return TreeErr_t::MEM_ALLOC_ERR;

    *node = node_ptr;

    return TreeErr_t::TREE_OK;

}

/*=====================================================================================*/

TreeErr_t DeleteNode ( TreeNode* node ) {

    assert(node != nullptr);

    if (node->left != nullptr)
        DeleteNode (node->left);
    if (node->right != nullptr)
        DeleteNode (node->right);

    free(node);

    return TreeErr_t::TREE_OK;

}

/*=====================================================================================*/

TreeErr_t InsertNode ( Tree_t* tree, TreeElem_t elem ) {

    assert(tree);
    _OK_STAT_

    TreeNode_t* parent = tree->root;
    TreeNode_t* child = tree->root;

    while (child != nullptr) {
        parent = child;

        if (atoi(elem) <= atoi(parent->data))
            child = parent->left;
        else
            child = parent->right;
    }

    TreeNode_t* node = nullptr;
    status = AllocNode(&node);
    TREE_STAT_CHECK_ (tree, status);

    node->data = elem;

    if (parent == nullptr)
        tree->root = node;

    else {
        if (atoi(elem) <= atoi(parent->data))
            parent->left = node;
        else
            parent->right = node;
    }

    tree->cpcty++;

    return TreeErr_t::TREE_OK;

}

/*=====================================================================================*/

TreeErr_t PrintSort ( Tree_t* tree ) {



}