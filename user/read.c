#include "types.h"
#include "user.h"
#include "x86.h"

int
main(int argc, char *argv[])
{
  char buf;;
  int fd = open("README", 0);
  int rc1 = getreadcount();
  read(fd, &buf, 1);
  int rc2 = getreadcount();
  close(fd);
  printf(1,"read successfull, rc: before - %d, after -  %d \n", rc1, rc2);
  exit();
}
