#include "kernel/types.h"
#include "user.h"

void main() {
  char buf1[4] = "ping";
  char buf2[4] = "pong";
  int P1[2];
  int P2[2];
  pipe(P1);
  pipe(P2);
  int ret = fork();
  if (ret == 0) {
    int pidChild = getpid();

    close(P1[1]);
    read(P1[0], buf1, 4);
    printf("%d: received ping\n", pidChild);
    close(P1[0]);

    close(P2[0]);
    write(P2[1], buf2, 4);
    close(P2[1]);

    exit(0);

  } else if (ret > 0) {
    int pidFather = getpid();

    close(P1[0]);
    write(P1[1], buf1, 4);
    close(P1[1]);

    close(P2[1]);
    read(P2[0], buf1, 4);
    printf("%d: received pong\n", pidFather);
    close(P2[0]);

    exit(0);
  }
}