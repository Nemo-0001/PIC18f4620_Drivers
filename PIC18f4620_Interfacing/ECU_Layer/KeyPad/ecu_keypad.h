/* 
 * File:   ecu_keypad.h
 * Author: Abdallah Elnemr
 *
 * Created on August 4, 2023, 3:41 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_keypad_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 4

#define KEYPAD_NOT_PRESSED    0XFF

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t keypad_row_pins[KEYPAD_ROWS];
    pin_config_t keypad_column_pins[KEYPAD_COLUMNS];
}keypad_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType keypad_initialize(const keypad_t *keypad);
Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value);

#endif	/* ECU_KEYPAD_H */

