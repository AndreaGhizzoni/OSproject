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

.SILENT: description clear run
.PHONY: description clear

default: description

description:
	echo "Makefile to compile the program assets generator. Usage:"
	echo "> make res    -> compile the program wich generate the assets file."
	echo "> make clear  -> clear the old assets generator program"
	echo "> make run    -> run the assets program generator."

run: clear res  
	./res

clear:
	$(RM) res 

res: clear 
	$(GCC) $(CFLAGS) res.c -o res

