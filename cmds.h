const char cmd_version = 0xA7;

enum CMD {

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
    cmd_jf       = 0x27,
    cmd_labl     = 0x30,
    cmd_call     = 0x40,
    cmd_ret      = 0x41,

};