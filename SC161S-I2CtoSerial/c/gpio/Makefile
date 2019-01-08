OBJ_C = ${wildcard *.c}
OBJ_O = ${patsubst %.o,%,$(OBJ_C)}

TARGET = main

CC = gcc -std=c99

DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG)

LIB = -lwiringPi

${TARGET}:${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)

%.o : %.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)
    
clean :
	rm $(TARGET)
