/* 
 * File:   mcal_ccp1.h
 * Author: Abdallah Elnemr
 * Created on Septemper 1, 2023, 5:43 PM
 */

#ifndef MCAL_CCP1_H
#define	MCAL_CCP1_H

/* ----------------- Includes -----------------*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "mcal_ccp1_cfg.h"

/* ----------------- Macro Declarations -----------------*/
/* CCP1 Module Mode Select  */
#define CCP1_MODULE_DISABLE                 ((uint8)0x00)
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP1_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP1_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP1_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)
#define CCP1_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP1_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP1_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)
#define CCP1_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)
#define CCP1_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)
#define CCP1_PWM_MODE                       ((uint8)0x0C)

/* CCP1 Capture Mode State  */
#define CCP1_CAPTURE_NOT_READY              0X00
#define CCP1_CAPTURE_READY                  0X01

/* CCP1 Compare Mode State  */
#define CCP1_COMPARE_NOT_READY              0X00
#define CCP1_COMPARE_READY                  0X01

/* ----------------- Macro Functions Declarations -----------------*/

/* Set the CCP1 Mode Variant */
#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M = _CONFIG)

/* ----------------- Data Type Declarations -----------------*/

/*
  @Summary      Define the values to select the CCP1 Main mode
*/
typedef enum{
    CCP1_CAPTURE_MODE_SELECTED = 0, /* Select CCP1 Capture Mode */
    CCP1_COMPARE_MODE_SELECTED,     /* Select CCP1 Compare Mode */
    CCP1_PWM_MODE_SELECTED          /* Select CCP1 PWM Mode */
}ccp1_mode_t;

/*
  @Summary      Defines the values to convert from 16bit to two 8 bit and vice versa
  @Description  Used to get two 8 bit values from 16bit also two 8 bit value are combine to get 16bit.
*/
typedef union{
    struct{
        uint8 ccpr1_low;  /* CCPR1 low register */
        uint8 ccpr1_high; /* CCPR1 high register */
    };
    struct{
        uint16 ccpr1_16Bit; /* Read CCPR1 as a 16 Bit value */
    };
}CCP1_REG_T;

/*
  @Summary      CCP1 Module configurations
  @Description  This data type used to describe the module initialization configuration
*/
typedef struct{
    ccp1_mode_t ccp1_mode;      /* CCP main mode */
    uint8 ccp1_mode_variant;    /* CCP selected mode variant */
    pin_config_t ccp_pin;       /* CCP Pin I/O configurations */
#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_PWM_MODE_SELECTED)
    uint32 PWM_Frequency;       /* CCP1 PWM mode frequency */
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
#endif
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP1_InterruptHandler)(void);   /* Call back used for all CCP1 Modes */
    interrupt_priority_cfg priority;    /* Configure the CCP1 mode interrupt */
#endif
}ccp1_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType CCP1_Init(const ccp1_t *_ccp_obj);
Std_ReturnType CCP1_DeInit(const ccp1_t *_ccp_obj);

#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status);
Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *capture_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP1_IsCompareComplete(uint8 *_compare_status);
Std_ReturnType CCP1_Compare_Mode_Set_Value(uint16 compare_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP1_PWM1_Set_Duty(const uint8 _duty);
Std_ReturnType CCP1_PWM1_Start(void);
Std_ReturnType CCP1_PWM1_Stop(void);
#endif

#endif	/* MCAL_CCP1_H */
