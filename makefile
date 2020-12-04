#IMS

CC=g++
CFLAGS=-std=gnu99
LDFLAGS = -lssl -lcrypto
DEPS = classes.h
OBJ = model.o classes.o

all: model


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

model : $(OBJ)
	$(CC) -o model $^ $(CFLAGS) $(LDFLAGS)