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

# ================================= FOLDER =====================================
BIN=bin
ASSETS=assets
SRC=src

# ================================= RULES ======================================
# specify the silent targets
.SILENT: description clearbin clearassets clear 

# default option to make will print description 
default : description

asd:
	echo $(CFLAGS)

# print the description project and all the make targets
description:
	echo "=============== CODEC ===============" 
	echo " Simply codec and de-codec as server"
	echo " Server usage:"
	echo ""
	echo " Client usage:"
	echo " "

# compile all the src files and puts objects into bin/
# - dep=clearbin 
# - compile all the src content
# - puts executeble files under bin directory 
bin: clearbin
	mkdir -p $(BIN) # -p prevents the error message if the directory exist

# generate an example of input file
# - dep=clearassets
# - generate the example file under assets folder 
assets: clearassets
	mkdir -p $(ASSETS) # -p prevents the error message if the directory exist

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
