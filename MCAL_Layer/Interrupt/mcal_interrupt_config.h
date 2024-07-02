/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef MCAL_INTERRUPT_CONFIG
#define	MCAL_INTERRUPT_CONFIG

/* Section : Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section: Macro Declarations */

#define INTERRUPT_ENABLE           1
#define INTERRUPT_DISABLE          0
#define INTERRUPT_OCCUR            1
#define INTERRUPT_NOT_OCCUR        0
#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_DISABLE 0

/* Section: Macro Functions Declarations */

#if INTERRUPT_PRIORITY_level_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This macro will enable priority level on interrupt */
#define INTERRUPT_PriorityLevelIsEnable()      (RCONbits.IPEN = 1)
/* This macro will disable priority level on interrupt */
#define INTERRUPT_PriorityLevelIsDisable()     (RCONbits.IPEN = 0)


/* This macro will enable high priority global interrupt */
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)
/* This macro will disable high priority global interrupt */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)


/* This macro will enable low priority global interrupt */
#define INTERRUPT_GlobalInterruptLowEnable()   (INTCONbits.GIEL = 1)
/* This macro will disable low priority global interrupt */
#define INTERRUPT_GlobalInterruptLowDisable()  (INTCONbits.GIEL = 0)

#else

/* This macro will enable global interrupt */
#define INTERRUPT_GlobalInterruptEnable()      (INTCONbits.GIE = 1)
/* This macro will disable global interrupt */
#define INTERRUPT_GlobalInterruptDisable()     (INTCONbits.GIE = 0)


/* This macro will enable peripheral interrupt */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/* This macro will disable peripheral interrupt */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#endif

/* Section: Data Type Declarations */

typedef enum{
    
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
    
}interrupt_priority_cfg;

/* Section: Function Declarations */


#endif	/* MCAL_INTERRUPT_CONFIG */