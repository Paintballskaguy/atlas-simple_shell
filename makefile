CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
DEPS = shell.h
OBJ = shell.o shell_main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o shell

