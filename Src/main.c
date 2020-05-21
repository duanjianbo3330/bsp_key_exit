/**
  ******************************************************************************
  * �ļ�����: main.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2015-10-04
  * ��    ��: ʹ��HAL�ⷽ�������ⲿ�жϼ�ⰴ��״̬������LED�ƺͷ�����״̬
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F1Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "led/bsp_led.h"
#include "beep/bsp_beep.h"
#include "key/bsp_key.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
void SystemClock_Config(void);

/* ������ --------------------------------------------------------------------*/

/**
  * ��������: ������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
int main(void)
{
  /* ��λ�������裬��ʼ��Flash�ӿں�ϵͳ�δ�ʱ�� */
  HAL_Init();
  /* ����ϵͳʱ�� */
  SystemClock_Config();
  
  /* ����LED��ʼ�� */
  LED_GPIO_Init();
  
  /* ���ط�������ʼ�� */
  BEEP_GPIO_Init();

  /* ���Ӱ�����ʼ�� */
  KEY_GPIO_Init();
  
  /* ����ѭ�� */
  while (1)
  {
    
  }
}

/**
  * ��������: ϵͳʱ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;  // �ⲿ����8MHz
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;  // 9��Ƶ���õ�72MHz��ʱ��
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       // ϵͳʱ�ӣ�72MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;              // AHBʱ�ӣ�72MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;               // APB1ʱ�ӣ�36MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;               // APB2ʱ�ӣ�72MHz
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

 	// HAL_RCC_GetHCLKFreq()/1000    1ms�ж�һ��
	// HAL_RCC_GetHCLKFreq()/100000	 10us�ж�һ��
	// HAL_RCC_GetHCLKFreq()/1000000 1us�ж�һ��
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);  // ���ò�����ϵͳ�δ�ʱ��
  /* ϵͳ�δ�ʱ��ʱ��Դ */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  /* ϵͳ�δ�ʱ���ж����ȼ����� */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/**
  * ��������: �����ⲿ�жϷ�����
  * �������: GPIO_Pin���ж�����
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==KEY_UP_GPIO_PIN)
  {
    HAL_Delay(20);/* ��ʱһС��ʱ�䣬�������� */
    if(HAL_GPIO_ReadPin(KEY_UP_GPIO,KEY_UP_GPIO_PIN)==KEY_UP_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED1_ON;
      LED2_ON;
      LED3_ON;
      LED4_ON;
      LED5_ON;
      LED6_ON;
      LED7_ON;
      LED8_ON;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY_UP_GPIO_PIN);
  }
  else if(GPIO_Pin==KEY1_GPIO_PIN)
  {
    HAL_Delay(20);/* ��ʱһС��ʱ�䣬�������� */
    if(HAL_GPIO_ReadPin(KEY1_GPIO,KEY1_GPIO_PIN)==KEY1_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED1_OFF;
      LED2_OFF;
      LED3_OFF;
      LED4_OFF;
      LED5_OFF;
      LED6_OFF;
      LED7_OFF;
      LED8_OFF;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_GPIO_PIN);
  }
  else if(GPIO_Pin==KEY2_GPIO_PIN)
  {
    HAL_Delay(20);/* ��ʱһС��ʱ�䣬�������� */
    if(HAL_GPIO_ReadPin(KEY2_GPIO,KEY2_GPIO_PIN)==KEY2_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED1_ON;
      LED2_ON;
      LED3_ON;
      LED4_ON;
      LED5_ON;
      LED6_ON;
      LED7_ON;
      LED8_ON;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_GPIO_PIN);
  }
  else if(GPIO_Pin==KEY3_GPIO_PIN)
  {
    HAL_Delay(20);/* ��ʱһС��ʱ�䣬�������� */
    if(HAL_GPIO_ReadPin(KEY3_GPIO,KEY3_GPIO_PIN)==KEY3_DOWN_LEVEL)
    {
      BEEP_TOGGLE;
      LED1_OFF;
      LED2_OFF;
      LED3_OFF;
      LED4_OFF;
      LED5_OFF;
      LED6_OFF;
      LED7_OFF;
      LED8_OFF;
    }
    __HAL_GPIO_EXTI_CLEAR_IT(KEY3_GPIO_PIN);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/