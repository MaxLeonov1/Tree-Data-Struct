#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*-----------------------------------------------------------------------------------------------*/

#include "stack.h"

/*-----------------------------------------------------------------------------------------------*/

ErrorCode StackCtor ( Stack_t* stack, size_t capacity ) {

    assert ( stack != nullptr );

    stack->capacity = capacity;
    stack->size = 0;
    stack->data = (STK_ELM_TYPE*) calloc ( capacity, sizeof(STK_ELM_TYPE) );

    ERR_HANDL_PRINT ( stack );

    _RET_STK_OK_

}

/*-----------------------------------------------------------------------------------------------*/

ErrorCode StackPush ( Stack_t* stack, STK_ELM_TYPE value ) {

    //printf("sus\n");

    assert(stack);

    ERR_HANDL_PRINT ( stack );

    if ( stack->size >= stack->capacity - 2 ) StackAllocation ( stack );

    stack->data[stack->size++] = value;

    //printf("%ld %ld\n", ControlSumCount(stack), stack->sum_elm_check);

    ERR_HANDL_PRINT ( stack );

    _RET_STK_OK_

}

/*-----------------------------------------------------------------------------------------------*/

ErrorCode StackPop ( Stack_t* stack, STK_ELM_TYPE* value ) {

    assert(stack);

    ERR_HANDL_PRINT ( stack ) ;

    if (value) *value = stack->data[stack->size - 1];
    stack->size--; 

    ERR_HANDL_PRINT ( stack ) ;

    _RET_STK_OK_

}

/*-----------------------------------------------------------------------------------------------*/

ErrorCode StackDtor ( Stack_t* stack ) {

    assert(stack);

    stack->capacity = 0;
    stack->size = 0;
    
    free ( stack->data );
    stack->data = nullptr;

    _RET_STK_OK_

}

/*-----------------------------------------------------------------------------------------------*/

ErrorCode StackAllocation ( Stack_t* stack ) {

    stack->data = (STK_ELM_TYPE*) realloc ( stack->data, ( stack->capacity*2 + 2 ) * sizeof(STK_ELM_TYPE) );

    ERR_HANDL_PRINT ( stack );

    stack->capacity = stack->capacity*2;

    _RET_STK_OK_

}

/*-----------------------------------------------------------------------------------------------*/