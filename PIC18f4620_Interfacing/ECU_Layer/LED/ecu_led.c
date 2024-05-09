/* 
 * File:   ecu_led.c
 * Author: Abdallah Elnemr
 *
 * Created on July 25, 2023, 1:55 PM
 */


#include "ecu_led.h"

Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == led){
        ret_val = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin,
                               .direction = GPIO_OUTPUT, .logic = led->led_status};
        gpio_pin_initialize(&pin_obj);
    }
    
    return ret_val;
}

Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == led){
        ret_val = E_NOT_OK;
    }
    else{
       pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin,
                               .direction = GPIO_OUTPUT, .logic = led->led_status}; 
       gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    
    return ret_val;
}

Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == led){
        ret_val = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin,
                               .direction = GPIO_OUTPUT, .logic = led->led_status};
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    
    return ret_val;
}

Std_ReturnType led_toggle(const led_t *led){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == led){
        ret_val = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin,
                               .direction = GPIO_OUTPUT, .logic = led->led_status};
        gpio_pin_toggle_logic(&pin_obj);
    }
    
    return ret_val;
}