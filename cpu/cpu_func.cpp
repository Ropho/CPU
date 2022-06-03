#include "cpu_func.h"


int prohod_code (cpu_type *cpu, my_stack *head, int size) {

    assert (cpu  != nullptr);
    assert (head != nullptr);

    int ip        = 0;
    type input    = 0;
    int num_cmd   = 0;
    int i         = 0;
    int str_len   = 0;

    while (1) {
    
        ++num_cmd;

        switch (cpu->code[ip]) {

            #define DEF_CMD(name, number, argc, hash, code) case number: code; break;
            #define DEF_REG(name, number, hash)

            #include "../asm/cmds.h"

            #undef DEF_CMD
            #undef DEF_REG

            default: {
                puts ("AAAA: aaaaaaa aaa");
                printf ("%d\n", ip); 
                return 1;
            break;
            }
        }
    
    }
    return 0;

}