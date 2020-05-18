#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int child_task(int read_pipe, int write_pipe) {
  char read_msg[25];
  char write_msg[] = "hello from child.";
  int nr, nw;

  if ((nr = read(read_pipe, read_msg, 25)) == -1) {
    perror("child failed to read from pipe");
    return 1;
  }

  printf("child received message from parent.\n");
  printf("message received: %s\n", read_msg);
  printf("bytes read: %d\n", nr);

  // Now we send a message back to the parent
  if ((nw = write(write_pipe, write_msg, strlen(write_msg) + 1)) == -1) {
    perror("child failed to write to pipe");
    return 1;
  }

  printf("child sent message to parent.\n");
  printf("message sent: %s\n", write_msg);
  printf("bytes written: %d\n", nw);
  return 0;
}

int parent_task(int read_pipe, int write_pipe) {
  char read_msg[25];
  char write_msg[] = "hello from parent.";
  int nw, nr;

  if ((nw = write(write_pipe, write_msg, strlen(write_msg) + 1)) == -1) {
    perror("parent failed to write to pipe");
    exit(1);
  }

  printf("parent sent message to child.\n");
  printf("message sent: %s\n", write_msg);
  printf("bytes written: %d\n", nw);

  if ((nr = read(read_pipe, read_msg, 25)) == -1) {
    perror("child failed to read from pipe");
    return 1;
  }

  printf("parent received message from child.\n");
  printf("message received: %s\n", read_msg);
  printf("bytes read: %d\n", nr);

  return 0;
}

int main() {
  int parent_to_child_pipe[2];

  // Create the pipe
  if (pipe(parent_to_child_pipe) == -1) {
    perror("could not create pipe");
    exit(1);
  }

  pid_t pid;
  if ((pid = fork()) == 0) {
    // Child process...
    exit(child_task(parent_to_child_pipe[0], parent_to_child_pipe[1]));
  } else {
    // Parent process...
    exit(parent_task(parent_to_child_pipe[0], parent_to_child_pipe[1]));

    // Wait on child process to complete
    wait(NULL);
    printf("parent process completing.\n");
  }
}
