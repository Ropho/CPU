# CPU&ASM

## CONTENTS
[1.INTRO](#INTRO)

[2.ASSEMBLY](#ASSEMBLY)

[3.CPU](#CPU)


## INTRO
The task of the project was using previously written projects to:

  > write own **assembly & system of commands**


  > write a **semblance of a real CPU**


### PREVIOUSLY USED PROJECTS 
+ [STACK](#https://github.com/Ropho/stack)
+ [working with text](#https://github.com/Ropho/ONEGIN)

### OPTIONS
+ Language
> C
+ Compiler
> GCC


## ASSEMBLY

### How to use
+ Write a program using commands from the [command list](#Command-list)

EXAMPLE OF A PROGRAM

```
in
push 4
sqrt
out
out
end

```
+ use **makefile** to compile and get a binary file with coded commands

+ type *./main coms/ur_txt.txt* your txt file in a makefile instead of a given file


### OPTIONS
+ Compile
 ``` c++ 
all:
    gcc assembler.cpp asm_func.cpp ../onegin/onegin_func.cpp -o main ; ./main coms/com.txt
```

## CPU

### Brief information
+ CPU represents the real cpu in a computer so it has:
+ **stack**, a separate project, written previously
+ **ram** is represented as a static array of integers

### How to use
+ from asm we have a binary file which we will read with the cpu using needed binary file
```
FILE *in = fopen ("../asm/binary.bin", "rb");
```
+ you get your working program


### OPTIONS
+ Compile
```c++
 all:
	gcc cpu.cpp cpu_func.cpp ../stack/stack_func.cpp ../onegin/onegin_func.cpp -lm -o main ; ./main
```
### Command-list
To look at a command list go https://github.com/Ropho/CPU-ASM/blob/main/asm/cmds.h
