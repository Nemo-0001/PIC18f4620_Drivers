/* 
 * File:   ecu_init.c
 * Author: Abdallah Elnemr
 *
 * Created on August 4, 2023, 4:19 PM
 */

#include "ecu_init.h"

//keypad
/*
keypad_t keypad1 = {
  .keypad_row_pins[0].port = PORTA_INDEX,
  .keypad_row_pins[0].pin = GPIO_PIN0,
  .keypad_row_pins[0].logic = GPIO_LOW,
  .keypad_row_pins[0].direction = GPIO_OUTPUT,
  .keypad_row_pins[1].port = PORTA_INDEX,
  .keypad_row_pins[1].pin = GPIO_PIN1,
  .keypad_row_pins[1].logic = GPIO_LOW,
  .keypad_row_pins[1].direction = GPIO_OUTPUT,
  .keypad_row_pins[2].port = PORTA_INDEX,
  .keypad_row_pins[2].pin = GPIO_PIN2,
  .keypad_row_pins[2].logic = GPIO_LOW,
  .keypad_row_pins[2].direction = GPIO_OUTPUT,
  .keypad_row_pins[3].port = PORTA_INDEX,
  .keypad_row_pins[3].pin = GPIO_PIN3,
  .keypad_row_pins[3].logic = GPIO_LOW,
  .keypad_row_pins[3].direction = GPIO_OUTPUT,
  .keypad_column_pins[0].port = PORTA_INDEX,
  .keypad_column_pins[0].pin = GPIO_PIN4,
  .keypad_column_pins[0].logic = GPIO_LOW,
  .keypad_column_pins[0].direction = GPIO_INPUT,
  .keypad_column_pins[1].port = PORTA_INDEX,
  .keypad_column_pins[1].pin = GPIO_PIN5,
  .keypad_column_pins[1].logic = GPIO_LOW,
  .keypad_column_pins[1].direction = GPIO_INPUT,
  .keypad_column_pins[2].port = PORTA_INDEX,
  .keypad_column_pins[2].pin = GPIO_PIN6,
  .keypad_column_pins[2].logic = GPIO_LOW,
  .keypad_column_pins[2].direction = GPIO_INPUT,
  .keypad_column_pins[3].port = PORTA_INDEX,
  .keypad_column_pins[3].pin = GPIO_PIN7,
  .keypad_column_pins[3].logic = GPIO_LOW,
  .keypad_column_pins[3].direction = GPIO_INPUT
};
//keypad
*/

void ecu_initialize(void){
    Std_ReturnType ret_val = E_NOT_OK;
    //ret_val = keypad_initialize(&keypad1);
}