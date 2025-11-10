#include "sup_func.h"



int djb2hash ( const char *str ) {

    int hash = 5381;
    int c = 0;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
}