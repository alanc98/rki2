#include <stdio.h>
#include <string.h>

#include "io.h"
#include "fb.h"
/*
** Hello RTEMS!
*/
int fb_command( int argc, char *argv[])
{
    printf("Test Framebuffer Command for the RPI4!\n");

    printf("Calling fb_init()\n");
    fb_init();

    printf("Calling drawRect\n");
    drawRect(150,150,400,400,0x03,0);
    drawRect(300,300,350,350,0x2e,1);

    printf("Calling drawCircle\n");
    drawCircle(960,540,250,0x0e,0);
    drawCircle(960,540,50,0x13,1);

    printf("Calling drawPixel\n");
    drawPixel(250,250,0x0e);

    printf("Calling drawChar and drawString\n");
    drawChar('O',500,500,0x05);
    drawString(100,100,"Hello world!",0x0f);

    printf("Calling drawLine\n");
    drawLine(100,500,350,700,0x0c);

    return(0);
}
