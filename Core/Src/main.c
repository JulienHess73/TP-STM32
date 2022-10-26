
#include "main.h"
#include "ini.h"
#include <stdio.h>
#include "algo_Huffman.h"
#include <stdlib.h>

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  GPIO_Init();
  init_uart();
  printf("\r\n----------------------------------------------------------------------\r\n");
  arbre_Huffman();

  while (1)
  {
	  TOGGLE_BIT(GPIOA->ODR, 5);
	  HAL_Delay(1000);
  }

}

