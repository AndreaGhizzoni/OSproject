# ================================ AUTHORS =====================================
#Federica Lago 157955
#Andrea Ghizzoni 157507
#PROJECT: #1 CODEC
#COURSE: Sistemi Operativi
#YEAR: 2014

# ================================ COPILER =====================================
GCC=gcc

# ============================ COMPILER OPTIONS ================================
# -Wall                           : turns on the warnings messages
# -Werror                         : make all warnings into errors
# -ansi                           : for strict C semantics
# -pedantic                       : necessary for -ansi 
# -faggressive-loop-optimizations : optimization flag
# -O2                             : optimization flag
# -Wunreachable-code              : detects that code will never be executed 
CFLAGS=-Wall -Werror -ansi -pedantic -faggressive-loop-optimizations -O2 \
	   -Wunreachable-code

SRC=$(wildcard *.c)
OBJS=$(shell ls | grep .o)

.SILENT: description 
.PHONY: description 

default: description

description:
	echo "Makefile to compile the utilities modules. Usage:"
	echo "> make util   -> to compile the utilities."

util: $(SRC)
	@rm -f $(OBJS)
	$(GCC) $(CFLAGS) -c $^

