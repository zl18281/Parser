#include "extension.h"

/*This function prints the symbol table by symbol and its value (Tested)*/
void print_symbol_table(symbol_table *t)
{
   int i;

   for(i = 0; i < MAX_SYMBOL; i++){
      if(t->table[i] != '!'){
         printf("\n%c:  %f\n", t->table[i], t->value[i]);
      }
   }
}

/*This function search for a symbol in the symbol table and change its value (Tested)*/
void change_value(symbol_table *t, char c, double new_value)
{
   int i;

   for(i = 0; i <MAX_SYMBOL; i++){
      if(t->table[i] == c){
         t->value[i] = new_value;
      }
   }
}

/*Exactly copy one "turtle" structure into another (Tested)*/
turtle *copy_turtle(turtle *turt){
   turtle *temp_turtle = (turtle *)malloc(sizeof(turtle));

   temp_turtle->radius = turt->radius;
   temp_turtle->turtle_x = turt->turtle_x;
   temp_turtle->turtle_y = turt->turtle_y;
   temp_turtle->turn_on_off = turt->turn_on_off;
   return temp_turtle;
}

/*Exactly copy one "program" structure into another (Tested)*/
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

/*This function convert a polish expression to its represented numerical value (Tested)*/
double polish_to_num(symbol_table *t, program *p)
{
   double temp;
   int walker;
   double pop_temp;
   polish_stack *s = (polish_stack *)malloc(sizeof(polish_stack));
   initialize_stack(s);

   for(walker = p->head; walker < p->tail; walker++){
      if(is_varnum(t, p->wds[walker])){
         push(s, to_num(t, p->wds[walker]));
      }
      if(is_op(p->wds[walker])){
         switch (p->wds[walker][0]) {
            case '+':
               push(s, (pop(s) + pop(s)));
               break;
            case '-':
               pop_temp = pop(s);
               push(s, (pop(s) - pop_temp));
               break;
            case '*':
               push(s, (pop(s) * pop(s)));
               break;
            case '/':
               pop_temp = pop(s);
               push(s, (pop(s) / pop_temp));
               break;
            default:
               push(s, (pop(s) + pop(s)));
         }
      }
   }
   temp = (pop(s));
   free(s);
   return temp;
}

/*This function change a string(variable or number) to a real numeric value (Tested)*/
double to_num(symbol_table *t, char *str)
{
   if(is_var(t, str)){
      return (search_table_value(t, str));
   }
   else{
      int decimal_point = (int)strlen(str);
      int i, j, k;
      int sum_int = 0;
      double sum_double = 0;

      for(i = 0; i < (int)strlen(str); i++){
         if(str[i] == '.'){
            decimal_point = i;
         }
      }
      for(j = 0; j < decimal_point; j++){
         sum_int += (to_digit(str[j]) * (int)pow((double)10, (double)(decimal_point - j - 1)));
      }
      for(k = (decimal_point + 1); k < (int)strlen(str); k++){
         sum_double += (to_digit(str[k]) * pow((double)10, (decimal_point - k)));
      }
      return (sum_int + sum_double);
   }
}

/*This function change a char (digit) to a real numerical digit (Tested)*/
int to_digit(char c)
{
   switch (c) {
      case '0':
         return 0;
      case '1':
         return 1;
      case '2':
         return 2;
      case '3':
         return 3;
      case '4':
         return 4;
      case '5':
         return 5;
      case '6':
         return 6;
      case '7':
         return 7;
      case '8':
         return 8;
      case '9':
         return 9;
      default:
         fprintf(stderr, "\n%s\n\n", "Not a digit !");
         exit(2);
   }
}

/*Check if the whole program is a "main" (Tested)*/
int is_main(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer)
{

   if(strcmp(p->wds[p->head], "{") == 0){
      if(p->head == p->tail){
         return 0;
      }else{
         p->head = p->head + 1;
      }
      if(is_instruction_list(p, t, sw_pointer, turt_pointer)){
         return 1;
      }
   }
   return 0;
}

/*Check if things after a "{" is an instruction list (Tested)*/
int is_instruction_list(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer)
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
      if(is_instruction(new_program, t, sw_pointer, turt_pointer) &&
         is_instruction_list(p, t, sw_pointer, turt_pointer)){
         free(new_program);
         return 1;
      }
      walker++;
   }
   free(new_program);
   return 0;
}

/*Check if part of a turtle program is an instruction (Tested)*/
int is_instruction(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer)
{
   if(is_fd(p, t, sw_pointer, turt_pointer) || is_lt(p, t, turt_pointer) ||
      is_rt(p, t, turt_pointer) || is_do(p, t, sw_pointer, turt_pointer) ||
      is_set(p, t) || is_move(p, t, turt_pointer) ||
      is_color(p, sw_pointer, turt_pointer) || is_home(p, turt_pointer) ||
      is_if(p, t, sw_pointer, turt_pointer)){
      return 1;
   }
   else{
      return 0;
   }
}

/*Check if part of a turtle program is FD (Tested)*/
int is_fd(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer)
{
   turtle *temp_turt = copy_turtle(turt_pointer);

   if((p->head + 1) == p->tail){
      if(strcmp(p->wds[p->head], "FD") == 0 && is_varnum(t, p->wds[p->head + 1])){
         if(turt_pointer->turn_on_off == 1){
	         printf("\n\n");
            print_symbol_table(t);
            printf("\nFD %f\n", to_num(t, p->wds[p->head + 1]));
            turt_pointer->turtle_x = temp_turt->turtle_x + to_num(t, p->wds[p->head + 1]) * cos(temp_turt->radius);
            turt_pointer->turtle_y = temp_turt->turtle_y + to_num(t, p->wds[p->head + 1]) * sin(temp_turt->radius);
            SDL_RenderDrawLine(sw_pointer->renderer, temp_turt->turtle_x, temp_turt->turtle_y,
                               turt_pointer->turtle_x, turt_pointer->turtle_y);
            Neill_SDL_UpdateScreen(sw_pointer);
            Neill_SDL_Events(sw_pointer);
            SDL_Delay(30);
         }
         free(temp_turt);
         return 1;
      }
   }
   free(temp_turt);
   return 0;
}

/*Check if part of a turtle program is LT*/
/*update turtle angle when turtle is turned on (Tested)*/
int is_lt(program *p, symbol_table *t, turtle *turt_pointer)
{
   if((p->head + 1) == p->tail){
      if(strcmp(p->wds[p->head], "LT") == 0 && is_varnum(t, p->wds[p->head + 1])){
         if(turt_pointer->turn_on_off == 1){
            turt_pointer->radius = turt_pointer->radius - (to_num(t, p->wds[p->head + 1]) / 180) * M_PI;
            printf("\nLT\n");
         }
         return 1;
      }
   }
   return 0;
}

/*Check if part of a turtle program is RT*/
/*update turtle angle when turtle is turned on (Tested)*/
int is_rt(program *p, symbol_table *t, turtle *turt_pointer)
{
   if((p->head + 1) == p->tail){
      if(strcmp(p->wds[p->head], "RT") == 0 && is_varnum(t, p->wds[p->head + 1])){
         if(turt_pointer->turn_on_off == 1){
            turt_pointer->radius = turt_pointer->radius + (to_num(t, p->wds[p->head + 1]) / 180) * M_PI;
            printf("\nRT\n");
         }
         return 1;
      }
   }
   return 0;
}

/*Check if part of a turtle program is DO (Tested)*/
int is_do(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer)
{
   program *temp_program = copy_struct(p);
   turtle *temp_turtle = copy_turtle(turt_pointer);

   if(temp_program->tail >= (temp_program->head + 7)){
      if(strcmp(temp_program->wds[temp_program->head], "DO") == 0 &&
         is_var(t, temp_program->wds[temp_program->head + 1]) &&
         strcmp(temp_program->wds[temp_program->head + 2], "FROM") == 0 &&
         is_varnum(t, temp_program->wds[temp_program->head + 3]) &&
         strcmp(temp_program->wds[temp_program->head + 4], "TO") == 0 &&
         is_varnum(t, temp_program->wds[temp_program->head + 5]) &&
         strcmp(temp_program->wds[temp_program->head + 6], "{") == 0){
            temp_program->head = temp_program->head + 7;
            temp_turtle->turn_on_off = 0;
            change_value(t, p->wds[p->head + 1][0], to_num(t, p->wds[p->head + 3]));
            if(is_instruction_list(temp_program, t, sw_pointer, temp_turtle)){
               int it;

               for(it = (int)to_num(t, p->wds[p->head + 3]);
               it <= (int)to_num(t, p->wds[p->head + 5]); it++){
                  int r;

                  change_value(t, p->wds[p->head + 1][0], it);
                  temp_program->head = p->head + 7;
                  temp_program->tail = p->tail;
                  r = is_instruction_list(temp_program, t, sw_pointer, turt_pointer);
                  if(r == 0){
                     fprintf(stderr, "%s", "Cannot execute DO LOOP");
                  }
               }
               free(temp_turtle);
               free(temp_program);
               return 1;
            }
      }
   }
   free(temp_turtle);
   free(temp_program);
   return 0;
}

/*Check if part of a turtle program is SET (Tested)*/
int is_set(program *p, symbol_table *t)
{
   program *temp_program = copy_struct(p);
   program *p_free = NULL;

   if(temp_program->tail >= (temp_program->head + 3)){
      if(strcmp(temp_program->wds[temp_program->head], "SET") == 0 &&
         is_var(t, temp_program->wds[temp_program->head + 1]) &&
         strcmp(temp_program->wds[temp_program->head + 2], ":=") == 0){
            temp_program->head = temp_program->head + 3;
            if(is_polish(t, temp_program)){
               p_free = temp_program;
               temp_program = copy_struct(p);
               temp_program->head = temp_program->head + 3;
               change_value(t, p->wds[p->head + 1][0], polish_to_num(t, temp_program));
               free(p_free);
               free(temp_program);
               return 1;
            }
      }
   }
   free(temp_program);
   return 0;
}

/*This function check if part of a turtle program is a "POLISH"*/
/*Recursive call of itself is used according to formal language definition (Tested)*/
int is_polish(symbol_table *t, program *p)
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
         if(is_polish(t, temp_program)){
            free(temp_program);
            return 1;
         }
      }
      if(is_varnum(t, temp_program->wds[temp_program->head])){
         temp_program->head = temp_program->head + 1;
         if(is_polish(t, temp_program)){
            free(temp_program);
            return 1;
         }
      }
   }
   free(temp_program);
   return 0;
}

/*Check if a string is a "VARNUM" (Tested)*/
int is_varnum(symbol_table *t, char *str)
{
   int i;
   int b = 0;

   if(is_var(t, str)){
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

/*Check if a string is a "VAR" (Tested)*/
int is_var(symbol_table *t, char *str)
{
   if((int)strlen(str) == 1 && (str[0] >= 'A' && str[0] <= 'Z')){
      if(!is_in_table(t, str[0])){
         insert_symbol_table(t, str[0], 0);
      }
      return 1;
   }
   return 0;
}

/*Check if a char is in the symbol table (Tested)*/
int is_in_table(symbol_table *t, char c)
{
   int i;

   for(i = 0; i < MAX_SYMBOL; i++){
      if(t->table[i] == (int)c){
         return 1;
      }
   }
   return 0;
}

/*Insert a char into the symbol table if it's not in the table (Tested)*/
void insert_symbol_table(symbol_table *t, char symbol, double symbol_value)
{
   int i;

   if(is_in_table(t, symbol)){
      return;
   }
   else{
       for(i = 0; i < MAX_SYMBOL; i++){
         if(t->table[i] == (int)'!'){
            t->table[i] = (int)symbol;
            t->value[i] = symbol_value;
            return;
         }
      }
   }
}

/*search a symbol in the symbol table and return its value (Tested)*/
double search_table_value(symbol_table *t, char *str)
{
   int i;

   for(i = 0; i < MAX_SYMBOL; i++){
      if((int)str[0] == t->table[i]){
         return (t->value[i]);
      }
   }
   fprintf(stderr, "%s", "Symbol not found !");
   exit(2);
}

/*Check if a string is a "OP" (Tested)*/
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

/*initialize a stack*/
void initialize_stack(polish_stack *s)
{
   s->top = -1;
}

/*add an element to stack*/
void push(polish_stack *s, double d)
{
   if(s->top >= STACKSIZE){
      fprintf(stderr, "%s", "Stack overflow !");
      exit(2);
   }
   s->top = s->top + 1;
   s->stk[s->top] = d;
}

/*pop an element from stack*/
double pop(polish_stack *s)
{
   if(s->top < 0){
      fprintf(stderr, "%s", "Stack underflow !");
      exit(2);
   }
   s->top = s->top - 1;
   return (s->stk[s->top + 1]);
}

/*Check if part of program is "MOV" instruction*/
/*Turtle position is moved*/
int is_move(program *p, symbol_table *t, turtle *turt_pointer)
{
    if((p->head + 2) == p->tail){
      if(strcmp(p->wds[p->head], "MOV") == 0 &&
         is_varnum(t, p->wds[p->head + 1]) &&
         is_varnum(t, p->wds[p->head + 2])){
         if(turt_pointer->turn_on_off == 1){
            turt_pointer->turtle_x = (int)to_num(t, p->wds[p->head + 1]) % WWIDTH;
            turt_pointer->turtle_y = (int)to_num(t, p->wds[p->head + 2]) % WHEIGHT;
            printf("\nMOV\n");
         }
         return 1;
      }
   }
   return 0;
}

/*Check if part of a program is "COLOR" instruction*/
/*Drawing color is changed to red, green or blue (Tested)*/
int is_color(program *p, SDL_Simplewin *sw, turtle *turt_pointer)
{
   if((p->head + 1) == p->tail){
      if(strcmp(p->wds[p->head], "COLOR") == 0 &&
         (strcmp(p->wds[(p->head + 1)], "RED") == 0 ||
          strcmp(p->wds[(p->head + 1)], "GREEN") == 0 ||
          strcmp(p->wds[(p->head + 1)], "BLUE") == 0)){
             if(turt_pointer->turn_on_off == 1){
                switch (p->wds[p->head + 1][0]) {
                   case 'R':
                      Neill_SDL_SetDrawColour(sw, (SDL_8BITCOLOUR - 1), 0, 0);
                      break;
                   case 'G':
                      Neill_SDL_SetDrawColour(sw, 0, (SDL_8BITCOLOUR - 1), 0);
                      break;
                   case 'B':
                      Neill_SDL_SetDrawColour(sw, 0, 0, (SDL_8BITCOLOUR - 1));
                      break;
                   default:
                      Neill_SDL_SetDrawColour(sw, (SDL_8BITCOLOUR - 1), 0, 0);
                      break;
                }
             printf("\nCOLOR\n");
             }
          return 1;
          }
   }
   return 0;
}

/*Check if part of a program is a "HOME" instruction*/
/*Turtle is set to origin with angle set to 0 (Tested)*/
int is_home(program *p, turtle *turt_pointer)
{
   if(p->head == p->tail){
      if(strcmp(p->wds[p->head], "HOME") == 0){
         if(turt_pointer->turn_on_off == 1){
            turt_pointer->turtle_x = WWIDTH / 2;
            turt_pointer->turtle_y = WHEIGHT / 2;
            turt_pointer->radius = 0;
            printf("\nHOME\n");
         }
         return 1;
      }
   }
   return 0;
}

/*Check if part of a turtle program is IF*/
/*This function again calls the "is_instruction_list" function to check the remaining after "{"*/
/*numbers from 1 to 5 are just position offsets of words after "IF"*/
/*"if block" is inserted to conduct the instruction list nested in IF (Tested)*/
int is_if(program *p, symbol_table *t, SDL_Simplewin *sw_pointer, turtle *turt_pointer)
{
   program *temp_program = copy_struct(p);
   turtle *temp_turtle = copy_turtle(turt_pointer);

   if(temp_program->tail >= (temp_program->head + 5)){
      if(strcmp(temp_program->wds[temp_program->head], "IF") == 0 &&
         is_varnum(t, temp_program->wds[temp_program->head + 1]) &&
         is_cmp(temp_program->wds[temp_program->head + 2]) &&
         is_varnum(t, temp_program->wds[temp_program->head + 3]) &&
         strcmp(temp_program->wds[temp_program->head + 4], "{") == 0){
            temp_program->head = temp_program->head + 5;
            temp_turtle->turn_on_off = 0;
            if(is_instruction_list(temp_program, t, sw_pointer, temp_turtle)){
               switch (p->wds[p->head + 2][0]) {
                  case '>': {
                     if((int)to_num(t, p->wds[p->head + 1]) > (int)(to_num(t, p->wds[p->head + 3]))){
                        int r;

                        temp_program->head = p->head + 5;
                        temp_program->tail = p->tail;
                        r = is_instruction_list(temp_program, t, sw_pointer, turt_pointer);
                        if(r == 0){
                           fprintf(stderr, "%s", "Cannot execute IF");
                        }
                     }
                     break;
                  }
                  case '=': {
                     if((int)to_num(t, p->wds[p->head + 1]) == (int)(to_num(t, p->wds[p->head + 3]))){
                        int r;

                        temp_program->head = p->head + 5;
                        temp_program->tail = p->tail;
                        r = is_instruction_list(temp_program, t, sw_pointer, turt_pointer);
                        if(r == 0){
                           fprintf(stderr, "%s", "Cannot execute IF");
                        }
                     }
                     break;
                  }

               }
               free(temp_program);
               free(temp_turtle);
               return 1;
            }
         }
   }
   free(temp_program);
   free(temp_turtle);
   return 0;
}

/*Check if a string is a comparison operator (Tested)*/
int is_cmp(char *str)
{
   if((int)strlen(str) == 1){
      if(str[0] == '>' || str[0] == '='){
         return 1;
      }
   }
   return 0;
}
