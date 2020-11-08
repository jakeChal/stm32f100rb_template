/*-----------------------------------------------------------------------------
/
/
/
/
/
/
/----------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_misc.h"
#include "stm32f10x_init.h"
#include "printf.h"

// #define UART_POLLING
#define countof(a) (sizeof(a) / sizeof(*(a)))

char data[2000];
#define data_size (countof(data))

void USART1_IRQHandler(void)
{
  static unsigned int counter = 0;
  if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {

    USART_SendData(USART1, (uint16_t)data[counter++]);

    if(counter == data_size)
    {
      /* Clear the USART1 Transmit interrupt */
      USART_ClearITPendingBit(USART1, USART_IT_TC);
      counter = 0;
    }

  }
}

int main(void)
{
  /* Initialize system */
  STM32_Configuration();

#ifdef UART_POLLING
  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
#endif

  for (unsigned i = 0; i < data_size; i++)
  {
    data[i] = 'x';
  }

  while (1)
  {
    GPIO_ToggleBit(GPIOC, GPIO_Pin_9);
    Delay(250);

    // If we were to use polling, then the data is transmitted using blocking mode
    // i.e the CPU will block  every other operation until the data transfer is complete.
    // Check that blinking rate decreases dramatically for big buffers!

#ifdef UART_POLLING
    char *s = data;
    while (*s)
    {
      while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ; // Wait for Empty
      USART_SendData(USART1, (uint16_t)*s++);
    }
#endif
  }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
  printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  while (1)
  {
  }
}

#endif
