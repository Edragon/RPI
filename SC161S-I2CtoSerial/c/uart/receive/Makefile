CC = gcc
CFLAGS = -Wall -g -O0

uart_receive:uart_receive.c 
	    $(CC) $(CFLAGS) -o $@ $^ -lwiringPi

clean:
	    $(RM) uart_receive .*.sw?
