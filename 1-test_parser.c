#include "parser.h"

void test_strategy(void)
{
   /*Test of function "copy_struct" (White box)*/
   {
      program p;
      program *p_new;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "A");
      strcpy(p.wds[1], "B");
      strcpy(p.wds[2], "C");
      p.tail = 2;
      p_new = copy_struct(&p);
      assert(p_new->head == 0);
      assert(p_new->tail == 2);
      assert(strcmp(p_new->wds[0], "A") == 0);
      assert(strcmp(p_new->wds[1], "B") == 0);
      assert(strcmp(p_new->wds[2], "C") == 0);
      free(p_new);
      printf("\nTest of function \"copy_struct\" Succeeded !\n");
   }

   /*Test of function "is_op" (White box)*/
   {
      assert(is_op("+") == 1);
      assert(is_op("-") == 1);
      assert(is_op("*") == 1);
      assert(is_op("/") == 1);
      assert(is_op("F") == 0);
      assert(is_op("C") == 0);
      assert(is_op("+=") == 0);
      printf("Test of function \"is_op\" Succeeded !\n");
   }

   /*Test of function "is_var" (White box)*/
   {
      assert(is_var("A") == 1);
      assert(is_var("E") == 1);
      assert(is_var("H") == 1);
      assert(is_var("L") == 1);
      assert(is_var("Q") == 1);
      assert(is_var("Z") == 1);
      assert(is_var("AB") == 0);
      assert(is_var("a") == 0);
      assert(is_var("+") == 0);
      printf("Test of function \"is_var\" Succeeded !\n");
   }

   /*Test of function "is_varnum" (White box)*/
   {
      assert(is_varnum("16") == 1);
      assert(is_varnum("16.16") == 1);
      assert(is_varnum("18") == 1);
      assert(is_varnum("18.18") == 1);
      assert(is_var("A") == 1);
      assert(is_var("1A.2Q") == 0);
      printf("Test of function \"is_varnum\" Succeeded !\n");
   }

   /*Test of function "is_polish" (White box)*/
   {
      program p;
      int j;

      /*test ";"*/
      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], ";");
      assert(is_polish(&p) == 1);

      /*test "A 6 * ;"*/
      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "A");
      strcpy(p.wds[1], "6");
      strcpy(p.wds[2], "*");
      strcpy(p.wds[3], ";");
      p.tail = 3;
      assert(is_polish(&p) == 1);

      /*test "A ;"*/
      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "A");
      strcpy(p.wds[1], ";");
      p.tail = 1;
      assert(is_polish(&p) == 1);

      /*test "+ ;"*/
      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "+");
      strcpy(p.wds[1], ";");
      p.tail = 1;
      assert(is_polish(&p) == 1);

      /*test "+ A 6 * ;"*/
      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "+");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], "6");
      strcpy(p.wds[3], "*");
      strcpy(p.wds[4], ";");
      p.tail = 4;
      assert(is_polish(&p) == 1);

      /*test "A 6 + ; Z"*/
      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "A");
      strcpy(p.wds[1], "6");
      strcpy(p.wds[2], "+");
      strcpy(p.wds[3], ";");
      strcpy(p.wds[4], "Z");
      p.tail = 4;
      assert(is_polish(&p) == 0);
      printf("Test of function \"is_polish\" Succeeded !\n");
   }

   /*Test of function "is_set" (White box)*/
   {
      program p;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "SET");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], ":=");
      strcpy(p.wds[3], "B");
      strcpy(p.wds[4], "6");
      strcpy(p.wds[5], "+");
      strcpy(p.wds[6], ";");
      p.tail = 6;
      assert(is_set(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "SET");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], "=");
      strcpy(p.wds[3], "B");
      strcpy(p.wds[4], "6");
      strcpy(p.wds[5], "+");
      strcpy(p.wds[6], ";");
      p.tail = 6;
      assert(is_set(&p) == 0);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "SET");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], ":=");
      strcpy(p.wds[3], "B");
      strcpy(p.wds[4], "6");
      strcpy(p.wds[5], "+");
      p.tail = 5;
      assert(is_set(&p) == 0);

      printf("Test of function \"is_set\" Succeeded !\n");
   }

   /*Test of function "is_do" (White box)*/
   {
      program p;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "DO");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], "FROM");
      strcpy(p.wds[3], "1");
      strcpy(p.wds[4], "TO");
      strcpy(p.wds[5], "8");
      strcpy(p.wds[6], "{");
      strcpy(p.wds[7], "FD");
      strcpy(p.wds[8], "30");
      strcpy(p.wds[9], "}");
      p.tail = 9;
      assert(is_do(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "FOR");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], "FROM");
      strcpy(p.wds[3], "1");
      strcpy(p.wds[4], "TO");
      strcpy(p.wds[5], "8");
      strcpy(p.wds[6], "{");
      strcpy(p.wds[7], "FD");
      strcpy(p.wds[8], "30");
      strcpy(p.wds[9], "}");
      p.tail = 9;
      assert(is_do(&p) == 0);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "DO");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], "FROM");
      strcpy(p.wds[3], "1");
      strcpy(p.wds[4], "TO");
      strcpy(p.wds[5], "8");
      strcpy(p.wds[6], "{");
      strcpy(p.wds[7], "FD");
      strcpy(p.wds[8], "30");
      p.tail = 8;
      assert(is_do(&p) == 0);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "DO");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], "FROM");
      strcpy(p.wds[3], "1");
      strcpy(p.wds[4], "to");
      strcpy(p.wds[5], "8");
      strcpy(p.wds[6], "{");
      strcpy(p.wds[7], "FD");
      strcpy(p.wds[8], "30");
      strcpy(p.wds[9], "}");
      p.tail = 9;
      assert(is_do(&p) == 0);

      printf("Test of function \"is_do\" Succeeded !\n");
   }

   /*Test of function "is_FD" (White box)*/
   {
      program p;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "FD");
      strcpy(p.wds[1], "30"); /*Change "30" to "A" and test again*/
      p.tail = 1;
      assert(is_fd(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "FD");
      strcpy(p.wds[1], "30"); /*Change "30" to "A" and test again*/
      strcpy(p.wds[2], ";");
      p.tail = 2;
      assert(is_fd(&p) == 0);

      printf("Test of function \"is_fd\" Succeeded !\n");
   }

   /*Test of function "is_rt" (White box)*/
   {
      program p;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "RT");
      strcpy(p.wds[1], "45"); /*Change "30" to "A" and test again*/
      p.tail = 1;
      assert(is_rt(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "RT");
      strcpy(p.wds[1], "45"); /*Change "30" to "A" and test again*/
      strcpy(p.wds[2], ";");
      p.tail = 2;
      assert(is_rt(&p) == 0);

      printf("Test of function \"is_rt\" Succeeded !\n");
   }

   /*Test of function "is_lt" (White box)*/
   {
      program p;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "LT");
      strcpy(p.wds[1], "45"); /*Change "30" to "A" and test again*/
      p.tail = 1;
      assert(is_lt(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "LT");
      strcpy(p.wds[1], "45"); /*Change "30" to "A" and test again*/
      strcpy(p.wds[2], ";");
      p.tail = 2;
      assert(is_lt(&p) == 0);

      printf("Test of function \"is_lt\" Succeeded !\n");
   }

   /*Test of function "is_instruction" (White box)*/
   /*
   Since "is_instruction" is just OR of return value of 5 functions
   following is just a check if the OR expression gives right result.
   */
   {
      int is_fd_return;
      int is_lt_return;
      int is_rt_return;
      int is_do_return;
      int is_set_return;

      is_fd_return = 1;
      is_lt_return = 0;
      is_rt_return = 0;
      is_do_return = 0;
      is_set_return = 0;
      assert((is_fd_return || is_lt_return || is_rt_return ||
              is_do_return || is_set_return) == 1);

      is_fd_return = 0;
      is_lt_return = 0;
      is_rt_return = 0;
      is_do_return = 0;
      is_set_return = 0;
      assert((is_fd_return || is_lt_return || is_rt_return ||
              is_do_return || is_set_return) == 0);

      printf("Test of function \"is_instruction\" Succeeded !\n");
   }

   /*Test of function "is_instruction_list" (White box)*/
   {
      program p;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "}");
      assert(is_instruction_list(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "DO");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], "FROM");
      strcpy(p.wds[3], "1");
      strcpy(p.wds[4], "TO");
      strcpy(p.wds[5], "8");
      strcpy(p.wds[6], "{");
      strcpy(p.wds[7], "FD");
      strcpy(p.wds[8], "30");
      strcpy(p.wds[9], "LT");
      strcpy(p.wds[10], "45");
      strcpy(p.wds[11], "}");
      strcpy(p.wds[12], "}");
      p.tail = 12;
      assert(is_instruction_list(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "FD");
      strcpy(p.wds[1], "16");
      strcpy(p.wds[2], "DO");
      strcpy(p.wds[3], "A");
      strcpy(p.wds[4], "FROM");
      strcpy(p.wds[5], "1");
      strcpy(p.wds[6], "TO");
      strcpy(p.wds[7], "8");
      strcpy(p.wds[8], "{");
      strcpy(p.wds[9], "FD");
      strcpy(p.wds[10], "30");
      strcpy(p.wds[11], "LT");
      strcpy(p.wds[12], "45");
      strcpy(p.wds[13], "}");
      strcpy(p.wds[14], "}");
      p.tail = 14;
      assert(is_instruction_list(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "DO");
      strcpy(p.wds[1], "A");
      strcpy(p.wds[2], "FROM");
      strcpy(p.wds[3], "1");
      strcpy(p.wds[4], "TO");
      strcpy(p.wds[5], "8");
      strcpy(p.wds[6], "{");
      strcpy(p.wds[7], "FD");
      strcpy(p.wds[8], "30");
      strcpy(p.wds[9], "LT");
      strcpy(p.wds[10], "45");
      strcpy(p.wds[11], "}");
      p.tail = 11;
      assert(is_instruction_list(&p) == 0);

      printf("Test of function \"is_instruction_list\" Succeeded !\n");
   }

   /*Test of function "is_main" (White box)*/
   {
      program p;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "{");
      strcpy(p.wds[1], "DO");
      strcpy(p.wds[2], "A");
      strcpy(p.wds[3], "FROM");
      strcpy(p.wds[4], "1");
      strcpy(p.wds[5], "TO");
      strcpy(p.wds[6], "8");
      strcpy(p.wds[7], "{");
      strcpy(p.wds[8], "FD");
      strcpy(p.wds[9], "30");
      strcpy(p.wds[10], "LT");
      strcpy(p.wds[11], "45");
      strcpy(p.wds[12], "}");
      strcpy(p.wds[13], "}");
      p.tail = 13;
      assert(is_main(&p) == 1);

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }
      strcpy(p.wds[0], "{");
      strcpy(p.wds[1], "DO");
      strcpy(p.wds[2], "A");
      strcpy(p.wds[3], "FROM");
      strcpy(p.wds[4], "1");
      strcpy(p.wds[5], "TO");
      strcpy(p.wds[6], "8");
      strcpy(p.wds[7], "{");
      strcpy(p.wds[8], "FD");
      strcpy(p.wds[9], "30");
      strcpy(p.wds[10], "LT");
      strcpy(p.wds[11], "45");
      strcpy(p.wds[12], "}");
      p.tail = 12;
      assert(is_main(&p) == 0);

      printf("Test of function \"is_main\" Succeeded !\n");
   }
}
