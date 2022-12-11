/*
 * RTOS_LEDs.c
 *
 * Created: 14-Jul-19 7:09:52 PM
 * Author      : Abdelrhman Rabie
 */ 

#include "LSTD_Types.h"
#include "LDELAY_Interface.h"
#include "LMath_Interface.h"
#include "MTIMER0_Interface.h"
#include "MDIO_Interface.h"
#include "HKPD_Interface.h"
#include "HLCD_Interface.h"
#include "OS_Interface.h"
#include "APP_Interface.h"




/************************************************************************
 * Global variables                                                   
 ************************************************************************/
/*Weigh sensor status*/
volatile u8 APP_u8WeightSensorState = APP_SENSOR_OFF;
/*Door sensor status*/
volatile u8 APP_u8DoorSensorState   = APP_SENSOR_OFF;
/*Pressed key value*/
volatile u8 APP_u8PressedKey	    = 'k';
/*Current app mode*/
volatile u8 APP_u8AppMode	 = APP_SET_TIME;
/*Current app output mode*/
volatile u8 APP_u8OutputState = APP_STOP_HEATING;

/*heating time*/
volatile u32 APP_u32SetTime       =  0 ;
/*heating remaining time*/
volatile u32 APP_u32RemainingTime =  0 ;	
/*blank string to clear line*/
u8  *APP_u8PtrClearDisplayedString  = "                ";

int main(void)
{
    /*System Initialization*/
	APP_voidInitializeSystem();
	/*Create system tasks*/
	APP_voidCreateSystemTasks();
	/*Start OS*/
	OS_voidStartOS();
	
	/*infinite loop*/
	while (1) 
    {
		
		/*
		 * Idle task
		 * Task running in between ticks
		 */
    
	}/*end of infinite loop*/

}/*end of main()*/

void APP_voidInitializeSystem(void)
{
	/*DIO Initialization*/
	HLED_u8InitOneLed(MDIO_PORTA,APP_HEATER_PIN);
	HLED_u8InitOneLed(MDIO_PORTA,APP_LAMP_PIN);
	HLED_u8InitOneLed(MDIO_PORTA,APP_MOTOR_PIN);
	/*sensors initialization*/
	HLED_u8InitOneLed(MDIO_PORTA,APP_DOOR_SENSOR_PIN);
	HLED_u8InitOneLed(MDIO_PORTA,APP_WEIGH_SENSOR_PIN);
	
	/*Initialize Keypad*/
	HKPD_voidInitializeKeypad();
	
	/*Initialize LCD*/
	HLCD_voidInitializeLCD();
	
	HLCD_voidCursorDisplayOnOff(HLCD_OFF);
	HLCD_voidCursorBlinkOnOff(HLCD_OFF);
	HLCD_voidDisplayString("Set Heating Time",HLCD_STRING);
	
	/*OS Initialization*/
	OS_voidInitializeOS();

}/*end of APP_voidInitializeSystem()*/

void APP_voidCreateSystemTasks(void)
{
	/*Create Tasks*/
	OS_voidCreateTask(APP_voidGetPressedKey		   , 2  , 0 ,OS_TASK_READY, 1 );
	OS_voidCreateTask(APP_voidUpdateSensorReadings , 2  , 1 ,OS_TASK_READY, 1 );
	OS_voidCreateTask(APP_voidUpdateCurrentMode    , 2  , 2 ,OS_TASK_READY, 2 );
	OS_voidCreateTask(APP_voidDisplayLCD		   , 2  , 3 ,OS_TASK_READY, 3 );
	OS_voidCreateTask(APP_voidUpdateOutputState    , 2  , 4 ,OS_TASK_READY, 3 );

}/*end of APP_voidCreateSystemTasks()*/

void APP_voidGetPressedKey(void)
{
	/*get pressed key value*/
	u8 Local_u8Temp = HKPD_u8GetPressedKey();
	
	/*any key pressed check*/
	if (Local_u8Temp != '?')
	{
		/*return pressed key value*/
		APP_u8PressedKey = Local_u8Temp;
	}
	else /*no key pressed*/
 	{
		/*return dummy value*/
		APP_u8PressedKey = 'K';
	
	}/*end of any key pressed check*/
	
}/*end of APP_voidGetPressedKey()*/

void APP_voidDisplayLCD(void)
{
	/*Display mode check*/
	/*Display set time mode*/
	if ( APP_u8AppMode == APP_SET_TIME )
	{
		/*Display set Heating Time message in line1*/
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString("Set Heating Time",HLCD_STRING);
		
		/*Display pressed keys in line 2*/
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayString(&APP_u32SetTime,HLCD_NUMBER);
		
	}
	/*Display remaining time mode*/
	else if ( APP_u8AppMode == APP_REMAINING_DISPLAY_TIME )
	{
		/*Display Remaining Time message in line1*/
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString("Remaining Time",HLCD_STRING);
		/*Display remaining heating time in line2*/
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayString(&APP_u32RemainingTime,HLCD_NUMBER);
				
	}
	/*Display close door message*/
	else if ( APP_u8AppMode == APP_CLOSE_DOOR )
	{
		/*Display Close Door message in line1*/
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString("Close Door",HLCD_STRING);
		
	}
	/*Display put food message*/
	else if ( APP_u8AppMode == APP_PUT_FOOD )
	{
		/*Display Put food message message in line1*/
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString("Put Food First",HLCD_STRING);
	}
	/*Display put food and close door message*/
	else if ( APP_u8AppMode == APP_CLOSE_DOOR_PUT_FOOD )
	{
		/*Display CloseDoorPutFood message in line1*/
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayString(APP_u8PtrClearDisplayedString,HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE1);
		HLCD_voidDisplayString("CloseDoorPutFood",HLCD_STRING);
	
	}/*end of display mode check*/ 
					
}/*end of APP_voidDisplayLCD()*/


void APP_voidUpdateSensorReadings(void)
{
	/*Check pressed key*/
	if (APP_u8PressedKey == 'A')
	{
		/*Toggle Weigh sensor state*/
		APP_u8WeightSensorState ^= 1;
		
	}
	else if (APP_u8PressedKey == 'B')
	{
		/*Toggle Door sensor state*/
		APP_u8DoorSensorState ^= 1;
		
	}/*end of pressed key Check*/

}/*end of APP_voidUpdateSensorReadings()*/

void APP_voidUpdateCurrentMode(void)
{
	
	/*Time before reset count*/
	static u8 Local_u8TimeCount          = 0;
	/*number of key pressed*/
	static u8 Local_u8InputNumberCounter = 0;
	/*input time array*/
	static u8 APP_u8SetTimeArr[4]		 = {0};
	
	
	/*Increment time counter each time to update mode*/
	Local_u8TimeCount++;
	
	/*current mode check*/
	if (APP_u8AppMode == APP_REMAINING_DISPLAY_TIME)
	{
		/*current mode is display remaining time*/
		/*Pressed key check*/
		if (APP_u8PressedKey == 'B')
		{
			/*if Door was opened during heating*/
			/*stop heating*/
			APP_u8OutputState = APP_STOP_HEATING;
			/*Change mode to close door mode*/
			APP_u8AppMode	  = APP_CLOSE_DOOR;
			/*Save remaining time*/
			APP_u32SetTime	  = APP_u32RemainingTime;
		}
		else if ( (APP_u8PressedKey == 'C') || (APP_u32RemainingTime == 0) )
		{
			/*reset set time */
			APP_u32SetTime			   = 0;
			/*reset timer counter*/
			Local_u8TimeCount		   = 0;
			/*reset pressed key counter*/
			Local_u8InputNumberCounter = 0;
			
			/*stop heating*/
			APP_u8OutputState		   = APP_STOP_HEATING;
			/*Change mode to Set time mode*/
			APP_u8AppMode			   = APP_SET_TIME;
				
		}/*end of Pressed key check*/
		
		/*check time passed*/
		if (Local_u8TimeCount == 5) /*if 1 seconds passed*/
		{
			/*zero time counter to count 1 second again*/
			Local_u8TimeCount  = 0;
			/*Decrement remaining time by 1*/
			APP_u32RemainingTime--;
			
		}/*end of time passed check*/
	}
	else /*all other modes*/
	{
		/*Button pressed check*/
		if ( (APP_u8PressedKey >= 0) && (APP_u8PressedKey < 10) )
		{
			/*reset time count*/
			Local_u8TimeCount = 0;
			
			/*number was pressed*/
			APP_u8AppMode	  = APP_SET_TIME;
			/*zero time counter start time wait from beginning*/
			
			/*accept 4 digit number*/		
			if (Local_u8InputNumberCounter < 4)
			{
				/*save pressed key in set time array*/
				APP_u8SetTimeArr[Local_u8InputNumberCounter] = APP_u8PressedKey;
				/*reset set time variable*/
				APP_u32SetTime = 0;
				
				/*loop inputed keys*/
				for (u8 i = 0; i < (Local_u8InputNumberCounter+1) ;i++)
				{
					/*calculate set time value*/
					u32 Local_u32Result = LMATH_u32GetExponential(10,(Local_u8InputNumberCounter-i));
					APP_u32SetTime = APP_u32SetTime + ( ((u32)APP_u8SetTimeArr[i]) * Local_u32Result ) ;
				
				}/*end of inputed keys loop*/
				
			}/*end of number of digits entered check*/
			
			/*increment number of key pressed*/
			Local_u8InputNumberCounter++;
		
		}
		else if (APP_u8PressedKey == 'C') /*cancel button pressed*/
		{
			/*reset set time */
			APP_u32SetTime			   = 0;
			/*reset timer counter*/
			Local_u8TimeCount		   = 0;
			/*reset pressed key counter*/
			Local_u8InputNumberCounter = 0;
			/*Change mode to set time mode*/
			APP_u8AppMode			   = APP_SET_TIME;
		
		}
		else if (APP_u8PressedKey == 'D') /**/
		{
			/*zero time counter start time wait from beginning*/
			Local_u8TimeCount = 0;
			
			/*sensors check*/
			/*when time is set, food in microwave, and door is closed start heating*/
			if( (APP_u32SetTime != 0) && (APP_u8WeightSensorState == APP_SENSOR_OFF) && (APP_u8DoorSensorState == APP_SENSOR_OFF) )
			{
				/*set remaining time with set time value*/
				APP_u32RemainingTime = APP_u32SetTime;
				/*start heating process*/
				APP_u8OutputState = APP_START_HEATING;
				/*Change mode to display remaining time mode*/
				APP_u8AppMode = APP_REMAINING_DISPLAY_TIME;
			}
			/*door is opened*/
			else if( (APP_u32SetTime != 0) && (APP_u8WeightSensorState == APP_SENSOR_OFF) && (APP_u8DoorSensorState == APP_SENSOR_ON) )
			{
				/*stop heating process*/
				APP_u8OutputState = APP_STOP_HEATING;
				/*change mode to close door*/
				APP_u8AppMode	  = APP_CLOSE_DOOR;
			}
			/*there is no food*/
			else if ( (APP_u32SetTime != 0) && (APP_u8WeightSensorState == APP_SENSOR_ON) && (APP_u8DoorSensorState == APP_SENSOR_OFF) )
			{
				/*stop heating process*/
				APP_u8OutputState = APP_STOP_HEATING;
				/*change mode to put food*/
				APP_u8AppMode	  = APP_PUT_FOOD;
			}
			/*door is open and there is n food*/
			else if ( (APP_u32SetTime != 0) && (APP_u8WeightSensorState == APP_SENSOR_ON) && (APP_u8DoorSensorState == APP_SENSOR_ON) )
			{
				/*stop heating process*/
				APP_u8OutputState = APP_STOP_HEATING;
				/*change mode to close door and put food*/
				APP_u8AppMode	  = APP_CLOSE_DOOR_PUT_FOOD;
			
			}/*end of sensors check*/
		
		}
		
		/*check time passed*/
		if (Local_u8TimeCount == 50) /*if 3 seconds passed*/
		{
			/*set mode to set time*/
			APP_u8AppMode	   = APP_SET_TIME;
			/*Make display temp current mode*/
			APP_u32SetTime     = 0;	
			/*reset time counter*/
			Local_u8TimeCount  = 0;
			/*reset number of pressed key counter*/	
			Local_u8InputNumberCounter = 0;
			
		}/*end of time passed check*/
		
	}/*end of current mode check*/
	
}/*end of APP_voidUpdateCurrentMode()*/


void APP_voidUpdateOutputState(void)
{
	/*Set heater on or off*/
	HLED_u8LedOnOff(MDIO_PORTA,APP_HEATER_PIN,APP_u8OutputState);
	/*Set Motor on or off*/
	HLED_u8LedOnOff(MDIO_PORTA,APP_MOTOR_PIN,APP_u8OutputState);
	/*Set Lamp on or off*/
	HLED_u8LedOnOff(MDIO_PORTA,APP_LAMP_PIN,APP_u8OutputState);	
	
	/*Set door sensor indication led on or off*/
	HLED_u8LedOnOff(MDIO_PORTA,APP_DOOR_SENSOR_PIN,APP_u8DoorSensorState);
	/*Set Weight sensor indication led on or off*/
	HLED_u8LedOnOff(MDIO_PORTA,APP_WEIGH_SENSOR_PIN,APP_u8WeightSensorState);

}/*end of APP_voidUpdateOutputState()*/