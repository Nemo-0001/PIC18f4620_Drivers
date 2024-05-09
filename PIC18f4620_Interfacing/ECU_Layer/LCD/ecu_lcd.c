/* 
 * File:   ecu_lcd.c
 * Author: Abdallah Elnemr
 *
 * Created on August 4, 2023, 5:40 PM
 */

#include "ecu_lcd.h"

static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd, uint8 data_command);
static Std_ReturnType lcd_4bits_send_enable_signal(const lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column);

static Std_ReturnType lcd_8bits_send_enable_signal(const lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column);

Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd){
    Std_ReturnType ret_val = E_OK;
    uint8 l_data_pins_counter = ZERO_INIT;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_initialize(&(lcd->lcd_rs));
        ret_val = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter = ZERO_INIT; l_data_pins_counter < 4; l_data_pins_counter++){
            ret_val = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret_val = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret_val = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret_val = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        ret_val = lcd_4bit_send_command(lcd, LCD_CLEAR);
        ret_val = lcd_4bit_send_command(lcd, LCD_RETURN_HOME);
        ret_val = lcd_4bit_send_command(lcd, LCD_ENTRY_MODE);
        ret_val = lcd_4bit_send_command(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret_val = lcd_4bit_send_command(lcd, LCD_4BIT_MODE_2LINE);
        ret_val = lcd_4bit_send_command(lcd, LCD_DDRAM_START);
    }
    return ret_val;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret_val = E_OK;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret_val = lcd_send_4bits(lcd, command >> 4);
        ret_val = lcd_4bits_send_enable_signal(&lcd);
        ret_val = lcd_send_4bits(lcd, command);
        ret_val = lcd_4bits_send_enable_signal(&lcd);
    }
    return ret_val;
}

Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret_val = E_OK;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret_val = lcd_send_4bits(lcd, data >> 4);
        ret_val = lcd_4bits_send_enable_signal(&lcd);
        ret_val = lcd_send_4bits(lcd, data);
        ret_val = lcd_4bits_send_enable_signal(&lcd);
    }
    return ret_val;
}

Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret_val = E_OK;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = lcd_4bit_set_cursor_pos(lcd, row, column);
        ret_val = lcd_4bit_send_char_data(lcd, data);
    }
    return ret_val;
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret_val = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret_val = E_NOT_OK;
    }
    else{
        while(*str){
           ret_val = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret_val;
}

Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret_val = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = lcd_4bit_set_cursor_pos(lcd, row, column);
        while(*str){
           ret_val = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret_val;
}

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos){
    Std_ReturnType ret_val = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
       ret_val = lcd_4bit_send_command(lcd, (LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = ZERO_INIT; lcd_counter <= 7; ++lcd_counter){
            ret_val = lcd_4bit_send_char_data(lcd, chr[lcd_counter]);
        }
        ret_val = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos); 
    }
    return ret_val;
}


Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd){
    Std_ReturnType ret_val = E_OK;
    uint8 l_data_pins_counter = ZERO_INIT;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_initialize(&(lcd->lcd_rs));
        ret_val = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter = ZERO_INIT; l_data_pins_counter < 8; l_data_pins_counter++){
            ret_val = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret_val = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret_val = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret_val = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        ret_val = lcd_8bit_send_command(lcd, LCD_CLEAR);
        ret_val = lcd_8bit_send_command(lcd, LCD_RETURN_HOME);
        ret_val = lcd_8bit_send_command(lcd, LCD_ENTRY_MODE);
        ret_val = lcd_8bit_send_command(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret_val = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINE);
        ret_val = lcd_8bit_send_command(lcd, LCD_DDRAM_START); //This will display the char at first location on the LCD by default--- +number from start 1 to go to next locations(EX : 0x81)
    }
    return ret_val;
}

Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret_val = E_OK;
    uint8 counter = ZERO_INIT;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(counter = ZERO_INIT; counter < 8; counter++){
            ret_val = gpio_pin_write_logic(&(lcd->lcd_data[counter]), (command >> counter) & (uint8)(0x01));
        }
        ret_val = lcd_8bits_send_enable_signal(&lcd);
    }
    return ret_val;
}

Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret_val = E_OK;
    uint8 counter = ZERO_INIT;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(counter = ZERO_INIT; counter < 8; counter++){
            ret_val = gpio_pin_write_logic(&(lcd->lcd_data[counter]), (data >> counter) & (uint8)(0x01));
        }
        ret_val = lcd_8bits_send_enable_signal(&lcd);
    }
    return ret_val;
}

Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret_val = E_OK;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = lcd_8bit_set_cursor_pos(lcd, row, column);
        ret_val = lcd_8bit_send_char_data(lcd, data);
    }
    return ret_val;
}

Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret_val = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret_val = E_NOT_OK;
    }
    else{
        while(*str){
           ret_val = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret_val;
}

Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret_val = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = lcd_8bit_set_cursor_pos(lcd, row, column);
        while(*str){
           ret_val = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret_val;
}

Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos){
    Std_ReturnType ret_val = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = lcd_8bit_send_command(lcd, (LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = ZERO_INIT; lcd_counter <= 7; ++lcd_counter){
            ret_val = lcd_8bit_send_char_data(lcd, chr[lcd_counter]);
        }
        ret_val = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret_val;
}


Std_ReturnType convert_byte_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret_val = E_OK;
    if(NULL == str){
        ret_val = E_NOT_OK;
    }
    else{
        memset(str, '/o', 4);
        sprintf(str, "%i", value);
    }
    return ret_val;
}

Std_ReturnType convert_short_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret_val = E_OK;
    if(NULL == str){
        ret_val = E_NOT_OK;
    }
    else{
        memset(str, '/o', 6);
        sprintf(str, "%i", value);
    }
    return ret_val;
}

Std_ReturnType convert_int_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret_val = E_OK;
    if(NULL == str){
        ret_val = E_NOT_OK;
    }
    else{
        memset(str, '/o', 11);
        sprintf(str, "%i", value);
    }
    return ret_val;
}

static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd, uint8 data_command){
    Std_ReturnType ret_val = E_OK;
    if(NULL == lcd){
        ret_val = E_NOT_OK;
    }
    else{
        ret_val = gpio_pin_write_logic(&(lcd->lcd_data[0]), (data_command >> 0) & (uint8)(0x01));
        ret_val = gpio_pin_write_logic(&(lcd->lcd_data[1]), (data_command >> 1) & (uint8)(0x01));
        ret_val = gpio_pin_write_logic(&(lcd->lcd_data[2]), (data_command >> 2) & (uint8)(0x01));
        ret_val = gpio_pin_write_logic(&(lcd->lcd_data[3]), (data_command >> 3) & (uint8)(0x01));
    }
    return ret_val;
}

static Std_ReturnType lcd_4bits_send_enable_signal(const lcd_4bit_t *lcd){
    Std_ReturnType ret_val = E_OK;
    ret_val = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_ms(5);
    ret_val = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    return ret_val;
}

static Std_ReturnType lcd_4bit_set_cursor_pos(const lcd_4bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret_val = E_OK;
    column--; //To make user not to take 0 in consideration
    switch(row){
        case ROW1 : ret_val = lcd_4bit_send_command(lcd, (0x80 + column)); break;
        case ROW2 : ret_val = lcd_4bit_send_command(lcd, (0xc0 + column)); break;
        case ROW3 : ret_val = lcd_4bit_send_command(lcd, (0x94 + column)); break;
        case ROW4 : ret_val = lcd_4bit_send_command(lcd, (0xd4 + column)); break;
        default : ;  
    }
    return ret_val;
}

static Std_ReturnType lcd_8bits_send_enable_signal(const lcd_8bit_t *lcd){
    Std_ReturnType ret_val = E_OK;
    ret_val = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_ms(5);
    ret_val = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    return ret_val;
}

static Std_ReturnType lcd_8bit_set_cursor_pos(const lcd_8bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret_val = E_OK;
    column--; //To make user not to take 0 in consideration
    switch(row){
        case ROW1 : ret_val = lcd_8bit_send_command(lcd, (0x80 + column)); break;
        case ROW2 : ret_val = lcd_8bit_send_command(lcd, (0xc0 + column)); break;
        case ROW3 : ret_val = lcd_8bit_send_command(lcd, (0x94 + column)); break;
        case ROW4 : ret_val = lcd_8bit_send_command(lcd, (0xd4 + column)); break;
        default : ;  
    }
    return ret_val;
}

