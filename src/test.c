//
// test.c
//
// Copyright (c) 2019 TakedaHiromasa <t-takeda.work>
//

#include <stdio.h>
#include <string.h>
#include "list.h"

int main() {
  List_t *list = new_list("char *");

  puts("# make list");
  printf("data_type = \"%s\"\n", list->data_type);
  printf("size:%d ", size(list));
  puts_list("%s", list);

  puts("\n# push_back [hello] [world] [!!]");
  push_back(list, "hello");
  push_back(list, "world");
  push_back(list, "!!");
  printf("size:%d ", size(list));
  puts_list("%s", list);

  puts("\n# push_front [->]");
  push_front(list, "->");
  printf("size:%d ", size(list));
  puts_list("%s", list);

  puts("\n# pop_back");
  printf("popped value = [%s]\n", pop_back(list));
  puts("\n# pop_front");
  printf("popped value = [%s]\n", pop_front(list));

  puts("");
  printf("size:%d ", size(list));
  puts_list("%s", list);

  puts("\n# Insert [HELLO] in front of [hello].");
  for (Node_t *itr = list->begin; itr != list->end; NEXT(itr)) {
    if (strcmp(itr->val, "hello") == 0) {
      insert(list, itr, "HELLO");
      break;
    }
  }
  puts_list("%s", list);

  puts("\n# erase [hello].");
  for (Node_t *itr = list->begin; itr != list->end; NEXT(itr)) {
    if (strcmp(itr->val, "hello") == 0) {
      erase(list, itr);
      break;
    }
  }
  puts_list("%s", list);

  puts("\n# clear list");
  clear(list);
  printf("size:%d ", size(list));
  puts_list("%s", list);
  printf("empty = %d\n", empty(list));

  return 0;
}