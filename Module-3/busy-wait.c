#include <stdio.h>
#include <stdint.h>
#include <unistd.h>  // for sleep()

// Busy-wait delay (bad practice in production)
void busy_delay() {
    for (volatile int i = 0; i < 5000000; i++);
}

int main() {
    printf("Busy wait LED blink (manual delay)...\n");

    for (int i = 0; i < 5; i++) {
        printf("LED ON\n");
        busy_delay();     // crude wait
        printf("LED OFF\n");
        busy_delay();
    }

    printf("\nNow using sleep()...\n");

    for (int i = 0; i < 5; i++) {
        printf("LED ON\n");
        sleep(1);         // 1 second
        printf("LED OFF\n");
        sleep(1);
    }

    return 0;
}

