#pragma once

#define MAX_STR_LEN_ 1024 

long long FileByteCount ( const char* filename );
unsigned int djb2hash ( const char *str );
int skip_space ( char* ptr, size_t* pos );