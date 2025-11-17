#pragma once

/*=====================================================================================*/

#define MAX_STR_LEN_ 1024 

#ifdef _WIN32
    #define CLS_ system("cls");
#else
    #define CLS_ system("clear");
#endif

#ifdef _DEBUG
    #define _IF_DEBUG(source) source
#else
    #define _IF_DEBUG(source)
#endif

/*=====================================================================================*/

long long FileByteCount ( const char* filename );
unsigned int djb2hash ( const char *str );
int skip_space ( char* ptr, size_t* pos );