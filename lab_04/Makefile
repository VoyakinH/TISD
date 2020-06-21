CFLAGS = -std=c99 -Wall -Werror -pedantic
CC = gcc

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< 	

clean:
	rm *.o
	
app.exe: array_stack.o arr_stack_op.o menu.o list_stack_op.o
	$(CC) $(CFLAGS) -o $@ $^