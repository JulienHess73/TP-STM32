#include "ini.h"
#include "main.h"

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

void GPIO_Init (void){
	__GPIOA_CLK_ENABLE();
	GPIOA->MODER |= (1<<10);
	GPIOA->MODER |= (0<<11);
}

int __io_putchar(int ch){
	WRITE_REG(USART2->DR,ch);
    while ( READ_BIT(USART2->SR, 1<<7) == 0 );
}

void myPrintf(int * text){
	for(int i=0;i<sizeof(text);i++){
		 WRITE_REG(USART2->DR, text[i]);
		 while ( READ_BIT(USART2->SR, 1<<7) == 0 );
	}
}

void init_uart (void)
{
	__USART2_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();

	//init PA2 en Alternate function mode
	GPIOA->MODER |= (1<<05);

	//Mettre Alternante function comme etant UART2
	GPIOA->AFR[0] |= (7<<8);

	//Mettre le bit UE à 1
	USART2->CR1 |= (1<<13);

	//Definit le baudrate
	USART2->BRR = 139;

	USART2->CR1|=1<<3;

}


