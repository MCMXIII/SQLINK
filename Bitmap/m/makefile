# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -ansi -pedantic

# define any directories containing header files other than /usr/include
# EXAMPLE -> INCLUDES = -I/home/proj/include  
INCLUDES =

# define any libraries to link into executable ( math library as an example )
# EXAMPLE ->LIBS =  -lm
LIBS =

# define the C source files
SRCS = bitmap.c main.c

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Replacing the suffix ‘.c’ of all files in the macro SRCS
# with the suffix ‘.o’ 
#
OBJS = $(SRCS:.c=.o)

# define the name of executable file 
MAIN = bitmap

#--------------------------------------------------------------------
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above 
#--------------------------------------------------------------------

all: $(MAIN)
	@echo  Program named ‘Exe’ has been compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

