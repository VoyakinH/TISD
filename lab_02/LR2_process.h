#ifndef __LR2_PROCESS_H__
#define __LR2_PROCESS_H__

void bubble(int keys[TABLE][2], int count);
void sort_table_qs(struct spectacle *table, int first, int last);
void sort_table_bubble(struct spectacle *table, int count);
void search(struct spectacle *table, int count);
void qs(int keys[TABLE][2], int first, int last);
unsigned long long tick(void);
void time_keys(struct spectacle *table, int keys[TABLE][2], int count);
void time_table(struct spectacle *table, int keys[TABLE][2], int count);
#endif

