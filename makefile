#IMS

CC=g++
CFLAGS=-std=c++17 #-Wall -Wextra -pedantic
LDFLAGS = #-lssl -lcrypto -lpcap
DEPS = classes.h
OBJ = model.o classes.o

all: model


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

model : $(OBJ)
	$(CC) -o model $^ $(CFLAGS) $(LDFLAGS)

run : 
	./model