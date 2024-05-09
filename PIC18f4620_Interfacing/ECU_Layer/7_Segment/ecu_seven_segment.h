/* 
 * File:   ecu_seven_segment.h
 * Author: Abdallah Elnemr
 *
 * Created on August 4, 2023, 2:22 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_seven_segment_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type seg_type;
}segment_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType seven_segment_initialize(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 num);

#endif	/* ECU_SEVEN_SEGMENT_H */

