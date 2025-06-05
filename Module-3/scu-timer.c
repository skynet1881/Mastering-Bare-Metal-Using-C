#include <stdint.h>
#include <stdio.h>

// SCU Timer registers
#define SCU_TIMER_BASE     0xF8F00600
#define SCU_TIMER_LOAD     (*(volatile uint32_t*)(SCU_TIMER_BASE + 0x00))
#define SCU_TIMER_COUNTER  (*(volatile uint32_t*)(SCU_TIMER_BASE + 0x04))
#define SCU_TIMER_CONTROL  (*(volatile uint32_t*)(SCU_TIMER_BASE + 0x08))
#define SCU_TIMER_ISR      (*(volatile uint32_t*)(SCU_TIMER_BASE + 0x0C))

// Control bits
#define SCU_TIMER_ENABLE      (1 << 0)
#define SCU_TIMER_AUTO_RELOAD (1 << 1)
#define SCU_TIMER_PRESCALER_SHIFT 8

// Create a calibrated ~0.5ms delay
void delay_0_5ms() {
    SCU_TIMER_CONTROL = 0;

    SCU_TIMER_LOAD = 10000;  // very small countdown (empirically tuned)
    SCU_TIMER_CONTROL = SCU_TIMER_ENABLE | (120 << SCU_TIMER_PRESCALER_SHIFT);  // max prescaler

    while (SCU_TIMER_COUNTER != 0);
}

// Create a delay of `ms` milliseconds by repeating
void scu_delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 2; i++) {
        delay_0_5ms();  // 0.5 ms * 2 = 1 ms
    }
}

int main() {
    
    while(1)
    {
        printf("LED ON \r\n");
        scu_delay_ms(1000);
        printf("LED OFF \r\n");
        scu_delay_ms(1000);
    }

    return 0;
}
