#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "neillsdl2.h"

/*MAX_TOKEN is the maximum words that can be scanned*/
/*MAX_TOKEN_SIZE is the maximum chars in a word*/
/*MAX_SYMBOL is the maximum chars in the symbol table*/
#define MAX_TOKEN 1000
#define MAX_TOKEN_SIZE 10
#define MAX_SYMBOL 50
#define STACKSIZE 50

/*"head" and "tail" is used to virtually divide the whole
program into some partial segment by moving around*/
struct prog {
   char wds[MAX_TOKEN][MAX_TOKEN_SIZE];
   int head;
   int tail;
};

typedef struct prog program;

/*This structure keeps status (position and direction)
of the "turtle"*/
struct turtle {
   double turtle_x;
   double turtle_y;
   double radius;
   int turn_on_off;
};

typedef struct turtle turtle;

/*This structure keeps records of symbols encountered.*/
struct symbol_table {
   int table[MAX_SYMBOL];
   double value[MAX_SYMBOL];
};

typedef struct symbol_table symbol_table;

struct polish_stack {
   double stk[STACKSIZE];
   int top;
};

typedef struct polish_stack polish_stack;

int is_main(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer);
int is_instruction_list(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer);
int is_instruction(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer);
int is_fd(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer);
int is_lt(program *p, symbol_table *t, turtle *turt_pointer);
int is_rt(program *p, symbol_table *t, turtle *turt_pointer);
int is_do(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer);
int is_set(program *p, symbol_table *t);
int is_varnum(symbol_table *t, char *str);
int is_var(symbol_table *t, char *str);
int is_polish(symbol_table *t, program *p);
int is_op(char *str);

program *copy_struct(program *p);
turtle *copy_turtle(turtle *turt);
double search_table_value(symbol_table *t, char *str);
double polish_to_num(symbol_table *t, program *p);
double to_num(symbol_table *t, char *str);
void change_value(symbol_table *t, char c, double new_value);
int to_digit(char c);
void print_symbol_table(symbol_table *t);
int is_in_table(symbol_table *t, char c);
void insert_symbol_table(symbol_table *t, char symbol, double symbol_value);

void initialize_stack(polish_stack *s);
void push(polish_stack *s, double d);
double pop(polish_stack *s);

void test_strategy(void);

#endif
