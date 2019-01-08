CC = gcc
CFLAGS = -Wall -g -O0

uart_send:uart_send.c 
	    $(CC) $(CFLAGS) -o $@ $^ -lwiringPi

clean:
	    $(RM) uart_send .*.sw?
