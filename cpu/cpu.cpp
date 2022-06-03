#include "cpu_func.h"

int main (void) {

    clock_t start_t = clock();
/////////////////////////////////////////////////
#ifndef NDEBUG
    dump
#endif

    FILE *in = fopen ("../asm/binary.bin", "rb");

    my_stack *head = nullptr;

    create (head)

    int size = FILESIZE_FUNC_FSTAT (in);

    cpu_type cpu = {};
    create (cpu.func)

    int sign = 0;

    fread (&sign, sizeof (int), 1, in);
    if (sign != SIGNATURE) {

        puts ("WRONG SIGNATURE");
        return 0;
    }

    char ver = 0;
    fread (&ver, sizeof (char), 1, in); 

    if (ver != VERSION) {

        puts ("WRONG VERSION");
        return 0;
    }

    cpu.code = (char*) calloc (size, sizeof (char));


    fread (cpu.code, sizeof (char), size, in);

/////////////////////////////////////////////////
    if (prohod_code (&cpu, head, size))
        puts ("BUGG in prohod");
/////////////////////////////////////////////////

    dead (head)             

    dead (cpu.func)

/////////////////////////////////////////////////
    clock_t end_t = clock();
    
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nTotal time taken by CPU: %f\n", total_t);
    return 0;
}
