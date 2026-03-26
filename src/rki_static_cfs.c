#include <stdio.h>
#include <string.h>
#include <bsp.h>
#include "rki_config.h"

#define TASK_ATTRIBUTES RTEMS_FLOATING_POINT

#ifdef RKI_INCLUDE_STATIC_CFS

/* Entry point to the cFS */
int OS_BSPMain(void);

/*
** Start the cFS by calling the entry point
*/
rtems_task StartStaticCfs(
  rtems_task_argument unused
)
{
  int return_code = 0;

  printf( "*** Starting cFS **** \n");
  return_code = OS_BSPMain();
  printf( "*** CFS TASK FINISHED with RC = %d***\n", return_code);
  rtems_task_delete( RTEMS_SELF );    /* should not return */
}

/*
** RTEMS shell command to start the cFS that is linked into the RKI 
*/
int rki_start_cfs_command(int argc, char *argv[])
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

  status = rtems_task_start( task_id, StartStaticCfs, 0 );
  if ( status != RTEMS_SUCCESSFUL )
  {
     printf("Error Starting cFS Task\n");
  }

   return(status);
}
#endif
