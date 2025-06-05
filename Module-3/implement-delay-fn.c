#include <stdint.h>
#include <stdio.h>

// Zybo 650 Mhz - 650 000 000 instructions in a second
// for loop needs 6 instructions 
// 1 second ~110 000 000
void delay_one_second()
{
    for(volatile uint32_t i = 0; i < 110000000; i++) 
    {
        __asm__ __volatile__("");
    }
}


int main() {
    while(1)
    {
        printf("LED ON \r\n");
        delay_one_second();
        printf("LED OFF \r\n");
        delay_one_second();
    }

    return 0;
}
