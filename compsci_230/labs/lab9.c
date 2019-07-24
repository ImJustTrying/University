#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int child_task(int read_pipe, int num_messages) {
  char msg_buf[256];
  int nr;

  for (int i = 0; i < num_messages; i++) {
    if ((nr = read(read_pipe, msg_buf, 256)) == -1) {
      perror("child failed to read from pipe");
      return 1;
    }

    printf("message received: %s\n", msg_buf);
    printf("bytes: %d\n", nr);
  }

  return 0;
}

int parent_task(int write_pipe, char* messages[], int length) {
  int nw;

  for (int i = 0; i < length; i++) {
    if ((nw = write(write_pipe, messages[i], strlen(messages[i]) + 1)) == -1) {
      perror("parent failed to write to pipe");
      return 1;
    }

    printf("message sent: %s\n", messages[i]);
    printf("bytes written: %d\n", nw);
  }

  return 0;
}

int main() {
  int parent_to_child_pipe[2];
  int num_messages = 2;

  // Create the pipe
  if (pipe(parent_to_child_pipe) == -1) {
    perror("could not create pipe");
    exit(1);
  }

  printf("0: %d, 1: %d\n", parent_to_child_pipe[0], parent_to_child_pipe[1]);
  pid_t pid;
  if ((pid = fork()) == 0) {
    // Child process...
    // First we close the write end of the pipe.
    close(parent_to_child_pipe[1]);
    child_task(parent_to_child_pipe[0], num_messages);
  } else {
    // Parent process...
    // First, we close the read end of the pipe.
    close(parent_to_child_pipe[0]);
    char* messages[] = { "Thank you for the money!", "Wish you were here in Paris with me." };
    int res = parent_task(parent_to_child_pipe[1], messages, num_messages);
    if (res == 1) { printf("Error occurred!\n"); }

    // Wait on child process to complete
    wait(NULL);
    printf("parent process completing.\n");
  }
}
