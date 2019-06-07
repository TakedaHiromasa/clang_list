//
// list.c
//
// Copyright (c) 2019 TakedaHiromasa <t-takeda.work>
//

#include <stdio.h>
#include "list.h"


/*
 * Allocates a new Node_t. NULL on failure.
 */
Node_t* new_node(void *val) {
  Node_t *self;
  if (!(self = malloc(sizeof(Node_t))))
    return NULL;

  self->val = val;
  self->prev = NULL;
  self->next = NULL;

  return self;
}


/*
 * Allocate a new List_t. NULL on failure.
 */
List_t* new_list(char *data_type) {
  List_t *self;
  if (!(self = malloc(sizeof(List_t))))
    return NULL;

  self->data_type = data_type;

  // begin & end = [dummy node]
  self->begin = self->end = new_node(NULL);

  return self;
}


/*
 * Clear all the contents of the list 
 * and release the memory. 
 */
void clear(List_t *self) {
  Node_t *curr = self->begin;
  Node_t *next;

  while(curr != self->end) {
    next = curr->next;
    free(curr);
    curr = next;
  }

  (self->begin = self->end)->prev = NULL;
}


/*
 * Return the inserted node.
 */
Node_t* insert(List_t *self, Node_t *itr, void *val) {
  Node_t *node = new_node(val);

  if(itr->prev == NULL){
    self->begin = node;
    (node->next = itr)->prev = node;
  } else {
    (node->prev = itr->prev)->next = node;
    (node->next = itr)->prev = node;
  }

  return node;
}


/*
 * Return the next iterator for a given iterator.
 */
Node_t* erase(List_t *self, Node_t *itr) {
  if(itr->prev == NULL){
    self->begin = itr->next;
    itr->next->prev = NULL;
  } else {
    (itr->prev->next = itr->next)->prev = itr->prev;
  }

  Node_t *ret = itr->next;
  free(itr);
  return ret;
}


void push_back(List_t *self, void *val) {
  Node_t *node = new_node(val);

  // List is empty
  if (self->begin == self->end) {
    node->next = self->end;
    self->begin = self->LIST_LAST = node;
  } else {
    // [pv|last_node|nx] <-> [pv|new_node|nx]
    (node->prev = self->LIST_LAST)->next = node;
    // [pv|new_node|nx] <-> [pv|dummy|nx]
    (node->next = self->end)->prev = node;
  }
}


void push_front(List_t *self, void *val) {
  Node_t *node = new_node(val);

  // List is empty
  if (self->begin == self->end) {
    node->next = self->end;
    self->begin = self->LIST_LAST = node;
  } else {
    // [pv|new_node|nx] <-> [pv|begin|nx]
    (node->next = self->begin)->prev = node;
    self->begin = node;
  }
}


void* pop_back(List_t *self) {
  if (self->begin == self->end)
    return NULL;

  Node_t *node = self->LIST_LAST;

  // List is only one node
  if (node == self->begin) {
    (self->begin = self->end)->prev = NULL;
  } else {
    (self->LIST_LAST = node->prev)->next = self->end;
  }

  return node->val;
}


void* pop_front(List_t *self) {
  if (self->begin == self->end)
    return NULL;

  Node_t *node = self->begin;

  // List is only one node
  if (node == self->LIST_LAST) {
    (self->begin = self->end)->prev = NULL;
  } else {
    (self->begin = node->next)->prev = NULL;
  }

  return node->val;
}


int size(List_t *self) {
  int size = 0;

  for (Node_t *itr = self->begin; itr != self->end; NEXT(itr))
    size++;

  return size;
}

/*
 * is empty. return True(1) or False(0)
 */
char empty(List_t *self) {
  return self->begin == self->end;
}


void puts_list(const char *format, const List_t *list) {
  printf("[ ");

  for (Node_t *itr = list->begin; itr != list->end; NEXT(itr)) {
    printf(format, itr->val);
    putchar(' ');
  }

  printf("]\n");
}