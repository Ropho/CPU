/*
DEF_CMD(end, 0x10, 0,
{
    return 0;
}
)



DEF_CMD(in, 0x15, 1,
{
            #ifdef INT_T
                scanf ("%d", &input);
            #else
                scanf ("%lf", &input);
            #endif
                pushka (head, input)
            ++ip;
})

DEF_CMD(out, 0x16, 1,
{
                #ifdef INT_T
                    printf ("VIVOD: %d\n", pop (head));
                #else
                    printf ("VIVOD: %.2f\n", pop (head));
                #endif

                ++ip;
})

DEF_CMD(push, 0x11, 1,
{
                ++ip;

                if (cpu->code[ip] == 0x00) {
                    ++ip;
                    pushka (head, *(type*)(cpu->code + ip))
                    ip += sizeof (type) / sizeof (char);
                }
                else if (cpu->code[ip] == 0x01) {
                    ++ip;
                    pushka (head, cpu->regs[cpu->code[ip]])
                    ++ip;
                }
                else if (cpu->code[ip] == 0x02) {

                    ++ip;
                    pushka  (head, cpu->ram[(int)cpu->regs[cpu->code[ip]]])
                    //Sleep (1000);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x03) {

                    ++ip;
                    pushka (head, cpu->ram[(int)*(type*)(cpu->code + ip)])
                    //Sleep (1000);
                    ip += sizeof (type) / sizeof (char);
                }
})

DEF_CMD(pop, 0x12, 1, 
{
    
                ++ip;

                if (cpu->code[ip] == 0x01) {
                    
                    ++ip;
                    cpu->regs[cpu->code[ip]] = pop (head);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x02) {

                    ++ip;
                    cpu->ram[(int)cpu->regs[cpu->code[ip]]] = pop (head);
                    //Sleep (1000);
                    ++ip;
                }
                else if (cpu->code[ip] == 0x03) {

                    ++ip;
                    cpu->ram[(int)*((type*)(cpu->code + ip))] = pop (head);
                    //Sleep (1000);
                    ip += sizeof (type) / sizeof (char);
                }
})

DEF_CMD(jump, 0x20, 1, 
{

                ++ip;     
                ip = *(int*)(cpu->code + ip);

})

DEF_CMD(ja, 0x21, 1, 
{
    type tmp1 = pop (head);
    type tmp2 = pop (head);

   if (tmp2 > tmp1) {                                                    
                                                                                            
        ++ip;                                                                               
        ip = *(int*)(cpu->code + ip);                                                                                                                                   \
    }                                                                                    
    else {                                                                                     
    ++ip;
    ip += sizeof (int) / sizeof (char); 
    }
})

DEF_CMD(jae, 0x22, 1, 
{
        
    type tmp1 = pop (head);
    type tmp2 = pop (head);

   if (tmp2 >= tmp1) {                                                    
                                                                                            
        ++ip;                                                                               
        ip = *(int*)(cpu->code + ip);                                                                                                                                   \
    }                                                                                    
    else {                                                                                     
    ++ip;
    ip += sizeof (int) / sizeof (char); 
    }
})

DEF_CMD(jb, 0x23, 1, 
{
    
    type tmp1 = pop (head);
    type tmp2 = pop (head);

   if (tmp2 < tmp1) {                                                    
                                                                                            
        ++ip;                                                                               
        ip = *(int*)(cpu->code + ip);                                                                                                                                   \
    }                                                                                    
    else {                                                                                     
    ++ip;
    ip += sizeof (int) / sizeof (char); 
    }
})

DEF_CMD(jbe, 0x24 1, 
{
    
    type tmp1 = pop (head);
    type tmp2 = pop (head);

   if (tmp2 <= tmp1) {                                                    
                                                                                            
        ++ip;                                                                               
        ip = *(int*)(cpu->code + ip);                                                                                                                                   \
    }                                                                                    
    else {                                                                                     
    ++ip;
    ip += sizeof (int) / sizeof (char); 
    }
})

DEF_CMD(je, 0x25, 1, 
{
    
    type tmp1 = pop (head);
    type tmp2 = pop (head);

    #ifdef INT_T
        if (tmp1 == tmp2) {
            ++ip;                                                                               
            ip = *(int*)(cpu->code + ip);                                                                                                                                   \
        }                                                                                    
        else {                                                                                     
        ++ip;
        ip += sizeof (int) / sizeof (char); 
        }
    #else
        if (fabs (tmp1 - tmp2) < EPS) {

            ++ip;                                                                               
            ip = *(int*)(cpu->code + ip);                                                                                                                                   \
        }                                                                                    
        else {                                                                                     
        ++ip;
        ip += sizeof (int) / sizeof (char); 
        }
    #endif                                                   
                                                                                            

})

DEF_CMD(jne, 0x26, 1, 
{
    
    type tmp1 = pop (head);
    type tmp2 = pop (head);

    #ifdef INT_T
        if (tmp1 != tmp2) {
            ++ip;                                                                               
            ip = *(int*)(cpu->code + ip);                                                                                                                                   \
        }                                                                                    
        else {                                                                                     
        ++ip;
        ip += sizeof (int) / sizeof (char); 
        }
    #else
        if (fabs (tmp1 - tmp2) > EPS) {

            ++ip;                                                                               
            ip = *(int*)(cpu->code + ip);                                                                                                                                   \
        }                                                                                    
        else {                                                                                     
        ++ip;
        ip += sizeof (int) / sizeof (char); 
        }
    #endif

})

DEF_CMD(call, 0x40, 1, 
{
     
        ++ip;
        pushka (cpu->func, ip + sizeof (int) / sizeof (char))
        ip = *(int*)(cpu->code + ip);
 

})

DEF_CMD(ret, 0x41, 0, 
{
    
    ip = pop (cpu->func);
})


DEF_CMD(add, 0x13, 0, 
{

    pushka (head, pop (head) + pop (head))
    ++ip;

})
    
DEF_CMD(sub, 0x17, 0, 
{

    type tmp1 = pop (head);
    type tmp2 = pop (head);  
    type qwe = (tmp2 - tmp1);

    pushka (head, qwe)
    ++ip;

})

DEF_CMD(mul, 0x14, 0, {
    
    pushka (head, pop (head) * pop (head))
    ++ip;
})

DEF_CMD(del, 0x18, 0, {
    

    double a = pop (head);
    double b = pop (head);
    pushka (head, b / a)
    ++ip;
})

DEF_CMD(sqrt, 0x19, 0, 
{
    pushka (head, sqrt (pop (head)))
    ++ip;
})
*/
//CMD_DEF(end, 0x10, {...})
//CMD_DEF(push, 0x11, {...})

DEF_REG(ax, 0x01, 0x3f8ab379)
DEF_REG(bx, 0x02, 0x5f6e4955)
DEF_REG(cx, 0x03, 0x51a1b819)
DEF_REG(dx, 0x04, 0x10895586)