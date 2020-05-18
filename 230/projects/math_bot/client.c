/*
 * Kevin Vicente
 * April 2019
 *
 * This is an implementation of a "math bot" -- a client program that will connect to a server,
 * receive an arithmetic problem and respond with the solution. It continues to do this until the
 * server replies with a response containing a hash value and the literal "BYE".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 100

void itoa(const int i, char* string) {
  int num_digits = 1;
  {
    int place = 10;
    while (i % place != i) { num_digits += 1; place *= 10; }
  }

  int place = 10, index = num_digits - 1;
  index += (i < 0) ? 1 : 0;

  while (index >= 0) {
    if (index == 0 && i < 0) { string[index--] = '-'; break; }
    int digit = (i % place - (i % (place / 10))) / (place / 10);
    digit = (digit < 0) ? -digit : digit;
    string[index--] = digit + '0';
    place *= 10;
  }

  if (i < 0) { string[num_digits + 1] = '\0'; }
  else { string[num_digits] = '\0'; }
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("arg = %d\nUsage: ./%s ID port address\n", argc, argv[0]);
    return 0;
  }

  unsigned short port = atoi(argv[2]);
  /*
   * struct sockaddr_in {
   *   short          sin_family;  // address family -- AF_INET for internet programs
   *   unsigned short sin_port;    // port number in network byte order (NBO)
   *   struct in_addr sin_addr;    // ip address in NBO
   *   unsigned char  sin_zero[8]; // not relevant -- ignore
   * };
   */

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(argv[3]);
  address.sin_port = htons(port);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) { fprintf(stderr, "Error creating socket\n"); }

  if (connect(sock, (struct sockaddr*) &address, sizeof(address)) == -1) {
    perror("Error connecting to server");
  }

  // Initially, send the greeting string
  const char prefix[] = "cs230 ";
  char client_response[BUFFER_SIZE] = "cs230 ";
  char server_response[BUFFER_SIZE];
  int length;
  {
    char* temp = "HELLO ";
    strcat(client_response, temp);
  }
  strcat(client_response, argv[1]);
  strcat(client_response, "\n");

  if (send(sock, client_response, strlen(client_response), 0) == -1) {
    perror("Error sending response");
    close(sock); return 1;
  }

  // main loop
  while (1) {
    length = recv(sock, server_response, BUFFER_SIZE, 0);
    if (length == -1) {
      perror("Error receiving response");
      close(sock); return 1;
    } else if (length >= BUFFER_SIZE) {
      server_response[length - 1] = '\0';
    } else {
      server_response[length] = '\0';
    }
    // printf("server response: %s", server_response);

    // Initially read and ignore the "cs230" and "STATUS" prefix
    strtok(server_response, " ");
    const char* response_type = strtok(NULL, " ");
    const char* operand1_str = strtok(NULL, " ");
    if (strcmp(operand1_str, "BYE\n") == 0) {
      printf("%s\n", response_type);
      break;
    }

    int operand1 = atoi(operand1_str);
    const char operator = *(strtok(NULL, " "));
    int operand2 = atoi(strtok(NULL, " "));
    char num_buffer[15];
    int result;

    switch(operator) {
      case '+': result = operand1 + operand2; break;
      case '-': result = operand1 - operand2; break;
      case '*': result = operand1 * operand2; break;
      case '/': result = operand1 / operand2; break;
      default: printf("unknown operation \"%c\" (%d)\n", operator, (int) operator);
    }
    // printf("%d %c %d = %d\n", operand1, operator, operand2, result);

    strcpy(client_response, prefix);
    itoa(result, num_buffer);
    strcat(client_response, num_buffer);
    strcat(client_response, "\n");
    // printf("client response: %s", client_response);

    if (send(sock, client_response, strlen(client_response), 0) == -1) {
      perror("Error sending response");
      close(sock); return 1;
    }
  }

  if (close(sock) == -1) { fprintf(stderr, "Error closing socket\n"); }
  return 0;
}
