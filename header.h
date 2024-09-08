#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct student {
int rollno;
char name[20];
float percentage;
struct student *next;
}SLL;

void add_new_record(SLL **);
void delete_a_record(SLL **);
void show_the_list(SLL *);
void modify_the_records(SLL **);
void save_data_into_file(SLL *);
void sort_the_list(SLL *);
void delete_all_records(SLL **);
void reverse_the_records(SLL *);
void exit_pgm(SLL **);
int count_node(SLL *);
void read_file(SLL **);
