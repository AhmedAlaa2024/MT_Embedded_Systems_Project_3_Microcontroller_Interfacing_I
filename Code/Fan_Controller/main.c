/*
 * main.c
 *
 *  Created on: Oct 2, 2021
 *      Author: ahmed
 */

#include "std_types.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"

int main(void)
{
	/* Initialize the LCD */
	LCD_init();
	/* Initialize the LM35 Temperature Sensor */
	LM35_init();
	/* Initialize the DC Motor */
	DcMotor_Init();

	/* Formating the LCD Screen */
	LCD_moveCursor(1, 3);
	LCD_displayString("Temp =     C");
	uint8 temp = 0, speed = 0;

	while(1)
	{
		/* Read the temperature sensor's value */
		temp = LM35_getTemperature();

		/* Determine the suitable speed of dc motor */
		if (temp < 30)
			speed = 0;
		else if ((temp >= 30) && (temp < 60))
			speed = 25;
		else if ((temp >= 60) && (temp < 90))
			speed = 50;
		else if ((temp >= 90) && (temp < 120))
			speed = 75;
		else if (temp >= 120)
			speed = 100;

		if(speed == 0)
		{
			/* Stop the dc motor */
			DcMotor_Rotate(OFF, speed);
			LCD_moveCursor(0, 3);
			LCD_displayString("FAN IS OFF");
		}
		else
		{
			/* Assign the speed to the dc motor */
			DcMotor_Rotate(CW, speed);
			LCD_moveCursor(0, 3);
			LCD_displayString("FAN IS ON ");
		}

		/* Display the temperature value on the LCD */
		LCD_moveCursor(1, 10);
		LCD_intgerToString(temp);
		LCD_displayCharacter(' ');
	}
	return 0;
}
