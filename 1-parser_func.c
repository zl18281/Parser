#include "parser.h"

/*Exactly copy one "program" structure into another (tested)*/
program *copy_struct(program *p)
{
   program *new_program;
   int i;

   new_program = (program *)malloc(sizeof(program));
   new_program->head = p->head;
   new_program->tail = p->tail;
   for(i = new_program->head; i <= new_program->tail; i++){
      strcpy(new_program->wds[i], p->wds[i]);
   }
   return new_program;
}

/*Check if the whole program is a "main"*/
int is_main(program *p)
{
   if(strcmp(p->wds[p->head], "{") == 0){
      if(p->head == p->tail){
         return 0;
      }else{
         p->head = p->head + 1;
      }
      if(is_instruction_list(p)){
         return 1;
      }
   }
   return 0;
}

/*Check if things after a "{" is an instruction list*/
/*"Walker" is used to iterate through the program to
find a instruction ahead and an instruction list behind*/
int is_instruction_list(program *p)
{
   int walker = p->head;
   program *new_program = copy_struct(p);

   if(p->head == p->tail && strcmp(p->wds[p->head], "}") == 0){
      free(new_program);
      return 1;
   }
   while(walker < p->tail){
      new_program->tail = walker;
      p->head = walker + 1;
      if(is_instruction(new_program) &&
         is_instruction_list(p)){
         free(new_program);
         return 1;
      }
      walker++;
   }
   free(new_program);
   return 0;
}

/*Check if part of a turtle program is an instruction*/
int is_instruction(program *p)
{
   if(is_fd(p) || is_lt(p) || is_rt(p) ||
      is_do(p) || is_set(p)){
      return 1;
   }
   else{
      return 0;
   }
}

/*Check if part of a turtle program is FD*/
int is_fd(program *p)
{
   if((p->head + 1) == p->tail){
      if(strcmp(p->wds[p->head], "FD") == 0 &&
         is_varnum(p->wds[p->head + 1])){
         return 1;
      }
   }
   return 0;
}

/*Check if part of a turtle program is LT*/
int is_lt(program *p)
{
   if((p->head + 1) == p->tail){
      if(strcmp(p->wds[p->head], "LT") == 0 &&
         is_varnum(p->wds[p->head + 1])){
         return 1;
      }
   }
   return 0;
}

/*Check if part of a turtle program is RT*/
int is_rt(program *p)
{
   if((p->head + 1) == p->tail){
      if(strcmp(p->wds[p->head], "RT") == 0 &&
         is_varnum(p->wds[p->head + 1])){
         return 1;
      }
   }
   return 0;
}

/*Check if part of a turtle program is DO*/
/*This function again calls the "is_instruction_list"
function to check the remaining after "{"*/
/*numbers from 1 to 7 are just position offsets of words after "DO"*/
int is_do(program *p)
{
   program *temp_program = copy_struct(p);

   if(temp_program->tail >= (temp_program->head + 7)){
      if(strcmp(temp_program->wds[temp_program->head], "DO") == 0 &&
         is_var(temp_program->wds[temp_program->head + 1]) &&
         strcmp(temp_program->wds[temp_program->head + 2], "FROM") == 0 &&
         is_varnum(temp_program->wds[temp_program->head + 3]) &&
         strcmp(temp_program->wds[temp_program->head + 4], "TO") == 0 &&
         is_varnum(temp_program->wds[temp_program->head + 5]) &&
         strcmp(temp_program->wds[temp_program->head + 6], "{") == 0){
            temp_program->head = temp_program->head + 7;
            if(is_instruction_list(temp_program)){
               free(temp_program);
               return 1;
            }
      }
   }
   free(temp_program);
   return 0;
}

/*Check if part of a turtle program is SET*/
/*This function calls the "is_polish" function to check the remaining after ":="*/
/*numbers from 1 to 3 are just position offsets of words after "SET"*/
int is_set(program *p)
{
   program *temp_program = copy_struct(p);

   if(temp_program->tail >= (temp_program->head + 3)){
      if(strcmp(temp_program->wds[temp_program->head], "SET") == 0 &&
         is_var(temp_program->wds[temp_program->head + 1]) &&
         strcmp(temp_program->wds[temp_program->head + 2], ":=") == 0){
            temp_program->head = temp_program->head + 3;
            if(is_polish(temp_program)){
               free(temp_program);
               return 1;
            }
      }
   }
   free(temp_program);
   return 0;
}

/*This function check if part of a turtle program is a "POLISH"*/
/*Recursive call of itself is used according to formal language definition*/
int is_polish(program *p)
{
   program *temp_program = copy_struct(p);

   if(temp_program->head == temp_program->tail &&
      strcmp(temp_program->wds[temp_program->head], ";") == 0){
      free(temp_program);
      return 1;
   }
   if(temp_program->tail >= (temp_program->head + 1)){
      if(is_op(temp_program->wds[temp_program->head])){
         temp_program->head = temp_program->head + 1;
         if(is_polish(temp_program)){
            free(temp_program);
            return 1;
         }
      }
      if(is_varnum(temp_program->wds[temp_program->head])){
         temp_program->head = temp_program->head + 1;
         if(is_polish(temp_program)){
            free(temp_program);
            return 1;
         }
      }
   }
   free(temp_program);
   return 0;
}

/*Check if a string is a "VARNUM"*/
int is_varnum(char *str)
{
   int i;
   int b = 0;

   if(is_var(str)){
      return 1;
   }

   for(i = 0; i < (int)strlen(str); i++){
      if((str[i] >= '0' && str[i] <= '9') || str[i] == '.'){
         b++;
      }
   }
   if(b == (int)strlen(str)){
      return 1;
   }
   return 0;
}

/*Check if a string is a "VAR"*/
int is_var(char *str)
{
   if((int)strlen(str) == 1 &&
      (str[0] >= 'A' && str[0] <= 'Z')){
      return 1;
   }
   return 0;
}

/*Check if a string is a "OP" (tested)*/
int is_op(char *str)
{
   if((int)strlen(str) == 1){
      if(str[0] == '+' || str[0] == '-' ||
         str[0] == '*' || str[0] == '/'){
         return 1;
      }
   }
   return 0;
}
