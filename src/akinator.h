#pragma once

#include "stdlib.h"

#include "tree.h"

//======================================================

#define _yes_ 0
#define _no_ 1

typedef struct {

    TreeNode_t* node = nullptr;

    const char* name = nullptr;
    const char* chartic = nullptr;
    int branch = _yes_;
    int ans = _yes_;

} subject_t;



void      AskAboutSubject ( subject_t* sub );
TreeErr_t FindSubject     ( Tree_t* tree );
TreeErr_t AddNewSubject   ( subject_t* sub );
TreeErr_t FindSubject     ( Tree_t* tree );
