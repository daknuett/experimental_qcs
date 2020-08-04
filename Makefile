CC=gcc
CFLAG= -g -O -lm
objs= qop.o qstate.o sampling.o unitaries.o

all: main

%.o: %.c
	$(CC) -c $(CFLAG) -o $@ $<

main: main.c $(objs)
	$(CC) $(CFLAG) $(objs) main.c -o main

clean:
	-rm main
	-rm $(objs)
