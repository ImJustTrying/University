#include <stdio.h>

#define BUF_SIZE 2048

void print_lines(char buffer[BUF_SIZE], FILE* file) {
  int i = 0, lines = 0;
  do {
    buffer[i] = fgetc(file);
    if (buffer[i] == '\n') { lines += 1; }
    i += 1;
  } while (i < BUF_SIZE && !feof(file) && lines != 20);

  if (i == BUF_SIZE) { buffer[i - 1] = '\0'; }
  else { buffer[i] = '\0'; }

  printf("\n%s\n", buffer);
}

int main(void) {
  char filename[256];
  char buffer[BUF_SIZE];

  printf("Please enter a filename\n> ");
  scanf("%255s", filename);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file \"%s\"\n", filename);
    return 1;
  }

  printf("File contents:\n");
  char input;
  do {
    print_lines(buffer, file);
    if (feof(file)) { break; }

    printf("Continue? (q to quit)\n> ");
    scanf(" %c", &input);
    if (input == 'q') { break; }
  } while (!feof(file));

  fclose(file);
  return 0;
}
