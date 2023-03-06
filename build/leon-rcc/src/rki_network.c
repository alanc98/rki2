/****************************************************************
**  rtems_net.c
**
**  Author:  Alan Cudmore
**
**  This module is responsible for RTEMS specific network initialization.
**
*/

#include "rki_config.h"

/*
** If the Network subsystem is not selected, just ifdef the whole thing out
*/
#ifdef RKI_INCLUDE_NETWORK

/*
** This is not defined in RTEMS 5.x
*/
#define MCLBYTES 2048

#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#include <rtems/rtems_bsdnet.h>
#include <sys/domain.h>
#include <sys/mbuf.h>
#include <sys/socketvar.h>
#include <sys/socket.h>
#include <sys/sockio.h>
#include <sys/callout.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
#include <vm/vm.h>
#include <arpa/inet.h>

#include <net/netisr.h>
#include <net/route.h>

#include <rtems/libio.h>


/*
 * Not just network config, but RTEMS config too
 * grlib is a bit different
 */
#define ENABLE_NETWORK
#include "rtems_config.h"
#include "config.c"

/*
** rki_init_network
*/
int rki_init_network(void)
{
   printf("rki_init_network: Calling system_init.\n");
   system_init();

   return(0);
}

#else

/*
** no network config!
*/
int rki_init_network( void )
{
   return(0);
}

#endif

