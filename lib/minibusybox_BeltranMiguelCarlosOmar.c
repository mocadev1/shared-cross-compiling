#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <math.h>         // numbers ceiling for "template strings" allocation

#include <limits.h>       // sleep command
#include <sys/utsname.h>  // uname command
#include <sys/stat.h>     // mkdir command
#include <sys/sysinfo.h>  // uptime command


const long int SECONDS_IN_DAY = 86400;
const long int SECONDS_IN_HOUR = 3600;

enum AVAILABLE_COMMANDS
{
  SLEEP,
  UNAME,
  MKDIR,
  UPTIME,
  RM,
};

typedef struct available_commands
{
  char *command_name;
  enum AVAILABLE_COMMANDS id;
  int required_arguments;
  int upto_arguments;
} available_commands;

available_commands commands_list[] = {
    {"sleep", SLEEP, 1,1},
    {"uname", UNAME, 0,0},
    {"my_mkdir", MKDIR, 1,2},
    {"uptime", UPTIME, 0, 0},
    {"rm", RM, 1, 2},
};

typedef struct desired_command
{
  char *name;
  char **args;
  int main_arglistc;
} desired_command;

// Linear search in available commands
available_commands *getAvailableCommand(char *program)
{
  for (int i = 0; i < sizeof commands_list / sizeof(available_commands); i++)
  {
    if (strcmp(program, commands_list[i].command_name) == 0)
    {
      return commands_list + i;
    }
  }
  return NULL;
}

int validate_argc(available_commands *available_command, int desired_command_argc)
{
  return 
    (desired_command_argc == available_command->required_arguments) || 
    (desired_command_argc <= available_command->upto_arguments)
    ? 1
    : 0;
}

char *get_argc_message(available_commands *available_command)
{
  /*
    getting how much lenght will the required (i.e. 32) arguments will take to print into the string   
  */
  int required_arg_lenght = snprintf( NULL, 0, "%d", available_command->required_arguments);
  char required_arg_str[required_arg_lenght];
  sprintf(required_arg_str, "%d", available_command->required_arguments);

  int upto_arg_lenght = snprintf( NULL, 0, "%d", available_command->upto_arguments);
  char upto_arg_str[upto_arg_lenght];
  sprintf(upto_arg_str, "%d", available_command->upto_arguments);

  char *requires_str = " command requires ";
  char *accepts_str = " and accepts up to ";
  char *args_str = " args.";

  char *message = malloc(sizeof(char) * 
    (
      strlen( available_command->command_name ) +
      strlen(requires_str)                      +
      required_arg_lenght                       +
      strlen(accepts_str)                       + 
      upto_arg_lenght                           +
      strlen(args_str)                          +
      + 1 // zero-terminating string additional
    ));
  
  strcpy(message, available_command->command_name);
  strcat(message, requires_str);
  strcat(message, required_arg_str);
  if(available_command->required_arguments != available_command->upto_arguments)
  {
    strcat(message, accepts_str);
    strcat(message, upto_arg_str);
  }
  strcat(message, args_str);

  return message;
}

int sleep_command(char *arg_list[])
{
  char *endPtr;
  long time_to_sleep = strtol(arg_list[0], &endPtr, 10);
  if (
      time_to_sleep == LONG_MIN ||
      time_to_sleep == LONG_MAX ||
      time_to_sleep == 0)
  {
    printf("invalid time interval '%s'\n", arg_list[0]);
    exit(1);
  }
  return sleep(time_to_sleep);
}

int uname_command(char *arg_list[])
{
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

int mkdir_command(char *arg_list[])
{
  char *path = arg_list[0];
  int mode = 0777;
  // if (arg_list[1])
  // {
  //   mode = strtol(arg_list[1], NULL, 10); // TODO: check that strtol returns a valid long int
  // }
  return mkdir(path, mode);
}

int uptime_command(char *arg_list[])
{
  struct sysinfo info;
  
  int return_value = sysinfo(&info);

  if(return_value == -1)
  {
    perror("sysinfo failed");
    return return_value;
  }


  printf("up %ld days %02ld:%02ld:%02ld\n",
   info.uptime / SECONDS_IN_DAY,                      // days
   (info.uptime % SECONDS_IN_DAY) / SECONDS_IN_HOUR,  // hours, the mod operation is to "remove" the days (in seconds) from the uptime 
   (info.uptime % SECONDS_IN_HOUR) / 60,              // minutes, same as above but for hours
   (info.uptime % 60)                                 // seconds
   );
  return return_value;
}

int call_command_with(enum AVAILABLE_COMMANDS cmd_id, char *arg_list[])
{
  switch (cmd_id)
  {
  case SLEEP:
    return sleep_command(arg_list);

  case UNAME:
    return uname_command(arg_list);

  case MKDIR:
    return mkdir_command(arg_list);

  case UPTIME:
    return uptime_command(arg_list);

  default:
    break;
  }
  return 1;
}

int spawn(desired_command desired_command)
{
  char *command = desired_command.name;

  available_commands *available_command = NULL;
  available_command = getAvailableCommand(command); // get valid command from commands_list

  if (!available_command)
  {
    printf("Unknown command\n");
    exit(1);
  }

  int is_valid_argc = validate_argc(
      available_command,
      desired_command.main_arglistc);
  if (!is_valid_argc) 
  {
    char *message = get_argc_message(available_command);
    printf("%s\n", message);
    free(message);
    exit(1);
  }

  enum AVAILABLE_COMMANDS cmd_id;
  cmd_id = available_command->id;

  return call_command_with(cmd_id, desired_command.args);
}

int main(int argc, char *argv[])
{
  struct desired_command desired_command;
  desired_command.name = argv[0];
  desired_command.args = &argv[1]; // Passing all args except by the first arg that its the command itself.

  /* ----- IMPORTANT --------
    substracting one to the `argc` count just to facilitate the args[i]
    usage in specific "commands" (functions) to be read as i.e. arg_list[0]
  */
  desired_command.main_arglistc = argc - 1; 

  spawn(desired_command);
  return 0;
}

