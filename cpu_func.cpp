#include "cpu_func.h"

#define IF_JUMP {                                                                           \
                                                                                            \
    int check_func = cpu->code[ip];                                                         \
    ++ip;                                                                                   \
    if (prohod == 1) {                                                                      \
                                                                                            \
        if (cpu->code[ip] == 0x01) {                                                        \
                                                                                            \
            ++ip;                                                                           \
            int str_len = cpu->code[ip];                                                    \
            ++ip;                                                                           \
                                                                                            \
            for (i = 0; i < str_len; ++i) {                                                 \
                ++ip;                                                                       \
            }                                                                               \
        }                                                                                   \
                                                                                            \
        else if (cpu->code[ip] == 0x02) {                                                   \
                                                                                            \
            ++ip;                                                                           \
            ip += sizeof (type) / sizeof (char);                                            \
        }                                                                                   \
                                                                                            \
        else if (cpu->code[ip] == 0x03) {                                                   \
            ++ip;                                                                           \
        }                                                                                   \
    break;                                                                                  \
    }                                                                                       \
                                                                                            \
    if (check (check_func, head)) {                                                         \
                                                                                            \
        if (cpu->code[ip] == 0x01) {                                                        \
                                                                                            \
            ++ip;                                                                           \
            int str_len = cpu->code[ip];                                                    \
            char str[str_len + 1] = {};                                                     \
            ++ip;                                                                           \
                                                                                            \
            for (i = 0; i < str_len; ++i) {                                                 \
                str[i] = cpu->code[ip];                                                     \
                ++ip;                                                                       \
            }                                                                               \
            str[str_len] = '\0';                                                            \
                                                                                            \
            i = 0;                                                                          \
            int num = -1;                                                                   \
            while (1) {                                                                     \
                if (strcmp (str, ((cpu->labels)[i]).name) == 0) {                           \
                    num = (cpu->labels[i]).num_ip;                                          \
                    break;                                                                  \
            }                                                                               \
                else                                                                        \
                    ++i;                                                                    \
            }                                                                               \
            ip = num;                                                                       \
        }                                                                                   \
                                                                                            \
        else if (cpu->code[ip] == 0x02) {                                                   \
            ++ip;                                                                           \
            int num = *((type*)(cpu->code + ip));                                           \
                                                                                            \
            ip = (cpu->labels[num - 1]).num_ip;                                             \
        }                                                                                   \
                                                                                            \
        else if (cpu->code[ip] == 0x03) {                                                   \
                                                                                            \
            ++ip;                                                                           \
                                                                                            \
        }                                                                                   \
    }                                                                                       \
    else {                                                                                  \
        if (cpu->code[ip] == 0x01) {                                                        \
                                                                                            \
            ++ip;                                                                           \
            int str_len = cpu->code[ip];                                                    \
            ++ip;                                                                           \
                                                                                            \
            for (i = 0; i < str_len; ++i) {                                                 \
                ++ip;                                                                       \
            }                                                                               \
        }                                                                                   \
                                                                                            \
        else if (cpu->code[ip] == 0x02) {                                                   \
                                                                                            \
            ++ip;                                                                           \
            ip += sizeof (type) / sizeof (char);                                            \
        }                                                                                   \
                                                                                            \
        else if (cpu->code[ip] == 0x03) {                                                   \
            ++ip;                                                                           \
        }                                                                                   \
    }                                                                                       \
break;                                                                                      \
}                                                                                           \


int prohod_code (file_in *cpu, my_stack *head, int prohod, int size) {



    int ip       = 0;
    type input   = 0;
    int num_cmd  = 0;
    int i = 0, str_len = 0, j = 0;
    int counter = 0;
    
    //puts ("HELLO");
    while (1) {
    
        ++num_cmd;

        //++counter;      //без бесконечных циклов сегодня
        //if (counter == 1000)
          //abort ();

        switch (cpu->code[ip]) {

            case cmd_call: {
            
                if (prohod == 1) {
                    
                    //puts ("CALL 1");
                     //jump next

                        ++ip;
                        int str_len = cpu->code[ip];
                        ++ip;

                        for (i = 0; i < str_len; ++i) {
                            ++ip;
                        }
                    
                break;
                }
                    //puts ("CALL 2");

                                  //jump next
                        ++ip;
                        int str_len = cpu->code[ip];
                        char str[str_len + 1] = {};
                        //puts (str);
                        ++ip;
                        //puts ("OK1");
                        for (i = 0; i < str_len; ++i) {
                            str[i] = cpu->code[ip];
                            ++ip;
                        }
                        str[str_len] = '\0';
                        //puts (str);
                        i = 0;
                        int num = -1;
                        //puts ("OK2");
                        while (1) {

                            if (strcmp (str, ((cpu->labels)[i]).name) == 0) {
                                num = (cpu->labels[i]).num_ip;
                                break;
                        }
                            else
                                ++i;
                        }
                        //puts ("OK3");
                        //printf ("%0x", cpu->code[ip]);
                        //abort ();
                        //puts ("OK3.5");
                        //printf ("%d", pop (cpu->func));
                        pushka (cpu->func, ip);
                        //abort ();
                        //printf ("%d %d", num, ip);
                        ip = num;
                        //puts ("OK4");
            break;
            }

            case cmd_labl: {

                ++ip;

                if (prohod != 1) {
                    //puts ("LABEL 2");
                    str_len = cpu->code[ip];
                
                    ++ip;

                    for (j = 0; j < str_len; ++j) {
                        ++ip;
                    }
            break;
                }

                //puts ("LABEL 1");
                i = 0;
                while (1) {
                    if (((cpu->labels)[i]).num_ip == -1)
                        break;
                    else
                        ++i;
                }
                ((cpu->labels)[i]).num_cmd = num_cmd;

                str_len = cpu->code[ip];
            
                ++ip;
                for (j = 0; j < str_len; ++j) {
                    ((cpu->labels)[i]).name[j] = cpu->code[ip];
                    ++ip;
                }

                ((cpu->labels)[i]).name[++j] = '\0';
                
                ((cpu->labels)[i]).num_ip = ip;
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
            if (prohod == 1) {
                //puts ("JUMP 1");
                if (cpu->code[ip] == 0x01) {  //jump next

                    ++ip;
                    int str_len = cpu->code[ip];
                    ++ip;

                    for (i = 0; i < str_len; ++i) {
                        ++ip;
                    }
                }

                else if (cpu->code[ip] == 0x02) {   //jump :1    (прыгает на 1 метку, а не на метку 1:)

                    ++ip;
                    ip += sizeof (int) / sizeof (char);
                }
                                                                //ДОДЕЛАТЬ!!! jump 5
                else if (cpu->code[ip] == 0x03) {
                    ++ip;
                }
            break;
            }
                //puts ("JUMP 2");

                if (cpu->code[ip] == 0x01) {  //jump next

                    ++ip;
                    int str_len = cpu->code[ip];
                    char str[str_len + 1] = {};
                    ++ip;

                    for (i = 0; i < str_len; ++i) {
                        str[i] = cpu->code[ip];
                        ++ip;
                    }
                    str[str_len] = '\0';

                    i = 0;
                    int num = -1;
                    while (1) {
                        if (strcmp (str, ((cpu->labels)[i]).name) == 0) {
                             num = (cpu->labels[i]).num_ip;
                            break;
                    }
                        else
                            ++i;
                    }
                    ip = num;
                }   

                else if (cpu->code[ip] == 0x02) {   //jump :1       

                    ++ip;
                    int num = *((int*)(cpu->code + ip));

                    ip = (cpu->labels[num - 1]).num_ip;
                    //printf ("%d \n", ip);
                    //printf ("%d\n", (cpu->labels[num - 2]).num_ip);
                    //printf ("%0x\n", cpu->code[ip]); 
                    //abort ();
                }        
                                                                //ДОДЕЛАТЬ!!! jump 5
                else if (cpu->code[ip] == 0x03) {

                    ++ip;

                }
            break;
            }

            case cmd_push: {   //cmd push

                ++ip;

            if (prohod == 1) {

                //puts ("PUSH 1");

                if (cpu->code[ip] == 0x00) {
                    ++ip;
                    ip += sizeof (type) / sizeof (char);
                }
                else if (cpu->code[ip] == 0x01) {
                    ++ip;
                    ++ip;
                }
                else if (cpu->code[ip] == 0x02) {
                    ++ip;
                    ++ip;
                }
                else if (cpu->code[ip] == 0x03) {
                    ++ip;
                    ip += sizeof (type) / sizeof (char);
                }
                break;
            }

                //puts ("PUSH 2");

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
                    Sleep (1000);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x03) {

                    ++ip;
                    pushka (head, cpu->ram[(int)*(type*)(cpu->code + ip)])
                    Sleep (1000);
                    ip += sizeof (type) / sizeof (char);
                }
            break;
            }

            case cmd_pop: {

                ++ip;
            if (prohod == 1) {
                //puts ("POP 1");
                if (cpu->code[ip] == 0x01) {                    
                    ++ip;
                    ++ip;
                }
                else if (cpu->code[ip] == 0x02) {
                    ++ip;
                    ++ip;
                }
                else if (cpu->code[ip] == 0x03) {
                    ++ip;
                    ip += sizeof (type) / sizeof (char);
                }
                break;
            }
                //puts ("POP 2");
                if (cpu->code[ip] == 0x01) {
                    
                    ++ip;
                    cpu->regs[cpu->code[ip]] = pop (head);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x02) {

                    ++ip;
                    cpu->ram[(int)cpu->regs[cpu->code[ip]]] = pop (head);
                    Sleep (1000);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x03) {

                    ++ip;
                    cpu->ram[(int)*((type*)(cpu->code + ip))] = pop (head);
                    Sleep (1000);
                    ip += sizeof (type) / sizeof (char);
                }
            break;
            }

            case cmd_add: {
        
        if (prohod == 1) {
            //puts ("ADD 1");
            ++ip;
            break;
        }
                //puts ("ADD 2");
                pushka (head, pop (head) + pop (head))
                ++ip;
            break;
            }

            case cmd_mul: {
        
        if (prohod == 1) {
            ++ip;
            break;
        }

                pushka (head, pop (head) * pop (head))
                ++ip;

            break;
            }

            case cmd_sqrt: {
        
        if (prohod == 1) {
            ++ip;
            break;
        }

                pushka (head, sqrt (pop (head)))
                ++ip;

            break;
            }

            case cmd_del: {
        
        if (prohod == 1) {
            ++ip;
            break;
        }
                double a = pop (head);
                double b = pop (head);
                pushka (head, b / a)
                ++ip;

            break;
            }

            case cmd_sub: {
        if (prohod == 1) {
            ++ip;
            break;
        }

                pushka (head, -(pop (head) - pop (head)))
                ++ip;

            break;
            }

            case cmd_in: {

        if (prohod == 1) {
            ++ip;
            break;
        }
            #ifdef KEK
                scanf ("%d", &input);
            #else
                scanf ("%lf", &input);
            #endif
                pushka (head, input);
                ++ip;

            break;
            }

            case cmd_out: {
        if (prohod == 1) {
            ++ip;
            break;
    }
                #ifdef KEK
                    printf ("VIVOD: %d\n", pop(head));
                #else
                    printf ("VIVOD: %.2f\n", pop (head));
                #endif

                ++ip;
            break;
            }

            default: {
                printf ("AAAA: unknown cmd");
                abort ();
            break;
            }
        }

        if (cpu->code[ip] == cmd_ret) {
            if (prohod == 1 && ip == size - 6) {
                //puts ("RET 1");
                //printf ("%d\n", ip);

                break;
            }
            else if (prohod == 2) {
                //puts ("RET 2");
                
                ip = pop (cpu->func);
            }
            else {
                //puts ("RET 1");
                //printf ("%d\n", ip);
                ++ip;
            }
        }

        if (cpu->code[ip] == cmd_end) {

            if (prohod == 1 && ip == size - 6) {
                //puts ("END 1");
                break;
            }
            else if (prohod == 2) {
                //puts ("END 2");
                break;
            }
            else {
               // puts ("U VAS FUNC");
                ++ip;
            }
        }
        //printf ("%d %d", ip, size - 5);
        if (ip >= size - 5) {
            //puts ("KONEC FAILA");
            break;
        }
    }
    return 1;
}



int check (int a, my_stack *head) {

    switch (a) {

        case cmd_jae : {
            return (pop (head) >= pop (head));
            break;
        }
        case cmd_ja: {
            return (pop (head) > pop (head));
            break;
        }

        case cmd_jb: {
            return (pop (head) < pop (head));
            break;
        }

        case cmd_jbe: {
            return (pop (head) <= pop (head));
            break;
        }

        case cmd_je: {
            #ifdef KEK
                return (pop (head) == pop (head));
            #else
            int cmem = fabs (pop(head) - pop (head)) < EPS;
            //printf ("/////////////CHECK: %d\n", cmem);
                return (cmem);
            #endif

            break;
        }

        case cmd_jne: {
            #ifdef KEK
                return (pop (head) != pop (head));
            #else
                return (fabs (pop(head) - pop (head)) > EPS);
            #endif            
            
            break;
        }
        default: {
            puts ("CHECK FUNC ERROR");
            break;
        }
    }
    return 0;
}

