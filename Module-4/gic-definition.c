// GIC (Generic Interrupt Controller) on ARM Cortex A9

/*
    What it does?
    - Manages all external and software driven interrupts
    - Routes all interrupts to CPU\s
    - Supports priority, masking, enabling / disabling, interrupt targets

    GIC Architecture Components:
    - Located at 0xF8F00100U
    - Handles interrupt sources
    - Determines whether to forward interrupt to CPU

    Interrupt Lifecycle:
    - A peripheral asserts a interrupt line (GPIO)
    - The GIC receives it and checks if it is enabled
    - If it is enabled and not masked:
        - GIC forwards it to CPU
    - CPU checks priority and accepts the interrupt
    - ISR (Interrupt Software Routine) runs
    - ISR acknowledge and then ends the interrupt process 

*/

