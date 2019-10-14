#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*MAX_TOKEN is the maximum words that can be scanned*/
/*MAX_TOKEN_SIZE is the maximum chars in a word*/
#define MAX_TOKEN 1000
#define MAX_TOKEN_SIZE 10

/*"head" and "tail" is used to virtually divide the whole
program into some partial segment by moving around*/
struct prog {
   char wds[MAX_TOKEN][MAX_TOKEN_SIZE];
   int head;
   int tail;
};

typedef struct prog program;

int is_main(program *p);
int is_instruction_list(program *p);
int is_instruction(program *p);
int is_fd(program *p);
int is_lt(program *p);
int is_rt(program *p);
int is_do(program *p);
int is_set(program *p);
int is_varnum(char *str);
int is_var(char *str);
int is_polish(program *p);
int is_op(char *str);
program *copy_struct(program *p);

/*functions for test_strategy*/
void test_strategy(void);

#endif
