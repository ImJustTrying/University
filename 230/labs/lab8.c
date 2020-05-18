/*
 * Kevin Vicente
 * March 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread(void* args);

int main(void) {
  pthread_t tid1, tid2;

  printf("Hello from the main thread.\n");
  printf("Creating thread 1.\n");
  pthread_create(&tid1, NULL, thread, NULL);
  printf("Creating thread 2.\n");
  pthread_create(&tid2, NULL, thread, NULL);

  printf("Main thread will wait for peer threads.\n");
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  printf("Peer threads have terminated.\n");
  return EXIT_SUCCESS;
}

void* thread(void* args) {
  printf("Hello from thread %u!\n", (unsigned) pthread_self());
  return NULL;
}
