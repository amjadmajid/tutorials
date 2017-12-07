/*

USING GDB

To use the GNU Debugger you must compile with the flag:
`-g`

To run the prgram under the control of the GDB type:
`run`

WORKING WITH VARIABLES

To display the value of a variable:
`print <variable>`
To force GDB to target a global name use `filename::variable`
To force GDB to target a local name use `function::variable`
Adding /x before the vaiable will display the value in hexadecimal

To set the value of a variable use:
`set var <varaible>=<expression>`
`set var <array/struct>={...}


To show the program arguments that are passed with `run` command use:
`show args`

To show the local variables use:
`info locals`

SOURCE FILE DISPLAY

To list a number of source code lines use:
`list <start line number> <end line number>`
per default 10 lines will be displayed.
-/+ symbols can be used to make the offset
before or after the <start line number>.
`list foo` will display 10 lines around the function stub

CONTROLLING  PROGRAM EXECUTION

To run the program from the bignning use:
`run`

To terminate the execution of a prgram use:
`quit`

BREAKPOINTS

To insert a breakpoint use:
`break <filename>:<line number>`
`break <filename>:<function name>`

To list the breakpoint use:
`info break`

To remove a breakpoint use:
`clear <line number>` or `clear <function name>`

To continue the execution use the command `continue`

SINGLE STEPPING
To step through the program use:
`step <number of lines>`
`next`
The `step` command will step into a function.
The `next` command will not step into a function.

STACK TRACE

To see the function call stack use:
`backtrance` or `bt`

CALLING FUNCTION and SETTING ARRAYS and STRUCTURES

To call a function use:
`print <func(args)>`

DISPLAY MEMORY [copied from http://visualgdb.com/gdbreference/commands/x]

x command
Displays the memory contents at a given address using the specified format.

Syntax

x [Address expression]
x /[Format] [Address expression]
x /[Length][Format] [Address expression]
x
Parameters

Address expression
Specifies the memory address which contents will be displayed. This can be the address itself or any C/C++ expression evaluating to address. The expression can include registers (e.g. $eip) and pseudoregisters (e.g. $pc). If the address expression is not specified, the command will continue displaying memory contents from the address where the previous instance of this command has finished.
Format
If specified, allows overriding the output format used by the command. Valid format specifiers are:
o - octal
x - hexadecimal
d - decimal
u - unsigned decimal
t - binary
f - floating point
a - address
c - char
s - string
i - instruction
The following size modifiers are supported:

b - byte
h - halfword (16-bit value)
w - word (32-bit value)
g - giant word (64-bit value)
Length
Specifies the number of elements that will be displayed by this command.
Examples

We will demonstrate the x command using a basic program that defines a byte array on the stack:

int main()
{
    char testArray[] = "0123456789ABCDEF";
    return 0;
}
We will now use the x command to display the contents of the memory occupied by the testArray array in various formats. We will also show how to use the x command to disassemble the instructions pointed by the program counter pseudo-register ($pc).

(gdb) start
Temporary breakpoint 1 at 0x8048446: file test.cpp, line 2.
Starting program: /home/bazis/test 

Temporary breakpoint 1, main () at test.cpp:2
2 {
(gdb) next
3 char testArray[] = "0123456789ABCDEF";
(gdb) next
4 return 0;
(gdb) x testArray
0xbfffef7b: 0x33323130
(gdb) x/c testArray
0xbfffef7b: 48 '0'
(gdb) x/5c testArray
0xbfffef7b: 48 '0' 49 '1' 50 '2' 51 '3' 52 '4'
(gdb) x/2c
0xbfffef80: 53 '5' 54 '6'
(gdb) x/wx testArray
0xbfffef7b: 0x33323130
(gdb) x/2hx testArray
0xbfffef7b: 0x3130 0x3332
(gdb) x/gx testArray
0xbfffef7b: 0x3736353433323130
(gdb) x/s testArray
0xbfffef7b: "0123456789ABCDEF"
(gdb) x/5bx testArray
0xbfffef7b: 0x30 0x31 0x32 0x33 0x34
(gdb) x/5i $pc
=> 0x8048477 <main()+58>: mov $0x0,%eax
0x804847c <main()+63>: mov 0x1c(%esp),%edx
0x8048480 <main()+67>: xor %gs:0x14,%edx
0x8048487 <main()+74>: je 0x804848e <main()+81>
0x8048489 <main()+76>: call 0x8048310 <__stack_chk_fail@plt>


HELP

classes are a group of commands

Calling `help` will list all the classes
Call `help <class name>` to get a list of all
commands in that class

*/

#include <stdio.h>
#include <stdlib.h>

struct date {
  int month;
  int day;
  int year;
};

struct date foo (struct date x)
{
    ++x.day;
    return x;
}

int main (void)
{
  struct date today = {23, 12, 2016};
  int array[5] = {1, 2, 3, 4, 5};

  struct date *newdate, foo();
  /*
  struct date *newdate;
  struct date foo();
  */

  char *string ="test string";
  int i=3;

  //This struct will be on the heap
  newdate = (struct date *) malloc (sizeof (struct date));
  newdate->month = 12;
  newdate->day = 24;
  newdate->year = 2016;

  today = foo (today);
  free (newdate);
return 0;
}
