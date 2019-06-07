//
// list.h
//
// Copyright (c) 2019 TakedaHiromasa <t-takeda.work>
//

/* ///【データ構造】/////////////////////////////////////////////////
    このリストは番兵として、一番後ろにダミーノードが存在する
    begin は先頭, end は末尾の次の要素へのイテレータを保持している

    begin                               end
     ∨                                   ∨
    [pv| val |nx] <-> [pv| val |nx] <-> [pv| dummy |nx]
    
////////////////////////////////////////////////////////////////// */

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

// Library version
#define LIST_VERSION "0.1"


/* //////////////////////////
    List macro
////////////////////////// */
#ifndef LIST_LAST
#define LIST_LAST end->prev
#endif

// #ifndef UNUSED_VARIABLE
// #define UNUSED_VARIABLE(x) (void)(x)
// #endif

/* //////////////////////////
    Iterator macro
////////////////////////// */
#ifndef INC_ITER
#define INC_ITER(itr) itr = itr->next
#endif

#ifndef DEC_ITER
#define DEC_ITER(itr) itr = itr->prev
#endif

#ifndef SELECTER
#define SELECTER(ONE_, TWO_, SELECT, ...) SELECT
#endif

#ifndef NEXT
#define NEXT(...) SELECTER(__VA_ARGS__, next, INC_ITER) (__VA_ARGS__)
#endif


/* //////////////////////////
    structs
////////////////////////// */
// List_t node struct.
typedef struct Node {
  void  *val;
  struct Node *prev;
  struct Node *next;
} Node_t;

// List_t struct.
typedef struct {
  char   *data_type;
  Node_t *begin;
  Node_t *end;
} List_t;


/* //////////////////////////
    Function declaration
////////////////////////// */

/* Functions of List */
// constructions
Node_t* new_node    (void   *val);
List_t* new_list    (char   *data_type);

// operations
void    clear       (List_t *self);
Node_t* insert      (List_t *self, Node_t *itr, void *val);
Node_t* erase       (List_t *self, Node_t *itr);
void    push_back   (List_t *self, void   *val);
void    push_front  (List_t *self, void   *val);
void*   pop_back    (List_t *self);
void*   pop_front   (List_t *self);
int     size        (List_t *self);
char    empty       (List_t *self);

void    puts_list   (const char *format, const List_t *list);

/* Functions of Iterator */
Node_t* next        (Node_t *itr, int n);


#ifdef __cplusplus
}
#endif

#endif /* LIST_H */