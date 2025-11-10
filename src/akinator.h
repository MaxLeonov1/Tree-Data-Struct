#pragma once

#include "stdlib.h"

#include "tree.h"

//======================================================

#define _yes_ 0
#define _no_ 1

//======================================================

void      AskAboutSubject ( char* data, int* is_cor );
void AskIfCorrect ( TreeNode_t* node, int* is_cor, char* wished, char* chartic );
TreeErr_t FindSubject     ( Tree_t* tree );
TreeErr_t AddNewSubject   ( TreeNode_t* node, char* name, char* chartic );
TreeErr_t FindSubject     ( Tree_t* tree );
