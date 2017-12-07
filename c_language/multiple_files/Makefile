# The compiler compiles each module independently. Therefore, each file uses 
# a function must prototype it first. So the compiler knows the function’s 
# argument types and the type of the return value.


# compile          files           output  the executable 
# $ gcc      mod1.c mod2.c main.c     -o           dbtest
# this command will separately compile the files and link them to output the 
# executable. 

# For example, if the gcc compiler gives output that looks like this:
# 	mod2.c:10: mod2.c: In function 'foo':
# 	mod2.c:10: error: 'i' undeclared (first use in this function) 
# 	mod2.c:10: error: (Each undeclared identifier is reported only once 
# 	mod2.c:10: error: for each function it appears in.)
# then the compiler indicates that mod2.c has an error at line 10, which is in 
# the function foo. Because no messages are displayed for mod1.c and main.c, 
# no errors are found compiling those modules. If the compile does not delete
# the object file (in this case the object files are main.o and mod1.o) then
# we do not need to recompile them again. instead we can use them directly 
# in the next compilation command.
# For example; 
# after fixing the mistake in mod2.c, we can run the following command
# $ gcc      mod1.o mod2.c main.o     -o           dbtest
# If the object file are deleted by the compiler we can force it to output them
# by including c flag
# for example;
# $ gcc -c mod1.c  this command should output => mod1.o 
# $ gcc -c mod2.c  this command should output => mod2.o 
# $ gcc -c main.c  this command should output => main.o 
# $ gcc      mod1.o mod2.o main.o     -o           dbtest //the compiler here 
#													      //will only link 
#														  //the objects files 
# $
# Because no error message was reported, the executable was placed in the file 
# dbtest.
