# intro

- source is https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
- Create init, run clean and main functions in there respective files
- Compile the programs. `gcc -Wall -Wextra -o main main.c init.c run.c clean.c run-file.c -I .`
- Create a Makefile

- makefile1

```Makefile
main: main.c init.c run.c clean.c run-file.c
	 gcc -Wall -Wextra -o main main.c init.c run.c clean.c run-file.c -I .
clean:
	rm main
```

- modify makefile to use `CC` and `CFLAGS`
- makefile2

```Makefile
CC=gcc
CFLAGS= -Wall -Wextra -I .
main: main.o init.o run.o clean.o run-file.o
	  $(CC) -o main main.o init.o run.o clean.o run-file.o
clean:
	rm main *.o
```

- modify makefile to re-compile when .h files are changed
- makefile3

```Makefile
CC=gcc
CFLAGS= -Wall -Wextra -I .
DEPS = clean.h init.h run-file.h run.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o init.o run.o clean.o run-file.o
	  $(CC) -o main main.o init.o run.o clean.o run-file.o
clean:
	rm main *.o
```

- Update the DEPS with `*.h`
- makefile4

```Makefile
CC=gcc
CFLAGS= -Wall -Wextra -I .
DEPS = *.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o init.o run.o clean.o run-file.o
	  $(CC) -o main main.o init.o run.o clean.o run-file.o
clean:
	rm main *.o
```

- simplify further
- makefile5

```Makefile
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
```

- Start with the run function, add read, parse and execute functions
