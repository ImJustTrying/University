#include <stdlib.h>
#include <string.h>
#include "items.h"

struct Item* item(char* name, char* description, struct Item* next) {
  struct Item* new_item = (struct Item*) malloc(sizeof(struct Item));
  if (new_item == NULL) { return NULL; }

  new_item->name = (char*) malloc(strlen(name));
  new_item->description = (char*) malloc(strlen(description));
  if (new_item->name == NULL || new_item->description == NULL) {
    free(new_item); return NULL;
  }

  strcpy(new_item->name, name);
  strcpy(new_item->description, description);
  new_item->next = next;
  return new_item;
}

struct Item* item_take_first(struct Item** head) {
  if (head != NULL && *head != NULL) {
    struct Item* t = *head;
    if ((*head)->next == NULL) { *head = NULL; }
    else { *head = (*head)->next; }
    return t;
  }
  return NULL;
}

struct Item* item_take(struct Item** head, char* name) {
  if (strcmp((*head)->name, name) == 0) {
    struct Item* result = *head;
    *head = (*head)->next;
    return result;
  }

  struct Item* buffer = *head;
  do {
    if (strcmp(buffer->next->name, name) == 0) { break; }
    buffer = buffer->next;
  } while (buffer != NULL && buffer->next != NULL);

  if (buffer == NULL) { return NULL; }
  struct Item* result = buffer->next;
  if (buffer->next != NULL) {
    buffer->next = buffer->next->next;
  }
  return result;
}

bool item_contains(struct Item* head, char* item_name) {
  struct Item* buf = head;
  while (buf != NULL) {
    if (strcmp(buf->name, item_name)) { return true; }
    buf = buf->next;
  }
  return false;
}

void item_place(struct Item** head, struct Item* new_item) {
  if (*head != NULL) { new_item->next = *head; }
  *head = new_item;
}

void delete_items(struct Item* head) {
  struct Item* buffer = head;
  while (buffer != NULL) {
    free(buffer->name);
    free(buffer->description);
    struct Item* temp = buffer->next;
    free(buffer);
    buffer = temp;
  }
}
