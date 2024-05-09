/* 
 * File:   ecu_relay.c
 * Author: Abdallah Elnemr
 *
 * Created on August 2, 2023, 1:52 AM
 */

#include "ecu_relay.h"

Std_ReturnType relay_initialize(const relay_t *relay){
    Std_ReturnType ret_val = E_OK;
    if(NULL == relay){
        ret_val = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = relay->relay_port, .pin = relay->relay_pin,
                               .direction = GPIO_OUTPUT, .logic = relay->relay_status};
        gpio_pin_initialize(&pin_obj);
    }
    return ret_val;
}

Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret_val = E_OK;
    if(NULL == relay){
        ret_val = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin,
                               .direction = GPIO_OUTPUT, .logic = relay->relay_status};
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret_val;
}

Std_ReturnType relay_turn_off(const relay_t*relay){
    Std_ReturnType ret_val = E_OK;
    if(NULL == relay){
        ret_val = E_NOT_OK;
    }
    else{
       pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin,
                               .direction = GPIO_OUTPUT, .logic = relay->relay_status};
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret_val;
}
