/* 
 * File:   ecu_init.h
 * Author: Abdallah Elnemr
 *
 * Created on August 4, 2023, 4:19 PM
 */

#ifndef ECU_INIT_H
#define	ECU_INIT_H

/* ----------------- Includes -----------------*/
#include "LED/ecu_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "Motor/ecu_dc_motor.h"
#include "7_Segment/ecu_seven_segment.h"
#include "KeyPad/ecu_keypad.h"
#include "LCD/ecu_lcd.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/

/* ----------------- Function Declarations -----------------*/
void ecu_initialize(void);

#endif	/* ECU_INIT_H */

