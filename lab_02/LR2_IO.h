#ifndef __LR2_IO_H__
#define __LR2_IO_H__
#define THEATER 70
#define NAME 80
#define TABLE 485

// Структура спекталя
struct spectacle {
	char theater[THEATER + 1]; // Название театра
	char name_spc[NAME + 1]; // Название спектакля
	char director[NAME+1]; // Имя режиссера
	int low; // Нижняя граница цены билета
	int high; // Верхняя граница цены билета
	int type_spc; // Тип спектакля
	union {
		struct { // Детский
			int age; // Возрастное ограничение
			int type; // Тип детского спектакля
		} child;
		struct { // Взрослый
			int type; // Тип взрослого спеткакля
		} adult;
		struct { // Музыкальный
			char composer[NAME + 1]; // Имя композитора
			char country[THEATER + 1]; // Страна
			int age; // Возрастное ограничение
			int dur; // Продолжительность 
		} musical;
	} spct;
};
void fill_keys(int keys[TABLE][2], struct spectacle *table, int count);
void print_keys(int keys[TABLE][2], int count);
void add_struct(struct spectacle *table, int i);
void remove_struct(struct spectacle *table, int *count);
void print_table_by_keys(struct spectacle *table, int keys[TABLE][2], int count);
void print_string(struct spectacle *table);
void print(struct spectacle *table, int count);
int read_line(char *s, int n);
int read_int(int *a);
void fill_file(struct spectacle *table, int *count);
void fill_manually(struct spectacle *table, int *count);

#endif

