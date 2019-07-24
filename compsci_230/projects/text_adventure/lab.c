/*
 * Kevin Vicente
 * February 2019
 *
 * This is a text adventure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG

struct Item {
  char* name;
  char* description;
  struct Item* next;
};

struct Room {
  char* description;
  struct Item* items;
  struct Room *up, *down, *north, *south, *east, *west;
};

enum Direction { North, East, South, West, Up, Down };


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

char* item_name(struct Item* item) { return item->name; }
char* item_description(struct Item* item) { return item->description; }
struct Item* item_next(struct Item* item) { return item->next; }

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
  buffer->next = buffer->next->next;
  return result;
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


struct Room* room(char* description, struct Item* items,
                  struct Room* up, struct Room* down,
                  struct Room* north, struct Room* south,
                  struct Room* east, struct Room* west)
{
  struct Room* new_room = (struct Room*) malloc(sizeof(struct Room));
  if (new_room == NULL) { return NULL; }
  new_room->description = (char*) malloc(strlen(description));
  strcpy(new_room->description, description);
  new_room->items = items;

  new_room->up = up; new_room->down = down;
  new_room->north = north; new_room->south;
  new_room->east = east; new_room->west;
  return new_room;
}

// This is the substitute for "room_exit_north"
// Set `room`s exit to `exit` in the direction `dir`. Also sets `exit`s exit accordingly
// (in the opposite direction, e.g. dir = North, `exit`s south exit is changed)
void set_room_exit(enum Direction dir, struct Room* room, struct Room* exit) {
  switch(dir) {
    case North: room->north = exit; exit->south = room; break;
    case South: room->south = exit; exit->north = room; break;
    case East:  room->east  = exit; exit->west  = room; break;
    case West:  room->west  = exit; exit->east  = room; break;
    case Up:    room->up    = exit; exit->down  = room; break;
    case Down:  room->down  = exit; exit->up    = room; break;
  }
}

void delete_room(struct Room* room) {
  if (room != NULL) {
    free(room->description);
    delete_items(room->items);
    free(room);
  }
}

#ifdef DEBUG
#include <stdbool.h>

bool test_item_take() {
  struct Item* items = item("key", "a golden key covered in dirt",
                         item("bag", "a trusty backpack", NULL));
  struct Item* key = item_take(&items, "key");
  
  bool result = key != NULL && strcmp(key->name, "key") == 0;
  delete_items(items);
  return result;
}

bool test_rooms() {
  struct Room* room1 = room("The first room", NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  struct Room* room2 = room("The second room", NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  set_room_exit(North, room1, room2);
  return room1->north == room2 && room2->south == room1;
}

#endif


int main(void) {
  #ifdef DEBUG
  if (test_item_take()) { printf("item_take() test successful!\n"); }
  else { printf("item_take() test failed!\n"); }

  if (test_rooms()) { printf("test_rooms() successful!\n"); }
  else { printf("test_rooms() failed!\n"); }
  #endif

  char* start_desc = "You wake up in a strange room with a lamp hung by a string dangling over you.\n"
  "You pick yourself up off of the ground and notice there is a dirty key that is near the spot you"
  " were sleeping on.\nThere is also a door with a bright white outline around it that seems to lead"
  " outdoors.\nYou recall the kidnappers that drugged you and quickly think about how to get out of"
  " this room before they return!\n";

  char* end_desc = "You find yourself to be in a hall in a seemingly abandoned building.\nYou "
  "quickly make your way down the nearest staircase and make your way out of the building without "
  "being spotted.\nDespite your swift escape, you feel a strange sense of disappointment with "
  "regards to its ease.\n";

  struct Item* start_items = item("key", "a golden key covered in dirt",
                      item("door", "a locked door with light from outside seeping through", NULL));

  struct Item* end_items = item("freedom", "who could resist!", NULL);

  struct Room* start = room(start_desc, start_items, NULL, NULL, NULL, NULL, NULL, NULL);
  struct Room* end = room(end_desc, end_items, NULL, NULL, NULL, NULL, NULL, NULL);
  set_room_exit(North, start, end);

  delete_room(start);
  delete_room(end);

  return 0;
}
