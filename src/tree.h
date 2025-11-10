#pragma once
#include <stdio.h>
#include <stdlib.h>

#define _DEBUG

/*=====================================================================================*/

typedef char* TreeElem_t;
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
    INSERT_EX_POS_ERR = 2,
    FILE_OPEN_ERR = 3,

} TreeErr_t;

/*=====================================================================================*/

void      TreeCtor        ( Tree_t* tree );
void      TreeDtor        ( Tree_t* tree );
TreeErr_t AllocNode       ( TreeNode_t** node );
void      CreateLogDir    ( char* dir_name );
TreeErr_t DeleteNode      ( TreeNode* node );
TreeErr_t InsertNode      ( TreeNode_t** node, TreeElem_t elem );
TreeErr_t InsertNodeAfter ( TreeNode_t* node, TreeElem_t elem, int child );

TreeErr_t SaveToDisk  ( Tree_t* tree, const char* disk_name );
void      WriteToDisk ( TreeNode_t* node, FILE* disk );

const char* StatusCodeToStr ( TreeErr_t status );
void TreeDump       ( Tree_t* tree, TreeErr_t status );
void PrintLogHeader ( Tree_t* tree, FILE* log_file, TreeErr_t status );
int  PrintGraphNodes( TreeNode_t* node, int rank, FILE* graph_text );
void CreateGraphImg ( Tree_t* tree, const char* graphname, const char* graph_dir );

/*=====================================================================================*/

#define _left_ 0
#define _right_ 1

#define FILE_MODE_ 0755
#define MAX_STR_LEN_ 500

#define EDGE_STD_SET_ "penwidth = 2.0, arrowsize = 0.5, constraint = \"true\""
#define DEF_DISK_NAME_ "treedisk.bin"

/*=====================================================================================*/

#ifndef _DEBUG
    #define _IF_DEBUG(source)
    #define TREE_INIT(name) Tree_t name = { nullptr, 0 };
#else
    #define _IF_DEBUG(source) source
    #define TREE_INIT(name) Tree_t name = { {#name, __FUNCTION__, __FILE__, __LINE__}, nullptr, 0 };
#endif

#define _OK_STAT_ TreeErr_t status = TreeErr_t::TREE_OK;
#define _RET_OK_ return TreeErr_t::TREE_OK;

#define TREE_STAT_CHECK_DUMP_(tree_p, status)   \
    if ( status != TreeErr_t::TREE_OK ) {  \
        TreeDump(tree_p, status);          \
        return status;                     \
    }

#define TREE_STAT_CHECK_                              \
    if ( status != TreeErr_t::TREE_OK ) return status; \

/*=====================================================================================*/