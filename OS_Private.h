/*
 * File        : OS_Private.h
 * Description : This file includes OS Service private prototypes and definitions
 * Author      : Abdelrhman Rabie 
 */

#ifndef _OS_PRIVATE_H_
#define _OS_PRIVATE_H_

/*Task data type*/
typedef struct 
{
    void(*TaskHandler)(void);
    u32 Periodicity;
	u32 FirstDelay;
	u8  State ;
}Task;


#endif

/*=================================================================================*
 * EOF
 *=================================================================================*/
