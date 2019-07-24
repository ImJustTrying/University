/*
 * Kevin Vicente
 * January 2019
 *
 * This is an implementation of the popular connect four game in C.
 * The game works by having the user and an AI take turns inserting disks onto
 * a board. The winner is the first one to create a horizontal, vertical, or diagonal
 * line of four of their pieces.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

/* 
 * This will take the indices of an origin piece (x1, y1) and a piece that is adjacent to it
 * (x2, y2). It will look for a series of num_pieces other pieces in the same direction.
 * If there is a string of num_pieces pieces in the same direction, the procedure returns true.
 * Otherwise it returns false.
 */
bool check_direction(char board[6][7], char piece, int x1, int y1, int x2, int y2, int num_pieces) {
  int dx = x2 - x1, dy = y2 - y1;

  for (int i = 1; i <= num_pieces; i++) {
    int cummulative_x = x2 + dx * i, cummulative_y = y2 + dy * i;
    if (cummulative_x < 6 && cummulative_y < 7 && cummulative_x >= 0 && cummulative_y >= 0) {
      if (board[cummulative_x][cummulative_y] != piece) { return false; }
    }
    // if the direction extends beyond the board, we know there is not a series
    else { return false; }
  }
  return true;
}

/*
 * We check all the neighbors of the origin piece (x, y) for a series of num_pieces pieces.
 * Returns (0, 0) if there was no series found. If a series is found, it will return
 * a vector pointing in the direction of the series. E.g. if the series starts at
 * (0, 0) and continues horizontally to the right, the returned vector will be (0, 1)
 * (in this function, x is the row and y is the column, so right is +y and down is +x).
 *
 * Note: the origin piece is not included in the series (so when num_pieces = 2, we are searching
 * for 2 other pieces past that point).
 * Also, becuase we can't use struct's, I just return the vector (x, y) as the int value 10 * x + y
 * (this is okay because x and y are bounded between -1 and 1, and so we can deduce the original
 * x and y from this value).
 */
int check_neighbors(char board[6][7], char piece, int x, int y, int num_pieces) {
  int result = 0;
  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      // ignore the case where these are zero, since it will give a false positive
      if (dx == 0 && dy == 0) { continue; }

      int nx = x + dx, ny = y + dy;
      if (nx >= 0 && nx < 6 && ny >= 0 && ny < 7 && board[nx][ny] == piece) {
        if (check_direction(board, piece, x, y, nx, ny, num_pieces - 1)) {
          result = dx * 10 + dy;
        }
      }
    }
  }
  return result;
}

// Helpers for the board state
bool col_is_full(char board[6][7], char column) {
  int c = (islower(column)) ? column - 'a' : column - 'A';
  return board[0][c] != '.';
}

bool can_insert_at(char board[6][7], int row, int col) {
  return (row >= 0 && row < 6 && col >= 0 && col < 7) && 
    board[row][col] == '.' && (row == 5 || board[row + 1][col] != '.')
    && !col_is_full(board, 'A' + col);
}

bool board_is_full(char board[6][7]) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      if (board[i][j] == '.') { return false; }
    }
  }
  return true;
}

// This expects the column not to be full.
// if the column is full, the piece will not be inserted
void insert_at_col(char board[6][7], char moves[42], char column, char piece) {
  int c = (islower(column)) ? column - 'a' : column - 'A';
  for (int i = 5; i >= 0; i--) {
    if (board[i][c] == '.') { board[i][c] = piece; break; }
  }
  // update moves
  int i = 0; while (i != 42 && moves[i] != '.') { i++; }
  moves[i] = 'A' + c;
}

/*
 * This searches the entire board for a series of num_pieces pieces.
 * If the series is found, it will be continued by another piece and we return true.
 * If it is not found, or if the series cannot be continued, we return false.
 * Note: search_piece is the piece we are searching for, ai_piece is necessary since this can only
 * insert the ai's piece.
 */
bool insert_after_series(char board[6][7], char moves[42], char search_piece, char ai_piece, int num_pieces) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      if (board[i][j] == search_piece) {
        // if there is a line of num_pieces, finish the line with a final piece
        int result = check_neighbors(board, search_piece, i, j, num_pieces - 1);
        int dx, dy;
        switch (result) {
          case -11: dx = -1; dy = -1; break;
          case  -9: dx = -1; dy =  1; break;
          case   9: dx =  1; dy = -1; break;
          case  11: dx =  1; dy =  1; break;
          case -10: dx = -1; dy =  0; break;
          case  10: dx =  1; dy =  0; break;
          case   1: dx =  0; dy =  1; break;
          case  -1: dx =  0; dy = -1; break;
          default : dx =  0; dy =  0; break;
        }

        if (dx != 0 || dy != 0) {
          // coordinates for where the next piece in the series needs to be placed
          int nx = i + dx * num_pieces, ny = j + dy * num_pieces;
          // check if the piece can be placed in the appropriate spot
          if (can_insert_at(board, nx, ny)) {
            char col = 'A' + ny;
            insert_at_col(board, moves, col, ai_piece);
            return true;
          }
        }
      }
    }
  }
  return false;
}

// Will attempt to find and block this pattern:
// . . X X . . . (i.e. two adjacent pieces on the same row with empty spaces on either side).
// Where X is the player's piece. This guarantees a connect four so we need to deal with it early on
bool block_two_horizontal(char board[6][7], char moves[42], char ai_piece) {
  char player_piece = (ai_piece == 'X') ? 'O' : 'X';
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 3; col++) {
      if (board[row][col] == '.' && board[row][col + 3] == '.' &&
          board[row][col + 1] == player_piece && board[row][col + 2] == player_piece) {
        // place a piece at either side (we happen to choose the left side by default)
        if (can_insert_at(board, row, col)) {
          insert_at_col(board, moves, 'A' + col, ai_piece);
          return true;
        }  else if (can_insert_at(board, row, col + 3)) {
          insert_at_col(board, moves, 'A' + col + 3, ai_piece);
          return true;
        }
      }
    }
  }
  return false;
}

void draw_board(char board[6][7]) {
  // print top row
  printf(" ");
  for (char a = 'A'; a <= 'G'; a++) {
    printf(" %c", a);
  }

  // for each row, print the row number and afterward print the board values
  // as pieces or empty spaces
  for (int i = 0; i < 6; i++) {
    printf("\n%i ", 6 - i);
    for (int j = 0; j < 7; j++) {
      printf("%c ", board[i][j]);
    }
  }
  printf("\n");
}



/* 
 * returns 0 if the game is not over
 * returns 1 if the game was won by the player
 * returns -1 if the game was won by the ai
 * returns 2 if the game is a draw
 */
int check_game_state(char board[6][7], char player_piece, char ai_piece) {
  // What we'll do here is look at each column, bottom to top.
  // When we encounter a piece, we will look to the pieces around it and if there
  // are pieces of the same type, we contniue looking for more in that direction
  for (int col = 0; col < 7; col++) {
    for (int row = 0; row < 6; row++) {
      if (board[row][col] == '.') { continue; }

      int result;
      if (board[row][col] == player_piece) {
        result = check_neighbors(board, player_piece, row, col, 3);
        if (result != 0) { return 1; }
      } else if (board[row][col] == ai_piece) {
        result = check_neighbors(board, ai_piece, row, col, 3);
        if (result != 0) { return -1; }
      }
    }
  }

  if (board_is_full(board)) { return 2; }
  else { return 0; }
}

// This will be run every time the user makes a move
void prompt_player_turn(char board[6][7], char moves[42], char player_piece) {
  char col;
  printf("Player's turn!\n");
  draw_board(board);

  do {
    printf("Please enter the column you would like to place a piece in.\n> ");
    scanf(" %c", &col);
    int c = (islower(col)) ? col - 'a' : col - 'A';

    if (isalpha(col)) {
      if (c > 6 || c < 0) { printf("Invalid column. Try again.\n"); continue; }
      if (col_is_full(board, col)) { printf("Column is full. Pick another.\n"); continue; }
      // We only get here if all the other checks are passed
      break;
    } else {
      printf("Invalid input. Try again.\n");
    }
  } while (true);

  insert_at_col(board, moves, col, player_piece);
  printf("\n");
}

// This will be run every time the ai makes a move
void prompt_ai_turn(char board[6][7], char moves[42], char ai_piece) {
  printf("AI's turn!\n");
  draw_board(board);
  printf("\n");

  /* 
   * First we look for any possible connect-fours that the ai can make.
   * Then we look for possible connect-fours that the player can make.
   * If neither of these are the case, then we look for series of 2
   * pieces and try to continue them.
   * If this is not available, we place a piece in a random column.
   */

  char player_piece = (ai_piece == 'X') ? 'O' : 'X';
  // if we insert the piece, we just do nothing and let the function return
  if (insert_after_series(board, moves, ai_piece, ai_piece, 3)) { }
  else if (insert_after_series(board, moves, player_piece, ai_piece, 3)) { }
  // Now we're done looking for moves that we need to make, we can look for potential problems
  // and opportunities
  else if (block_two_horizontal(board, moves, ai_piece)) {  }
  else if (insert_after_series(board, moves, ai_piece, ai_piece, 2)) {  }
  else {
    char col = 'A' + (rand() % 7);
    insert_at_col(board, moves, col, ai_piece);
  }
}

// Returns the piece the player will be using ('X' or 'O')
char init_game(char board[6][7], char moves[42]) {
  // fill board with empty spaces ('.')
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      board[i][j] = '.';
      moves[7 * i + j] = '.';
    }
  }

  char response, player_piece;
  printf("Welcome to connect four!\nWould you like to go first? (Y or N)\n> ");
  // space before the %c clears all whitespace (including \n, for example)
  scanf(" %c", &response);

  if (response == 'Y' || response == 'y') {
    player_piece = 'X';
    prompt_player_turn(board, moves, player_piece);
  } else if (response == 'N' || response == 'n') {
    // do nothing
    player_piece = 'O';
  } else {
    printf("Invalid response. Defaulting to player first.\n");
    player_piece = 'X';
    prompt_player_turn(board, moves, player_piece);
  }

  return player_piece;
}

// We put this in a separate function instead of main so that we can recursively call it
// should the user decides to play again.
void game_loop(char board[6][7], char moves[42]) {
  char player_piece = init_game(board, moves);
  char ai_piece = (player_piece == 'X') ? 'O' : 'X';

  // main loop
  while (check_game_state(board, player_piece, ai_piece) == 0) {
    prompt_ai_turn(board, moves, ai_piece);
    if (check_game_state(board, player_piece, ai_piece) != 0) { break; }
    prompt_player_turn(board, moves, player_piece);
  }

  // Draw the board one last time
  draw_board(board);
  int result = check_game_state(board, player_piece, ai_piece);
  if (result == 1) {
    printf("You win!\n");
  } else if (result == -1) {
    printf("You lose!\n");
  } else if (result == 2) {
    printf("Draw!\n");
  }
  int i = 0; while (i != 42 && moves[i] != '.') { i++; } moves[i] = '\0';
  printf("Moves: \"%s\"\n", moves);

  char response;
  printf("Would you like to play again? (Y or N)\n> ");
  scanf(" %c", &response);

  if (response == 'y' || response == 'Y') {
    printf("\n\n");
    game_loop(board, moves);
  } else {
    printf("Thanks for playing!\n");
  }
}


int main() {
  char board[6][7];
  char moves[42];

  srand(time(NULL));
  game_loop(board, moves);
  return 0;
}
