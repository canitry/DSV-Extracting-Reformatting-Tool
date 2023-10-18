# if you type 'make' without arguments, this is the default
PROG    = extract
all:    $(PROG)

# Tell make about the file dependencies
HEAD	= token.h
OBJ     = token.o main.o wrtrow.o

# special libraries This can be blank
LIB     =

# select the compiler and flags
# you can over-ride these on the command line e.g. make DEBUG= 
CC      = gcc
DEBUG	= -ggdb
CSTD	=
WARN	= -Wall -Wextra -Werror
CDEFS	=
CFLAGS	= -I. $(DEBUG) $(WARN) $(CSTD) $(CDEFS)

$(OBJ):	$(HEAD)

# specify how to compile the target
$(PROG):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

#Specify the test number to test at a time

LISTMAIN = A B C D E F G
LISTVALG = V
LIST1    = 1 2 
LIST2    = 3 4 
LIST3    = 5 
LIST4    = 6 7 
LIST5    = 8 9 10 
LIST6    = 11 12 

.PHONY: clean alltest testmain testA testB testC testD testE testF testV

alltest:   testmain testA testB testC testD testE testF testV

testmain:   $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTMAIN)

testA:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LIST1)

testB:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LIST2)

testC:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LIST3)

testD:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LIST4)

testE:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LIST5)

testF:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LIST6)

testV:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTVALG)

# remove binaries
clean:
	rm -f $(OBJ) $(PROG)
