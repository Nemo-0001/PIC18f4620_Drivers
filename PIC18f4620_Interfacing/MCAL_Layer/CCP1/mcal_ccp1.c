/* 
 * File:   mcal_ccp1.h
 * Author: Abdallah Elnemr
 * Created on Septemper 1, 2023, 5:43 PM
 */

/* ----------------- Includes -----------------*/
#include "mcal_ccp1.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_InterruptHandler)(void) = NULL;
#endif

Std_ReturnType CCP1_Init(const ccp1_t *_ccp_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* CCP1 Module Disable */
        CCP1_SET_MODE(CCP1_MODULE_DISABLE);
        
        /* CCP1 Module Capture Mode Initialization */
        if(CCP1_CAPTURE_MODE_SELECTED == _ccp_obj->ccp1_mode){
            /* CCP1 Module Capture variants Mode Initialization */
            switch(_ccp_obj->ccp1_mode_variant){
                case CCP1_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_FALLING_EDGE); break;
                case CCP1_CAPTURE_MODE_1_RISING_EDGE  : CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_RISING_EDGE);  break;
                case CCP1_CAPTURE_MODE_4_RISING_EDGE  : CCP1_SET_MODE(CCP1_CAPTURE_MODE_4_RISING_EDGE);  break;
                case CCP1_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP1_CAPTURE_MODE_16_RISING_EDGE); break;
                default : ret = E_NOT_OK; /* Not supported variant */
            }
        }
        /* CCP1 Module Compare Mode Initialization */
        else if(CCP1_COMPARE_MODE_SELECTED == _ccp_obj->ccp1_mode){
            /* CCP1 Module Compare variants Mode Initialization */
            switch(_ccp_obj->ccp1_mode_variant){
                case CCP1_COMPARE_MODE_SET_PIN_LOW      : CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_LOW);      break;
                case CCP1_COMPARE_MODE_SET_PIN_HIGH     : CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_HIGH);     break;
                case CCP1_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP1_SET_MODE(CCP1_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
                case CCP1_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_SW_INTERRUPT); break;
                case CCP1_COMPARE_MODE_GEN_EVENT        : CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_EVENT);        break;
                default : ret = E_NOT_OK; /* Not supported variant */
            }
        }
        /* CCP1 Module PWM Mode Initialization */
        else if(CCP1_PWM_MODE_SELECTED == _ccp_obj->ccp1_mode){
#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_PWM_MODE_SELECTED)
            if(CCP1_PWM_MODE == _ccp_obj->ccp1_mode_variant){
                CCP1_SET_MODE(CCP1_PWM_MODE);
            }
            else {/* Nothing */}
            /* PWM Frequency Initialization */
            PR2 = (uint8)((_XTAL_FREQ / (_ccp_obj->PWM_Frequency * 4.0 * _ccp_obj->timer2_prescaler_value * 
                    _ccp_obj->timer2_postscaler_value)) - 1);
#endif
        }
        else {/* Nothing */}
        
        /* PIN Configurations */
        ret = gpio_pin_initialize(&(_ccp_obj->ccp_pin));
        
/* Interrupt Configurations */ 
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP1_InterruptEnable();
        CCP1_InterruptFlagClear();
        CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->priority){
            /* Enables all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->priority){
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            CCP1_LowPrioritySet();
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif          
#endif        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType CCP1_DeInit(const ccp1_t *_ccp_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* CCP1 Module Disable */
        CCP1_SET_MODE(CCP1_MODULE_DISABLE);
/* Interrupt Configurations */ 
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP1_InterruptDisable();
#endif        
        ret = E_OK;
    }
    return ret;
}

#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _capture_status){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status = CCP1_CAPTURE_READY;
            CCP1_InterruptFlagClear();
        }
        else{
            *_capture_status = CCP1_CAPTURE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *capture_value){
    Std_ReturnType ret = E_NOT_OK;
    CCP1_REG_T capture_temp_value = {.ccpr1_low = 0, .ccpr1_high = 0};
    if(NULL == capture_value){
        ret = E_NOT_OK;
    }
    else{
        /* Copy captured value */
        capture_temp_value.ccpr1_low = CCPR1L;
        capture_temp_value.ccpr1_high = CCPR1H;
        /* Write the 16-bit capture value */
        *capture_value = capture_temp_value.ccpr1_16Bit;
        ret = E_OK;
    }
    return ret;
}
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP1_IsCompareComplete(uint8 *_compare_status){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _compare_status){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status = CCP1_COMPARE_READY;
            CCP1_InterruptFlagClear();
        }
        else{
            *_compare_status = CCP1_COMPARE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType CCP1_Compare_Mode_Set_Value(uint16 compare_value){
    Std_ReturnType ret = E_NOT_OK;
    CCP1_REG_T capture_temp_value = {.ccpr1_low = 0, .ccpr1_high = 0};
    /* Copy compared value */
    capture_temp_value.ccpr1_16Bit = compare_value;
    CCPR1L = capture_temp_value.ccpr1_low;
    CCPR1H = capture_temp_value.ccpr1_high;
    ret = E_OK;
    return ret;
}
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP1_PWM1_Set_Duty(const uint8 _duty){
    Std_ReturnType ret = E_NOT_OK;
    uint16 l_duty_temp = 0;
    l_duty_temp = (uint16)(4 * (PR2 + 1) * (_duty / 100.0));
    
    ret = E_OK;
    return ret;
}

Std_ReturnType CCP1_PWM1_Start(void){
    Std_ReturnType ret = E_NOT_OK;
    /* Code */
    ret = E_OK;
    return ret;
}

Std_ReturnType CCP1_PWM1_Stop(void){
    Std_ReturnType ret = E_NOT_OK;
    /* Code */
    ret = E_OK;
    return ret;
}
#endif
