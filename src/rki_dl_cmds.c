#include <stdio.h>
#include <string.h>
#include "rki_config.h"

#ifdef RKI_INCLUDE_DL_CMDS

#include <rtems/shell.h>
#include <rtems/rtl/dlfcn-shell.h>
#include <dlfcn.h>
#include <rtems/rtl/rap-shell.h>
#include <rtems/rtl/rtl-shell.h>

#define TASK_ATTRIBUTES RTEMS_FLOATING_POINT

typedef void (*call_t)(void);

rtems_task LaunchCfs(
  rtems_task_argument unused
)
{
   void*  handle;
   call_t call;
   int    call_ret;
   int    unresolved;
   char*  message = "loaded";

   handle = dlopen ("/nonvol/core-cpu1.exe", RTLD_NOW | RTLD_GLOBAL);
   if (!handle)
   {
     printf("dlopen failed: %s\n", dlerror());
     rtems_task_delete( RTEMS_SELF );    /* should not return */
   }

   if (dlinfo (handle, RTLD_DI_UNRESOLVED, &unresolved) < 0)
   {
     message = "dlinfo error checking unresolved status";
   }
   else if (unresolved)
   {
     message = "has unresolved externals";
   }
   printf ("handle: %p %s\n", handle, message);

   call = dlsym (handle, "OS_BSPMain");
   if (call == NULL)
   {
     printf("dlsym failed: symbol OS_BSPMain not found\n");
     rtems_task_delete( RTEMS_SELF );    /* should not return */
   }
   else
   {
      printf("dlsym OK: symbol OS_BSPMain found\n");
   }

#if 1
   call ();
#endif

   printf( "*** CFS TASK FINISHED ***\n");
   rtems_task_delete( RTEMS_SELF );    /* should not return */
}

/*
** Dynamic load command 
*/
int dl_load_and_start_cfe( int argc, char *argv[])
{
   rtems_id          task_id;
   rtems_name        task_name;
   rtems_status_code status;

   task_name = rtems_build_name( 'c', 'F', 'S', ' ' );

   status = rtems_task_create(
    task_name, 100, RTEMS_MINIMUM_STACK_SIZE * 4, RTEMS_DEFAULT_MODES,
    TASK_ATTRIBUTES, &task_id
   );
   if ( status != RTEMS_SUCCESSFUL )
   {
      printf("Error creating cFS Task\n");
   }

   status = rtems_task_start( task_id, LaunchCfs, 0 );
   if ( status != RTEMS_SUCCESSFUL )
   {
      printf("Error Starting cFS Task\n");
   }
   return(status);
}

/*
** Add the DL commands to the shell
*/
void rki_add_dl_commands(void)
{
   rtems_shell_add_cmd("dlopen","misc","dynamic loader dlopen",shell_dlopen);
   rtems_shell_add_cmd("dlclose","misc","dynamic loader dlclose",shell_dlclose);
   rtems_shell_add_cmd("dlsym","misc","dynamic loader dlsym",shell_dlsym);
   rtems_shell_add_cmd("dlcall","misc","dynamic loader dlcall",shell_dlcall);

   rtems_shell_add_cmd("rap","misc","dynamic loader rap command",shell_rap);

   rtems_shell_add_cmd("rtl","misc","dynamic loader rtl command",rtems_rtl_shell_command);

   rtems_shell_add_cmd("startcfedl","misc","Load and start the cFE Core",dl_load_and_start_cfe);
   
}
#else
/*
** no DL commands 
*/
void rki_add_dl_commands(void)
{
   return;
}
#endif
