mymcp23017:main.o mymcp23017.o
	gcc -Wall -o mymcp23017 main.o mymcp23017.o -lwiringPi -std=gnu99
main.o: main.c mymcp23017.h
	gcc -Wall -c main.c -lwiringPi -std=gnu99
mymcp23017.o: mymcp23017.c mymcp23017.h
	gcc -Wall -c mymcp23017.c -lwiringPi -std=gnu99
clean:
	rm main.o mymcp23017.o mymcp23017