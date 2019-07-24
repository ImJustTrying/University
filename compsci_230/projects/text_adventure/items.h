#ifndef ITEMS_H
#define ITEMS_H

#include <stdbool.h>

struct Item {
  char *name, *description;
  struct Item* next;
};

struct Item* item(char* name, char* description, struct Item* next);
struct Item* item_take(struct Item** head, char* name);
struct Item* item_take_first(struct Item** head);
bool item_contains(struct Item* head, char* item_name);
void item_place(struct Item** head, struct Item* new_item);
void delete_items(struct Item* head);

#endif
