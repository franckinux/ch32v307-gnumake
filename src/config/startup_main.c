/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#include "app.h"
#include "systick.h"
#include "ch32v30x.h"
#include "thread.h"
#include "fifos.h"


void Error_Handler(void);


static void gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void main(void)
{
  uint32_t later = 0;

  gpio_init();

  // Get the systick counter running
  Systick_Init();

  fifos_init();
  if (!app_init()) {
    Error_Handler();
  }

  while(1)
  {
      __disable_irq();
      uint32_t now = GetTick();
      __enable_irq();

      if (now - later >= MAIN_DELAY) {
        app_loop();

        later = now;
      }
  }
}


void Error_Handler(void)
{
  __disable_irq();
  GPIO_WriteBit(GPIOA, GPIO_Pin_15, Bit_SET);
  while (1)
  {
  }
}
