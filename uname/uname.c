#include <stdio.h>
#include <sys/utsname.h>  // uname command

int uname_command(int argc, char *argv[]) {
  struct utsname uname_struct;
  int return_value = uname(&uname_struct);

  if(return_value == -1)
    return return_value;

  printf("Kernel name: %s\n", uname_struct.sysname);
  printf("Kernel release: %s\n", uname_struct.release);
  printf("Kernel version: %s\n", uname_struct.version);
  printf("Processor architecture: %s\n", uname_struct.machine);
  return return_value;
}