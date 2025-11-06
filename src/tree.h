#pragma once
#include <stdio.h>
#include <stdlib.h>

#define _DEBUG

/*=====================================================================================*/

typedef double TreeElem_t;
typedef struct TreeNode TreeNode_t;
typedef struct Tree Tree_t;
typedef struct TreeDebugInfo TreeDebugInfo_t;

/*=====================================================================================*/

struct TreeDebugInfo {

    const char* name;
    const char* func;
    const char* file;
    const int line;

};

struct TreeNode {

    TreeElem_t  data;
    TreeNode_t* left;
    TreeNode_t* right;

};

struct Tree {

    #ifdef _DEBUG
    TreeDebugInfo_t info;
    #endif

    TreeNode_t* root;

    size_t cpcty;

};

/*=====================================================================================*/

typedef enum {

    TREE_OK = 0,
    MEM_ALLOC_ERR = 1,

} TreeErr_t;

/*=====================================================================================*/

void      TreeCtor   ( Tree_t* tree );
void      TreeDtor   ( Tree_t* tree );
TreeErr_t AllocNode  ( TreeNode_t** node );
TreeErr_t DeleteNode ( TreeNode* node );
TreeErr_t InsertNode ( Tree_t* tree, TreeElem_t elem );

const char* StatusCodeToStr ( TreeErr_t status );
void TreeDump       ( Tree_t* tree, TreeErr_t status );
void PrintLogHeader ( Tree_t* tree, FILE* log_file, TreeErr_t status );
int  PrintGraphNodes( TreeNode_t* node, int rank, FILE* graph_text );
void CreateGraphImg ( Tree_t* tree, const char* graphname, const char* graph_dir );

/*=====================================================================================*/

#define FILE_MODE_ 0755
#define MAX_STR_LEN_ 500

#define EDGE_STD_SET_ "penwidth = 2.0, arrowsize = 0.5, constraint = \"true\""

/*=====================================================================================*/

#ifndef _DEBUG
#define TREE_INIT(name) Tree_t name = { nullptr, 0 };
#else
#define TREE_INIT(name) Tree_t name = { {#name, __FUNCTION__, __FILE__, __LINE__}, nullptr, 0 };
#endif

#define TREE_STAT_CHECK_(tree_p, status)   \
    if ( status != TreeErr_t::TREE_OK ) {  \
        TreeDump(tree_p, status);          \
        return status;                     \
    }

/*=====================================================================================*/