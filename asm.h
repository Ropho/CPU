#ifndef ASM_H
#define ASM_H

#include "enum.h"
#include "onegin.h"
#include "cmds.h"


int cmd_num (char *cmd);

void assembler_fillin (TEXT *cmd_file, FILE *out);

#endif