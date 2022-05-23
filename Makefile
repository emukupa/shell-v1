main: main.c init.c run.c clean.c run-file.c
	 gcc -Wall -Wextra -o main main.c init.c run.c clean.c run-file.c -I .
clean:
	rm main 