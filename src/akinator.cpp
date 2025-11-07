#include <stdlib.h>
#include <assert.h>

#include "akinator.h"
#include "tree.h"



TreeErr_t AddNewSubject ( subject_t* sub ) {

    assert(sub);
    assert(sub->node);
    _OK_STAT_

    status = AllocNode( &sub->node->left );
    status = AllocNode( &sub->node->right );
    TREE_STAT_CHECK_

    if ( sub->branch == _yes_ ) {
        sub->node->left->data = sub->name;
        sub->node->right->data = sub->node->data;
        sub->node->data = sub->chartic;
    } else {
        sub->node->right->data = sub->name;
        sub->node->left->data = sub->node->data;
        sub->node->data = sub->chartic;
    }

    return TreeErr_t::TREE_OK;

}



TreeErr_t FindSubject ( Tree_t* tree ) {

    assert(tree);
    _OK_STAT_

    TreeNode_t* parent = tree->root;
    TreeNode_t* child = tree->root;

    do {

        subject_t sub;
        sub.node = parent;
        sub.name = parent->data;
    
        if ( parent->left && parent->right ) {


            
        } else {

            AskIfCorrect ( &sub );

        }

    } while ( 
        parent->left != nullptr || 
        parent->right != nullptr 
    );

}



void AskAboutSubject ( subject_t* sub ) {



}



void AskIfCorrect ( subject_t* sub ) {

    assert(sub);

    while(1) {
        const char* resp = nullptr;
        printf( "You have thought of %s? [answer yes or no]\n", sub->name );
        scanf( "%s", resp );

        if ( resp[0] == 'y' )
            printf( "Hah, I knew it!\n" );
            break;

        if ( resp[0] == 'n' ) {
            printf( 
                "It's a shame:(\n"
                "May I know what you wished? [type what you thought of]\n"
            );
            scanf( "%s", sub->name );
            printf(
                "Can you write how it differs from the one I proposed? [write in form \"It is ...\"]\n"
            );
            scanf( "%s", sub->chartic );

            AddNewSubject(sub);
            break;
        }

        printf( "What is it? I asked to type yes or no!\n" );

    }

}