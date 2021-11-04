#include "asm.h"



//сделать запись сначала в массив а потом всё сразу в файл (намного быстрее)
void assembler_fillin (TEXT *cmd_file, FILE *out) {

    file_in cpu = {};
        
    cpu.sign = signature;

    cpu.ver = cmd_version;

    fwrite (&cpu.sign, sizeof (int), 1, out);

    fwrite (&cpu.ver, sizeof (char), 1, out);       //брать версию из файла

        
    for  (int i = 0; i < cmd_file->number_lines; ++i) {

        char *buf = cmd_file->array_pointers[i].str;
        char *srch = nullptr; //search

        
        srch = (strchr (buf, '\r'));
        if (srch != nullptr)
            *srch = '\0';

        srch = strchr(buf, ';');
        if (srch != nullptr) 
            *srch = '\0';

        srch = strchr (buf, ' ');
        if (srch == nullptr) {
            
            srch = strchr (buf, ':');

            if (srch == nullptr) {
                if (*(buf + strlen (buf) - 1) == '\r')
                    *(buf + strlen (buf) - 1) = '\0';
                int tmp = cmd_num (buf);
                fwrite (&tmp, sizeof (char), 1, out);
            }
            else {
                int tmp = cmd_labl;
                fwrite (&tmp, sizeof (char), 1, out);

                *srch = '\0';
                tmp = strlen (buf);
                fwrite (&tmp, sizeof (char), 1, out);

                while (buf != srch) {
                    fwrite (buf, sizeof (char), 1, out);
                    ++buf;
                }
            }
        }
        else {
            
            char str[30] = {};
            strncpy (str, buf, srch - buf);
            int tmp = cmd_num (str);
            fwrite (&tmp, sizeof (char), 1, out); 
            
            strcpy (str, buf);
            //puts (str);
            //abort ();

            if (tmp == cmd_call) {

                strcpy (str, strchr (str, ' ')  + 1);
                //puts (str);
                int str_len = strlen (str);
                fwrite (&str_len, sizeof (char), 1, out);

                for (int i = 0; i < str_len; ++i) {

                    int tmp = str[i];
                    fwrite (&tmp, sizeof (char), 1, out);
                }
                
                //abort ();

            }
            else if (tmp == cmd_jump || tmp == cmd_jae || tmp == cmd_ja || tmp == cmd_je ||
                     tmp == cmd_jb || tmp == cmd_jbe || tmp == cmd_jne) {

                char *check = strchr (str + (srch - buf), ':');
                if (check == nullptr)  {
                    ++srch; //srch != ' '

                    if (isdigit (*srch)) {
                        tmp = 0x00;     //jump 5
                        fwrite (&tmp, sizeof (char), 1, out);
                        
                        tmp = atoi (srch);
                        fwrite (&tmp, sizeof (int), 1, out);
                    }
                    else { 
                        tmp = 0x01; // jump next
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = strlen (srch);
                        fwrite (&tmp, sizeof (char), 1, out);

                        while (*srch != '\0') {
                            fwrite (srch, sizeof (char), 1, out);
                            ++srch;    
                        }
                    }
                }
                else {
                    tmp = 0x02; //jump :1
                    fwrite (&tmp, sizeof (char), 1, out);

                    *check = '\0';
                    srch += 2;
                        type tmp1 = convert (srch);
                        fwrite (&tmp1, sizeof (type), 1, out);
                }
            }
            else if (tmp == cmd_pop) {

                if (strchr (str + (srch - buf), '[') == nullptr) {
                                                                    //we can search for 'a', 'b', 'c' and 'd'
                    if (strcmp ((str + (srch - buf)), " ax") == 0) {
                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " bx") == 0) {
                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " cx") == 0) {
                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x03;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " dx") == 0) {
                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x04;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                }

                else {
                    if (strcmp ((str + (srch - buf)), " [ax]") == 0) {
                        
                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " [bx]") == 0) {
                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " [cx]") == 0) {
                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x03;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " [dx]") == 0) {
                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x04;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else {
                        tmp = 0x03;
                        fwrite (&tmp, sizeof (char), 1, out);

                        char *skobka1 = strchr (str + (srch - buf), '[');
                        char *skobka2 = strchr (str + (srch - buf), ']');
                        ++skobka1;
                        *skobka2 = '\0';

                        type tmp1 =  convert (skobka1);
                        fwrite (&tmp1, sizeof (type), 1, out);
                    }

                }
            }

            else if (tmp == cmd_push) {

                if (strchr (str + (srch - buf), '[') == nullptr) {

                    if (strcmp ((str + (srch - buf)), " ax") == 0) {
                        
                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " bx") == 0) {
                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " cx") == 0) {
                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x03;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " dx") == 0) {
                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x04;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else {

                        tmp = 0x00;
                        fwrite (&tmp, sizeof (char), 1, out);
                        
                        type tmp1 = convert (str + (srch - buf));
                        
                        fwrite (&tmp1, sizeof (type), 1, out);
                        //printf ("%f\n", tmp1); 
                    }
                }
                else {
                    if (strcmp ((str + (srch - buf)), " [ax]") == 0) {
                        
                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x01;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " [bx]") == 0) {
                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " [cx]") == 0) {
                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x03;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else if (strcmp ((str + (srch - buf)), " [dx]") == 0) {
                        tmp = 0x02;
                        fwrite (&tmp, sizeof (char), 1, out);

                        tmp = 0x04;
                        fwrite (&tmp, sizeof (char), 1, out);
                    }
                    else {
                        tmp = 0x03;
                        fwrite (&tmp, sizeof (char), 1, out);

                        char *skobka1 = strchr (str + (srch - buf), '[');
                        char *skobka2 = strchr (str + (srch - buf), ']');
                        ++skobka1;
                        *skobka2 = '\0';

                        type tmp1 = convert (skobka1);
                        fwrite (&tmp1, sizeof (type), 1, out);
                    }
                }
            }
            else {

                type tmp1 = convert (str + (srch - buf));
                        
                fwrite (&tmp1, sizeof (type), 1, out);            
            }
        }
    }
}

