/* 
 * File:   ecu_seven_segment.c
 * Author: Abdallah Elnemr
 *
 * Created on August 4, 2023, 2:23 PM
 */

#include "ecu_seven_segment.h"

Std_ReturnType seven_segment_initialize(const segment_t *seg){
    Std_ReturnType ret_val = E_OK;
    if(NULL == seg){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret_val = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret_val = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret_val = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
    }
    return ret_val;
}

Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 num){
    Std_ReturnType ret_val = E_OK;
    if((NULL == seg) && (num > 9)){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]), (num) & 0x01);
        ret_val = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), (num >> 1) & 0x01);
        ret_val = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), (num >> 2) & 0x01);
        ret_val = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), (num >> 3) & 0x01);
    }
    return ret_val;
}
