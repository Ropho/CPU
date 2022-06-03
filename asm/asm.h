#include "enum.h"
#include "../onegin/onegin.h"

enum CMDS {

    #define DEF_CMD(name, number, argc, hash, code) CMD_##name = number,
    #define DEF_REG(name, number, hash)

    #include "cmds.h"

    #undef DEF_CMD
    #undef DEF_REG 
};

enum REGS {

    #define DEF_CMD(name, number, argc, hash, code) 
    #define DEF_REG(name, number, hash) REG_##name = number,

    #include "cmds.h"

    #undef DEF_CMD
    #undef DEF_REG 
};

int get_reg (char *reg);


typedef struct label {
    int hash = 0;
    int ip = 0;
}label;


typedef struct labels {     //LABEL
    int cnt_labels = 0;
    label cmd_label[10] = {};

}labels;
                                                                  


typedef struct asm_type {

    char ver = VERSION;

    int sign = SIGNATURE;

    int len_of_code = 0;

    char *code = nullptr;

    labels cmd_labels = {};

}asm_type;

int hash_C (char *head);
int cmd_num (char *cmd);
int rotl (int n);
int get_reg (char* reg);

int assembler_fillin (TEXT *cmd_file, FILE *out, int prohod, asm_type *asem);
