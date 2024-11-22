#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "vlib.h"

int main(int argc, char** argv)
{
    int fd, bytes;
    unsigned char data[3];

    MAP();

    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

    int left, middle, right;
    signed char x, y;

    x = 0;
    y = 0;

    while(1)
    {
        // Read Mouse     
        bytes = read(fd, data, sizeof(data));

        if(bytes > 0)
        {
            //WBR_SPRITE(1, 0, x, y, 0);
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;

            x += data[1];
            y -= data[2];
            printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);
            //WBR_SPRITE(1, 0, x, y, 1);
        }

        WBR_SPRITE(1, 0, ((x*3)+300), ((y*3)+200), 1);   
    }
    return 0; 
}