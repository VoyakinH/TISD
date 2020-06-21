KEY2 = -std=c99 -Wall -Werror -pedantic
app.exe: main.o balance.o efficiency.o export.o hash.o read_file.o search.o tree.o
	gcc -o app.exe main.o balance.o efficiency.o export.o hash.o read_file.o search.o tree.o $(KEY)
%.o: %.c
	gcc -c $< -o $@ $(KEY)
clean:
	rm *.exe *.o *.png