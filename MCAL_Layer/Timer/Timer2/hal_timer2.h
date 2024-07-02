/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H


/* ----------------------------------- Section : Includes ----------------------------------- */

#include "../../GPIO/hal_gpio.h"
#include "../../mcal_std_types.h"
#include "../../Interrupt/mcal_internal_interrupt.h"
#include "../../Interrupt/mcal_interrupt_manager.h"

/* ----------------------------------- Section: Macro Declarations ----------------------------------- */

/* ----------------------------------- Section: Macro Functions Declarations ----------------------------------- */

/* Enable or Disable Timer1 Module */
#define TIMER2_MODULE_ENABLE()              (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()             (T2CONbits.TMR2ON = 0)

/* Timer2 Input Clock Post-scaler */
#define TIMER2_PRESCALER_SELECT(_PRESCALER_) (T2CONbits.T2CKPS = _PRESCALER_)

/* Timer2 Input Clock Post-scaler */
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_) (T2CONbits.TOUTPS = _POSTSCALER_)

/* ----------------------------------- Section: Data Type Declarations ----------------------------------- */


/* Timer2 Input Clock Post-scaler */
typedef enum{
    TIMER2_POSTSCALER_DIV_BY_1 = 0,
    TIMER2_POSTSCALER_DIV_BY_2 ,
    TIMER2_POSTSCALER_DIV_BY_3 ,
    TIMER2_POSTSCALER_DIV_BY_4 ,
    TIMER2_POSTSCALER_DIV_BY_5 ,
    TIMER2_POSTSCALER_DIV_BY_6 ,
    TIMER2_POSTSCALER_DIV_BY_7 ,
    TIMER2_POSTSCALER_DIV_BY_8 ,
    TIMER2_POSTSCALER_DIV_BY_9 ,
    TIMER2_POSTSCALER_DIV_BY_10 ,
    TIMER2_POSTSCALER_DIV_BY_11 ,
    TIMER2_POSTSCALER_DIV_BY_12 ,
    TIMER2_POSTSCALER_DIV_BY_13 ,
    TIMER2_POSTSCALER_DIV_BY_14 ,
    TIMER2_POSTSCALER_DIV_BY_15 ,
    TIMER2_POSTSCALER_DIV_BY_16 ,
}timer2_postscaler_select_t;


/* Timer2 Input Clock Pre-scaler */
typedef enum{
    TIMER2_PRESCALER_DIV_BY_1 = 0,
    TIMER2_PRESCALER_DIV_BY_4 ,
    TIMER2_PRESCALER_DIV_BY_16
}timer2_prescaler_select_t;



typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TMR2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8                      timer2_preload_value   ;
    uint8                      timer2_reserved        ;
    timer2_postscaler_select_t timer2_postscaler_value;
    timer2_prescaler_select_t  timer2_prescaler_value ;
}timer2_t;

/* -----------------------------------Section: Software Interfaces Declarations ----------------------------------- */

Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value);


//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



#endif	/* HAL_TIMER2_H */

