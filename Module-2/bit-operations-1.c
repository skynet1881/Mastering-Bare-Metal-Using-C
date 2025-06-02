
#include <stdint.h>
#include <stdio.h>

int main()
{
    uint8_t reg = 0b10101100;

    // check register bit 3 if it is set
    if(reg & (1 << 3))  // 1000
    {
        printf("Bit 3 is SET \r\n");
    }
    else
    {
        printf("Bit 3 is CLEAR \r\n");
    }

    // Set bit 0
    reg |= (1 << 0);
    printf("After setting bit 0: 0x%02X \r\n", reg); // 10101101 - 0xAD

    // Clear bit 2
    reg &= ~(1 << 2);  // & 011
    printf("After clearing bit 2: 0x%02X \r\n", reg); // 10101001 - 0xA9

    // Toggle bit 7
    reg ^= (1 << 7);
    printf("After toggling bit 7: 0x%02X \r\n", reg); // 00101001 - 0x29

    // Extract bit 6
    uint8_t bit6 = (reg >> 6) & 0x01;                 // 00101001 - 0
    printf("Bit 6 is: 0x%02X \r\n", bit6);

    return 0;
}
