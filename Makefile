CC=gcc 
CFLAGS= -Wall -Wextra -I .
DEPS = *.h
OBJ = main.o init.o run.o clean.o run-file.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
main: $(OBJ)
	  $(CC) -o $@ $^ $(CFLAGS)
clean:
	rm main *.o