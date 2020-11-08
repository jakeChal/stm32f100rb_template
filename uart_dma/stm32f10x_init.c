#include "stm32f10x.h"
#include "stm32f10x_init.h"


extern char data[2000];

void STM32_Configuration(void)
{
  /* System Clocks Configuration */
  RCC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();

  /* NVIC configuration */
  NVIC_Configuration();

  /* Configure the DMA */
  DMA_Configuration();

  /* Set USART Parameters */
  USART_Configuration();

  /* Set SysTick to 1ms */
  SysTick_Config(SystemCoreClock / 1000);
}

void RCC_Configuration(void)
{
  /* GPIOC clock enable (LED3/LED4) */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* GPIOA clock enable (USER Button) */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  /* GPIOA clock enable (USART1) */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

  /* DMA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOC Configuration: LED3/LED4 Output Push-Pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* GPIOA Configuration: User Button Input Floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Select GPIOA Pin 0 as EXTI Line 0 */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

  /* Configure USART1 Rx (PA10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART1 Tx (PA9) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

  /* USART1 configured as follow:
          - BaudRate = 9600 baud
          - Word Length = 8 Bits
          - Two Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure);

  /* Enable USARTy DMA TX request */
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

  USART_Cmd(USART1, ENABLE);

  /* Enable USARTy DMA TX Channel */
  DMA_Cmd(DMA1_Channel4, ENABLE);
}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  /* Enable the DMA1 ch4 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR; // Where data will be moved
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)data; // Where to read data from
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; // MEM -> UART (Peripheral)
  DMA_InitStructure.DMA_BufferSize = data_size;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // We are transferring from MEM -> PERIPHERAL, so mem increments
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // Need to set back to start of data after transferring!
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel4, &DMA_InitStructure);

  // Transfer Complete Interrupt Enable set
  DMA1_Channel4->CCR |= DMA_CCR4_TCIE;
}