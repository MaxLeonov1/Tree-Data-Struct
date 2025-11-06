#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include "tree.h"



/*=====================================================================================*/

const char* StatusCodeToStr ( TreeErr_t status ) {

    switch(status) {
        case TreeErr_t::MEM_ALLOC_ERR:
            return "ERROR IN ALLOCATION";
        case TreeErr_t::TREE_OK:
            return "OK";
    }

}

/*=====================================================================================*/

void CreateLogDir ( char* dir_name, int call_num ) {

    assert(dir_name);
 
    char proj_path[MAX_STR_LEN_] = {0};
    time_t log_time_sec = time(NULL);
    struct tm* log_time = localtime( &log_time_sec );
    
    getcwd(proj_path, sizeof(proj_path));
    sprintf ( proj_path, "%s/logs", proj_path );
    mkdir ( proj_path, FILE_MODE_ ); 

    sprintf ( dir_name,
              "%s/log_%d.%d.%d_%d:%d:%d",
              proj_path,
              log_time->tm_mday,
              log_time->tm_mon,
              1900 + log_time->tm_year,
              log_time->tm_hour,
              log_time->tm_min,
              log_time->tm_sec );
    
    mkdir ( dir_name, FILE_MODE_ );

}

/*=====================================================================================*/

void TreeDump ( Tree_t* tree, TreeErr_t status ) {

    assert(tree);

    static int call_num = 1;
    char filename[MAX_STR_LEN_] = {0};
    char graphname[MAX_STR_LEN_] = {0};
    static char log_dir[MAX_STR_LEN_] = {0};

    if (call_num == 1) CreateLogDir ( log_dir, call_num );

    snprintf ( filename, sizeof(filename), "%s/list_log.htm", log_dir );
    snprintf ( graphname, sizeof(graphname), "graph_%d.svg", call_num );

    call_num++;

    FILE* log_file = fopen ( filename, "a" );
    if ( log_file == nullptr ) exit(0);

    fprintf ( log_file,
              "\n<div style=\"height:4px;background:#000\"/>\n" 
              "<pre>\n"
              "<body style=\"background-color: white;\">\n" );

    PrintLogHeader ( tree, log_file, status );
    
    fprintf ( log_file, "<h3>[IMG]:</h3>\n" );

    CreateGraphImg ( tree, graphname, log_dir );

    fprintf ( log_file, "<img "
                        "src = \"%s\" "
                        "style=\"width: 80vw; height: auto; max-width: 100%%;\" >",
                        graphname );

    fclose ( log_file );

}

/*=====================================================================================*/

void PrintLogHeader ( Tree_t* tree, FILE* log_file, TreeErr_t status ) {

    assert(tree);
    assert(log_file);

    if ( status != TreeErr_t::TREE_OK )
        fprintf(
            log_file,
            "<h3 style=\"color:red;\">[ERROR][%d]</h3>\n"
            "<h3 style=\"color:red;\">[%s]</h3>\n",
            status, StatusCodeToStr(status)
        );
    else
        fprintf(
            log_file,
            "<h3 style=\"color:green;\">[NO ERROR DUMP]</h3>\n"
        );

    fprintf( 
        log_file,
        "<h3>[TREE INFO]:</h3>\n"
        "name: %s\n"
        "location: %s::%d, %s()\n"
        "<h3>[TREE DATA]:</h3>\n"
        "capacity: %lu\n",
        tree->info.name,
        tree->info.file,
        tree->info.line,
        tree->info.func,
        tree->cpcty 
    );

    
}

/*=====================================================================================*/

void CreateGraphImg ( Tree_t* tree, const char* graphname, const char* graph_dir ) {

    assert(tree);
    assert(graphname);
    assert(graph_dir);

    char graph_txt_path[MAX_STR_LEN_] = {0};
    char graph_svg_path[MAX_STR_LEN_] = {0};
    snprintf ( graph_svg_path, sizeof(graph_svg_path), "%s/%s", graph_dir, graphname );
    snprintf ( graph_txt_path, sizeof(graph_txt_path), "%s/graph.txt", graph_dir );

    FILE* graph_text = fopen ( graph_txt_path, "w" );

    fprintf ( graph_text, 
              "digraph structs {\n"
              "   rankdir = HR;\n"
              "   bgcolor = \"white\""
              /*"   splines = \"ortho\";\n"*/
              "   node [fontname=\"Helvetica-BoldOblique\", fontsize=\"11\","
              " style=\"filled,bold\", fillcolor = \"#fff0b3\", color = \"#ffe680\"];\n"
              );
    
    PrintGraphNodes(tree->root, 1, graph_text);

    fprintf ( graph_text, "}" );
    fclose ( graph_text );

    char cmd_line[MAX_STR_LEN_] = {0};
    snprintf ( cmd_line, sizeof(cmd_line), "dot -Tsvg %s -o %s", graph_txt_path, graph_svg_path );
    system ( cmd_line );

}



int PrintGraphNodes(TreeNode_t* node, int rank, FILE* graph_text) {

    assert(node);
    assert(graph_text);

    static int idx = 0;
    int idx_left = 0;
    int idx_right = 0;

    if(rank == 1) idx = 0;

    if (node->left)  idx_left  = PrintGraphNodes(node->left,  rank+1, graph_text);
    if (node->right) idx_right = PrintGraphNodes(node->right, rank+1, graph_text);

    fprintf(
        graph_text, 
        "node_%d[shape=Mrecord, rank=%d, "
        "label=\" { %p | data: '%s' | { Left: %p | Right: %p } } \",];\n",
        idx,
        rank,
        node,
        node->data,
        node->left,
        node->right
    );

    if (node->left)
        fprintf(
            graph_text,
            "node_%d -> node_%d["EDGE_STD_SET_"];\n",
            idx, idx_left
        );

    if (node->right) {
        fprintf(
            graph_text,
            "node_%d -> node_%d["EDGE_STD_SET_"];\n",
            idx, idx_right
        );
        
    }

    return idx++;

}