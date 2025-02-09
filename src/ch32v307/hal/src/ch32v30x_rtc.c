/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32v30x_rtc.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : This file provides all the RTC firmware functions.
********************************************************************************/
#include "ch32v30x_rtc.h"

/* RTC_Private_Defines */
#define RTC_LSB_MASK     ((uint32_t)0x0000FFFF)  /* RTC LSB Mask */
#define PRLH_MSB_MASK    ((uint32_t)0x000F0000)  /* RTC Prescaler MSB Mask */

/********************************************************************************
* Function Name  : RTC_ITConfig
* Description    : Enables or disables the specified RTC interrupts.
* Input          : RTC_IT: specifies the RTC interrupts sources to be enabled or disabled.
*                     RTC_IT_OW: Overflow interrupt
*                     RTC_IT_ALR: Alarm interrupt
*                     RTC_IT_SEC: Second interrupt
* Return         : NewState: new state of the specified RTC interrupts(ENABLE or DISABLE).
*********************************************************************************/
void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RTC->CTLRH |= RTC_IT;
  }
  else
  {
    RTC->CTLRH &= (uint16_t)~RTC_IT;
  }
}

/********************************************************************************
* Function Name  : RTC_EnterConfigMode
* Description    : Enters the RTC configuration mode.
* Input          : None
* Return         : None
*********************************************************************************/
void RTC_EnterConfigMode(void)
{
  RTC->CTLRL |= RTC_CTLRL_CNF;
}

/********************************************************************************
* Function Name  : RTC_ExitConfigMode
* Description    : Exits from the RTC configuration mode.
* Input          : None
* Return         : None
*********************************************************************************/
void RTC_ExitConfigMode(void)
{
  RTC->CTLRL &= (uint16_t)~((uint16_t)RTC_CTLRL_CNF);
}

/********************************************************************************
* Function Name  : RTC_GetCounter
* Description    : Gets the RTC counter value
* Input          : None
* Return         : RTC counter value
*********************************************************************************/
uint32_t RTC_GetCounter(void)
{
  uint16_t high1 = 0, high2 = 0, low = 0;

  high1 = RTC->CNTH;
  low   = RTC->CNTL;
  high2 = RTC->CNTH;

  if (high1 != high2)
  {
    return (((uint32_t) high2 << 16 ) | RTC->CNTL);
  }
  else
  {
    return (((uint32_t) high1 << 16 ) | low);
  }
}

/********************************************************************************
* Function Name  : RTC_SetCounter
* Description    : Sets the RTC counter value.
* Input          : CounterValue: RTC counter new value.
* Return         : None
*********************************************************************************/
void RTC_SetCounter(uint32_t CounterValue)
{
  RTC_EnterConfigMode();
  RTC->CNTH = CounterValue >> 16;
  RTC->CNTL = (CounterValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/********************************************************************************
* Function Name  : RTC_SetPrescaler
* Description    : Sets the RTC prescaler value
* Input          : PrescalerValue: RTC prescaler new value
* Return         : None
*********************************************************************************/
void RTC_SetPrescaler(uint32_t PrescalerValue)
{
  RTC_EnterConfigMode();
  RTC->PSCRH = (PrescalerValue & PRLH_MSB_MASK) >> 16;
  RTC->PSCRL = (PrescalerValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/********************************************************************************
* Function Name  : RTC_SetAlarm
* Description    : Sets the RTC alarm value
* Input          : AlarmValue: RTC alarm new value
* Return         : None
*********************************************************************************/
void RTC_SetAlarm(uint32_t AlarmValue)
{
  RTC_EnterConfigMode();
  RTC->ALRMH = AlarmValue >> 16;
  RTC->ALRML = (AlarmValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/********************************************************************************
* Function Name  : RTC_GetDivider
* Description    : Gets the RTC divider value
* Input          : None
* Return         : RTC Divider value
*********************************************************************************/
uint32_t RTC_GetDivider(void)
{
  uint32_t tmp = 0x00;
  tmp = ((uint32_t)RTC->DIVH & (uint32_t)0x000F) << 16;
  tmp |= RTC->DIVL;
  return tmp;
}

/********************************************************************************
* Function Name  : RTC_WaitForLastTask
* Description    : Waits until last write operation on RTC registers has finished
* Input          : None
* Return         : None
*********************************************************************************/
void RTC_WaitForLastTask(void)
{
  while ((RTC->CTLRL & RTC_FLAG_RTOFF) == (uint16_t)RESET)
  {
  }
}

/********************************************************************************
* Function Name  : RTC_WaitForSynchro
* Description    : Waits until the RTC registers
*                  are synchronized with RTC APB clock
* Input          : None
* Return         : None
*********************************************************************************/
void RTC_WaitForSynchro(void)
{
  RTC->CTLRL &= (uint16_t)~RTC_FLAG_RSF;
  while ((RTC->CTLRL & RTC_FLAG_RSF) == (uint16_t)RESET)
  {
  }
}

/********************************************************************************
* Function Name  : RTC_GetFlagStatus
* Description    : Checks whether the specified RTC flag is set or not
* Input          : RTC_FLAG: specifies the flag to check
*                    RTC_FLAG_RTOFF: RTC Operation OFF flag
*                    RTC_FLAG_RSF: Registers Synchronized flag
*                    RTC_FLAG_OW: Overflow flag
*                    RTC_FLAG_ALR: Alarm flag
*                    RTC_FLAG_SEC: Second flag
* Return         : The new state of RTC_FLAG (SET or RESET)
*********************************************************************************/
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  if ((RTC->CTLRL & RTC_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/********************************************************************************
* Function Name  : RTC_ClearFlag
* Description    : Clears the RTC's pending flags
* Input          : RTC_FLAG: specifies the flag to clear
*                    RTC_FLAG_RSF: Registers Synchronized flag
*                    RTC_FLAG_OW: Overflow flag
*                    RTC_FLAG_ALR: Alarm flag
*                    RTC_FLAG_SEC: Second flag
* Return         : None
*********************************************************************************/
void RTC_ClearFlag(uint16_t RTC_FLAG)
{
  RTC->CTLRL &= (uint16_t)~RTC_FLAG;
}


/********************************************************************************
* Function Name  : RTC_GetITStatus
* Description    : Checks whether the specified RTC interrupt has occurred or not
* Input          : RTC_IT: specifies the RTC interrupts sources to check
*                    RTC_FLAG_OW: Overflow interrupt
*                    RTC_FLAG_ALR: Alarm interrupt
*                    RTC_FLAG_SEC: Second interrupt
* Return         : The new state of the RTC_IT (SET or RESET)
*********************************************************************************/
ITStatus RTC_GetITStatus(uint16_t RTC_IT)
{
  ITStatus bitstatus = RESET;

  bitstatus = (ITStatus)(RTC->CTLRL & RTC_IT);
  if (((RTC->CTLRH & RTC_IT) != (uint16_t)RESET) && (bitstatus != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/********************************************************************************
* Function Name  : RTC_ClearITPendingBit
* Description    : Clears the RTC's interrupt pending bits
* Input          : RTC_IT: specifies the interrupt pending bit to clear
*                    RTC_FLAG_OW: Overflow interrupt
*                    RTC_FLAG_ALR: Alarm interrupt
*                    RTC_FLAG_SEC: Second interrupt
* Return         : None
*********************************************************************************/
void RTC_ClearITPendingBit(uint16_t RTC_IT)
{
  RTC->CTLRL &= (uint16_t)~RTC_IT;
}

