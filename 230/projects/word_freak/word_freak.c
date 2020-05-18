/*
 * Kevin Vicente
 * March 6, 2019
 *
 * This is a program that takes in filenames as input and outputs a table of words that are read
 * from them and their frequencies.
 */

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "table.h"

// 5 Kibibytes plues one extra byte
#define BUF_SIZE 1024 * 5 + 1



unsigned chars_in_longest_word = 0;

unsigned num_digits(unsigned num);
void num_to_string(unsigned num, char* buffer);
void to_lower(char* word, unsigned length);
void word_count(Table* table, char* string, unsigned length);
void print_formatted_table(Table table);


int main(int argc, char* argv[]) {
  unsigned num_files;
  char** filenames;
  char* env_files = getenv("WORD_FREAK");
  char* file_contents = (char*) malloc(BUF_SIZE - 1);
  if (file_contents == NULL) { write(STDERR_FILENO, "Memory allocation error.\n", 25); return 1; }

  Table table = NULL;
  bool eof;
  ssize_t retval;
  int fd = -1, std_in = STDIN_FILENO;


  // Determine how we will receive our input by assigning filenames to null, argv or env
  if (argc <= 1) {
    if (env_files == NULL) { filenames = NULL; }
    else { filenames = &env_files; }
    num_files = 1;
  } else {
    filenames = argv + 1;
    num_files = argc - 1;
  }

  // Iterate through all the files (if appropriate) and read from the file descriptors
  for (unsigned i = 0; i < num_files; i++) {
    if (filenames == NULL) { fd = STDIN_FILENO; }
    else { fd = open(filenames[i], O_RDONLY); }
    if (fd == -1) {
      write(STDERR_FILENO, "Error opening file.\n", 20);
      free(file_contents);
      return 1;
    }

    eof = false;
    bool read_partial_word = false;
    char* partial_word = NULL;
    unsigned offset = 0;

    while (!eof) {
      // prepend the cut-off word to the buffer
      if (read_partial_word) {
        strcpy(file_contents, partial_word);
        free(partial_word); partial_word = NULL;
        read_partial_word = false;
      }

      retval = read(fd, &file_contents[offset], BUF_SIZE - offset - 1);
      if (retval == -1) {
        write(STDERR_FILENO, "Error reading file.\n", 20);
        free(file_contents);
        return 1;
      }
      eof = retval < BUF_SIZE - 1;

      // We copy the last (alphanumeric) characters from the buffer into another one in case it is
      // a cut-off word, and prepend it to the next iteration's buffer
      unsigned j = retval - 1;
      while (ispunct(file_contents[j]) || isalnum(file_contents[j])) { j -= 1; }
      file_contents[j + 1] = '\0';

      if (!eof && j != retval - 1) {
        read_partial_word = true;
        partial_word = (char*) malloc(retval - j);
        if (partial_word == NULL) {
          write(STDERR_FILENO, "Memory allocation error.\n", 25);
          free(file_contents);
          return 1;
        }
        strncpy(partial_word, &file_contents[j], retval - j - 1);
        partial_word[retval - j - 1] = '\0';
        offset = retval - j - 1;
      } else { offset = 0; }

      word_count(&table, file_contents, j + 1);
    }
  }

  free(file_contents);
  print_formatted_table(table);
  destroy_table(table);
  return 0;
}

// Transforms all uppercase letters to lowercase in place
void to_lower(char* word, unsigned length) {
  unsigned ascii_difference = 'a' - 'A';
  for (unsigned i = 0; i < length; i++) { 
    if (isupper(word[i])) { word[i] += ascii_difference; }
  }
}

unsigned num_digits(unsigned num) { return (unsigned) floor(log10((double) num)) + 1; }

// Only works for nonnegative integers in base 10
void num_to_string(unsigned num, char* buffer) {
  if (num == 0) { buffer = "0"; return; }

  // start at the one's place
  unsigned place = 1, index = num_digits(num);
  buffer[index] = '\0'; index -= 1;

  while (place <= num) {
    // This will be the digit in the place's place (e.g. in 123, if place is 10, digit will be 2)
    unsigned digit = (num % (place * 10) - num % place) / place;
    buffer[index] = '0' + digit;
    index -= 1; place *= 10;
  }
}


// This is the function that reads words from a string and updates their counts in the table
void word_count(Table* table, char* string, unsigned length) {
  unsigned num_chars_read = 0;
  bool prev_whitespace = false;

  for (unsigned i = 0; i < length; i++) {
    // count all punctuation and whitespace (other than "'" or "-") as word seperators
    if (ispunct(string[i]) && string[i] != '\'' && string[i] != '-'
        || isspace(string[i]) || string[i] == '\0') {
      if (i != 0 && !prev_whitespace) {
        if (num_chars_read > chars_in_longest_word) { chars_in_longest_word = num_chars_read; }
        to_lower(&string[i - num_chars_read], num_chars_read);
        update_entry(table, &string[i - num_chars_read], num_chars_read);
        num_chars_read = 0;
      }
      if (string[i] == '\0') { break; }
      if (!prev_whitespace) { prev_whitespace = true; }
    } else {
      num_chars_read += 1;
      if (prev_whitespace) { prev_whitespace = false; }
    }
  }
}


void print_formatted_table(Table table) {
  if (table == NULL) { return; }
  struct Entry* ptr = table;
  // number of digits in the first entry (since it is the largest in the list)
  const unsigned greatest_freq_digits = num_digits(ptr->count);
  const unsigned buffer_length = 4 + chars_in_longest_word + greatest_freq_digits;
  unsigned word_padding, num_padding;
  char output_buffer[buffer_length];
  char num_buffer[greatest_freq_digits + 1];

  while (ptr != NULL) {
    word_padding = chars_in_longest_word - ptr->length + 1;
    num_padding = greatest_freq_digits - num_digits(ptr->count);
    num_to_string(ptr->count, num_buffer);

    // We've calculated the padding size, now we fill in the buffer
    strcpy(output_buffer, ptr->word);                           // copy word into buffer
    memset(&output_buffer[ptr->length - 1], ' ', word_padding); // add spaces for padding
    strcpy(&output_buffer[chars_in_longest_word], " : ");       // write colon
    strcat(output_buffer, num_buffer);                          // copy number into buffer
    memset(&output_buffer[buffer_length - num_padding - 1], ' ', num_padding); // add spaces
    output_buffer[buffer_length - 1] = '\n';                    // add new line

    int err = write(STDOUT_FILENO, output_buffer, buffer_length);
    if (err == -1) { write(STDERR_FILENO, "Error writing to stdout.\n", 25); break; }
    ptr = ptr->next;
  }
}
