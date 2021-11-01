#include "enum.h"
#include "onegin.h"
#include "cmds.h"

int cmd_num (char *cmd) {

    if (strcmp (cmd, "push") == 0)
        return cmd_push;
    if (strcmp (cmd, "pop") == 0)
        return cmd_pop;
    if (strcmp (cmd, "add") == 0)
        return cmd_add;
    if (strcmp (cmd, "mul") == 0)
        return cmd_mul;
    if (strcmp (cmd, "end") == 0)
        return cmd_end;
    if (strcmp (cmd, "in") == 0)
        return cmd_in;
    if (strcmp (cmd, "out") == 0)
        reutrn cmd_out;
    
    else 
        return 0;
}

void assembler_fillin (TEXT *cmd_file, FILE *out) {

    file_in cpu = {};
        
    cpu.sign = signature;

    cpu.ver = cmd_version;

    fwrite (&cpu.sign, sizeof (int), 1, out);

    fwrite (&cpu.ver, sizeof (char), 1, out);

        
    for  (int i = 0; i < cmd_file->number_lines; ++i) {

        char *buf = cmd_file->array_pointers[i].str;
        char *srch = nullptr; //search

        
        srch = (strchr (buf, '\r'));
        if (srch != nullptr)
            *srch = '\0';

        //puts (buf);
        srch = strchr(buf, ';');
        if (srch != nullptr) 
            *srch = '\0';

        srch = strchr (buf, ' ');
        if (srch == nullptr) {
            
            if (*(buf + strlen (buf) - 1) == '\r')
                *(buf + strlen (buf) - 1) = '\0';
            int tmp = cmd_num(buf);
            fwrite (&tmp, sizeof (char), 1, out);
        }
        else {
            
            char str[30] = {};
            strncpy (str, buf, srch - buf);
            int tmp = cmd_num (str);
            fwrite (&tmp, sizeof (char), 1, out); 
            
            strcpy (str, buf);

            if (tmp == cmd_pop) {

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

                        tmp = atoi (skobka1);
                        fwrite (&tmp, sizeof (int), 1, out);
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
                        
                        tmp = atoi (str + (srch - buf));
                        
                        fwrite (&tmp, sizeof (int), 1, out);  
                    }
                }
                else {
                            //puts (str + (srch - buf));
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

                        tmp = atoi (skobka1);
                        fwrite (&tmp, sizeof (int), 1, out);
                    }

                }

                    
                }
                
                else {

                        tmp = atoi (str + (srch - buf));
                        
                        fwrite (&tmp, sizeof (int), 1, out);            
                }
            }
        }
}

int main (void) {
    
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
    FILE *in  = fopen ("com.txt", "rb");
    FILE *out = fopen ("binary.bin", "wb");

    TEXT *cmd_file = (TEXT*)calloc(1, sizeof (TEXT));

    TEXT_struct_fillin (cmd_file, in);

    assembler_fillin (cmd_file, out);

    fclose (out);

    return 0;
}