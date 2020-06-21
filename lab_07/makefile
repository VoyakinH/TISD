KEY2 = -std=c99 -Wall -Werror -pedantic
app.exe: main.o arr_func.o CDIO.o
	gcc -o app.exe main.o arr_func.o CDIO.o $(KEY)
%.o: %.c
	gcc -c $< -o $@ $(KEY)
clean:
	rm *.exe *.o *.png