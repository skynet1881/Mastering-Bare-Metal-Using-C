#include <stdint.h>
#include <unistd.h> // this is for sleep

// GPIO base addresses from xparameters.h
#define GPIO_BTN_BASEADDR   0x41200000
#define GPIO_LED_BASEADDR   0x41210000
#define GPIO_SW_BASEADDR    0x41220000

#define GPIO_DATA_OFFSET    0x0

int main() {
    
    // Define here some pointers to the MMIO registers
    volatile uint32_t* btn_reg = (uint32_t*)(GPIO_BTN_BASEADDR + GPIO_DATA_OFFSET);
    volatile uint32_t* sw_reg = (uint32_t*)(GPIO_SW_BASEADDR + GPIO_DATA_OFFSET);
    volatile uint32_t* led_reg = (uint32_t*)(GPIO_LED_BASEADDR + GPIO_DATA_OFFSET);

    while(1)
    {
        uint32_t btn_value = *btn_reg;
        uint32_t sw_value = *sw_reg;
        uint32_t led_value = btn_value | sw_value;

        *led_reg = led_value;
        sleep(1);
    }

    return 0;
}

