/* 
 * File:   ecu_motor.c
 * Author: Abdallah Elnemr
 *
 * Created on August 2, 2023, 7:29 AM
 */

#include "ecu_dc_motor.h"

Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor){
    Std_ReturnType ret_val = E_OK;
    if(NULL == dc_motor){
        ret_val = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        gpio_pin_initialize(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret_val;
}

Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor){
    Std_ReturnType ret_val = E_OK;
    if(NULL == dc_motor){
        ret_val = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret_val;
}

Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor){
    Std_ReturnType ret_val = E_OK;
    if(NULL == dc_motor){
        ret_val = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
    }
    return ret_val;
}

Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor){
    Std_ReturnType ret_val = E_OK;
    if(NULL == dc_motor){
        ret_val = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret_val;
}