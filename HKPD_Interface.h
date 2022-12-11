/*
 * File        : MDIO_Interface.h
 * Description : This interface file includes Keypad Driver prototypes and definitions for Atmega32
* Author      : Abdelrhman Rabie
 */

#ifndef __HKPD_Interface_h__
#define __HKPD_Interface_h__

 

/* 
 * Prototype   : void HKPD_u8InitializeKeypad(void);
 * Description : initialize 4X4 keypad at a given port set 4 pins output and 4 pins input
 * Arguments   : void
 * Return      : void  
 */
 void HKPD_voidInitializeKeypad(void);

/*
 * Prototype   : u8 HKPD_GetPressedKey(void);
 * Description : Return which key in the keypad has been pressed
 * Arguments   : void
 * return      : u8 pressed key
 */
 u8 HKPD_u8GetPressedKey(void);
 
#endif

/*===================================================================
 * EOF
 *===================================================================*/
