#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

#include "akinator.h"
#include "tree.h"
#include "../utils/colors.h"
#include "../utils/sup_func.h"
#include "../stk_lib/stack.h"

#pragma GCC diagnostic ignored "-Wformat=2"
#pragma GCC diagnostic ignored "-Wformat-overflow"
#pragma GCC diagnostic ignored "-Wformat-truncation"

/*=====================================================================================*/

TreeErr_t AddNewSubject ( TreeNode_t* node, char* name, char* question ) {

    assert(node);
    _OK_STAT_

    status = InsertNode( &node->left, name, node );
    TREE_STAT_CHECK_
    status = InsertNode( &node->right, node->data, node );
    TREE_STAT_CHECK_

    if (node->is_alloc == 1)
        free(node->data);
    
    node->data = my_strdup(question);
    node->is_alloc = 1;
    if (!node->data) return TreeErr_t::MEM_ALLOC_ERR;

    _RET_OK_

}

/*=====================================================================================*/

TreeErr_t GuessSubject ( Tree_t* tree ) {

    assert(tree);
    _OK_STAT_

    TreeNode_t* parent = tree->root;
    int is_cor = _yes_;

    while (1) {
    
        if ( parent->left && parent->right ) {

            AskAboutSubject( parent->data, &is_cor );

            if ( is_cor == _yes_ )
                parent = parent->left;
            else
                parent = parent->right;
            
        } else {

            char wished[MAX_STR_LEN_] = "";
            char chartic[MAX_STR_LEN_] = "";

            AskIfCorrect (parent, &is_cor, wished, chartic);

            if ( is_cor == _no_ ) {
                AddNewSubject (parent, wished, chartic);
                printf("%sI will remember it's for next time:)%s\n", BLUE, RES_COL);
            }
            _RET_OK_

        }
    } 

    _RET_OK_

}

/*=====================================================================================*/

void AskAboutSubject ( char* data, int* is_cor ) {

    assert(data);
    assert(is_cor);

    while(1) {
        char resp[MAX_STR_LEN_] = "";
        printf( "%sIs your subject %s%s%s? [answer yes or no]\n%s", BLUE, GREEN, data, BLUE, RES_COL);
        scanf( "%s", resp );

        if ( resp[0] == 'y' ) {
            *is_cor = _yes_;
            break;
        }
        if ( resp[0] == 'n' ) {
            *is_cor = _no_;
            break;
        }

        printf( "%sWhat is it? I asked to type yes or no!\n%s", RED, RES_COL );

    }

}

/*=====================================================================================*/

void AskIfCorrect ( TreeNode_t* node, int* is_cor, char* wished, char* question ) {

    assert(node);
    assert(wished);
    assert(question);

    while(1) {

        char resp[MAX_STR_LEN_] = "";
        printf( 
            "%sYou have thought of %s%s%s? [answer yes or no]\n%s",
            BLUE, GREEN, node->data, BLUE, RES_COL );
        scanf( "%s", resp );

        if ( resp[0] == 'y' ) {
            *is_cor = _yes_;
            printf( "%sHah, I knew it!\n%s", BLUE, RES_COL );
            break;
        }
        if ( resp[0] == 'n' ) {
            *is_cor = _no_;
            printf( 
                "%sIt's a shame:(\n"
                "May I know what you wished? [type what you thought of]\n%s",
                BLUE, RES_COL
            );
            scanf( " %[^\n]", wished );
            printf(
                "%sCan you write how it differs from %s%s%s? [write in form \"It is ...\"]%s\n",
                BLUE, GREEN, node->data, BLUE, RES_COL
            );
            scanf( " %[^\n]", question );
            break;
        }

        printf( "%sWhat is it? I asked to type yes or no!\n%s", RED, RES_COL );

    }

}

/*=====================================================================================*/
/*=====================================================================================*/

void CompareSubject ( Tree_t* tree ) {

    assert(tree);

    STK_INIT(node_path)
    StackCtor(&node_path, 4);
    char sub[MAX_STR_LEN_] = "";

    printf("%sType searching subject\n%s", BLUE, RES_COL);
    scanf(" %[^\n]", sub);
    u_int sub_hash = djb2hash(sub);
    
    int is_found = FindSubjects(tree->root, sub_hash, &node_path);

    if ( is_found == 0 )
        printf(
            "%sThere is no %s%s%s in base\n%s",
             BLUE, GREEN, sub, BLUE, RES_COL
            );
    else {

        STK_ELM_TYPE stk_node = nullptr;
        STK_ELM_TYPE stk_prev_node = nullptr;
        StackPop(&node_path, &stk_prev_node);
        TreeNode_t* prev_node = (TreeNode_t*)stk_prev_node;

        printf("%s%s%s is ",GREEN, sub, BLUE);

        int char_cnt = 0;

        while (node_path.size > 0) {

            StackPop(&node_path, &stk_node);
            TreeNode_t* node = (TreeNode_t*)stk_node;

            if (char_cnt>0) printf("and also ");

            if (prev_node->left == node)
                printf("%s ", prev_node->data);
            if (prev_node->right == node)
                printf("not %s ", prev_node->data);

            char_cnt++;
            prev_node = node;
        }
        printf("%s\n", RES_COL);
    }

    StackDtor(&node_path);
}

/*=====================================================================================*/

int FindSubjects ( TreeNode_t* node, u_int sub_hash, Stack_t* node_path) {

    assert(node);
    int is_found = 0;


    if (sub_hash == node->data_hash) {
        StackPush(node_path, node);
        is_found++;
    }

    if(node->left) {
        is_found = FindSubjects(node->left, sub_hash, node_path);
        if (is_found) {
            StackPush(node_path, node);
            return is_found;
        }
    }
    if(node->right) {
        is_found = FindSubjects(node->right, sub_hash, node_path);
        if (is_found) {
            StackPush(node_path, node);
            return is_found;
        }
    }

    return is_found;
}

/*=====================================================================================*/

#define DESTR_AND_RET_            \
    StackDtor(subj_1.node_path);  \
    StackDtor(subj_2.node_path);  \
    return;

void FindDifference ( Tree_t* tree ) {

    assert(tree);

    Subj_t subj_1;
    Subj_t subj_2;
    STK_INIT(node_path_1)
    STK_INIT(node_path_2)
    subj_1.node_path = &node_path_1;
    subj_2.node_path = &node_path_2;
    StackCtor(subj_1.node_path, 4);
    StackCtor(subj_2.node_path, 4);
    
    u_int sub_hash_1 = 0;
    u_int sub_hash_2 = 0;
    int is_found = 0;

    is_found = FindPath(tree, &sub_hash_1, subj_1.node_path, "Type first subject");
    if(!is_found) {
        DESTR_AND_RET_
    }
    is_found = FindPath(tree, &sub_hash_2, subj_2.node_path, "Type second subject");
    if(!is_found) {
        DESTR_AND_RET_
    }

    if (sub_hash_1 == sub_hash_2)
        printf("%sYou type similar objects\n%s", BLUE, RES_COL);

    int is_diff = 0;
    PrintSimmular( &subj_1, &subj_2, &is_diff );

    if (is_diff) {
        PrintDifference( &subj_1, "The first differnt in being: " );
        PrintDifference( &subj_2, "The second differnt in being: " );
    }

    DESTR_AND_RET_
}

#undef DESTR_AND_RET_

/*=====================================================================================*/

void PrintSimmular ( Subj_t* subj_1, Subj_t* subj_2, int* is_diff ) {

    int sim_cnt = 0;

    StackPop(subj_1->node_path, &subj_1->prev_node);
    StackPop(subj_2->node_path, &subj_2->prev_node);

    printf("%sThey simmular in being: %s", BLUE, GREEN );
    while (subj_1->node_path->size>0 || subj_2->node_path->size>0 && !is_diff) {

        StackPop(subj_1->node_path, &subj_1->node);
        StackPop(subj_2->node_path, &subj_2->node);

        if (subj_1->node != subj_2->node) {

            *is_diff = 1;
            if (sim_cnt == 0) printf("%snothing%s", RED, RES_COL);
            break;
        } else {

            if (sim_cnt > 0) printf("and also ");

            if (subj_1->prev_node->left == subj_1->node)
                printf("%s ", subj_1->prev_node->data);
            if (subj_1->prev_node->right == subj_2->node)
                printf("not %s ", subj_1->prev_node->data);
            sim_cnt++;
        }
        subj_1->prev_node = subj_1->node;
        subj_2->prev_node = subj_2->node;
    }
    printf("%s\n", RES_COL);

}

/*=====================================================================================*/

void PrintDifference ( Subj_t* subj, const char* mes ) {

    int diff_cnt = 0;

    printf("%s%s%s", BLUE, mes, GREEN);
    while (subj->node_path->size>=0) {

        if (diff_cnt > 0) printf("and also ");

        if (subj->prev_node->left == subj->node)
            printf("%s ", subj->prev_node->data);
        if (subj->prev_node->right == subj->node)
            printf("not %s ", subj->prev_node->data);

        diff_cnt++;

        if (subj->node_path->size != 0) {
            subj->prev_node = subj->node;
            StackPop(subj->node_path, &subj->node);
        } else break;
    }
    printf("%s\n", RES_COL);

}

/*=====================================================================================*/

int FindPath ( Tree_t* tree, u_int* sub_hash, Stack_t* node_path, const char* mes) {

    char sub[MAX_STR_LEN_] = "";

    printf("%s%s\n%s", BLUE, mes, RES_COL);
    scanf(" %[^\n]", sub);
    *sub_hash = djb2hash(sub);

    int is_found = FindSubjects(tree->root, *sub_hash, node_path);

    if ( is_found == 0 )
        printf("%sThere is no %s%s%s in base\n%s", BLUE, GREEN, sub, BLUE, RES_COL);

    return is_found;
}

/*=====================================================================================*/
