#include "asm.h"

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

                                                  // may be skip spaces?
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
            int cum = cmd_num (str);
            
            *(asem->code + ip) = (char)cum;
            ++ip;

            strcpy (str, buf);

            // Проверять : перед меткой иначе считать число, иначе грамматическая ошибка

            if (cum == cmd_call || cum == cmd_jump || cum == cmd_jae || cum == cmd_ja 
             || cum == cmd_je   || cum == cmd_jb   || cum == cmd_jbe || cum == cmd_jne) {

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
                /*
                char *check = strchr (str + (srch - buf), ':');
                if (check == nullptr)  {
                    ++srch; //srch != ' '
                
                    if (isdigit (*srch)) {
                        cum = 0x00;     //jump 5
                *(asem.code + ip) = (char)cum;
                        ++ip;
                        
                        cum = atoi (srch);
                        *(int*)(asem.code + ip) = cum;
                        ip += sizeof (int) / sizeof (char);
                    }
                  

                       // cum = 0x01; // jump next
                       
                        *(asem.code + ip) = (char)cum;
                        ++ip;
                    

                        cum = strlen (srch);
                        *(asem.code + ip) = (char)cum;
                        ++ip;

                        while (*srch != '\0') {
                            *(asem.code + ip) = *srch;
                            ++ip;
                            ++srch;    
                    
                    }
                }
                /*
                else {
                    cum = 0x02; //jump :1
                *(asem.code + ip) = (char)cum;
                    ++ip;

                    *check = '\0';
                    srch += 2;
                        type tmp1 = convert (srch);
                        *(type*)(asem.code + ip) = tmp1;
                        ip += sizeof (type) / sizeof (char);
                }
            */    
            }
            
            else if (cum == cmd_pop) {
                
                if (prohod == 1) {
                    ip += 2 * sizeof (char) / sizeof (char);
                }
                
                else {

                if (strchr (str + (srch - buf), '[') == nullptr) {

                    cum = 0x01;
                    *(asem->code + ip) = (char)cum;
                    ++ip;
                    // define                                                //we can search for 'a', 'b', 'c' and 'd'
                    if (strcmp ((str + (srch - buf)), " ax") == 0) {

                        cum = 0x01;
                        *(asem->code + ip) = (char)cum;
                        ++ip;
                    }
                    else if (strcmp ((str + (srch - buf)), " bx") == 0) {

                        cum = 0x02;
                        *(asem->code + ip) = (char)cum;
                        ++ip;
                    }
                    else if (strcmp ((str + (srch - buf)), " cx") == 0) {

                        cum = 0x03;
                        *(asem->code + ip) = (char)cum;
                        ++ip;
                    }
                    else if (strcmp ((str + (srch - buf)), " dx") == 0) {

                        cum = 0x04;
                        *(asem->code + ip) = (char)cum;
                        ++ip;
                    }
                    else {

                        puts ("UNKNOWN SYMBOL");
                        return 1;
                    }
                }

                else {
                    // убрать копипаст
                    if (strcmp ((str + (srch - buf)), " [ax]") == 0) {
                        
                        cum = 0x02;
                        *(asem->code + ip) = (char)cum;
                        ++ip;

                        cum = 0x01;
                        *(asem->code + ip) = (char)cum;
                        ++ip;
                    }
                    else if (strcmp ((str + (srch - buf)), " [bx]") == 0) {

                        cum = 0x02;
                        *(asem->code + ip) = (char)cum;
                        ++ip;

                        cum = 0x02;
                        *(asem->code + ip) = (char)cum;
                        ++ip;
                    }
                    else if (strcmp ((str + (srch - buf)), " [cx]") == 0) {

                        cum = 0x02;
                        *(asem->code + ip) = (char)cum;
                        ++ip;

                        cum = 0x03;
                        *(asem->code + ip) = (char)cum;
                        ++ip;
                    }
                    else if (strcmp ((str + (srch - buf)), " [dx]") == 0) {

                        cum = 0x02;
                        *(asem->code + ip) = (char)cum;
                        ++ip;

                        cum = 0x04;
                        *(asem->code + ip) = (char)cum;
                        ++ip;
                    }
                    else {

                        cum = 0x03;
                        *(asem->code + ip) = (char)cum;
                        ++ip;

                        char *skobka1 = strchr (str + (srch - buf), '[');
                        char *skobka2 = strchr (str + (srch - buf), ']');
                        ++skobka1;
                        *skobka2 = '\0';

                        // scanf
                        type tmp1 =  convert (skobka1);
                        *(type*)(asem->code + ip) = tmp1;
                        ip += sizeof (type) / sizeof (char);
                    }

                }
                }
            }

            else if (cum == cmd_push) {

                if (prohod == 1) {

                    if (strchr (str + (srch - buf), 'x') == nullptr)
                    // ПЕРЕДЕЛАТЬ! sizeof
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

                        if (strcmp ((str + (srch - buf)), " ax") == 0) {
                            
                            cum = 0x01;
                            *(asem->code + ip) = (char)cum;
                            ++ip;

                            cum = 0x01;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                        }
                        else if (strcmp ((str + (srch - buf)), " bx") == 0) {

                            cum = 0x01;
                            *(asem->code + ip) = (char)cum;
                            ++ip;

                            cum = 0x02;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                        }
                        else if (strcmp ((str + (srch - buf)), " cx") == 0) {

                            cum = 0x01;
                            *(asem->code + ip) = (char)cum;
                            ++ip;

                            cum = 0x03;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                        }
                        else if (strcmp ((str + (srch - buf)), " dx") == 0) {

                            cum = 0x01;
                            *(asem->code + ip) = (char)cum;
                            ++ip;

                            cum = 0x04;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                        }
                        else {

                            cum = 0x00;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                            
                            type tmp1 = convert (str + (srch - buf));
                            *(type*)(asem->code + ip) = tmp1;
                            ip += sizeof (type) / sizeof (char);
                        }
                    }
                    else {
                        if (strcmp ((str + (srch - buf)), " [ax]") == 0) {
                            
                            cum = 0x02;
                            *(asem->code + ip) = (char)cum;
                            ++ip;

                            cum = 0x01;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                        }
                        else if (strcmp ((str + (srch - buf)), " [bx]") == 0) {

                            cum = 0x02;
                            *(asem->code + ip) = (char)cum;
                            ++ip;

                            cum = 0x02;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                        }
                        else if (strcmp ((str + (srch - buf)), " [cx]") == 0) {

                            cum = 0x02;
                            *(asem->code + ip) = (char)cum;
                            ++ip;

                            cum = 0x03;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                        }
                        else if (strcmp ((str + (srch - buf)), " [dx]") == 0) {

                            cum = 0x02;
                            *(asem->code + ip) = (char)cum;
                            ++ip;

                            cum = 0x04;
                            *(asem->code + ip) = (char)cum;
                            ++ip;
                        }
                        else {
                            
                            cum = 0x03;
                            *(asem->code + ip) = (char)cum;
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


