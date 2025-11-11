#pragma once

#include "stdlib.h"

#include "tree.h"

//======================================================

#define _yes_ 0
#define _no_ 1

//======================================================

void      AskAboutSubject ( char* data, int* is_cor );
void      AskIfCorrect    ( TreeNode_t* node, int* is_cor, char* wished, char* question );
TreeErr_t GuessSubject    ( Tree_t* tree );
void      FindSubject     ( Tree_t* tree );
TreeErr_t AddNewSubject   ( TreeNode_t* node, char* name, char* question );
void      CompareSubjects ( TreeNode_t* node, unsigned int sub_hash, TreeNode_t** found_node );
