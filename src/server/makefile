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
# -lpthread 	                  : for pthread
CFLAGS=-Wall -Werror -ansi -pedantic -faggressive-loop-optimizations -O2 \
	   -Wunreachable-code 

SRC=$(wildcard include/*.c)
OBJS=$(shell ls | grep .o)

.SILENT: description clear
.PHONY: description clear

default: description

description:
	echo "Makefile to compile all the server dep. Usage:"
	echo "> make dep    -> to compile all the server dep."
	echo "> make server -> to compile the server with all the dep."
	echo "> make clear  -> clear all objects file in root directory"

clear:
	$(RM) $(OBJS)

dep: $(SRC)
	$(GCC) $(CFLAGS) -c $^

server: clear dep
	$(GCC) $(CFLAGS) main.c -o server $(OBJS) ../util/cipher.o -lpthread


