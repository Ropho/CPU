#include "asm.h"

int assembler_fillin (TEXT *cmd_file, FILE *out, int prohod, asm_type *asem) {
    
    assert (cmd_file != nullptr);
    assert (out      != nullptr);

    int ip = 0;

    for  (int i = 0; i < cmd_file->number_lines; ++i) {

        char *buf = cmd_file->array_pointers[i].str;
        char *srch = nullptr;


        if (prohod == 1) {

            srch = (strchr (buf, '\r'));          //убираем \r для каждой строки
            if (srch != nullptr)
                *srch = '\0';

            srch = strchr(buf, ';');              //убираем ; для каждой строки
            if (srch != nullptr) 
                *srch = '\0';
        }

        srch = strchr (buf, ' ');

        if (srch == nullptr) {
            
            srch = strchr (buf, ':');

            if (srch == nullptr) {                  //add, mul, in

                if (prohod == 1) {
                    if (*(buf + strlen (buf) - 1) == '\r')
                        *(buf + strlen (buf) - 1) = '\0';
                }

                if (prohod == 2) {
                    *(asem->code + ip) = (char) cmd_num (buf);
                }
                
                ++ip;
            }
            else {

                *srch = '\0';

                if (prohod == 1) {
                    ((asem->cmd_labels).cmd_label + (asem->cmd_labels).cnt_labels)->hash = hash_C (buf);
                    ((asem->cmd_labels).cmd_label + (asem->cmd_labels).cnt_labels)->ip   = ip;

                    ++(asem->cmd_labels).cnt_labels;

                    *srch = ':';
                }

            }
        
        }
        else {              //push 1, pop ax....
            
                                                    // sscanf("%s")
            char str[30] = {};
            strncpy (str, buf, srch - buf);
            int com = cmd_num (str);
            
            *(asem->code + ip) = (char)com;
            ++ip;

            strcpy (str, buf);

            if (com == cmd_call || com == cmd_jump || com == cmd_jae || com == cmd_ja 
             || com == cmd_je   || com == cmd_jb   || com == cmd_jbe || com == cmd_jne) {

                if (prohod == 2) {
                        
                    ++srch;

                    int hash = hash_C (srch);
                    
                    for (int i = 0; i <= (asem->cmd_labels).cnt_labels; ++i) {

                        if (hash == ((asem->cmd_labels).cmd_label + i)->hash) {

                            *(int*)(asem->code + ip) = (((asem->cmd_labels).cmd_label + i)->ip);

                            ip += sizeof (int) / sizeof (char);
                           
                            break;
                        }
                    }
                }
                else {
                    ip += sizeof (int) / sizeof (char);
                }
            }
            
            else if (com == cmd_pop) {
                
                if (prohod == 1) {
                    ip += 2 * sizeof (char) / sizeof (char);
                }
                
                else {

                if (strchr (str + (srch - buf), '[') == nullptr) {
                    
                    com = 0x01;
                    *(asem->code + ip) = (char)com;
                    ++ip;
                    
                    com = get_reg (str + (srch - buf) + 1);
                    
                    *(asem->code + ip) = (char)com;
                    ++ip;

                }

                else {

                    com = 0x02;
                    *(asem->code + ip) = (char)com;
                    ++ip;

                    char tmp[3] = {};
                    strncpy (tmp, str + (srch - buf) + 2, 2);
                    tmp[2] = '\0';                                  //было ' [ax]' стало 'ax'
                    
                    if (!isdigit (tmp[0])) {
                        com = get_reg (tmp);
                        
                        *(asem->code + ip) = (char)com;
                        ++ip;
                    
                    }
                    else {

                        com = 0x03;
                        *(asem->code + ip) = (char)com;
                        ++ip;

                        char *skobka1 = strchr (str + (srch - buf), '[');
                        char *skobka2 = strchr (str + (srch - buf), ']');
                        ++skobka1;
                        *skobka2 = '\0';

                        type tmp1 =  convert (skobka1);
                        *(type*)(asem->code + ip) = tmp1;
                        ip += sizeof (type) / sizeof (char);
                    }

                }
                }
            }

            else if (com == cmd_push) {

                if (prohod == 1) {

                    if (strchr (str + (srch - buf), 'x') == nullptr)
                        
                        #ifdef INT_T
                            ip += sizeof (char) + sizeof (int) / sizeof (char);
                        #else
                            ip += sizeof (char) + sizeof (double) / sizeof (char);
                        #endif
                    else 
                        ip += 2 * sizeof (char) / sizeof (char);
                
                }
                else {
                    if (strchr (str + (srch - buf), '[') == nullptr) {

                    
                        if (strchr (str + (srch - buf), 'x') != nullptr) {
                            
                            com = 0x01;
                            *(asem->code + ip) = (char)com;
                            ++ip;
                    
                            com = get_reg (str + (srch - buf) + 1);
                    
                            *(asem->code + ip) = (char)com;
                            ++ip;

                        }
                        else {

                            com = 0x00;
                            *(asem->code + ip) = (char)com;
                            ++ip;
                            
                            type tmp1 = convert (str + (srch - buf));
                            *(type*)(asem->code + ip) = tmp1;
                            ip += sizeof (type) / sizeof (char);
                        }
                    }
                    else {
                        
                        if (strchr (str + (srch - buf), 'x') != nullptr) {

                            com = 0x02;
                            *(asem->code + ip) = (char)com;
                            ++ip;

                            char tmp[3] = {};
                            strncpy (tmp, str + (srch - buf) + 2, 2);
                            tmp[2] = '\0';                                  //было ' [ax]' стало 'ax'
                            
                            if (!isdigit (tmp[0])) {
                                com = get_reg (tmp);
                                
                                *(asem->code + ip) = (char)com;
                                ++ip;
                            
                            }

                        }
                        else {
                            
                            com = 0x03;
                            *(asem->code + ip) = (char)com;
                            ++ip;

                            char *skobka1 = strchr (str + (srch - buf), '[');
                            char *skobka2 = strchr (str + (srch - buf), ']');
                            ++skobka1;
                            *skobka2 = '\0';

                            type tmp1 = convert (skobka1);
                            *(type*)(asem->code + ip) = tmp1;
                            ip += sizeof (type) / sizeof (char);
                        }
                    }
                }

            }
        }
    }

    if (prohod == 2) {
        fwrite (&(asem->sign), sizeof (int), 1, out);
        fwrite (&(asem->ver), sizeof (char), 1, out);
        fwrite (asem->code, sizeof (char), ip, out);
    }
    return 0;
}

int rotl (int n) {
    unsigned d = 13;
    n *= d;
    return (n << d)|(n >> (32 - d));
}

int hash_C (char *head) {
    
    assert (head != nullptr);
    
    int hash = 0x1337;

    int tmp = 0;

    for (int i = 0; i < strlen (head); ++i) 
        tmp += head[i];
        hash ^= rotl (tmp);

                                                    //avalanche
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);
    
    return hash;
}

int get_reg (char* reg) {

    assert (reg != nullptr);

    #define DEF_CMD(name, number, hash, argc, code)
    #define DEF_MOD(name, number)
    #define DEF_REG(name, number, hash) if (hash == hash_C (reg)) return number;

    #include "cmds.h"

    #undef DEF_CMD
    #undef DEF_MOD
    #undef DEF_REG 
}