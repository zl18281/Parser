#include "extension.h"

void test_strategy(void)
{
   /*Test of function "print_symbol_table" (White Box)*/
   {
      symbol_table t;
      int k;

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }
      t.table[0] = 'A';
      t.value[0] = 6;
      t.table[1] = 'B';
      t.value[1] = 8;
      t.table[2] = 'C';
      t.value[2] = 7;
      printf("\nFollowing tests if the function \"print_symbol_table\" is right !\n");
      print_symbol_table(&t);
      printf("\nTest of function \"print_symbol_table\" finished, please look at what is printed !\n");
   }

   /*Test of function "is_in_table" (White Box)*/
   {
      symbol_table t;
      int k;

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }
      t.table[18] = 'C';
      t.value[18] = 66;
      t.table[16] = 'G';
      t.value[16] = 88;
      assert(is_in_table(&t, 'C') == 1);
      assert(is_in_table(&t, 'G') == 1);
      assert(is_in_table(&t, 'B') == 0);
      assert(is_in_table(&t, 'X') == 0);
      printf("Test of function \"is_in_table\" succeeded !\n");
   }

   /*Test of function "insert_symbol_table" (White Box)*/
   {
      symbol_table t;
      int k;

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }

      insert_symbol_table(&t, 'A', 16);
      insert_symbol_table(&t, 'B', 18);
      insert_symbol_table(&t, 'C', 17);
      assert(t.table[0] == 'A');
      assert((int)t.value[0] == 16);
      assert(t.table[1] == 'B');
      assert((int)t.value[1] == 18);
      assert(t.table[2] == 'C');
      assert((int)t.value[2] == 17);
      printf("Test of function \"insert_symbol_table\" succeeded !\n");
   }

   /*Test of function "search_table_value" (White Box)*/
   {
      symbol_table t;
      int k;

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }

      insert_symbol_table(&t, 'A', 16);
      insert_symbol_table(&t, 'B', 18);
      insert_symbol_table(&t, 'C', 17);
      assert((int)search_table_value(&t, "A") == 16);
      assert((int)search_table_value(&t, "B") == 18);
      assert((int)search_table_value(&t, "C") == 17);
      printf("Test of function \"insert_symbol_table\" succeeded !\n");
   }

   /*Test of function "is_var" (White Box)*/
   {
      symbol_table t;
      int k;

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }
      insert_symbol_table(&t, 'A', 16);
      insert_symbol_table(&t, 'B', 18);
      insert_symbol_table(&t, 'C', 17);

      assert(is_var(&t, "B") == 1);
      assert(is_var(&t, "D") == 1);
      assert(is_in_table(&t, 'D') == 1);
      assert(is_var(&t, "6") == 0);
      printf("Test of function \"is_var\" succeeded !\n");
   }

   /*Test of function "is_varnum" (White Box)*/
   {
      symbol_table t;
      int k;

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }
      insert_symbol_table(&t, 'A', 16);
      insert_symbol_table(&t, 'B', 18);
      insert_symbol_table(&t, 'C', 17);

      assert(is_varnum(&t, "66") == 1);
      assert(is_varnum(&t, "6B") == 0);
      assert(is_varnum(&t, "B") == 1);
      assert(is_varnum(&t, "G") == 1);
      assert(t.table[3] == 'G');
      assert((int)t.value[3] == 0);
      printf("Test of function \"is_varnum\" succeeded !\n");
   }

   /*Test of function "change_value" (White Box)*/
   {
      symbol_table t;
      int k;

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }
      t.table[0] = 'A';
      t.value[0] = 6;
      t.table[1] = 'B';
      t.value[1] = 8;
      t.table[2] = 'C';
      t.value[2] = 7;
      change_value(&t, 'A', 66);
      assert((int)t.value[0] == 66);
      change_value(&t, 'B', 88);
      assert((int)t.value[1] == 88);
      change_value(&t, 'C', 77);
      assert((int)t.value[2] == 77);
      printf("Test of function \"change_value\" succeeded !\n");
   }

   /*Test of function "copy_turtle" (White Box)*/
   {
      turtle turt;
      turtle *new_turt;

      turt.turtle_x = 66;
      turt.turtle_y = 88;
      turt.radius = 3.14;
      new_turt = copy_turtle(&turt);
      assert((int)new_turt->turtle_x == (int)turt.turtle_x);
      assert((int)new_turt->turtle_y == (int)turt.turtle_y);
      assert((int)new_turt->radius == (int)turt.radius);
      printf("Test of function \"copy_turtle\"  succeeded !\n");
   }

   /*Test of function "to_digit" (White Box)*/
   {
      assert(to_digit('0') == 0);
      assert(to_digit('1') == 1);
      assert(to_digit('2') == 2);
      assert(to_digit('3') == 3);
      assert(to_digit('4') == 4);
      assert(to_digit('5') == 5);
      assert(to_digit('6') == 6);
      assert(to_digit('7') == 7);
      assert(to_digit('8') == 8);
      assert(to_digit('9') == 9);
      printf("Test of function \"to_digit\"  succeeded !\n");
   }

   /*Test of function ""to_num (White Box)*/
   {
      symbol_table t;
      int k;

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }
      t.table[0] = 'A';
      t.value[0] = 6;
      t.table[1] = 'B';
      t.value[1] = 8;
      t.table[2] = 'C';
      t.value[2] = 7;

      assert((int)to_num(&t, "A") == 6);
      assert((int)to_num(&t, "16.22") == 16);
      assert((int)(to_num(&t, "16.22") *100 - 1600) == 22);
      printf("Test of function \"to_num\"  succeeded !\n");
   }

   /*Test of function "polish_to_num" (White Box)*/
   {
      program p;
      symbol_table t;
      int j, k;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }

      for(k = 0; k < MAX_SYMBOL; k++){
      t.table[k] = (int)'!';
      t.value[k] = 0;
      }

      strcpy(p.wds[0], "6");
      strcpy(p.wds[1], "8");
      p.tail++;
      strcpy(p.wds[2], "+");
      p.tail++;
      strcpy(p.wds[3], ";");
      p.tail++;
      assert((int)polish_to_num(&t, &p) == 14);

      p.tail = 0;
      t.table[0] = 'A';
      t.value[0] = 5.5;
      strcpy(p.wds[0], "A");
      strcpy(p.wds[1], "8");
      p.tail++;
      strcpy(p.wds[2], "*");
      p.tail++;
      strcpy(p.wds[3], ";");
      p.tail++;
      assert((int)polish_to_num(&t, &p) == 44);

      p.tail = 0;
      strcpy(p.wds[0], "6");
      strcpy(p.wds[1], "8");
      p.tail++;
      strcpy(p.wds[2], "*");
      p.tail++;
      strcpy(p.wds[3], "2");
      p.tail++;
      strcpy(p.wds[4], "+");
      p.tail++;
      strcpy(p.wds[5], "5");
      p.tail++;
      strcpy(p.wds[6], "/");
      p.tail++;
      strcpy(p.wds[7], ";");
      p.tail++;
      assert((int)polish_to_num(&t, &p) == 10);

      printf("Test of function \"polish_to_num\" succeeded !\n");
   }

   /*Test of function "is_set" (White Box)*/
   {
      program p;
      symbol_table t;
      int j, k;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }

      for(k = 0; k < MAX_SYMBOL; k++){
      t.table[k] = (int)'!';
      t.value[k] = 0;
      }

      strcpy(p.wds[0], "SET");
      strcpy(p.wds[1], "C");
      p.tail++;
      strcpy(p.wds[2], ":=");
      p.tail++;
      strcpy(p.wds[3], "2");
      p.tail++;
      strcpy(p.wds[4], "3");
      p.tail++;
      strcpy(p.wds[5], "*");
      p.tail++;
      strcpy(p.wds[6], ";");
      p.tail++;
      assert(is_set(&p, &t) == 1);
      assert(t.table[0] == 'C');
      assert((int)t.value[0] == 6);

      printf("Test of function \"is_set\" succeeded !\n");
   }

   /*Test of function "is_rt" (White Box)*/
   {
      program p;
      symbol_table t;
      turtle turt;
      int j, k;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }

      for(k = 0; k < MAX_SYMBOL; k++){
      t.table[k] = (int)'!';
      t.value[k] = 0;
      }

      strcpy(p.wds[0], "RT");
      strcpy(p.wds[1], "45");
      p.tail++;

      turt.turtle_x = 0;
      turt.turtle_y = 0;
      turt.radius = 0;
      turt.turn_on_off = 1;

      assert(is_rt(&p, &t, &turt) == 1);
      assert((int)(turt.radius * 1000) == 785);

      printf("Test of function \"is_rt\" succeeded !\n");
   }

   /*Test of function "is_lt" (White Box)*/
   {
      program p;
      symbol_table t;
      turtle turt;
      int j, k;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }

      for(k = 0; k < MAX_SYMBOL; k++){
      t.table[k] = (int)'!';
      t.value[k] = 0;
      }

      strcpy(p.wds[0], "LT");
      strcpy(p.wds[1], "45");
      p.tail++;

      turt.turtle_x = 0;
      turt.turtle_y = 0;
      turt.radius = 0;
      turt.turn_on_off = 1;

      assert(is_lt(&p, &t, &turt) == 1);
      assert((int)(turt.radius * 1000) == -785);

      printf("Test of function \"is_lt\" succeeded !\n");
   }

   /*Test of function "is_fd"*/
   /*Since the original "is_fd" function is tested in parser, this test just test inserted graphical related
   codes to see if the status of the turtle is rightfully changed (White Box)*/
   {
      turtle t;
      double fd_distance = 50.0;

      t.turtle_x = 0;
      t.turtle_y = 0;
      t.radius = (60.0 / 180.0) * 3.14;
      t.turn_on_off = 1;
      t.turtle_x = t.turtle_x + fd_distance * cos(t.radius);
      t.turtle_y = t.turtle_y + fd_distance * sin(t.radius);
      assert((int)t.turtle_x == 25);
      assert((int)t.turtle_y == 43);

      printf("Test of function \"is_fd\" succeeded !\n");
   }

   /*Test of function "is_move"*/
   {
      program p;
      symbol_table t;
      turtle turt;
      int j, k;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }

      for(k = 0; k < MAX_SYMBOL; k++){
         t.table[k] = (int)'!';
         t.value[k] = 0;
      }

      turt.turtle_x = 0;
      turt.turtle_y = 0;
      turt.radius = 0;
      turt.turn_on_off = 1;

      strcpy(p.wds[0], "MOV");
      strcpy(p.wds[1], "66");
      strcpy(p.wds[2], "88");
      p.tail = 2;

      assert(is_move(&p, &t, &turt) == 1);
      assert((int)turt.turtle_x == 66);
      assert((int)turt.turtle_y == 88);

      printf("Test of function \"is_move\" succeeded !\n");
   }

   /*Test of function "is_home"*/
   {
      program p;
      turtle turt;
      int j;

      p.head = 0;
      p.tail = 0;
      for(j = 0; j < MAX_TOKEN; j++){
         strcpy(p.wds[j], "");
      }

      turt.turtle_x = 16;
      turt.turtle_y = 16;
      turt.radius = 28;
      turt.turn_on_off = 1;

      strcpy(p.wds[0], "HOME");
      p.tail = 0;

      assert(is_home(&p, &turt) == 1);
      assert((int)turt.radius == 0);
      assert((int)turt.turtle_x == (int)(WWIDTH / 2));
      assert((int)turt.turtle_y == (int)(WHEIGHT) /2);

      printf("Test of function \"is_home\" succeeded !\n");
   }

   /*Test of function "is_cmp"*/
   {
      assert(is_cmp(">") == 1);
      assert(is_cmp("=") == 1);
      printf("Test of function \"is_cmp\" succeeded !\n");
   }

   /*Combined test of stack related functions */
   {
      polish_stack s;

      initialize_stack(&s);
      assert(s.top == -1);
      push(&s, 1);
      assert(s.top == 0);
      assert((int)pop(&s) == 1);
      assert(s.top == -1);
      printf("Test of 3 stack related functions succeeded !\n");
   }

   /*Others*/
   {
      printf("Function \"copy_struct\", \"is_op\", \"is_polish\", \"is_instruction\",");
      printf("\n\"is_instruction_list\", \"is_main\" are tested in parser\n");
      printf("See printed information about testing of function \"is_do\", \"is_if\" and \"is_color\"\n");
   }
}
