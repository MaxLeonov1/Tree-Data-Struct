#pragma once

#include "stdlib.h"

#include "tree.h"
#include "../stk_lib/stack.h"
#include "../utils/sup_func.h"

/*=====================================================================================*/

#define _yes_ 0
#define _no_ 1

/*=====================================================================================*/

typedef struct {

    Stack_t* node_path = nullptr;
    TreeNode_t* node = nullptr;
    TreeNode_t* prev_node = nullptr;

} Subj_t;

/*=====================================================================================*/

void      AskAboutSubject ( char* data, int* is_cor );
void      AskIfCorrect    ( TreeNode_t* node, int* is_cor, char* wished, char* question );
TreeErr_t GuessSubject    ( Tree_t* tree );
void      CompareSubject  ( Tree_t* tree );
void      FindDifference  ( Tree_t* tree );
TreeErr_t AddNewSubject   ( TreeNode_t* node, char* name, char* question );
int       FindSubjects    ( TreeNode_t* node, u_int sub_hash, Stack_t* node_path);
void      PrintDifference ( Subj_t* subj, const char* mes );
int       FindPath        ( Tree_t* tree, u_int* sub_hash, Stack_t* node_path, const char* mes );
void      PrintSimmular   ( Subj_t* subj_1, Subj_t* subj_2, int* is_diff );
