#ifndef ROOMS_H
#define ROOMS_H
#include "items.h"

struct Room {
  char* description;
  struct Item* items;
  struct Room *up, *down, *north, *south, *east, *west;
  unsigned number;
};

enum Direction { North, East, South, West, Up, Down };


struct Room* room(char* description, struct Item* items, unsigned num);
void set_room_exit(enum Direction dir, struct Room* room, struct Room* exit);
void delete_room(struct Room* room);

#endif
