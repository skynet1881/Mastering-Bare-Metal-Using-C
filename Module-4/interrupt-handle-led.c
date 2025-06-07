#include "xparameters.h"
#include "xgpio.h"
#include "xscugic.h"
#include "xil_exception.h"
#include <stdio.h>

#define GPIO_DEVICE_ID       XPAR_AXI_GPIO_BTN_DEVICE_ID
#define INTC_DEVICE_ID       XPAR_SCUGIC_SINGLE_DEVICE_ID
#define GPIO_INTERRUPT_ID    XPAR_FABRIC_AXI_GPIO_BTN_IP2INTC_IRPT_INTR

#define GPIO_LED_DATA_OFSET  0
#define GPIO_LED_REG         (*(volatile uint32_t*)(XPAR_GPIO_1_BASEADDR + GPIO_LED_DATA_OFSET))    

static XGpio Gpio;
static XScuGic Intc;
volatile int btn_flag = 0;

void GpioInterruptHandler(void *CallbackRef)
{
    btn_flag = 1;
    XGpio_InterruptClear(&Gpio, XGPIO_IR_CH1_MASK);
}

int SetupInterrupts()
{
    XScuGic_Config *GicConfig;
    int status;

    // Lookup
    GicConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
    if(!GicConfig) 
        return XST_FAILURE;

    status = XScuGic_CfgInitialize(&Intc, GicConfig, GicConfig->CpuBaseAddress);
    if(status != XST_SUCCESS)
        return XST_FAILURE;

    status = XScuGic_Connect(&Intc, 
                            GPIO_INTERRUPT_ID,
                            (Xil_InterruptHandler)GpioInterruptHandler,
                            (void*)&Gpio);

    if(status != XST_SUCCESS)
        return XST_FAILURE;

    XScuGic_Enable(&Intc, GPIO_INTERRUPT_ID);
    
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
                                (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                                &Intc);

    Xil_ExceptionEnable();

    return XST_SUCCESS;
}

int main() {
    
    int status;
    status = XGpio_Initialize(&Gpio, GPIO_DEVICE_ID);
    if(status != XST_SUCCESS)
    {
        printf("GPIO init fail \r\n");
        return XST_FAILURE;
    }

    XGpio_SetDataDirection(&Gpio, 1, 0xFF); // Input

    status = SetupInterrupts();
    if(status != XST_SUCCESS)
    {
        printf("Interrupt setup fail \r\n");
        return XST_FAILURE;
    }

    XGpio_InterruptEnable(&Gpio, XGPIO_IR_CH1_MASK);
    XGpio_InterruptGlobalEnable(&Gpio);

    while(1)
    {
        if(btn_flag)
        {
            printf("Interrupt triggerred \r\n");
            GPIO_LED_REG ^= 0xFF;

            btn_flag = 0;
        }
    }

    return 0;
}
