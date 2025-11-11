#include "sup_func.h"



unsigned int djb2hash ( const char* str ) {

    unsigned int hash = 5381;
    char c = 0;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
}
