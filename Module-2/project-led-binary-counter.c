
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <xil_io.h>

#define GPIO_BTN_BASEADDR   0x41200000
#define GPIO_LED_BASEADDR   0x41210000
#define GPIO_DATA_OFFSET    0x0

int main()
{
    uint8_t counter = 0;
    uint8_t prev_btn = 0;

    while(1)
    {
        // Read button states
        uint8_t btn_val = Xil_In32(GPIO_BTN_BASEADDR + GPIO_DATA_OFFSET) & 0x03; // BTN0 & BTN1   

        // Rising edge detection - presses are detected - only act on new press
        if((btn_val != 0) && (btn_val != prev_btn))
        {
            if(btn_val & 0x01) // BTN0 pressed
            {
                counter++;
            }
            if(btn_val & 0x02) // BTN1 pressed
            {
                counter--;
            }

            // Write to LEDs
            Xil_Out32(GPIO_LED_BASEADDR + GPIO_DATA_OFFSET, counter);
            
            // Debug logs
            printf("Counter value: %d (0x%02X) \r\n", counter, counter);
        }
        
        prev_btn = btn_val;
        usleep(200000); // debounce delay 200 ms
    }

    return 0;
}
