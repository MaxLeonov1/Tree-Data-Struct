#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "akinator.h"
#include "../utils/colors.h"
#include "../utils/sup_func.h"



void print_cmd_arg_options(bool cls);
void print_interactive_menu(bool cls);
int  RunMenu(Tree* tree);


void print_cmd_arg_options(bool cls) {
    if(cls) CLS_
    fprintf(
        stderr,
        "%s==========================================================\n"
        "| -i <input_file_path>  | defines input file             |\n"
        "| -o <output_file_path> | defines output file [optional] |\n" 
        "==========================================================\n%s",
        BLUE, RES_COL
    );
}



void print_interactive_menu(bool cls) {
    if(cls) CLS_
    printf(
        "%s===================================\n"
        "| Choose operation mode:          |\n"
        "| 1. Guessing mode                |\n"
        "| 2. Find subject characteristics |\n"
        "| 3. Compare subjects             |\n"
        "| 4. Exit program                 |\n"
        "===================================\n%s",
        BLUE, RES_COL
    );
}



int RunMenu(Tree* tree) {
    int prt_menu = 1;
    int choice = 0;
    
    do {
        if(prt_menu) print_interactive_menu(false);
        
        if (scanf("%d", &choice) != 1) {
            printf(
                "%sInvalid input. Please enter a number.\n%s",
                RED, RES_COL
            );
            while (getchar() != '\n');
            prt_menu = 0;
            continue;
        }

        switch (choice) {
            case 1: {
                CLS_
                TreeErr_t status = GuessSubject(tree);
                CLS_
                _IF_DEBUG(TreeDump(tree, TreeErr_t::TREE_OK, nullptr);)
                _DUMP_IF_ERR_(*tree, status, "ERROR AT GUESSING")
                prt_menu = 1;
                break;
            }
            case 2: {
                CLS_
                FindSubject(tree);
                _IF_DEBUG(TreeDump(tree, TreeErr_t::TREE_OK, nullptr);)
                prt_menu = 1;
                break;
            }
            case 3: {
                CLS_
                FindDifference(tree);
                _IF_DEBUG(TreeDump(tree, TreeErr_t::TREE_OK, nullptr);)
                prt_menu = 1;
                break;
            }
            case 4: {
                CLS_
                printf("%sGoodbye!\n%s", BLUE, RES_COL);
                break;
            }
            default: {
                printf(
                    "%sInvalid choice. Please select 1-4.\n%s",
                     RED, RES_COL
                    );
                prt_menu = 0;
                break;
            }
        }
    } while (choice != 4);

    return choice;
}

int main(int argc, char* argv[]) {
    
    const char* input_filename = NULL;
    const char* output_filename = "treedisk.bin";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc)
                input_filename = argv[++i];
            else {
                fprintf(stderr, "-i requires a filename argument\n");
                print_cmd_arg_options(false);
                return 1;
            }

        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc)
                output_filename = argv[++i];
            else {
                fprintf(stderr, "-o requires a filename argument\n");
                print_cmd_arg_options(false);
                return 1;
            }

        } else {
            fprintf(stderr, "Unknown option '%s'\n", argv[i]);
            print_cmd_arg_options(false);
            return 1;
        }
    }

    if (input_filename == NULL) {
        fprintf(stderr, "Input filename is required [-i option]\n");
        print_cmd_arg_options(false);
        return 1;
    }

    TREE_INIT(tree_1)
    TreeCtor(&tree_1);

    TreeErr_t read_status = ReadFromDisk(&tree_1, input_filename);
    _IF_DEBUG(TreeDump(&tree_1, TreeErr_t::TREE_OK, nullptr);)
    
    if (read_status != TreeErr_t::TREE_OK) {
        fprintf(stderr, "Failed to read tree from '%s'\n", input_filename);
        TreeDump(&tree_1, read_status, "ERROR AT READING");
        TreeDtor(&tree_1);
        return 1;
    }

    RunMenu(&tree_1);

    TreeErr_t save_status = SaveToDisk(&tree_1, output_filename);
    if (save_status != TreeErr_t::TREE_OK) {
        fprintf(stderr, "Failed to save tree to '%s'\n", output_filename);
        TreeDump(&tree_1, save_status, "ERROR AT SAVING");
    }

    TreeDtor(&tree_1);
    return 0;
}