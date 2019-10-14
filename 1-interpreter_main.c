#include "interpreter.h"

int main(int argc, char** argv)
{
   int i, j, k;
   program prog;
   symbol_table sym_tab;
   turtle turt;
   FILE *f;
   SDL_Simplewin sw;

   test_strategy();

   Neill_SDL_Init(&sw);
   Neill_SDL_SetDrawColour(&sw, rand()%SDL_8BITCOLOUR,
                           rand()%SDL_8BITCOLOUR,
                           rand()%SDL_8BITCOLOUR);
   if(argc != 2){
      printf("Argument number not right !");
      exit(2);
   }

   /*Initialize symbol table*/
   for(k = 0; k < MAX_SYMBOL; k++){
      sym_tab.table[k] = (int)'!';
      sym_tab.value[k] = 0;
   }

   /*Initialize turtle*/
   turt.radius = 0;
   turt.turtle_x = WWIDTH / 2;
   turt.turtle_y = WHEIGHT / 2;
   turt.turn_on_off = 1;

   /*Initialize "program" structure to trivial*/
   prog.head = 0;
   prog.tail = 0;
   for(j = 0; j < MAX_TOKEN; j++){
      strcpy(prog.wds[j], "");
   }

   f = fopen(argv[1], "r");
   if(f == NULL){
      printf("\nCannot open %s", argv[1]);
      exit(2);
   }

   /*Scan a turtle program into "program" structure
   word by word and point the "tail" at the last word*/
   i = 0;
   while(fscanf(f, "%s", prog.wds[i++]) == 1 && i < MAX_TOKEN){
      prog.tail = (i - 1);
   }

   /*Start parsing and interpretation instruction by instruction*/
   if(is_main(&prog, &sym_tab, &sw, &turt)){
      SDL_Delay(10000);
      printf("\nParsed OK\n\n");
      SDL_Quit();
      atexit(SDL_Quit);
      return 0;
   }
   printf("\nFailed\n\n");
   exit(2);
}

