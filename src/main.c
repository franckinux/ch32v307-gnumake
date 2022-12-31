/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#include "systick.h"

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
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

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    GPIO_Toggle_INIT();

    // Get the systick counter running
    Systick_Init();

    uint32_t last_toggle = 0;
    uint8_t l0 = 0;
    uint8_t l1 = 1;

    while(1)
    {
      uint32_t now = GetTick();

      if (now - last_toggle >= 500) {
        GPIO_WriteBit(GPIOA, GPIO_Pin_15, (l0 == 0) ? (l0 = Bit_SET) : (l0 = Bit_RESET));
        GPIO_WriteBit(GPIOB, GPIO_Pin_4, (l1 == 0) ? (l1 = Bit_SET) : (l1 = Bit_RESET));

        last_toggle = now;
      }
    }
}

