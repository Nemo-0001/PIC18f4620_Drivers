/* 
 * File:   mcal_gpio.c
 * Author: Abdallah Elnemr
 *
 * Created on July 25, 2023, 1:23 PM
 */

#include "mcal_gpio.h"

volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};


#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
      switch(_pin_config->direction){
            case GPIO_OUTPUT :
                CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_INPUT :
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            default :
                ret_val = E_NOT_OK;
        }  
    }
    
    return ret_val;
}
#endif

#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == _pin_config || NULL == direction || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
        *direction = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret_val;
}
#endif

#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
        switch( logic){
            case GPIO_LOW :
                CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_HIGH :
                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            default :
                ret_val = E_NOT_OK;
        }
    }
    
    return ret_val;
}
#endif

#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret_val;
}
#endif

#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret_val;
}
#endif

#if GPIO_PORT_PIN_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config){
    Std_ReturnType ret_val = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_direction_initialize(_pin_config);
        ret_val = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    
    return ret_val;
}
#endif



#if GPIO_PORT_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction){
    Std_ReturnType ret_val = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction;
    }
    return ret_val;
}
#endif

#if GPIO_PORT_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction){
    Std_ReturnType ret_val = E_OK;
    
    if((NULL == direction) && (port > PORT_MAX_NUMBER-1)){
        ret_val = E_NOT_OK;
    }
    else{
        *direction = *tris_registers[port];
    }
    
    return ret_val;
}
#endif

#if GPIO_PORT_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic){
    Std_ReturnType ret_val = E_OK;
    
    if(port > PORT_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic;
    }
    
    return ret_val;
}
#endif

#if GPIO_PORT_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic){
    Std_ReturnType ret_val = E_OK;
    
    if((NULL == logic) && (port > PORT_MAX_NUMBER-1)){
        ret_val = E_NOT_OK;
    }
    else{
        *logic = *lat_registers[port];
    }
    
    return ret_val;
}
#endif

#if GPIO_PORT_CONFIGRATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
    Std_ReturnType ret_val = E_OK;
    
    if(port > PORT_MAX_NUMBER-1){
        ret_val = E_NOT_OK;
    }
    else{
        *lat_registers[port] ^= PORTA_MASK;
    }
    
    return ret_val;
}
#endif
