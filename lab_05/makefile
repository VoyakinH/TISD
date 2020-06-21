KEY = -std=c99 -Wall -Werror -pedantic
FILES = main.o init_automat.o queue.o rand.o refresh_automat.o time.o
app.exe: $(FILES)
	gcc -o app.exe $(FILES) $(KEY)
%.o: %.c
	gcc -c $< -o $@ $(KEY)
clear:
	rm *.exe *.o