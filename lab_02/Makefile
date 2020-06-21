CFILES := $(wildcard *.c)
OBJECTS := $(CFILES:%.c=%.o)

CC := gcc
CFLAGS = -Werror -Wall -pedantic -std=c99 -g

app.out: $(OBJECTS) *.h
	$(CC) $(CFLAGS) $(OBJECTS) -o app.out
%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<
run: app.out
	./app.out
clean:
	rm *.o *.out
