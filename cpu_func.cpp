#include "cpu_func.h"

#define IF_JUMP {                                                                           \
                                                                                            \
    int check_func = cpu->code[ip];                                                         \
                                                                                            \
    if (check_srav (check_func, head)) {                                                    \
                                                                                            \
        ++ip;                                                                               \
        ip = *(int*)(cpu->code + ip);                                                       \
                                                                                            \
        break;                                                                              \
    }                                                                                       \
                                                                                            \
    ++ip;                                                                                   \
    ip += sizeof (int) / sizeof (char);                                                     \
                                                                                            \
    break;                                                                                  \
}                                                                                           \


int prohod_code (cpu_type *cpu, my_stack *head, int size) {

    assert (cpu  != nullptr);
    assert (head != nullptr);
    int ip        = 0;
    type input    = 0;
    int num_cmd   = 0;
    int i = 0, str_len = 0, j = 0;

    while (1) {
    
        ++num_cmd;

        switch (cpu->code[ip]) {

            case cmd_call: {
                    
                ++ip;
                pushka (cpu->func, ip + sizeof (int) / sizeof (char))
                ip = *(int*)(cpu->code + ip);
    int a = 0x0D;
 
            break;
            }


            case cmd_jae: 
                IF_JUMP

            case cmd_ja:
                IF_JUMP

            case cmd_jb:
                IF_JUMP
            
            case cmd_jbe:
                IF_JUMP
            
            case cmd_je:
                IF_JUMP
            
            case cmd_jne:
                IF_JUMP


            case cmd_jump: {

                ++ip;     
                ip = *(int*)(cpu->code + ip);

                break;
            }

            case cmd_push: {

                ++ip;

                if (cpu->code[ip] == 0x00) {
                    ++ip;
                    pushka (head, *(type*)(cpu->code + ip))
                    ip += sizeof (type) / sizeof (char);
                }
                else if (cpu->code[ip] == 0x01) {
                    ++ip;
                    pushka (head, cpu->regs[cpu->code[ip]])
                    ++ip;
                }
                else if (cpu->code[ip] == 0x02) {

                    ++ip;
                    pushka  (head, cpu->ram[(int)cpu->regs[cpu->code[ip]]])
                    //Sleep (1000);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x03) {

                    ++ip;
                    pushka (head, cpu->ram[(int)*(type*)(cpu->code + ip)])
                    //Sleep (1000);
                    ip += sizeof (type) / sizeof (char);
                }
                break;
            }

            case cmd_pop: {
                
                ++ip;

                if (cpu->code[ip] == 0x01) {
                    
                    ++ip;
                    cpu->regs[cpu->code[ip]] = pop (head);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x02) {

                    ++ip;
                    cpu->ram[(int)cpu->regs[cpu->code[ip]]] = pop (head);
                    //Sleep (1000);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x03) {

                    ++ip;
                    cpu->ram[(int)*((type*)(cpu->code + ip))] = pop (head);
                    //Sleep (1000);
                    ip += sizeof (type) / sizeof (char);
                }
            break;
            }

            case cmd_add: {

                pushka (head, pop (head) + pop (head))
                ++ip;

            break;
            }

            case cmd_mul: {
        
                pushka (head, pop (head) * pop (head))
                ++ip;

            break;
            }

            case cmd_sqrt: {
                
                pushka (head, sqrt (pop (head)))
                ++ip;

            break;
            }

            case cmd_del: {
        
                double a = pop (head);
                double b = pop (head);
                pushka (head, b / a)
                ++ip;

            break;
            }

            case cmd_sub: {
                
                type qwe = (pop (head) - pop (head));
                qwe = qwe * -1;
                pushka (head, qwe)
                ++ip;

            break;
            }

            case cmd_in: {

            #ifdef INT_T
                scanf ("%d", &input);
            #else
                scanf ("%lf", &input);
            #endif
                pushka (head, input);

                ++ip;

            break;
            }

            case cmd_out: {

                #ifdef INT_T
                    printf ("VIVOD: %d\n", pop (head));
                #else
                    printf ("VIVOD: %.2f\n", pop (head));
                #endif

                ++ip;
            break;
            }
            
            case cmd_print: {
                        
                //FILE *out = fopen ("out.txt", "wb");

                for (i = 0; i < num_cmd; ++i)
                    printf ("%c", cpu->ram[i]);

                ++ip;

            break;
            }

            default: {
                puts ("AAAA: unknown cmd");
                printf ("%d\n", ip); 
                abort ();
            break;
            }
        }

        if (cpu->code[ip] == cmd_ret) {
            
            ip = pop (cpu->func);
        }

        if (cpu->code[ip] == cmd_end) {

            return 0;
        }
    
    }

}



int check_srav (int a, my_stack *head) {

    type tmp1 = pop (head);
    type tmp2 = pop (head);

    switch (a) {

        case cmd_jae : {

            return (tmp2 >= tmp1);
            break;
        }
        case cmd_ja: {

            return (tmp2 > tmp1);
            break;
        }

        case cmd_jb: {

            return (tmp2 < tmp1);
            break;
        }

        case cmd_jbe: {

            return (tmp2 <= tmp1);
            break;
        }

        case cmd_je: {
            #ifdef INT_T
                return (tmp1 == tmp2);
            #else
                return (fabs (tmp1 - tmp2) < EPS);
            #endif

            break;
        }

        case cmd_jne: {
            #ifdef INT_T
                return (tmp1 != tmp2);
            #else
                return (fabs (tmp1 - tmp2) > EPS);
            #endif            
            
            break;
        }
        default: {
            puts ("CHECK FUNC ERROR");
            break;
        }
    }
    return -1;
}

