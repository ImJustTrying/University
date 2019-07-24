#include <stdlib.h>
#include <string.h>
#include "rooms.h"

struct Room* room(char* description, struct Item* items, unsigned num) {
  struct Room* new_room = (struct Room*) malloc(sizeof(struct Room));
  if (new_room == NULL) { return NULL; }
  new_room->description = (char*) malloc(strlen(description));
  strcpy(new_room->description, description);
  new_room->items = items;
  new_room->number = num;

  new_room->up    = NULL; new_room->down  = NULL;
  new_room->north = NULL; new_room->south = NULL;
  new_room->east  = NULL; new_room->west  = NULL;
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
