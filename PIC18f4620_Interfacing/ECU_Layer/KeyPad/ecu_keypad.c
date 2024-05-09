/* 
 * File:   ecu_keypad.c
 * Author: Abdallah Elnemr
 *
 * Created on August 4, 2023, 3:41 PM
 */

#include "ecu_keypad.h"

static const uint8 btn_values[KEYPAD_ROWS ][KEYPAD_COLUMNS] = {
                                                                {'7', '8', '9', '/'},
                                                                {'4', '5', '6', '*'},
                                                                {'1', '2', '3', '-'},
                                                                {'#', '0', '=', '+'},
};

Std_ReturnType keypad_initialize(const keypad_t *keypad){
    Std_ReturnType ret_val = E_OK;
    uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT;
    if(NULL == keypad){
        ret_val = E_NOT_OK;
    }
    else{
        for(rows_counter = ZERO_INIT; rows_counter < KEYPAD_ROWS; rows_counter++){
              ret_val = gpio_pin_initialize(&(keypad->keypad_row_pins[rows_counter]));
        }
        for(columns_counter = ZERO_INIT; columns_counter < KEYPAD_ROWS; columns_counter++){
              ret_val = gpio_pin_direction_initialize(&(keypad->keypad_column_pins[columns_counter]));
        }
    }
    return ret_val;
}

Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value){
    Std_ReturnType ret_val = E_OK;
    *value = KEYPAD_NOT_PRESSED;
    uint8 l_rows_counter = ZERO_INIT, l_columns_counter = ZERO_INIT, l_counter = ZERO_INIT;
    uint8 column_logic = ZERO_INIT;
    if((NULL == keypad) || (NULL == value)){
        ret_val = E_NOT_OK;
    }
    else{
         for(l_rows_counter = ZERO_INIT; l_rows_counter < KEYPAD_ROWS; l_rows_counter++){
              for(l_counter = ZERO_INIT; l_counter < KEYPAD_ROWS; l_counter++){
                  ret_val = gpio_pin_write_logic(&(keypad->keypad_row_pins[l_counter]), GPIO_LOW);
              }
              ret_val = gpio_pin_write_logic(&(keypad->keypad_row_pins[l_rows_counter]), GPIO_HIGH);
              __delay_ms(10);
              for(l_columns_counter = ZERO_INIT; l_columns_counter < KEYPAD_COLUMNS; l_columns_counter++){
                  ret_val = gpio_pin_read_logic(&(keypad->keypad_column_pins[l_columns_counter]), &column_logic);
                  if(GPIO_HIGH == column_logic){
                      *value = btn_values[l_rows_counter][l_columns_counter];
                  }
              }
         }
    }
    return ret_val;
}
