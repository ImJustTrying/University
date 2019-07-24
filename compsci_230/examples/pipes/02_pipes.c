#include <stdio.h>
#include <stdlib.h>

void popen_read_example() {
  printf("*** popen_read_example() BEGIN ***\n");
  FILE *stream = popen("ls", "r");

  if (stream == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  while ((nread = getline(&line, &len, stream)) != -1) {
    printf("Retrieved line of length %zu:\n", nread);
    printf("%s", line);
  }
}

void popen_write_example() {
  printf("*** popen_write_example() BEGIN ***\n");
  FILE* stream = popen("wc", "w");

  if (stream == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }

  fprintf(stream, "So, how many newline, word, and byte counts do we have?");
  printf("\n");
}

int main() {
  popen_read_example();
  popen_write_example();
  return 0;
}
