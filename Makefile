CC=gcc 
CFLAGS= -Wall -Wextra -I .
DEPS = *.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
main: main.o init.o run.o clean.o run-file.o
	  $(CC) -o main main.o init.o run.o clean.o run-file.o
clean:
	rm main *.o