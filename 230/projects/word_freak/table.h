/*
 * Kevin Vicente
 * March 2019
 *
 * We will represent a table of words and their frequencies with a doubly linked list of Entry
 * structures. The linked list will be sorted (in non-ascending order) by count. The logic is that
 * words with high frequency (e.g. "the" or "and" or "or") will be accessed very often, and words
 * lower frequency will be accessed less. To reduce search time, we keep high frequency words at
 * the beginning of the list, and lower frequency words near the end.
 */

#ifndef GLOSSARY_H
#define GLOSSARY_H
#include <stdbool.h>

struct Entry {
  char* word;
  unsigned count, length;
  struct Entry *next, *previous;
};

typedef struct Entry* Table;

bool add_entry(Table* table_head, char* word, unsigned length);
// will call add_entry if word is not found in table, otherwise increments the entry's count
bool update_entry(Table* table_head, char* word, unsigned length);
void update_entry_position(Table* table_head, struct Entry* ent);
void destroy_table(Table table_head);

#endif
