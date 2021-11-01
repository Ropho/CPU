#include "stack_func.h"
#include "onegin.h"
#include "enum.h"
#include "cmds.h"

extern size_t EXIT_COND;   //условие выхода из проги

int main (void) {

    FILE *out = fopen ("DUMP", "w");       //clearing the dump  file
    kotik(out)
    fclose (out);
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
    FILE *in = fopen ("binary.bin", "rb");

#if defined D_2 || defined D_1      //mode with canaries and verificator

    my_stack *head = nullptr;

    create (head)

    int size = FILESIZE_FUNC_FSTAT (in);

    file_in cpu = {};

    fread (&cpu.sign, sizeof (int), 1, in);
    if (cpu.sign != signature) {

        puts ("WRONG SIGNATURE");
        return 0;
    }

    fread (&cpu.ver, sizeof (char), 1, in);
    if (cpu.ver != cmd_version) {

        puts ("WRONG VERSION");
        return 0;
    }

    cpu.code = (char*) calloc (size, sizeof (char));


    fread (cpu.code, sizeof (char), size, in);
/*
    for (int i = 0; i < size; ++i)
        printf ("%d ", code[i]);
    return 0;
*/
    int ip = 0;
    int input = 0;

    while (1) {

        switch (cpu.code[ip]) {

            case cmd_push:    //cmd push
                ++ip;
                if (cpu.code[ip] == 0x00) {
                    //printf ("kek");
                    ++ip;
                    pushka (head, *(int*)(cpu.code + ip))
                    ip += sizeof (int) / sizeof (char);
                }
                else if (cpu.code[ip] == 0x01) {
                    ++ip;
                    pushka (head, cpu.regs[cpu.code[ip]])
                    ++ip;
                }
                else if (cpu.code[ip] == 0x02) {

                    ++ip;
                    pushka  (head, cpu.ram[cpu.regs[cpu.code[ip]]])
                    Sleep (1000);
                    ++ip;
                }
                else if (cpu.code[ip] == 0x03) {

                    ++ip;
                    pushka (head, cpu.ram[*(int*)(cpu.code + ip)])
                    Sleep (1000);
                    ip += sizeof (int) / sizeof (char);
                }
                //printf ("%d ", pop (head));
            break;

            case cmd_pop:

                ++ip;

                if (cpu.code[ip] == 0x01) {
                    
                    ++ip;
                    cpu.regs[cpu.code[ip]] = pop (head);
                    ++ip;
                }
                else if (cpu.code[ip] == 0x02) {

                    ++ip;
                    cpu.ram[cpu.regs[cpu.code[ip]]] = pop (head);
                    ++ip;
                }
                else if (cpu.code[ip] == 0x03) {

                    ++ip;
                    cpu.ram[*((int*)(cpu.code + ip))] = pop (head);
                    Sleep (1000);
                    ip += sizeof (int) / sizeof (char);
                }
            break;

            case cmd_add:
                pushka (head, pop (head) + pop (head))
                ++ip;
            break;

            case cmd_mul:
                pushka (head, pop (head) * pop (head))
                ++ip;

            break;

            case cmd_in:
                scanf ("%d", &input);
                pushka (head, input);
                ++ip;

            break;
            
            case cmd_out:
                printf ("%d", pop(head));
                ++ip;
            break;

            default:
            break;
        }

        if (cpu.code[ip] == cmd_end) {
            dead (head)
            break;
        }
    }

}
#endif