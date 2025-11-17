#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------------------------*/

#include "stack.h"
#include "../utils/colors.h"

/*-----------------------------------------------------------------------------------------------*/

void StackDump ( Stack_t* stack ) {

    #ifdef _DEBUG

    //printf("sus\n");

    printf ( "-------------------------\n"
             "stack [%p] %s::line %d\n"
             "-------------------------\n"
             "size = %lu\n"
             "capacity = %lu\n"
             "data [%p]\n"
             "-------------------------\n",
             stack, stack->file_name, stack->line_num, stack->size, stack->capacity, stack->data );

    #endif

    if ( stack->data != nullptr ) {

        PrintStackElements ( stack );

    }

    #ifdef DEBUG
    printf ( "-------------------------\n" );
    #endif

}

/*-----------------------------------------------------------------------------------------------*/

void PrintStackElements ( Stack_t* stack ) {

    for ( size_t ind = 0; ind < stack->capacity; ind++) {

        if ( ind < stack->size ) {

            printf ( "* [%lu] = %s%p%s\n", 
                     ind,
                     BLUE, stack->data[ind], RES_COL);

        } else {

            printf ( "  [%lu] = %s%p%s\n",
                     ind,
                     BLUE, stack->data[ind], RES_COL);

        }
            
    }

}

/*-----------------------------------------------------------------------------------------------*/

ErrorCode StackErrorHandler ( Stack_t* stack, bool is_dump ) {

    if ( stack->data == nullptr ) {

        if ( is_dump ) StackDump ( stack );
        return ErrorCode::STACK_ALLOCATION_ERROR;

    }

    if ( stack->capacity <= 0 ) {

        if ( is_dump ) StackDump ( stack );
        return ErrorCode::ZERO_CAPACITY_ERROR;

    }

    if ( stack->size < 0 ) {

        if ( is_dump ) StackDump ( stack );
        return ErrorCode::ZERO_SIZE_ERROR;


    }

    _RET_STK_OK_

}

/*-----------------------------------------------------------------------------------------------*/