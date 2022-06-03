#include "stack_func.h"

extern size_t EXIT_COND;   //условие выхода из проги


int main (void) {
    
    FILE *out = fopen ("DUMP", "w");       //clearing the dump  file
    kotik(out)
    fclose (out);
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// TYPE HERE //////////////////////////////////////////////////////
// USE 4 FUNCTIONS
// create (name) - create stack with given name
// pushka (name) - push stack
// popkaa (name) - pop  stack
// dead (name)   - kill stack

#ifdef D_3          //mode with HASH
    
    my_stack *head = nullptr;

    
    create (head)
     

    pushka (head, 4)

    pushka (head, 4)
    pushka (head, 4)
    pushka (head, 4)
    pushka (head, 4)
    pushka (head, 4)
    pushka (head, 4)

    popka (head)

    dead (head)

    return 0;
#endif

#if defined D_2 || defined D_1      //mode with canaries and verificator

    my_stack *head = nullptr;

    create (head)

    pushka (head, 4)

    popka (head)

    dead (head)

    return 0;
#endif

#ifdef NDEBUG       //mode without anything (easy death)

    my_stack *head = nullptr;

    create (head)

    pushka (head, 4)
    
    popka (head)

    popka (head)

    popka (head)

    pushka (head,1)

    dead (head)

    return 0;
#endif    
}