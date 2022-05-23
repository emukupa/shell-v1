# intro

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

- Start with the run function, add read, parse and execute functions
