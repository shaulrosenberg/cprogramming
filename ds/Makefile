TARGETS := dlist
CC = gcc
CFLAGS := -ansi -pedantic-errors -Wall -Wextra

# DIRS
SRC_DIRS := /home/shaul/shaul.rosenberg/ds/src
INC_DIRS := /home/shaul/shaul.rosenberg/ds/include
TEST_DIRS := /home/shaul/shaul.rosenberg/ds/test
LIB_DIR := /home/shaul/shaul.rosenberg/ds/lib

HOME := /home/shaul/shaul.rosenberg/ds/
SHELL := /bin/bash
#DLIB := "export LD_LIBRARY_PATH=$$PWD:$$LD_LIBRARY_PATH"
#LDLIB := -Wl,-rpath=$(HOME) -L$(HOME)

# FLAGS
LDFLAGS := $(addprefix -iquote ,$(INC_DIRS))

# $@ is the name of the target to be made.
# get depen from -mt , and target from console, use foreach ( , eval)

$(TARGETS).out: $(TEST_DIRS)/$(TARGETS)_test.c lib$(TARGETS).so
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $< -L$(HOME) -l$(TARGETS)

lib$(TARGETS).so:	$(TARGETS).o
	$(CC) -shared -o $@ $(TARGETS).o

$(TARGETS).o:	
	$(CC) -c -fPIC $(LDFLAGS) $(SRC_DIRS)/$(TARGETS).c -o $@




.phony: build, clean, debug, all
clean:
	-@rm -f *.o
	-@rm -f *.so
	-@rm -f *.out
	@echo 'cleaning done'

