#include <stdio.h>
#include <stdlib.h>



typedef double TreeElem_t;
typedef struct TreeNode TreeNode_t;
typedef struct Tree Tree_t;

struct TreeNode {

    TreeElem_t  data;
    TreeNode_t* left;
    TreeNode_t* right;

};

struct Tree {

    TreeNode_t node_0;

    size_t cpcty;

};

#define TREE_INIT(name) Tree_t name = { {0, nullptr, nullptr}, 0 };

void TreeCtor ( Tree_t* tree );
