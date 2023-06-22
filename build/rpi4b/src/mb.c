#include "io.h"
#include <stdio.h>

// The buffer must be 16-byte aligned as only the upper 28 bits of the address can be passed via the mailbox
volatile unsigned int __attribute__((aligned(16))) mbox[36];

enum {
    VIDEOCORE_MBOX = (PERIPHERAL_BASE + 0x0000B880),
    MBOX_READ      = (VIDEOCORE_MBOX + 0x0),
    MBOX_POLL      = (VIDEOCORE_MBOX + 0x10),
    MBOX_SENDER    = (VIDEOCORE_MBOX + 0x14),
    MBOX_STATUS    = (VIDEOCORE_MBOX + 0x18),
    MBOX_CONFIG    = (VIDEOCORE_MBOX + 0x1C),
    MBOX_WRITE     = (VIDEOCORE_MBOX + 0x20),
    MBOX_RESPONSE  = 0x80000000,
    MBOX_FULL      = 0x80000000,
    MBOX_EMPTY     = 0x40000000
};

/* This macro is in RT-Thread */
#define BUS_ADDRESS(phys)	(((phys) & ~0xC0000000)  |  0xC0000000)

unsigned int mbox_call(unsigned char ch)
{
    printf("In mbox_call\n");
    // 28-bit address (MSB) and 4-bit value (LSB)
    unsigned int r = ((unsigned int)((long) &mbox) &~ 0xF) | (ch & 0xF);

    // From RT-Thread - did not seem to help 
    r = BUS_ADDRESS(r);

    printf("mbox_call: addr of mbox array = 0x%08X\n",mbox);
    printf("mbox_call: r = 0x%08X\n",r);

    // Wait until we can write
    while (mmio_read(MBOX_STATUS) & MBOX_FULL);
    printf("mailbox is not full - calling MBOX_WRITE\n");
    // Write the address of our buffer to the mailbox with the channel appended
    mmio_write(MBOX_WRITE, r);

    while (1) {
        // Is there a reply?
        while (mmio_read(MBOX_STATUS) & MBOX_EMPTY)
	    printf("in mbox_call Mailbox status read = %X\n",(mmio_read(MBOX_STATUS)));
        printf("in mbox_call - broke out of while empty mmio_read(MBOX_STATUS) = 0x%08X\n",mmio_read(MBOX_STATUS));
        // Is it a reply to our message?
        if (r == mmio_read(MBOX_READ))
	{
	   printf("mailbox response = 0x%08X\n",mbox[1]);
           printf("MBOX response is successful, returning %d\n",(mbox[1] == MBOX_RESPONSE));
	   return mbox[1]==MBOX_RESPONSE; // Is it successful?
	}
    }
    printf("mbox_call - should never get here\n");
    return 0;
}
