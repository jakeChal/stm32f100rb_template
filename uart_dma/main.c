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

char data[2000];

void DMA1_Channel4_IRQHandler(void)
{
  /* Test on DMA1 Channel4 Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_IT_TC4))
  {
    /* Clear DMA1 Channel4 Transfer Complete interrupt pending bit */
    DMA_ClearITPendingBit(DMA1_IT_TC4);
  }
  GPIO_ToggleBit(GPIOC, GPIO_Pin_8);
}

int main(void)
{
  /* Initialize system */
  STM32_Configuration();

  for (unsigned i = 0; i < data_size; i++)
  {
    data[i] = 'x';
  }

  while (1)
  {
    GPIO_ToggleBit(GPIOC, GPIO_Pin_9);
    Delay(250);

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
