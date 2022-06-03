#include "stack_func.h"

size_t EXIT_COND = 0;

#ifdef D_3

    static long long rotl (long long n) {
        unsigned d = 13;
        n *= d;
        return (n << d)|(n >> (32 - d));
    }

    long long hash_calc (my_stack *head) {

        assert (head != nullptr);
        
        long long hash = 0x1337;

        verificator (head);

        hash ^= rotl (head->left_canary);
        hash ^= rotl (head->error);
        hash ^= rotl (head->size_array);
        hash ^= rotl (head->size_stack);
        
        if (head->arr != nullptr) {
            hash ^= *((long long*)(head->arr - sizeof (long long) / sizeof (type)));
            hash ^= *((long long*)(head->arr + head->size_array));
        }

        if (head->size_stack > 0 && head->arr != nullptr)
            for (int i = 0; i < head->size_stack; ++i)
                hash ^= rotl (*(head->arr + i));

        int tmp = 0;

        for (int i = 0; i < strlen (head->stack_name); ++i) 
            tmp += head->stack_name[i];
            hash ^= rotl (tmp);
        
        tmp = 0;
        for (int i = 0; i < strlen (head->func_name); ++i)
            tmp += head->func_name[i];
            hash ^= rotl (tmp);
        
        tmp = 0;
        for (int i = 0; i < strlen (head->file_name); ++i)
            tmp += head->file_name[i];
            hash ^= rotl (tmp); 
        
        hash ^= rotl (head->line);
        hash ^= rotl (head->right_canary);

        //avalanche
        hash ^= (hash >> 16);
        hash *= 0x85ebca6b;
        hash ^= (hash >> 13);
        hash *= 0xc2b2ae35;
        hash ^= (hash >> 16);
        
        return hash;    
    }
#endif

#ifndef NDEBUG

     void dump (my_stack *head) {

        assert (head != nullptr);

        FILE *out = fopen ("DUMP", "a");
        assert (out != nullptr);

        fprintf (out, "STACK <%s> [%p] at (%s) at (%s) (%d): ", head->stack_name, head, head->func_name, head->file_name, head->line);

        if (head->error == MEMMORY_ALLOCATION_ERROR) {

            fprintf (out, "ARA ARA, memmory trouble (ERROR : %d)\n", head->error);
            fclose (out);
            return;
        }

        else if (head->error == STACK_UNDERFLOW) {

            fprintf (out, "ARA ARA, STACK UNDERFLOW (ERROR : %d)\n", head->error);
            fclose (out);
            return;
        }

        else if (head->error == STACK_OVERFLOW) {

            fprintf (out, "ARA ARA, STACK OVERFLOW (ERROR : %d) STACK WAS REALLOC''ED ", head->error);
        }

        else if (head->error == NAS_VZLOMALI) {
            fprintf (out, "RIP canary dead (ERROR : %d) ", head->error);
        }


        if (head->size_stack == 0 && head->size_array == SIZE_CONSTRUCTOR) {
            if ((head->size_array > 0 && *(head->arr) != MUSOR) || head->arr == nullptr || head->size_array == 0)
                fprintf (out, "Stack created\n\n");
            else 
                fprintf (out, "EMPTY STACK\n\n");
        }
        else if (head->arr == nullptr && head->size_stack == MUSOR && head->size_array == MUSOR) {
            
            fprintf (out, "Stack DEcreated\n\n");
        }
        else {

            fprintf (out,"\n{\n");

    #if defined D_2 || defined D_3
        if (head->left_canary == alive)
            fprintf (out, "left canary alive :)\n\n");
        else
            fprintf (out, "left canary dead :(\n\n");

        fprintf (out,"size = %d\ncapacity = %d\n", head->size_stack, head->size_array);

        if (head->arr != nullptr && (*((long long*)(head->arr - sizeof (long long) / sizeof (type))) == alive))
            fprintf (out, "left canary in stack alive :)\n");
        else
            fprintf (out, "left canary in stack dead :(\n");

        for (int i = 0; i < head->size_stack; ++i)
            fprintf (out, "\t[%d] = %d\n", i, *(head->arr + i));

        if (*((long long*)(head->arr + head->size_array)) == alive)
            fprintf (out, "right canary in stack alive :)\n");
        else
            fprintf (out, "right canary in stack dead :(\n");

        if (head->right_canary == alive)
            fprintf (out, "\nright canary alive :)\n");
        else
            fprintf (out, "\nright canary dead :(\n");
        fprintf (out, "}\n\n");

    #else
            fprintf (out,"size = %d\ncapacity = %d\n", head->size_stack, head->size_array);
            #ifdef INT_T
                for (int i = 0; i < head->size_stack; ++i)
                    fprintf (out, "\t[%d] = %d\n", i, *(head->arr + i));
                fprintf (out, "}\n\n");
            #else
                
            for (int i = 0; i < head->size_stack; ++i)
                fprintf (out, "\t[%d] = %.3f\n", i, *(head->arr + i));
            fprintf (out, "}\n\n");
            #endif
    #endif
        }
        
        fclose (out);
        return;
    }

#else 
    
    static void dump (my_stack *head) {

        FILE *out = fopen ("DUMP", "a");
        fprintf (out,"size = %d\ncapacity = %d\n", head->size_stack, head->size_array);

        for (int i = 0; i < head->size_stack; ++i)
            fprintf (out, "\t[%d] = %d\n", i, *(head->arr + i));

        fprintf (out, "\n");
        fclose (out);
        return;
    }

#endif


#ifndef NDEBUG

     void verificator (my_stack *head) {

        assert (head != nullptr);

        if (head->arr == nullptr && head->size_array != 0) {

            head->error = MEMMORY_ALLOCATION_ERROR;
            EXIT_COND = 1;
            return;
        }

        else if (head->size_stack < 0) {

            head->error = STACK_UNDERFLOW;
            EXIT_COND = 1;
            return;
        }

        else if (head->size_stack > head->size_array) {

            head->error = STACK_OVERFLOW;
            EXIT_COND = 0;
            return;
        }
        
    #if defined D_2 || defined D_3

        else if (head->left_canary != alive || head->right_canary != alive) {

            head->error = NAS_VZLOMALI;
            EXIT_COND = 1;
            return;
        }
        
        else if (head->arr != nullptr) {
            if (*((long long*)(head->arr - sizeof (long long) / sizeof (type))) != alive || 
                *((long long*)(head->arr + head->size_array))                  != alive) {
                head->error = NAS_VZLOMALI;
                EXIT_COND = 1;
                return;
            }
        }
    #endif
    }

    void cur_inf (my_stack *head, const int line, const char *func, const char *file) {

        assert (head != nullptr);

        head->line = line;
        strcpy (head->func_name, "");
        strcpy (head->func_name, func);
        strcat (head->func_name, "\0");

        strcpy (head->file_name, "");
        strcpy (head->file_name, file);
        strcat (head->file_name, "\0");

        return;
    }

#endif

void constructor (my_stack *head, int size_array) {

    assert (head != nullptr);

    head->size_stack   = 0;
    head->size_array   = size_array;
    
#ifndef NDEBUG
    head->error        = NO_ERROR;
#endif

    if (head->size_array > 0) {

#if defined D_2 || defined D_3
    head->arr          = (int*)calloc(head->size_array * sizeof (type) + 2 * sizeof (long long), sizeof (char)); //with 2 canaries

    assert (head->arr != nullptr);  //verificator

    *((long long*)head->arr) = alive; 

    head->arr = head->arr + sizeof (long long) / sizeof (type);

    *((long long*)(head->arr + head->size_array)) = alive;
#else
    head->arr = (type*)calloc(head->size_array, sizeof (type));
#endif
    }
    
    else if (head->size_array == 0) { 
        
#if defined D_2 || defined D_3
        head->arr = (int*)calloc(2 * sizeof (long long), sizeof (char)); //2 canaries
        *((long long*)head->arr) = alive; 
        head->arr = head->arr + sizeof (long long) / sizeof (type);
        *(long long*)(head->arr) = alive;

#else
        head->arr = nullptr;
#endif
    }
    else if (head->size_array < 0)
        head->arr = nullptr;

#if defined D_2 || defined D_3
    head->left_canary  = alive;
    head->right_canary = alive;
#endif

#ifdef D_3
    head->hash = 0;
#endif

#ifndef NDEBUG
    verificator (head);
    dump (head);
#endif
}


void delete_stack (my_stack **head) {

    assert (*head != nullptr);
    destructor (*head);
#ifndef NDEBUG
    dump (*head);
#endif
    //free(*head);      //ТУТ КРАШ!!!
    *head = nullptr;

}

static void destructor (my_stack *head) {

    assert (head != nullptr);
#if defined D_2 || defined D_3
    free (head->arr - sizeof (long long) / sizeof (type));

    head->left_canary = MUSOR;
    head->right_canary = MUSOR;
#else
    //free (head->arr); // ТУТ КРАШ!!!!
#endif

    (head)->arr = nullptr;
    (head)->size_stack = MUSOR;
    (head)->size_array = MUSOR;

#ifdef D_3
    head->hash = MUSOR;
#endif

#ifndef NDEBUG
    head->error = MUSOR;
#endif
}

void push (my_stack *head, type value) {

    assert (head != nullptr);
    
    head->size_stack += 1;

#if defined D_2 || defined D_3
    verificator (head);

    if (head->error == STACK_OVERFLOW) {

        int old_size = head->size_array;

        if (head->size_array != 0)
             head->size_array = head->size_array * MULTIPLIER;
        else head->size_array ++;
        
        if (head->size_array > 0) {
            long long tmp = *(long long*)(head->arr + old_size);
            *(long long*)(head->arr + old_size) = 0;
            head->arr = head->arr - sizeof (long long) / sizeof (type);

            head->arr = (type*) realloc (head->arr, sizeof (type) * head->size_array + 2 * sizeof (long long));
            assert (head->arr != nullptr);

            // можно добавить умный реалок 

            head->arr = head->arr + sizeof (long long) / sizeof (type);

            *(long long*)(head->arr + head->size_array) = tmp;
        }
    } 
#endif

#ifdef D_1
    verificator (head);

    if (head->error == STACK_OVERFLOW) {

        if  (head->size_array != 0)
             head->size_array = head->size_array * MULTIPLIER;
        else head->size_array ++;
        
        if (head->size_array > 0)
            head->arr = (type*) realloc (head->arr, sizeof (type) * head->size_array);

        assert (head->arr != nullptr);

            // можно добавить умный реалок 

    } 
#endif

#ifdef NDEBUG
    if (head->size_stack > head->size_array) {

        if (head->size_array != 0)
                head->size_array = head->size_array * MULTIPLIER;
        else head->size_array ++;
        
        if (head->size_array > 0)
            head->arr = (type*) realloc (head->arr, sizeof (type) * head->size_array);
            
        assert (head->arr != nullptr);

            // можно добавить умный реалок 

    } 
#endif

    if (EXIT_COND != 1)
        *(head->arr + head->size_stack - 1) = value;

    dump (head);

#ifndef NDEBUG
    head->error = NO_ERROR;
#endif

#ifdef D_3
    head->hash = hash_calc (head);
#endif

}

type pop (my_stack *head) {

    assert (head != nullptr);

    --(head->size_stack);

        
#ifndef NDEBUG
    verificator (head);
#endif

    if (EXIT_COND != 1) {

        type tmp = *(head->arr + head->size_stack);
        *(head->arr + head->size_stack) = MUSOR;
    
        if (head->size_stack < head->size_array / DIVISOR) {
        #if defined D_2 || defined D_3  
            int old_size = head->size_array;

            head->size_array = head->size_array / DIVISOR;
        
            long long tmp = *(long long*)(head->arr + old_size);
            *(long long*)(head->arr + old_size) = 0;
            head->arr = head->arr - sizeof (long long) / sizeof (type);
            head->arr = (type*) realloc (head->arr, sizeof (type) * head->size_array + 2 * sizeof (long long));
            assert (head->arr != nullptr);
            head->arr = head->arr + sizeof (long long) / sizeof (type);

            *(long long*)(head->arr + head->size_array) = tmp;
        #else
            //head->size_array = head->size_array / DIVISOR;
            //head->arr = (type*) realloc (head->arr, sizeof (type) * head->size_array);
        #endif
        }

        dump (head);
    #ifdef D_3
        head->hash = hash_calc (head);
    #endif
        return tmp;
    }

    dump (head);

#ifdef D_3
    head->hash = hash_calc (head);
#endif
    return 666;
}
