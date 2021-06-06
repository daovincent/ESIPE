#ifndef __MSORTCHAIN_H__
#define __MSORTCHAIN_H__

typedef struct link{
  int data;
  struct link* next;
} link;


link* create_link(int data);
link* insert_first(link* first, int data);
void free_list(link* list);
link* split_middle(link* first);
void print_list(link* first);
link* fuse_back(link* a,link* b);
link* msort(link* first);
#endif
