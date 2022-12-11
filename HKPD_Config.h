/*
 * File        : HKPD_Config.h
 * Description : This file includes Keypad Driver Configuration parameters for Atmega32
 * Author      : Abdelrhman Rabie 
 */


#ifndef __HKPD_Config_h__
#define __HKPD_Config_h__

/*pin connections on keypad register*/
/*choose keypad port*/
#define KEYPAD_PORT  MDIO_PORTD 
/*Column connections*/
#define C1 3
#define C2 2
#define C3 1
#define C4 0
/*Row connections*/
#define R1 4
#define R2 5
#define R3 6
#define R4 7

 
/*Keypad buttons assigned values array*/
const u8 KeyPadArr[4][4]={{ 1,  2,  3,  'A'},
					      { 4,  5,  6,  'B'},
					      { 7,  8,  9,  'C'},
					      {'#', 0, '*', 'D'}};
							  

#endif

/*===================================================================
 * EOF
 *===================================================================*/