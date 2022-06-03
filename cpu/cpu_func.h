#ifndef CPU_FUNC_H
#define CPU_FUNC_H

#include "../onegin/onegin.h"
#include "../stack/stack_func.h"
#include "../asm/enum.h"
#include <time.h>


#define dump {FILE *out = fopen ("DUMP", "w"); kotik(out) fclose (out);}

extern size_t EXIT_COND;

typedef struct cpu_type {

    char *code;
    type regs[4];
    type ram[1000];
    my_stack *func;

} cpu_type;

int prohod_code (cpu_type *cpu, my_stack *head, int size);

int check_srav (int a, my_stack *head);


#endif