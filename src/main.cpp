#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "akinator.h"
#include "sup_func.h"



int main(int argc, char* argv[]) {
    
    const char* input_filename = NULL;
    const char* output_filename = "treedisk.bin";
    int run_guess = 0;
    int run_find = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                input_filename = argv[++i];
            } else {
                fprintf(stderr, "-i requires a filename argument\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_filename = argv[++i];
            } else {
                fprintf(stderr, "-o requires a filename argument\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-g") == 0) {
            run_guess = 1;
        } else if (strcmp(argv[i], "-f") == 0) {
            run_find = 1;
        } else {
            fprintf(stderr, "Unknown option '%s'\n", argv[i]);
            return 1;
        }
    }

    if (input_filename == NULL) {
        fprintf(stderr, "Input filename is required [-i option]\n");
        return 1;
    }

    TREE_INIT(tree_1)
    TreeCtor(&tree_1);

    TreeErr_t read_status = ReadFromDisk(&tree_1, input_filename);
    if (read_status != TreeErr_t::TREE_OK) {
        fprintf(stderr, "Failed to read tree from '%s'\n", input_filename);
        TreeDump(&tree_1, read_status, "ERROR AT READING");
        TreeDtor(&tree_1);
    }

    if (run_guess) {
        TreeErr_t status = GuessSubject(&tree_1);
        _DUMP_IF_ERR_ (tree_1, status, "ERROR AT GUESSING")
    }

    if (run_find) {
        FindSubject(&tree_1);
    }

    if (!run_guess && !run_find) {
        TreeErr_t status = GuessSubject(&tree_1);
        _DUMP_IF_ERR_ (tree_1, status, "ERROR AT GUESSING")
    }

    TreeErr_t save_status = SaveToDisk(&tree_1, output_filename);
    if (save_status != TreeErr_t::TREE_OK) {
        fprintf(stderr, "Failed to save tree to '%s'\n", output_filename);
        TreeDump(&tree_1, save_status, "ERROR AT SAVING");
    }

    TreeDtor(&tree_1);
    return 0;

}