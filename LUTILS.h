/*
 * File        : LUTILS.h
 * Description : This file includes macros used for Bit manipulation
 * Author      : Abdelrhman Rabie 
 */

#ifndef __L_UTILS_H__
#define __L_UTILS_H__

#define  L_UTILS_SET_BIT(REG,BIT)     		  REG|=(1<<BIT)
#define  L_UTILS_CLEAR_BIT(REG,BIT)           REG&=~(1<<BIT)
#define  L_UTILS_TOGGLE_BIT(REG,BIT)          REG^=(1<<BIT)
#define  L_UTILS_GET_BIT(REG,BIT)             ((REG>>BIT)&1)
#define  L_UTILS_SET_BIT_VALUE(REG,BIT,Value) ( (Value == 0) ? ( REG &= ~(1<<BIT) ) : ( REG |= (1<<BIT) ) )

#endif