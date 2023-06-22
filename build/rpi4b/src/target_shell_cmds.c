/*
** RTEMS Kernel Image Target command setup 
**
*/
#include "rki_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <bsp.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#include <rtems/shell.h>
#include <rtems/bdbuf.h>
#include <rtems/error.h>

/*
** External functions
*/
int fb_command( int argc, char *argv[]);
/*
** function to start the shell and add new commands.
*/
void rki_add_target_cmds(void)
{
   printf("Adding Target specific commands\n");
   rtems_shell_add_cmd("fb","misc","RPI4b Framebuffer test",fb_command);
}
