#include <stdlib.h>
#include <sys/stat.h>

#include "sup_func.h"

/*=====================================================================================*/

unsigned int djb2hash ( const char* str ) {

    u_int hash = 5381;
    u_char c = 0;
    
    while ((c = (u_char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
}

/*=====================================================================================*/

int skip_space ( char* ptr, size_t* pos ) {

    int sp_count = 0;

    while ( ptr[*pos] == ' ' ) {

        sp_count++;
        pos++;

    }

    return sp_count;

}

/*=====================================================================================*/

long long FileByteCount ( const char* filename ) {

    struct stat file_info = {};

    stat ( filename, &file_info );

    return file_info.st_size;

}
