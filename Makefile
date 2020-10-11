CC	= g++
CFLAGS	+= -O3
BIN_DIR	= ./bin
SRC_DIR	= ./src
DOC_DIR	= ./docs
INC_DIR	= ./include
LIB_DIR	= ./lib
BIN	= siftfeat match dspfeat match_num

all: $(BIN) libopensift.so docs

docs:
	doxygen Doxyfile

libopensift.so:
	make -C $(SRC_DIR) $@

$(BIN):
	make -C $(SRC_DIR) $@

clean:
	make -C $(SRC_DIR) $@;	\
	make -C $(INC_DIR) $@;	\

distclean: clean
	rm -f $(LIB_DIR)/*
	rm -f $(BIN_DIR)/*

docsclean:
	rm -rf $(DOC_DIR)/html/

.PHONY: docs clean docsclean libopensift.so
