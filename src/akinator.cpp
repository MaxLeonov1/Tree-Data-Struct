#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "akinator.h"
#include "tree.h"

#pragma GCC diagnostic ignored "-Wformat=2"
#pragma GCC diagnostic ignored "-Wformat-overflow"
#pragma GCC diagnostic ignored "-Wformat-truncation"

/*=====================================================================================*/

TreeErr_t AddNewSubject ( TreeNode_t* node, char* name, char* chartic ) {

    assert(node);
    _OK_STAT_

    status = InsertNode( &node->left, name );
    TREE_STAT_CHECK_
    status = InsertNode( &node->right, node->data );
    TREE_STAT_CHECK_

    free(node->data);
    node->data = strdup(chartic);

    _RET_OK_

}

/*=====================================================================================*/

TreeErr_t FindSubject ( Tree_t* tree ) {

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

            char wished[MAX_STR_LEN_] = {0};
            char chartic[MAX_STR_LEN_] = {0};

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

void AskIfCorrect ( TreeNode_t* node, int* is_cor, char* wished, char* chartic ) {

    assert(node);
    assert(wished);
    assert(chartic);

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
                "Can you write how it differs from the one I proposed? [write in form \"It is ...\"]\n"
            );
            scanf( " %[^\n]", chartic );
            break;
        }

        printf( "What is it? I asked to type yes or no!\n" );

    }

}

/*=====================================================================================*/