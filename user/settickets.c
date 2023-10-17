#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  if(argc != 2){
    printf(2, "Invalid Usage: settickets...\n");
    exit();
  }
  settickets( (int) argv[1]);
  exit();
}
