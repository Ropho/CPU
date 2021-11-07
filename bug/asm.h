#include "enum.h"
#include "onegin.h"

enum CMDS {

    #define DEF_CMD(name, number, argc, code) CMD_##name = number,

    #define DEF_REG(name, number, hash)

    #include "cmds.h"

    #undef DEF_CMD
    #undef DEF_REG 
};

enum REGS {

    #define DEF_CMD(name, number, argc, code) 
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

int hash_C (char *head) ;
int cmd_num (char *cmd);
int rotl (int n);
int get_reg (char* reg);

int assembler_fillin (TEXT *cmd_file, FILE *out, int prohod, asm_type *asem);

enum CMD {
/*
    #define CMD_DEF(name, number, code) cmd_##name = number,
    #define REG_DEF(....)
    #define MOD_DEF(....)
    #include "...."
    #undef CMD_DEF
    #undef REG_DEF
    #undef MOD_DEF
*/
    cmd_end      = 0x10,
    cmd_push     = 0x11,
    cmd_pop      = 0x12,
    cmd_add      = 0x13,
    cmd_mul      = 0x14,
    cmd_in       = 0x15,
    cmd_out      = 0x16,
    cmd_sub      = 0x17,
    cmd_del      = 0x18,
    cmd_sqrt     = 0x19,
    cmd_jump     = 0x20,
    cmd_ja       = 0x21,
    cmd_jae      = 0x22,
    cmd_jb       = 0x23,
    cmd_jbe      = 0x24,
    cmd_je       = 0x25,
    cmd_jne      = 0x26,
    cmd_labl     = 0x30,
    cmd_call     = 0x40,
    cmd_ret      = 0x41,
    cmd_print    = 0x50,

};

// defines
