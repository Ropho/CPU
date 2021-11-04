#ifndef STACK_FUNC_H
#define STACK_FUNC_H

//#define NDEBUG
#define D_1
//#define D_2                   //uslovnaya compilyatsya
//#define D_3

#include "stdio.h"
#include "malloc.h"
#include "assert.h"
#include "string.h"

//#define KEK    //define если работаем с Int иначе double

#ifdef KEK
    typedef int type;
    #define convert atoi
#else
    typedef double type;
    #define convert atof
#endif

#define kotik(out) fprintf(out, "\
                  　　　　　／＞　 フ   \n\
　　                　　　 | 　_　 _|   \n\
　 　　                 　／`ミ _x 彡   \n\
                　　 　 /　　　 　 |    \n\
                　　　 /　 ヽ　　 ﾉ     \n\
                　／￣|　　 |　|　|     \n\
                　| (￣ヽ＿_ヽ_)_)      \n\
                　＼二つ                \n\
                DEAD INSIDE 1000-7     \n\n");


#ifndef NDEBUG
    #define alive 0xDEAD
    #define EX_VER  {if (EXIT_COND) {printf ("u've been crashed (%x)", alive); return 0;}}
#endif


#ifndef NDEBUG

    #define stk_name(name, a) {strcpy (a, #name); strcat (a, "\0");} 
    #define $ ,__LINE__,__PRETTY_FUNCTION__,__FILE__
    #define hash(name) if (name->hash != hash_calc(name)) EXIT_COND = 1;
    

    #define create(name) {name = (my_stack*)calloc(1, sizeof (my_stack)); \
       cur_inf (name $); stk_name(name, name->stack_name) constructor (name, SIZE_CONSTRUCTOR); EX_VER}

#ifdef D_3
    #define pushka(name, value) {cur_inf (name $); push (name, value);  hash(name) EX_VER}  
    #define popka(name)  {cur_inf (name $);    pop (name); hash(name) EX_VER}
#endif

#if defined D_2 || defined D_1 
    #define pushka(name, value) {cur_inf (name $); push (name, value); EX_VER}  
    #define popka(name)  {cur_inf (name $);    pop (name); EX_VER}
#endif

    #define dead(name) {cur_inf (name $); delete_stack (&name);}

#endif

#ifdef NDEBUG
    #define create(name) {name = (my_stack*)calloc(1, sizeof (my_stack)); constructor (name, SIZE_CONSTRUCTOR);}
    #define pushka(name, value) {push (name, value);}  
    #define popka(name)  {pop (name);}
    #define dead(name) {delete_stack (&name);}
#endif

const int SIZE_CONSTRUCTOR = 10;
const size_t MULTIPLIER = 10;
const size_t DIVISOR = 20;

#define MUSOR 666


enum ERRORS {

    NO_ERROR                 = 0,
    MEMMORY_ALLOCATION_ERROR = 1,
    STACK_OVERFLOW           = 2,
    STACK_UNDERFLOW          = 3,
    NAS_VZLOMALI             = 4,
};


typedef struct my_stack {


#if defined D_2 || defined D_3
    long long left_canary;
#endif

    int size_array;
    int    size_stack;
    type   *arr;

#ifndef NDEBUG
    int error;
    char stack_name[10];
    char func_name[10];
    char file_name[20];
    int  line;
#endif


#ifdef D_3
    long long hash;
#endif

#if defined D_2 || defined D_3
    long long right_canary;
#endif
} my_stack;



void cur_inf (my_stack *head, const int line, const char *func, const char *file);

void constructor (my_stack *head, int size_array);

void delete_stack (my_stack **head);

static void destructor (my_stack *head);

void push (my_stack *head, type value);

type pop (my_stack *head);

void verificator (my_stack *head);

void dump (my_stack *head);

long long hash_calc (my_stack *head);

#endif