#include <stdint.h>
#include <unistd.h>  // For sleep()

#define GPIO_BASE        0xE000A000
#define GPIO_DATA_0      (GPIO_BASE + 0x40)
#define GPIO_DIRM_0      (GPIO_BASE + 0x204)
#define GPIO_OEN_0       (GPIO_BASE + 0x208)

#define MIO_LED_PIN      7
#define LED_MASK         (1 << MIO_LED_PIN)

int main() {
    // Cast the addresses as volatile pointers
    volatile uint32_t* gpio_data  = (uint32_t*)GPIO_DATA_0;
    volatile uint32_t* gpio_dirm  = (uint32_t*)GPIO_DIRM_0;
    volatile uint32_t* gpio_oen   = (uint32_t*)GPIO_OEN_0;

    // Set MIO7 direction to output
    *gpio_dirm |= LED_MASK;

    // Enable output on MIO7
    *gpio_oen |= LED_MASK;

    while (1) {
        *gpio_data |= LED_MASK;   // Turn LED on
        sleep(1);

        *gpio_data &= ~LED_MASK;  // Turn LED off
        sleep(1);
    }

    return 0;
}

