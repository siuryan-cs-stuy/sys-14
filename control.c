#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

#define KEY 35

int main( int argc, char *argv[] ) {
  int sd;

  if (argc >= 3) {
    if (strcmp(argv[1], "-c") == 0) {
      sd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0664);

      if (sd == -1) {
        printf("semaphore already exists\n");
        return 0;
      }

      semctl(sd, 0, SETVAL, atoi(argv[2]));
      printf("semaphore created: %d\n", sd);
      printf("semaphore value: %d\n", atoi(argv[2]));
    }
  }

  else if (strcmp(argv[1], "-v") == 0) {
    sd = semget(KEY, 1, 0664);
    printf("semaphore gotten: %d\n", sd);
    int sem_val = semctl(sd, 0, GETVAL);
    printf("semaphore value: %d\n", sem_val);
  }

  else if (strcmp(argv[1], "-r") == 0) {
    sd = semget(KEY, 1, 0664);
    int val = semctl(sd, 0, IPC_RMID);
    printf("semaphore removed: %d\n", val);
  }

  else {
    printf("incorrect arguments\n");
  }

  return 0;
}
