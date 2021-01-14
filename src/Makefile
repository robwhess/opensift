CC	= g++
CFLAGS	+= -fpermissive -Wno-deprecated-declarations -Wno-write-strings -fPIC
BIN_DIR = ../bin
INC_DIR	= ../include
LIB_DIR	= ../lib
INCL	= -I$(INC_DIR) `pkg-config --cflags opencv4 gtk+-2.0`
LIBS	= -L$(LIB_DIR) -lm -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core
OBJ	= imgfeatures.o utils.o sift.o kdtree.o minpq.o xform.o
BIN     = siftfeat match dspfeat match_num

all: $(BIN) libopensift.so

libopensift.so: $(OBJ)
	g++ -shared $(CFLAGS) $(LDFLAGS) -o $(LIB_DIR)/$@ $^ $(LIBS)

siftfeat: libopensift.so siftfeat.c
	$(CC) $(CFLAGS) $(INCL) siftfeat.c -o $(BIN_DIR)/$@ -lopensift $(LIBS)

match: libopensift.so match.c
	$(CC) $(CFLAGS) $(INCL) match.c -o $(BIN_DIR)/$@ -lopensift $(LIBS)

match_num: libopensift.so match.c
	$(CC) $(CFLAGS) $(INCL) match_num.c -o $(BIN_DIR)/$@ -lopensift $(LIBS)

dspfeat: libopensift.so dspfeat.c
	$(CC) $(CFLAGS) $(INCL) dspfeat.c -o $(BIN_DIR)/$@ -lopensift $(LIBS)

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
