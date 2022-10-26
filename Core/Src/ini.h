void SystemClock_Config(void);
void Error_Handler(void);
void GPIO_Init (void);
void init_uart (void);
void myPrintf(int* text);


#define TOGGLE_BIT(REG,BIT)	(REG ^= (1<<BIT));
