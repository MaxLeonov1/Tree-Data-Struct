#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tree.h"

#pragma GCC diagnostic ignored "-Wformat=2"

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
    if ( !node_ptr ) return TreeErr_t::MEM_ALLOC_ERR;

    node_ptr->left = nullptr;
    node_ptr->right = nullptr;
    node_ptr->data = nullptr;    

    *node = node_ptr; 

    _RET_OK_

}

/*=====================================================================================*/

TreeErr_t DeleteNode ( TreeNode* node ) {

    assert(node != nullptr);

    if (node->left != nullptr)
        DeleteNode (node->left);
    if (node->right != nullptr)
        DeleteNode (node->right);

    free(node->data);
    free(node);

    _RET_OK_

}

/*=====================================================================================*/

TreeErr_t InsertNode ( TreeNode_t** node, TreeElem_t elem ) {

    assert(node);
    _OK_STAT_

    TreeNode_t* node_new = nullptr;
    status = AllocNode(&node_new);
    TREE_STAT_CHECK_
    node_new->data = strdup(elem);
    *node = node_new;

    _RET_OK_

}

/*=====================================================================================*/

TreeErr_t InsertNodeAfter ( TreeNode_t* node, TreeElem_t elem, int child ) {

    assert(node);
    _OK_STAT_

    if ( 
        node->left && child == _left_ ||
        node->right && child == _right_
    )
        return TreeErr_t::INSERT_EX_POS_ERR;

    if ( child == _left_ ) {
        status = InsertNode( &node->left, elem );
        TREE_STAT_CHECK_
    } else {
        status = InsertNode( &node->right, elem );
        TREE_STAT_CHECK_
    }     
    
    _RET_OK_

}

/*=====================================================================================*/

TreeErr_t SaveToDisk ( Tree_t* tree, const char* disk_name ) {

    assert(tree);

    if (disk_name == nullptr)
        disk_name = DEF_DISK_NAME_;

    FILE* disk = fopen( disk_name, "wb" );
    if (disk == nullptr) return TreeErr_t::FILE_OPEN_ERR;

    WriteToDisk(tree->root, disk);

    fclose(disk);

    _RET_OK_

}

/*=====================================================================================*/

void WriteToDisk ( TreeNode_t* node, FILE* disk ) {

    assert(node);
    assert(disk);

    fprintf(disk, "(%s", node->data);

    if (node->left)
        WriteToDisk(node->left, disk);
    if (node->right)
        WriteToDisk(node->right, disk);
        
    fprintf(disk, ")");

}