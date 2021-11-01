#ifndef ENUM_H
#define ENUM_H

#include "windows.h"

const int signature = 0xADDEADDE;

typedef struct file_in {

    int sign;
    char ver;
    char *code;
    int regs[4];
    int ram[1000];

} file_in;



#endif