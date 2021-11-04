#ifndef ENUM_H
#define ENUM_H

#include "stack_func.h"
#include "windows.h"
#include "math.h"

const int signature = 0xADDEADDE;
const double EPS = 0.01;

typedef struct label {

    char name[20];
    int num_cmd;
    int num_ip;

} label;

typedef struct file_in {

    int sign;
    char ver;
    char *code;
    type regs[4];
    type ram[1000];
    label labels[100];
    my_stack *func;

} file_in;

#endif