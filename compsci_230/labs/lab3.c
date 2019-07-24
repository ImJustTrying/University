/*
 * Kevin Viccente
 * March 2019
 *
 * This is a file that takes filenames as input from the command prompt and prints out their 
 * contents.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

// 1 Kibibyte
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
  if (argc <= 1) { write(STDERR_FILENO, "No arguments provided.\n", 23); return 0; }
  char buffer[BUFFER_SIZE + 1];

  int file = open(argv[1], O_RDONLY);
  if (file == -1) {
    write(STDERR_FILENO, "Error opening file.\n", 20);
    printf("Received error number: %i\n", errno);
    return 1;
  }

  size_t retval;
  do {
    retval = read(file, buffer, BUFFER_SIZE);
    if (retval == -1) { write(STDERR_FILENO, "Error reading file.\n", 20); return 1; }
    // Use retval in case the number of characters read is less than BUFFER_SIZE
    buffer[retval + 1] = '\0';
    printf("%s", buffer);
  } while (retval == BUFFER_SIZE);

  if (close(file) == -1) { write(STDERR_FILENO, "Error closing file.\n", 20); return 1; }
  return 0;
}
