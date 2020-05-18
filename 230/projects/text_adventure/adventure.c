/*
 * Kevin Vicente
 * February-March 2019
 *
 * This is a text adventure game. The following contains spoilers, so be cautious.
 * The game consists of 8 rooms, each labeled with a number. Each room can be moved with a
 * controller. The goal is to complete a 8-puzzle. There are hints and items scattered amongst the
 * rooms to hint to this fact.
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "rooms.h"
#include "items.h"

// This is so that all functions can access and update these (and to shorten argument lists).
struct Room* activated = NULL;
struct Room* top_left = NULL;


// returns the starting room.
struct Room* init_game() {
  struct Room* beginning = room(
    "The rooms is brightly lit by overhanging fluorescent lights.\nThe walls are tiled and seem worn.\n"
    "There are doors on all 4 sides of the room.\nThere is a red button with the number 6 on it.\n"
    "The only notable thing in the room is what seems to be a map lying on the ground.\n",
    item("map", "A dusty map with a digram of 8 rooms forming a square with a single room missing "
                "in the bottom right corner.\n",
      item("button", "A red circular button attached to the wall.\nIt has the number 6 on it.\n", NULL)
    ), 6
  );

  struct Room* north = room(
    "This room is similar to the room you woke up in, except this time there is a red button on the"
    " wall facing towards you.\nIt has the number 2 on it.",
    item("note (1)",
         "I need help.\nI don't remember how I got here or why, but I've been wandering around this "
         "place for hours and I can't tell how I'm meant to get out.\nThe only notable thing I've "
         "seen is the red buttons on the walls in the rooms, but they don't seem to have any effect"
         " on anything.\n",
      item("button", "A red circular button attached to the wall.\nIt has the number 2 on it.\n", NULL)
    ), 2
  );

  struct Room* south = room(
    "The lights in the room are flickering.\nThere are once again 4 doors on all 4 walls.\n"
    "There seems to be a glimmer in the corner.\nYou step closer to investigate and notice a strange"
    " controller on the ground.\nThere is a red button on the wall with the number 5 on it.\n",
    item("controller",
         "A small device with an LED screen and button with the word \"move\" on it.\nThe screen is"
         " caked in dirt, to the point that you cannot make out the text that is being displayed.\n",
      item("button", "A red circular button attached to the wall.\nIt has the number 5 on it.\n", NULL)
    ), 5
  );

  struct Room* east = room(
    "This room seems unusually clean, as if someone had recently scrubbed the walls and floor.\n"
    "There is a red button on the wall with the number 8 on it.\n",
    item("button", "A red circular button attached to the wall.\nIt has the number 8 on it.\n", NULL),
    8
  );

  struct Room* west = room(
    "The room is quite dirty, with stained tiles along the wall and small bugs and rodents crawling"
    " along the floor.\nThere lies a package of batteries covered in cockroaches.\nThere is a red "
    "button on the wall with the number 4 on it.\n",
    item("batteries", "A 4-pack of AA bateries.\n",
      item("button", "A red circular button attached to the wall.\nIt has the number 4 on it.\n", NULL)
    ), 4
  );

  struct Room* north_west = room(
    "In this room, the wall tiles are painted over with scribblings.\nThe lights in the room"
    " are flickering, so it is hard to see what is on the walls, but you move in closer to find "
    " out.\nOne depicts the solving of an 8-puzzle, another a drawing of a person running through "
    "a hedge maze.\nFinally, you notice a note that lies underneath the drawings and the button on"
    " the wall with the number 1 on it.\n",
    item("note (2)",
         "I found this remote thing with a single button that says move.\nIt would give errors "
         "everytime I tried to use it.\nIt said it can't move \"until the selected room is "
         "unoccupied\"?\n",
      item("button", "A red circular button attached to the wall.\nIt has the number 1 on it.\n", NULL)
    ), 1
  );

  struct Room* north_east = room(
    "This room is unique since it does not have any tiling like the other rooms.\nIt is painted "
    "completely white to the point where the walls, floor and ceiling are indistinguishable.\nA "
    " button lies in the center of the room on the floor labeled with a number 3.\n",
    item("button", "A red circular button attached to the wall.\nIt has the number 3 on it.\n", NULL),
    3
  );

  struct Room* south_west = room(
    "This room is similar to the room you woke up in, except some of the tiling on the walls has "
    "fallen off.\nThere is a red button with an 7 on it, and a note left near the northern door.\n",
    item("note (3)",
         "I got really furstrated today.\nI've been here for what seems like forever, so I got mad"
         " I punched one of the buttons on the wall.\nAfter I calmed down, I spammed the button on"
         "the controller and then the ground started shaking around me.\nAfter I tried to open the"
         " door to go back to the room I was in, but the door locked itself and I couldn't go back"
         ".\nI could only guess that maybe this controller was moving the rooms?\nMaybe this is "
         "the key to get out of this place?\n",
      item("button", "A red circular button attached to the wall.\nIt has the number 7 on it.\n", NULL)
    ), 7
  );


  top_left = north_west;
  set_room_exit(North, beginning, north);
  set_room_exit(South, beginning, south);
  set_room_exit(East, beginning, east);
  set_room_exit(West, beginning, west);
  set_room_exit(South, west, south_west);
  set_room_exit(North, west, north_west);
  set_room_exit(North, east, north_east);
  set_room_exit(West, north, north_west);
  set_room_exit(East, north, north_east);
  set_room_exit(West, south, south_west);
  return beginning;
}

// Moves (or tells the user it cannot move) to the next room
bool move(enum Direction dir, struct Room** current) {
  struct Room* old = *current;
  switch(dir) {
    case North: *current = ((*current)->north == NULL) ? *current : (*current)->north; break;
    case South: *current = ((*current)->south == NULL) ? *current : (*current)->south; break;
    case West:  *current = ((*current)->west == NULL)  ? *current : (*current)->west;  break;
    case East:  *current = ((*current)->east == NULL)  ? *current : (*current)->east;  break;
  }

  if (*current == old) { printf("You cannot move in this direction.\n"); return false; }
  else { printf("You move into the next room...\n"); return true; }
}

// Uses an item and gives the user information about what happens as a result
void use(struct Room* current, struct Item* inventory, char item[20], bool in_inventory) {
  if (strcmp(item, "map")) {
    printf("The map displays this:\n");
    struct Room* left = top_left;
    struct Room* mid = top_left->east;
    struct Room* right = top_left->east->east;

    for (int i = 0; i < 3; i++) {
      if (left != NULL) { printf("%i ", left->number); left = left->south; }
      else if (i != 2) { printf("* "); left = mid->south->west; }
      if (mid != NULL) { printf("%i ", mid->number); mid = mid->south; }
      else if (i != 2) { printf("* "); mid = left->south->east; }
      if (right != NULL) { printf("%i\n", right->number); right = right->south; }
      else if (i != 2) { printf("*\n"); right = mid->south->east; }
    }
  } else if (strcmp(item, "controller")) {
    
  } else if (strcmp(item, "button")) {
    activated = current;
    printf("You press the button.\nNothing seems to happen.\n");
  } else if (strcmp(item, "note")) {
    struct Item* note;
    if (in_inventory) { note = inventory; }
    else { note = current->items; }

    while (note != NULL) {
      if (strstr(note->name, item) != NULL) { break; }
      note = note->next;
    }

    if (note != NULL) {
      printf("You read the %s:\n%s", note->name, note->description);
    }
  }
}

// Returns true only on a successful command execution. Returns false if the command could not be
// recognized or if 
bool parse_input(struct Room** current, struct Item** inventory, char verb[10], char noun[20]) {
  if (strcmp(verb, "use") == 0) {
    if (item_contains(*inventory, noun)) { use(*current, *inventory, noun, true); }
    else if (item_contains((*current)->items, noun)) { use (*current, *inventory, noun, false); }
    else { printf("You do not have %s.\n", noun); return false; }
  }

  else if (strcmp(verb, "take") == 0) {
    if (strcmp(noun, "button") == 0) { printf("You cannot take the button.\n"); }
    else if (strcmp(noun, "note") == 0) {
      // need a special caase for the notes since they are numbered. we look for the item in the
      // room containing the substring "note"
      item_place(inventory, item_take_first(&(*current)->items));
    }
    else if (item_contains((*current)->items, noun)) {
      item_place(inventory, item_take(&(*current)->items, noun));
      printf("You take the %s: %s\n", (*inventory)->name, (*inventory)->description);
    }
    else { printf("There is no %s in this room.\n", noun); return false; }
  }

  else if (strcmp(verb, "drop") == 0) {
    if (item_contains(*inventory, noun)) {
      item_place(&(*current)->items, item_take(inventory, noun));
      printf("You drop the %s.\n", noun);
    } else { printf("You do not have a(n) %s.\n", noun); return false; }
  }

  else if (strcmp(verb, "go") == 0) {
    enum Direction dir = -1;
    switch (noun[0]) {
      case 'n': dir = North; break;
      case 's': dir = South; break;
      case 'w': dir = West;  break;
      case 'e': dir = East;  break;
      case 'u': dir = Up;    break;
      case 'd': dir = Down;  break;
    }

    if (dir == Down || dir == Up || dir == -1) {
      printf("%s is an invalid direction.\n", noun);
      return false;
    }

    return move(dir, current);
  }

  else if (strcmp(verb, "look") == 0) {
    printf("%s\n", (*current)->description);
  }

  else {
    printf("Unrecognized command, please try again.\n");
    return false;
  }

  return true;
}

// This is a (not-that-elegant) method to chack if the puzzle is solved. It is solved if the rooms
// are in this arrangment:
// 1  2  3
// 4  5  6
// 7  8  
bool check_room_state() {
  struct Room* current = top_left;
  for (int i = 0; i < 3; i++) {
    if (current == NULL) { return false; }
    if (current->number != i * 3 + 1) { return false; }
    if (current->east == NULL || current->east->number != i * 3 + 2) { return false; }
    if ((current->east->east == NULL && i != 2) || current->east->east->number != i * 3 + 3) {
      return false;
    }
  }
  return true;
}

int main(void) {
  struct Item* inventory = NULL;
  struct Room* current = init_game();
  struct Room* prev = NULL;
  char verb_buffer[10];
  char noun_buffer[20];

  printf(
    "Welcome to my text adventure!\nOur game follows a protagonist who awakes in a strange"
    " room and proceeds to make their way out.\nUse the following commands to play:\n"
    "look: provide a description of the room.\ntake ITEM: take an item and place it in your inventory"
    "\nuse ITEM: use an item in you inventory or in the room.\n"
    "go DIRECTION: move in a direction (north, east, west, or south)\ndrop ITEM: drop an item from "
    "your inventory\nEnjoy!\n\nYou awake in a strange room, not remembering how or why you got here.\n"
  );

  while(!check_room_state(current)) {
    if (prev != current) { printf("%s", current->description); prev = current; }
    printf("\n> ");
    // Read commands from the user in the form "verb noun"
    scanf(" %s", verb_buffer);
    if (strcmp(verb_buffer, "look") != 0) { scanf(" %s", noun_buffer); }
    parse_input(&current, &inventory, verb_buffer, noun_buffer);
  }

  printf("You win!\n");
  return 0;
}
