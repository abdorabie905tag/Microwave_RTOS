/*
 * File        : LDELAY_Private.h
 * Description : This file includes delay service definitions used by driver for Atmega32
 * Author      : Abdelrhman Rabie
 */


#ifndef __LDELAY_PRIVATE_H__
#define __LDELAY_PRIVATE_H__

/*those time parameters are measured by oscilloscope*/

/*one loop iteration time*/
#define LDELAY_LoopTime           137
/*time lost in calculation*/
#define LDELAY_CalculationTime    696
/*time lost in context switching*/
#define LDELAY_ContextSwitch      1710

#endif

/*==============================================================================================================================================
 * EOF 
 *==============================================================================================================================================*/