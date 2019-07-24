#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256
int main(void) {
  char buffer[BUF_SIZE];
  int sum = 0;
  int ret_val = -1;

  while (ret_val != 0) {
    ret_val = read(STDIN_FILENO, buffer, BUF_SIZE);
    if (ret_val == -1) { write(STDERR_FILENO, "Error reading from stdin.\n", 26); }
    else { sum += ret_val; }
  }
}
