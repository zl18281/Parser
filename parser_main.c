#include "parser.h"

int main(int argc, char** argv)
{
   int i,j;
   program prog;
   FILE *f;

   if(argc != 2){
      fprintf(stderr,
         "\nArgument number for %s not right!\n\n", argv[0]);
      exit(2);
   }

   test_strategy();

   /*Initialize "program" structure to trivial*/
   prog.head = 0;
   prog.tail = 0;
   for(j = 0; j < MAX_TOKEN; j++){
      strcpy(prog.wds[j], "");
   }

   f = fopen(argv[1], "r");
   if(f == NULL){
      fprintf(stderr, "\nCannot open file %s\n\n", argv[1]);
      exit(2);
   }

   /*Scan a turtle program into "program" structure
     and point the "tail" at the last word*/
   i = 0;
   while(fscanf(f, "%s", prog.wds[i++]) == 1 &&
         i < MAX_TOKEN){
      prog.tail = (i - 1);
   }

   /*Start parsing*/
   if(is_main(&prog)){
      printf("\nParsed OK\n\n");
      fclose(f);
      return 0;
   }
   fclose(f);
   printf("\nFailed\n\n");
   return 0;
}

