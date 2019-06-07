//
// list_iterator.c
//
// Copyright (c) 2019 TakedaHiromasa <t-takeda.work>
//

#include "list.h"

/*
 * Return the next Node_t or NULL when no more
 * nodes remain in the list.
 */
Node_t* next(Node_t *itr, int n) {  
  for (int i = 0; i < n; i++) {
    if(itr->next == NULL) break;
    INC_ITER(itr);
  }

  return itr;
}