/*
 * Kevin Vicente
 * April 2019
 *
 * This program will simulate a ticketing system. In our system, there will be three operators and
 * any number of phone calls sent to these operators. Our goal is to give out tickets to all the
 * phone calls until we run out. The phone calls are represented by threads (excluding the main)
 * and operators are represented by a counting semaphore.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_OPERATORS 3
#define NUM_LINES 5
#define NUM_TICKETS 240

// Declare these as global since there is no consistent way to initialize and destroy these in the
// thread procedure
sem_t connect_lock;
sem_t operator_lock;
sem_t id_lock;
sem_t ticket_lock;
unsigned tickets_given = 0;
unsigned next_id = 0;

void* phone_call(void* args);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Invalid number of arguments\n");
    printf("Usage: ./jimmy_fallon num_callers\n");
    return 0;
  }

  const unsigned NUM_THREADS = (unsigned) atoi(argv[1]);
  pthread_t threads[NUM_THREADS];

  // Initialize semaphores before the threads are created
  sem_init(&connect_lock, 0, 1);
  sem_init(&id_lock, 0, 1);
  sem_init(&ticket_lock, 0, 1);
  sem_init(&operator_lock, 0, NUM_OPERATORS);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, phone_call, (void*) &next_id);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // Destroy semaphores after all threads are joined
  sem_destroy(&connect_lock);
  sem_destroy(&id_lock);
  sem_destroy(&ticket_lock);
  sem_destroy(&operator_lock);

  printf("Sold %u tickets!\n", tickets_given);
  return 0;
}

void* phone_call(void* args) {
  static unsigned connected = 0;
  unsigned id = *((unsigned*) args);  

  // Update next_id
  sem_wait(&id_lock);
  *((unsigned*) args) += 1;
  sem_post(&id_lock);

  if (tickets_given >= NUM_TICKETS) {
    printf("Caller [%u] is denied line, tickets sold out\n", id);
    return NULL;
  }

  if (connected >= NUM_LINES) { printf("Caller [%u] is calling line, busy signal\n", id); }
  // Wait for a connection
  while (connected >= NUM_LINES) { sleep(1); }

  sem_wait(&connect_lock);
  connected += 1;
  sem_post(&connect_lock);
  printf("Caller [%u] has available line, waiting for pick up\n", id);

  sem_wait(&operator_lock);
  printf("Caller [%u] is speaking to an operator\n", id);
  sleep(1);
  if (tickets_given >= NUM_TICKETS) {
    printf("Caller [%u] is denied, tickets sold out\n", id);
    sem_post(&operator_lock);
    return NULL;
  }
  sem_post(&operator_lock);
  printf("Caller [%u] has bought a ticket\n", id);

  sem_wait(&connect_lock);
  connected -= 1;
  sem_post(&connect_lock);
  printf("Caller [%u] has hung up\n", id);

  sem_wait(&ticket_lock);
  tickets_given += 1;
  sem_post(&ticket_lock);
  return NULL;
}
