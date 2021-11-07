#ifndef ASM_H
#define ASM_H

#include "enum.h"
#include "onegin.h"
#include "cmds.h"


typedef struct label
{
    int hash = 0;
    int ip = 0;
}label;


// calloc на колличество строк (достаточная оценка)
typedef struct labels    //label
{
    int cnt_labels = 0;
    label cmd_label[10] = {};

}labels;
                                                                  


typedef struct asm_type {

    char ver = Version;

    int sign = Signature;

    int len_of_code = 0;

    char *code = nullptr;

    labels cmd_labels = {};

}asm_type;


int cmd_num (char *cmd);

int assembler_fillin (TEXT *cmd_file, FILE *out, int prohod, asm_type *asem);


#endif