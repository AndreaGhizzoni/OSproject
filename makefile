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

# ================================= DESCRIPTION =====================================
DESCR = "This project allows some clients to ask services to servers as encode or decode messages and list all the messeges encoded on one of them."
TARGETS = "Aviable targets are BIN, which generetes executable binary files, ASSETS, which generets possible inputs, and CLEAN to remove every temporary file. Use TEST target to call all previous targets and start running the programm."

# ================================= FOLDER =====================================
BIN=bin
ASSETS=assets
SRC=src

# ================================= RULES ======================================
# specify the silent targets
.SILENT: description clearbin clearassets clearobjs clear 

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

# compile all the src files and puts objects into bin/
# - dep=clearbin 
# - compile all the src content
# - puts executeble files under bin directory 
bin: clearbin
	@mkdir -p $(BIN) # -p prevents the error message if the directory exist
	$(MAKE) -C src/assets/ assets 
	$(MAKE) -C src/util/ util
	$(MAKE) -C src/server/ server
	$(MAKE) -C src/client/ client 
	@mv src/server/server bin
	@mv src/client/client bin

# generate an example of input file
# - dep=clearassets
# - generate the example file under assets folder 
res: clearassets
	@mkdir -p $(ASSETS) # -p prevents the error message if the directory exist
	$(MAKE) -C src/assets assets run

# test the program with the generated assets
# - dep=assets bin
# - run the program with with the assets as arguments
test: assets bin

#========== CLEANING TARGETS 
# simply call clear bin and clear assets
# - dep=clearbin clearassets
clear: clearbin clearassets

# check if bin directory exists. if true remove all its content, otherwhise
# create will be create 
clearbin :
	if [ -d "$(BIN)" ]; then rm -rf $(BIN); fi

# check if assets directory exists. if true remove all its content, otherwhise
# create will be create 
clearassets:
	if [ -d "$(ASSETS)" ]; then rm -rf $(ASSETS); fi

# remove all the objects files in src/ folder
clearobjs:
	rm -f src/server/*.o
	rm -f src/client/*.o
	rm -f src/util/*.o
