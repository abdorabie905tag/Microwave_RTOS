/*
 * File        : APP_Interface.h
 * Description : This file includes Microwave application modules prototypes andd definitions
* Author      : Abdelrhman Rabie
 */

#ifndef __APP_INTERFACE_H__
#define __APP_INTERFACE_H__


#define APP_SET_TIME				0
#define APP_REMAINING_DISPLAY_TIME  1
#define APP_CLOSE_DOOR				2
#define APP_PUT_FOOD				3
#define APP_CLOSE_DOOR_PUT_FOOD     4


#define APP_STOP_HEATING			0
#define APP_START_HEATING			1


#define APP_SENSOR_OFF			    0
#define APP_SENSOR_ON			    1

#define APP_BUTTON_OFF			    1
#define APP_BUTTON_ON			    0


#define APP_HEATER_PIN			 MDIO_PA0
#define APP_LAMP_PIN			 MDIO_PA1
#define APP_MOTOR_PIN			 MDIO_PA2

#define APP_DOOR_SENSOR_PIN		 MDIO_PA3
#define APP_WEIGH_SENSOR_PIN	 MDIO_PA4

void APP_voidInitializeSystem(void);
void APP_voidCreateSystemTasks(void);
void APP_voidGetPressedKey(void);
void APP_voidDisplayLCD(void);
void APP_voidUpdateSensorReadings(void);
void APP_voidUpdateCurrentMode(void);
void APP_voidUpdateOutputState(void);


#endif
