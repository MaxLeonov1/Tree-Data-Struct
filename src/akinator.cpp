#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "akinator.h"
#include "tree.h"
#include "sup_func.h"

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

    free(node->data);
    node->data = strdup(question);
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

            if ( is_cor == _no_ )
                AddNewSubject (parent, wished, chartic);
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
        char resp[MAX_STR_LEN_] = {0};
        printf( "Is your subject %s? [answer yes or no]\n", data );
        scanf( "%s", resp );

        if ( resp[0] == 'y' ) {
            *is_cor = _yes_;
            break;
        }
        if ( resp[0] == 'n' ) {
            *is_cor = _no_;
            break;
        }

        printf( "What is it? I asked to type yes or no!\n" );

    }

}

/*=====================================================================================*/

void AskIfCorrect ( TreeNode_t* node, int* is_cor, char* wished, char* question ) {

    assert(node);
    assert(wished);
    assert(question);

    while(1) {

        char resp[MAX_STR_LEN_] = {0};
        printf( "You have thought of %s? [answer yes or no]\n", node->data );
        scanf( "%s", resp );

        if ( resp[0] == 'y' ) {
            *is_cor = _yes_;
            printf( "Hah, I knew it!\n" );
            break;
        }
        if ( resp[0] == 'n' ) {
            *is_cor = _no_;
            printf( 
                "It's a shame:(\n"
                "May I know what you wished? [type what you thought of]\n"
            );
            scanf( " %[^\n]", wished );
            printf(
                "Can you write how it differs from %s? [write in form \"It is ...\"]\n",
                node->data
            );
            scanf( " %[^\n]", question );
            break;
        }

        printf( "What is it? I asked to type yes or no!\n" );

    }

}

/*=====================================================================================*/

void FindSubject ( Tree_t* tree ) {

    assert(tree);
    char sub[MAX_STR_LEN_] = {0};

    printf("Type searching subject\n");
    scanf(" %[^\n]", sub);

    unsigned int sub_hash = djb2hash(sub);
    TreeNode_t* found_node = nullptr;
    printf("%u\n", sub_hash);
    
    CompareSubjects(tree->root, sub_hash, &found_node);

    if ( found_node == nullptr )
        printf("There is no %s in base\n", sub);
    else {
        TreeNode_t* parent = found_node->parent;
        printf("%s can be defined as:\n", sub);

        while ( parent != nullptr ) {

            printf("%s\n", parent->data);
            // if (parent->parent->left == parent)
            //     printf("%s\n", parent->data);
            // if (parent->parent->right == parent)
            //     printf("not %s\n", parent->data);

            parent = parent->parent;
        }
    }

}

/*=====================================================================================*/

void CompareSubjects ( TreeNode_t* node, unsigned int sub_hash, TreeNode_t** found_node ) {

    assert(node);

    static int is_found = 0;

    if(node->left)
        CompareSubjects(node->left, sub_hash, found_node);
    if(node->right)
        CompareSubjects(node->right, sub_hash, found_node);

    if ( sub_hash == node->data_hash ) {
        *found_node = node;
    }

}

/*=====================================================================================*/