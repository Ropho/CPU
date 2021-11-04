#ifndef CPU_FUNC_H
#define CPU_FUNC_H

#include "onegin.h"
#include "enum.h"
#include "cmds.h"

extern size_t EXIT_COND;   //условие выхода из проги

int prohod_code (file_in *cpu, my_stack *head, int prohod, int size);

int check (int a, my_stack *head);

#endif