#pragma once

#include <stdlib.h>

#include "../src/tree.h"

/*-------------------------------------------------------*/

typedef TreeNode_t* STK_ELM_TYPE;

/*-------------------------------------------------------*/

typedef struct {

    #ifdef _DEBUG

    int   line_num;
    char* file_name;
    char* stack_name;

    long sum_elm_check;

    #endif

    STK_ELM_TYPE* data;
    size_t        size;
    size_t        capacity;

} Stack_t;

/*-------------------------------------------------------*/

typedef enum {

    HANDLED_SUCCSESFULY = 0,  
    ZERO_CAPACITY_ERROR = 1,
    SIZE_OVERFLOW_ERROR = 2,
    STACK_ALLOCATION_ERROR = 3,
    ZERO_SIZE_ERROR = 4,
    INCORRECT_CONTROL_SUM_ERROR = 5,

} ErrorCode;

/*-------------------------------------------------------*/       

#ifdef _DEBUG 

#define ERR_HANDL_PRINT( stack ) \
    if ( StackErrorHandler( stack, false ) != HANDLED_SUCCSESFULY ) \
    return StackErrorHandler( stack, true )

#else

#define ERR_HANDL_PRINT( stack ) \
    if ( StackErrorHandler( stack, false ) != HANDLED_SUCCSESFULY ) \
    return StackErrorHandler( stack, false )

#endif

#ifdef _DEBUG

#define STK_INIT( name ) Stack_t name = { \
.line_num = __LINE__, \
.file_name = __FILE__, \
.stack_name = #name, \
.sum_elm_check = 0, \
.data = nullptr, \
.size = 0, \
.capacity = 0 };

#define STK_INIT_EXS( name ) name = { \
.line_num = __LINE__, \
.file_name = __FILE__, \
.stack_name = #name, \
.sum_elm_check = 0, \
.data = nullptr, \
.size = 0, \
.capacity = 0 };

#else

#define STK_INIT( name ) Stack_t name = { \
.data = nullptr, \
.size = 0, \
.capacity = 0 };                   

#define STK_INIT_EXS( name ) name = { \
.data = nullptr, \
.size = 0, \
.capacity = 0 };                   

#endif

#define _RET_STK_OK_ return ErrorCode::HANDLED_SUCCSESFULY;

/*-------------------------------------------------------*/

ErrorCode StackCtor       ( Stack_t* stack, size_t capacity );
ErrorCode StackPush       ( Stack_t* stack, STK_ELM_TYPE value );
ErrorCode StackPop        ( Stack_t* stack, STK_ELM_TYPE* value );
ErrorCode StackDtor       ( Stack_t* stack );
ErrorCode StackAllocation ( Stack_t* stack );

void      StackDump               ( Stack_t* stack );
void      PrintStackElements      ( Stack_t* stack );
ErrorCode StackErrorHandler       ( Stack_t* stack, bool is_dump );

/*-------------------------------------------------------*/