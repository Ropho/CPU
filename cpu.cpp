#include "cpu_func.h"

int main (void) {

    FILE *out = fopen ("DUMP", "w");       //clearing the dump  file
    kotik(out)
    fclose (out);
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
    FILE *in = fopen ("binary.bin", "rb");

#if defined D_2 || defined D_1

    my_stack *head = nullptr;

    create (head)

    int size = FILESIZE_FUNC_FSTAT (in);

    file_in cpu = {};
    create (cpu.func)

    for (int i = 0; i < 100;++i)
        (cpu.labels[i]).num_ip = -1;

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

    if (prohod_code (&cpu, head, 1, size) == 0) {
        printf ("BUGGGG 1");
    }

    if (prohod_code (&cpu, head, 2, size) == 0) {
        printf ("BUGGGG 2");
    }
    

/*
    dead (head)             //ПРОСТО КЕКВ НЕ ФРИШИТСЯ НИЧЕГО
    puts ("CRASH_1???");

    //dead (cpu.func)
    puts ("CRASH_2???");
*/
    return 0;
}
#endif
