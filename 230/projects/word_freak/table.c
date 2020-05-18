/* * Kevin Vicente
 * March 2019
 *
 * This is the implementation of our sorted linked list.
 * Note that when I refer to our 'invariant' I am talking about the property of the list being
 * in nonascending order (with regards to the entry's count attribute).
 */

#include "table.h"
#include <stdlib.h>
#include <string.h>

bool add_entry(Table* table_head, char* word, unsigned length) {
  struct Entry* new_entry = (struct Entry*) malloc(sizeof(struct Entry));
  if (new_entry == NULL) { return false; }
  new_entry->word = (char*) malloc(length + 1);
  if (new_entry->word == NULL) { return false; }

  // Our word is not null terminated, so we need to copy exactly length characters
  // and add our own null character.
  strncpy(new_entry->word, word, length);
  new_entry->word[length] = '\0';
  new_entry->count = 1;
  new_entry->length = length + 1;

  update_entry_position(table_head, new_entry);
  return true;
}

bool update_entry(Table* table_head, char* word, unsigned length) {
  struct Entry* prev = *table_head;
  // This is so that we can use strcmp()
  char word_buf[length + 1];
  memcpy(word_buf, word, length);
  word_buf[length] = '\0';

  // First we check the first element in the table
  if (prev != NULL) {
    if (prev->length == length + 1 && strcmp(word_buf, prev->word) == 0) {
      prev->count += 1; return true;
    }
  }

  // After this loop, prev will point to the entry that contains 'word'
  while (prev != NULL && prev->next != NULL) {
    // length + 1 since the length in an entry includes an extra null character
    if (prev->next->length != length + 1) { prev = prev->next; continue; }
    if (strcmp(word_buf, prev->next->word) == 0) {
      prev->next->count += 1;
      struct Entry* temp = prev->next;
      prev->next = prev->next->next;
      if (prev->next != NULL) { prev->next->previous = prev; }
      update_entry_position(table_head, temp);
      return true;
    }
    prev = prev->next;
  }

  // Edge cases: only one entry in the table so far or the word is either the last entry or not in
  // the list at all
  if (prev != NULL && prev->next == NULL) {
    if (prev->length == length + 1 && strcmp(word_buf, prev->word) == 0) {
      prev->count += 1;
      prev->previous->next = prev->next;
      update_entry_position(table_head, prev);
      return true;
    }
    return add_entry(table_head, word, length);
  }

  // This handles any words that are not in the table (or the case of an empty table)
  if (prev == NULL) { return add_entry(table_head, word, length); }
}


// This requires that ent is not currently in the table
void update_entry_position(Table* table_head, struct Entry* ent) {
  /* Three cases:
   * (1) The table is empty.
   * (2) The table has one entry.
   * (3) The table has more than one entry.
   */

  // Case 1
  if (*table_head == NULL) {
    *table_head = ent;
    ent->previous = NULL; ent->next = NULL;
    return;
  }

  // Case 2
  struct Entry* first = *table_head;
  if (first->next == NULL) {
    if (first->count >= ent->count) {
      first->next = ent;
      ent->previous = first;
      ent->next = NULL;
    } else {
      first->previous = ent; ent->next = first;
      first->next = NULL; ent->previous = NULL;
      *table_head = ent;
    }
    return;
  }

  // Case 3
  struct Entry* buf = first;
  while (buf != NULL && buf->next != NULL) {
    if (buf->count <= ent->count) { break; }
    buf = buf->next;
  }

  if (buf->count <= ent->count) {
    ent->previous = buf->previous; ent->next = buf;
    // if buf is not the first entry in the table...
    if (buf->previous != NULL) { buf->previous->next = ent; }
    else { *table_head = ent; }
    buf->previous = ent; 
  }

  // This will execute if we reach the end of the list
  // and the last entry has a greater count than ent
  else { buf->next = ent; ent->previous = buf; ent->next = NULL; }
}

void destroy_table(Table table_head) {
  struct Entry* buf = table_head;
  struct Entry* temp;
  while (buf != NULL) {
    free(buf->word);
    temp = buf->next;
    free(buf);
    buf = temp;
  }
}
