# ================================ AUTHORS =====================================
#Andrea Ghizzoni 157507
#Federica Lago 157955
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

# ================================= DESCRIPTION =====================================
DESCR = "This project allows some clients to ask services to servers as encode or decode messages and list all the messeges encoded on one of them."
TARGETS = "Aviable targets:"
T_BIN="make bin -> generates executable binary files"
T_RES="make res -> generets possible inputs"
T_TEST="make test -> calls the targets bin and res, then runs the programm"
T_CLEAR="make clear -> removes every temoprary file or directory"

# ================================= FOLDER =====================================
BIN=bin
RES=res
SRC=src

# ================================= RULES ======================================
# specify the silent targets
.SILENT: description clearbin clearres clearobjs clear 

# default option to make will print description 
default : description

# DEVELOP PURPOSE ONLY! remove when finish.
zip:
	# TODO make the tar.gz with all the necessary to deploy

# print the description project and all the make targets
description:
	echo "=============== CODEC ===============" 
	echo $(DESCR)
	echo ""
	echo $(TARGETS)
	echo $(T_BIN)
	echo $(T_RES)
	echo $(T_TEST)
	echo $(T_CLEAR)

# compile all the src files and puts objects into bin/
# - dep=clear res
# - compile all the src content
# - puts executeble files under bin directory 
bin: clear res
	@mkdir -p $(BIN) # -p prevents the error message if the directory exist
	$(MAKE) -C src/util/ util
	$(MAKE) -C src/server/ server
	$(MAKE) -C src/client/ client 
	@mv src/server/server bin
	@mv src/client/client bin

# generate an example of input file
# - dep=clearres
# - generate the example file under res folder 
res: clearres
	@mkdir -p $(RES) # -p prevents the error message if the directory exist
	$(MAKE) -C src/res res run

# test the program with the generated assets
# - dep=bin
# - run the program with with the assets as arguments
test: bin 
	@echo "=========== TESTING ============"
	./bin/server --name asd &
	./bin/client --name asd --key lol --message miobellissimomessaggio --encode & 
	./bin/client --name asd --key lol --message yxantxxxeexyabqehmsvua --decode &

	

#========== CLEANING TARGETS 
# simply call clear bin and clear res
# - dep=clearbin clearres 
clear: clearbin clearres clearobjs

# check if bin directory exists. if true remove all its content, otherwhise
# create will be create 
clearbin :
	if [ -d "$(BIN)" ]; then rm -rf $(BIN); fi

# check if res directory exists. if true remove all its content, otherwhise
# create will be create 
clearres:
	if [ -d "$(RES)" ]; then rm -rf $(RES); fi

# remove all the objects files in src/ folder
clearobjs:
	rm -f src/server/*.o
	rm -f src/client/*.o
	rm -f src/util/*.o
