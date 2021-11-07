#include "asm.h"

// аргументы командной строки
int main (void) {
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
    //FILE *in  = fopen ("com.txt", "rb");
    //FILE *in  = fopen ("fib.txt", "rb");  //ПАРАМОНАЧИ
    //FILE *in  = fopen ("qua.txt", "rb");  //ПАРАМОНАТКА
    FILE *in  = fopen ("quadr.txt", "rb"); //КВАДРАТЫ ЦЕЛЫХ ЧИСЕЛ
    //FILE *in = fopen ("ris.txt", "rb");   //рисунок
    
    assert (in != nullptr);

    FILE *out = fopen ("binary.bin", "wb");

    assert (out != nullptr);

    TEXT cmd_file = {};

    TEXT_struct_fillin (&cmd_file, in);
    
    asm_type asem = {};

    // Можно сделать нормальную оценку на MAX_SIZE_CMD * n_lines
    asem.code = (char*)calloc(MAX_LEN, sizeof (char));
    assert (asem.code != nullptr);

    if (assembler_fillin (&cmd_file, out, 1, &asem))
        puts ("BUGG in 1st asem");
    
    if (assembler_fillin (&cmd_file, out, 2, &asem))
        puts ("BUGG in 2nd asem");


    fclose (in);
    fclose (out);

    return 0;
}

// defines
int cmd_num (char *cmd) {

    assert (cmd != nullptr);

    if (strcmp (cmd, "push") == 0)
        return cmd_push;
    if (strcmp (cmd, "pop") == 0)
        return cmd_pop;
    if (strcmp (cmd, "add") == 0)
        return cmd_add;
    if (strcmp (cmd, "mul") == 0)
        return cmd_mul;
    if (strcmp (cmd, "sub") == 0)
        return cmd_sub;
    if (strcmp (cmd, "del") == 0)
        return cmd_del;
    if (strcmp (cmd, "sqrt") == 0)
        return cmd_sqrt;
    if (strcmp (cmd, "end") == 0)
        return cmd_end;
    if (strcmp (cmd, "in") == 0)
        return cmd_in;
    if (strcmp (cmd, "out") == 0)
        return cmd_out;
    if (strcmp (cmd, "jump") == 0)
        return cmd_jump;
    if (strcmp (cmd, "call") == 0)
        return cmd_call;
    if (strcmp (cmd, "ret") == 0)
        return cmd_ret;
    if (strcmp (cmd, "ja") == 0)
        return cmd_ja;
    if (strcmp (cmd, "jae") == 0)
        return cmd_jae;
    if (strcmp (cmd, "jb") == 0)
        return cmd_jb;
    if (strcmp (cmd, "jbe") == 0)
        return cmd_jbe;
    if (strcmp (cmd, "je") == 0)
        return cmd_je;
    if (strcmp (cmd, "jne") == 0)
        return cmd_jne;
    if (strcmp (cmd, "print") == 0)
        return cmd_print;
    else 
        return 0;
}