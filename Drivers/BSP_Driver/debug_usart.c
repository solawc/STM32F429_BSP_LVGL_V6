#include "debug_usart.h"

void bsp_debug_usart_init(void)
{
    MX_USART1_UART_Init();

#if USR_USART1_DMA
    bsp_usart1_dma2_init();
#endif

    // __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);  
    // HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    // HAL_NVIC_EnableIRQ(USART1_IRQn);
    // ringbuffer_init();
}

// void USART1_IRQHandler(void)
// {
//   uint8_t ch;
//   if(__HAL_UART_GET_FLAG( &huart1, UART_FLAG_RXNE) != RESET)
//   {
//     ch = huart1.Instance->DR;
//     ringbuffer_write(ch);
//     //HAL_UART_Transmit(&huart1,&ch,1,1);
//   }
// }

int fputc(int ch, FILE *f)
{
#if USE_BLUETOOSE
    HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 1000);
#else
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
#endif

  return ch;
}

#if USR_USART1_DMA
void debug_dma_printf(uint8_t *str)
{
  uint32_t k=0;
  do
  {
    k++;
  }while(*(str+k)!='\0');
  HAL_UART_Transmit_DMA(&huart1,str, k);
}
#endif


ringbuff_t debug_ringbuf;

bool ringbuffer_init(void)
{
  debug_ringbuf.head = 0;
  debug_ringbuf.tail = 0;
  debug_ringbuf.len = 0;

  return true;
}

bool ringbuffer_write(uint8_t data)
{
  if(debug_ringbuf.len >= RINGBUF_LENGTH)
  { 
      return false;
  }
  debug_ringbuf.buff[debug_ringbuf.tail] = data;
  debug_ringbuf.tail = (debug_ringbuf.tail+1)%RINGBUF_LENGTH;

  debug_ringbuf.len++;

  return true;
}

bool ringbuffer_read(uint8_t *data)
{
  if(debug_ringbuf.len == 0)
  {
    return false;
  }

  *data = debug_ringbuf.buff[debug_ringbuf.head];
  debug_ringbuf.head = (debug_ringbuf.head+1)%RINGBUF_LENGTH;
  debug_ringbuf.len--;

  return true;
}






