CC	= gcc
CFLAGS	+=
BIN_DIR = ../bin
INC_DIR	= ../include
LIB_DIR	= ../lib
INCL	= -I$(INC_DIR) `pkg-config --cflags opencv gtk+-2.0`
LIBS	= -L$(LIB_DIR) -lopensift -lm `pkg-config --libs opencv gtk+-2.0`
OBJ	= imgfeatures.o utils.o sift.o kdtree.o minpq.o xform.o
BIN     = siftfeat match dspfeat match_num

all: $(BIN) libopensift.a

libopensift.a: $(OBJ)
	ar rc $(LIB_DIR)/$@ $(OBJ)
	ranlib  $(LIB_DIR)/$@

siftfeat: libopensift.a siftfeat.c
	$(CC) $(CFLAGS) $(INCL) siftfeat.c -o $(BIN_DIR)/$@ $(LIBS)

match: libopensift.a match.c
	$(CC) $(CFLAGS) $(INCL) match.c -o $(BIN_DIR)/$@ $(LIBS)

match_num: libopensift.a match.c
	$(CC) $(CFLAGS) $(INCL) match_num.c -o $(BIN_DIR)/$@ $(LIBS)

dspfeat: libopensift.a dspfeat.c
	$(CC) $(CFLAGS) $(INCL) dspfeat.c -o $(BIN_DIR)/$@ $(LIBS)

imgfeatures.o: imgfeatures.c $(INC_DIR)/imgfeatures.h
	$(CC) $(CFLAGS) $(INCL) -c imgfeatures.c -o $@

utils.o: utils.c $(INC_DIR)/utils.h
	$(CC) $(CFLAGS) $(INCL) -c utils.c -o $@

sift.o: sift.c $(INC_DIR)/sift.h
	$(CC) $(CFLAGS) $(INCL) -c sift.c -o $@

kdtree.o: kdtree.c $(INC_DIR)/kdtree.h
	$(CC) $(CFLAGS) $(INCL) -c kdtree.c -o $@

minpq.o: minpq.c $(INC_DIR)/minpq.h
	$(CC) $(CFLAGS) $(INCL) -c minpq.c -o $@

xform.o: xform.c $(INC_DIR)/xform.h
	$(CC) $(CFLAGS) $(INCL) -c xform.c -o $@

clean:
	rm -f *~ *.o core

.PHONY: clean
