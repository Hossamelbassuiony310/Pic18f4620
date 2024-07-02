/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "mcal_external_interrupt.h"


/* Pointer to function to hold the callbaks for INTx */
InterruptHandler INT0_InterruptHandler = NULL;
InterruptHandler INT1_InterruptHandler = NULL;
InterruptHandler INT2_InterruptHandler = NULL;
/* Pointer to function to hold the callbaks for RBx */
InterruptHandler RB4_InterruptHandler_HIGH = NULL;
InterruptHandler RB4_InterruptHandler_LOW = NULL;
InterruptHandler RB5_InterruptHandler_HIGH = NULL;
InterruptHandler RB5_InterruptHandler_LOW = NULL;
InterruptHandler RB6_InterruptHandler_HIGH = NULL;
InterruptHandler RB6_InterruptHandler_LOW = NULL;
InterruptHandler RB7_InterruptHandler_HIGH = NULL;
InterruptHandler RB7_InterruptHandler_LOW = NULL;


static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);


static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);


static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);


void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);


/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        /* Disable the External interrupt */
        
        ret = Interrupt_INTx_Disable(int_obj);
        
        /* Clear Interrupt Flag : External interrupt did not occur */
        
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        
        /* Configure External interrupt edge */
        
        ret |= Interrupt_INTx_Edge_Init(int_obj);
        
        /* Configure External interrupt Priority */
        #if INTERRUPT_PRIORITY_level_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret |= Interrupt_INTx_Priority_Init(&int_obj);
        #endif
        /* Configure External interrupt I/O pin */
        
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        
        /* Configure Default interrupt CallBack */
        
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
        
        /* Enable the External interrupt */
        
        ret |= Interrupt_INTx_Enable(int_obj);
        
    }
    return ret;
}


/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        
        /* Disable the External interrupt */
        Interrupt_RBx_Disable(int_obj);
        
        /* Clear Interrupt Flag : External interrupt did not occur */
        EXT_RBx_InterruptFlagClear();
//********************************************************************************************************************************
#if INTERRUPT_PRIORITY_level_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelIsEnable();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            /* This macro will enable low priority global interrupt */
            INTERRUPT_GlobalInterruptLowEnable();
            /* This routine set the RBx External Interrupt Priority to be Low priority */
            EXT_RBx_Priority_Low();
        }
        else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){
            /* This macro will enable high priority global interrupt */
            INTERRUPT_GlobalInterruptHighEnable();
            /* This routine set the RBx External Interrupt Priority to be High priority */
            EXT_RBx_Priority_High();
        }
        else{ /*NoThing*/}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
//********************************************************************************************************************************
        
        /* Initialize the RBx pin to be input */
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
        
        /* Initialize the call back function */
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4 :
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN5 :
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN6 :
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;    
            case GPIO_PIN7 :
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;  
            default :
                ret = E_NOK;
        }
        
        /* Enable the External interrupt */
        EXT_RBx_InterruptEnable();
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        /* Disable the External interrupt */
        ret = Interrupt_RBx_Disable(int_obj);
        /* Clear Interrupt Flag : External interrupt did not occur */
        EXT_RBx_InterruptFlagClear();
    }
    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
#if INTERRUPT_PRIORITY_level_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
#if INTERRUPT_PRIORITY_level_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelIsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{ /*NoThing*/}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
#if INTERRUPT_PRIORITY_level_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelIsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{ /*NoThing*/}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable(); 
                ret = E_OK; 
                break;
            default : ret = E_NOK;
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_InterruptDisable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptDisable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptDisable(); 
                ret = E_OK; 
                break;
            default : ret = E_NOK;
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */

#if INTERRUPT_PRIORITY_level_ENABLE==INTERRUPT_FEATURE_ENABLE

static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if( int_obj == NULL){
        ret = E_NOK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT1_HighPrioritySet(); }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT1_LowPrioritySet(); }
                else{ /*NoThing*/}
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT2_LowPrioritySet(); }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT2_HighPrioritySet(); }
                else{ /*NoThing*/}
                ret = E_OK;
                break;
            default : ret = E_NOK;    
        }
    }
    return ret;
}

#endif

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                if(INTERRUPT_FAILING_EDGE == int_obj->edge){ EXT_INT0_FallingEdgeSet(); }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT0_RisingEdgeSet(); }
                else{ /*NoThing*/}
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                if(INTERRUPT_FAILING_EDGE == int_obj->edge){ EXT_INT1_FallingEdgeSet(); }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT1_RisingEdgeSet(); }
                else{ /*NoThing*/}
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_FAILING_EDGE == int_obj->edge){ EXT_INT2_FallingEdgeSet(); }
                else if (INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT2_RisingEdgeSet(); }
                else{ /*NoThing*/}
                ret = E_OK;
                break;
            default : ret = E_NOK; 
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}


static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_InterruptFlagClear(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                 EXT_INT1_InterruptFlagClear(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptFlagClear(); 
                ret = E_OK; 
                break;
            default : ret = E_NOK;
        }
        ret = E_OK;
    }
    return ret;
}


//--------------------------------------------------------------------------------------------------------------------------------------------

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        
        }
    return ret;
}


/**
 * 
 * @param int_obj
 * @return 
 */

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        /* Disable the External interrupt */
        EXT_RBx_InterruptDisable();
        ret = E_OK;
        }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        
        }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        
        }
    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOK;
    if(NULL == InterruptHandler){
        ret = E_NOK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOK;
    if(NULL == InterruptHandler){
        ret = E_NOK;
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOK;
    if(NULL == InterruptHandler){
        ret = E_NOK;
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOK;
    if(NULL == int_obj){
        ret = E_NOK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOK;
        }
        ret = E_OK;
    }
    return ret;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

/**
 * 
 */
void INT0_ISR(void){
    /* the INT0 external interrupt occurred (must be cleared in software) */
    
    EXT_INT0_InterruptFlagClear();
    
    /* Code */
    
    /* Callback function gets called rvery time this ISR executes */
    
    if( INT0_InterruptHandler ){ INT0_InterruptHandler(); }
    
}

/**
 * 
 */
void INT1_ISR(void){
    /* the INT1 external interrupt occurred (must be cleared in software) */
    
    EXT_INT1_InterruptFlagClear();
    
    /* Code */
    
    /* Callback function gets called rvery time this ISR executes */
    
    if( INT1_InterruptHandler ){ INT1_InterruptHandler(); }
    
}

/**
 * 
 */
void INT2_ISR(void){
    /* the INT2 external interrupt occurred (must be cleared in software) */
    
    EXT_INT2_InterruptFlagClear();
    
    /* Code */
    
    /* Callback function gets called rvery time this ISR executes */
    
    if( INT2_InterruptHandler ){ INT2_InterruptHandler(); }
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------

/**
 * 
 * @param RB4_Source
 */
void RB4_ISR(uint8 RB4_Source){
    /* the RB4 external interrupt occurred (must be cleared in software) */
    
    EXT_RBx_InterruptFlagClear();
    
    /* Code */
    
    /* Callback function gets called rvery time this ISR executes */
    if( 0 == RB4_Source ){
        if( RB4_InterruptHandler_HIGH ){ RB4_InterruptHandler_HIGH(); }
        else{ /* NoThing */ }
    }
    else if (1 == RB4_Source){
        if( RB4_InterruptHandler_LOW ){ RB4_InterruptHandler_LOW(); }
        else{ /* NoThing */ }
    }
    else{ /* NoThing */ }
}


/**
 * 
 * @param RB5_Source
 */
void RB5_ISR(uint8 RB5_Source){
    /* the RB4 external interrupt occurred (must be cleared in software) */
    
    EXT_RBx_InterruptFlagClear();
    
    /* Code */
    
    /* Callback function gets called rvery time this ISR executes */
    if( 0 == RB5_Source ){
        if( RB5_InterruptHandler_HIGH ){ RB5_InterruptHandler_HIGH(); }
        else{ /* NoThing */ }
    }
    else if (1 == RB5_Source){
        if( RB5_InterruptHandler_LOW ){ RB5_InterruptHandler_LOW(); }
        else{ /* NoThing */ }
    }
    else{ /* NoThing */ }
}


/**
 * 
 * @param RB6_Source
 */
void RB6_ISR(uint8 RB6_Source){
    /* the RB4 external interrupt occurred (must be cleared in software) */
    
    EXT_RBx_InterruptFlagClear();
    
    /* Code */
    
    /* Callback function gets called rvery time this ISR executes */
    if( 0 == RB6_Source ){
        if( RB6_InterruptHandler_HIGH ){ RB6_InterruptHandler_HIGH(); }
        else{ /* NoThing */ }
    }
    else if (1 == RB6_Source){
        if( RB6_InterruptHandler_LOW ){ RB6_InterruptHandler_LOW(); }
        else{ /* NoThing */ }
    }
    else{ /* NoThing */ }
}


/**
 * 
 * @param RB7_Source
 */
void RB7_ISR(uint8 RB7_Source){
    /* the RB4 external interrupt occurred (must be cleared in software) */
    
    EXT_RBx_InterruptFlagClear();
    
    /* Code */
    
    /* Callback function gets called rvery time this ISR executes */
    if( 0 == RB7_Source ){
        if( RB7_InterruptHandler_HIGH ){ RB7_InterruptHandler_HIGH(); }
        else{ /* NoThing */ }
    }
    else if (1 == RB7_Source){
        if( RB7_InterruptHandler_LOW ){ RB7_InterruptHandler_LOW(); }
        else{ /* NoThing */ }
    }
    else{ /* NoThing */ }
}

