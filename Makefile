CC=gcc
CFLAGS=-g -c -O2 -m64 -Wall -Wfatal-errors -fomit-frame-pointer -funroll-loops
SRC=.
INC=.
OBJS=crc.o tsdecode.o fgetopt.o mempool.o dataqueue.o udpsource.o tsreceive.o hlsmux.o
LIB=libfillet.a

all: $(LIB) fillet

fillet: fillet.o $(OBJS)
	$(CC) fillet.o $(OBJS) -L./ -lm -lpthread -o fillet

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)
	@echo finishing building lib

fillet.o: $(SRC)/fillet.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/fillet.c

tsreceive.o: $(SRC)/tsreceive.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/tsreceive.c

udpsource.o: $(SRC)/udpsource.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/udpsource.c

dataqueue.o: $(SRC)/dataqueue.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/dataqueue.c

mempool.o: $(SRC)/mempool.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/mempool.c

hlsmux.o: $(SRC)/hlsmux.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/hlsmux.c

fgetopt.o: $(SRC)/fgetopt.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/fgetopt.c

tsdecode.o: $(SRC)/tsdecode.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/tsdecode.c

crc.o: $(SRC)/crc.c
	$(CC) $(CFLAGS) $(INC) $(SRC)/crc.c

clean:
	rm -rf *o fillet