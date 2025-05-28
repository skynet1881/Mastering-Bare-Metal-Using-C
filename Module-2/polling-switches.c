
#include <stdint.h>
#include <unistd.h>  // For sleep()
#include <stdio.h>

#include "xil_io.h" // For Xil_In32()

#define GPIO_BTN_BASEADDR   0x41200000
#define GPIO_SW_BASEADDR    0x41220000
#define GPIO_DATA_OFFSET    0x0

int main()
{
    while(1)
    {
        uint32_t btn_val = Xil_In32(GPIO_BTN_BASEADDR + GPIO_DATA_OFFSET);
        uint32_t sw_val  = Xil_In32(GPIO_SW_BASEADDR + GPIO_DATA_OFFSET);
        
        printf("Button: 0x%X Switch: 0x%X \r\n", btn_val, sw_val);

        sleep(1);
    }

    return 0;
}
