/* 
 * File:   ECU_RELAY_C
 * Author: Hossam_ElBassuiony
 * Created on July 16, 2023, 9:04 PM
 */

#include "ecu_dc_motor.h"

static pin_config_t motor_pin1;
static pin_config_t motor_pin2;

Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
            Std_ReturnType ret = E_NOK;
    }
    else{  
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[0]));
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[1]));
    }
}
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
            Std_ReturnType ret = E_NOK;
    }
    else{
        
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);
        
        };
        
}
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
            Std_ReturnType ret = E_NOK;
    }
    else{
                
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_HIGH);
        
    }
}
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
            Std_ReturnType ret = E_NOK;
    }
    else{
                
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);
        
    }
}

