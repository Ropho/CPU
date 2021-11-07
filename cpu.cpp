#include "cpu_func.h"

int main (void) {

    dump

    FILE *in = fopen ("binary.bin", "rb");

    my_stack *head = nullptr;

    create (head)

    int size = FILESIZE_FUNC_FSTAT (in);

    cpu_type cpu = {};
    create (cpu.func)

    int sign = 0;

    fread (&sign, sizeof (int), 1, in);
    if (sign != Signature) {

        puts ("WRONG SIGNATURE");
        return 0;
    }

    char ver = 0;
    fread (&ver, sizeof (char), 1, in); 

    if (ver != Version) {

        puts ("WRONG VERSION");
        return 0;
    }

    cpu.code = (char*) calloc (size, sizeof (char));


    fread (cpu.code, sizeof (char), size, in);

    prohod_code (&cpu, head, size);

    dead (head)             

    dead (cpu.func)

    return 0;
}
