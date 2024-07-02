/* 
 * File:   application.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on November 28, 2020, 8:43 PM
 */


#include "main.h"


led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

void Int0_ISR(void){
    led_turn_toggle(&led1);
}

interrupt_INTx_t int0_obj = {
  .EXT_InterruptHandler =  Int0_ISR,
  .edge = INTERRUPT_RISING_EDGE,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .source = INTERRUPT_EXTERNAL_INT0,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = GPIO_PIN0,
  .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

int main() {
    Std_ReturnType ret = E_NOK;
    
    application_intialize();
    
    ret = Interrupt_INTx_Init(&int0_obj);
    ret = led_initialize(&led1);
    while(1){
        
    }
    return (EXIT_SUCCESS);
}


void application_intialize(void){
    Std_ReturnType ret = E_NOK;
    ecu_layer_intialize();
}

//*****************************************************************************************************************************************************
//*****************************************************************************************************************************************************


// Timer0

/*

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

volatile uint16 PushButtonCounter = 0;

void Timer0_DefaultInterruptHandler(void){
    
}

timer0_t timer0_counter_obj = {
    .TMR0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .timer0_mode = TIMER0_COUNTER_MODE,
    .timer0_counter_edge = TIMER0_COUNTER_FALLING_EDGE_CFG,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .prescaler_enable = TIMER0_PRESCALER_DISABLE_CFG,
    .timer0_preload_value = 0
};

int main() { 
    Std_ReturnType ret = E_NOK;
    
    application_intialize();
    
    ret = Timer0_Init(&timer0_counter_obj);
    ret = led_initialize(&led1);
    
    while(1){
        ret = Timer0_Read_Value(&timer0_counter_obj, &PushButtonCounter);
        if(PushButtonCounter == 5){
            led_turn_on(&led1);
        }
        else{
            led_turn_off(&led1);
        }
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOK;
    ecu_layer_intialize();
}

*/

//*****************************************************************************************************************************************************
//*****************************************************************************************************************************************************

// Interuppt

/*
void Int0_APP_ISR(void){
    led_turn_toggle(&led1);
    __delay_ms(250);
}
void Int1_APP_ISR(void){
    led_turn_toggle(&led2);
    __delay_ms(250);
}
void Int2_APP_ISR(void){
    led_turn_toggle(&led3);
    __delay_ms(250);
}

interrupt_INTx_t int0_obj = {
  .EXT_InterruptHandler =  Int0_APP_ISR,
  .edge = INTERRUPT_RISING_EDGE,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .source = INTERRUPT_EXTERNAL_INT0,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = GPIO_PIN0,
  .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_INTx_t int1_obj = {
  .EXT_InterruptHandler =  Int1_APP_ISR,
  .edge = INTERRUPT_RISING_EDGE,
  .priority = INTERRUPT_LOW_PRIORITY,
  .source = INTERRUPT_EXTERNAL_INT1,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = GPIO_PIN1,
  .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_INTx_t int2_obj = {
  .EXT_InterruptHandler =  Int2_APP_ISR,
  .edge = INTERRUPT_RISING_EDGE,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .source = INTERRUPT_EXTERNAL_INT2,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = GPIO_PIN2,
  .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

int main() { 
    Std_ReturnType ret = E_NOK;

    application_intialize();
    
    ret = Interrupt_INTx_Init(&int0_obj);
    ret = Interrupt_INTx_Init(&int1_obj);
    ret = Interrupt_INTx_Init(&int2_obj);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    
    while(1){
        
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOK;
    ecu_layer_intialize();
}
*/ 

//*****************************************************************************************************************************************************
//*****************************************************************************************************************************************************

//CHARACTER_LCD

/*
int main(){
    Std_ReturnType ret = E_NOK;
    application_intialize();
    ret = lcd_4bit_send_char_data(&lcd_1, 'A');
    ret = lcd_8bit_send_char_data(&lcd_2, 'A');
    while(1){
        ret = lcd_4bit_send_char_data(&lcd_1, 'A');
    }
    
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOK;
    ecu_layer_intialize();
}
*/

//*****************************************************************************************************************************************************
//*****************************************************************************************************************************************************

//KEYPAD

/*

uint8 keypad_value = ZERO_INIT;

int main(){
    Std_ReturnType ret = E_NOK;
    application_intialize();
    
    while(1){
        ret = keypad_get_value(&keypad1 , &keypad_value);
    }
    
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOK;
    ecu_layer_intialize();
    
}
*/

//*****************************************************************************************************************************************************
//*****************************************************************************************************************************************************

//7_SEGMANT

/*
pin_config_t seg1_enable = {
    .port = PORTD_INDEX,
    .pin  = GPIO_PIN0,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t seg2_enable = {
    .port = PORTD_INDEX,
    .pin  = GPIO_PIN1,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

segment_t seg1 = {
    .segmant_type             = SEGMANT_COMMON_ANODE,
    .segment_pin[0].port      = PORTC_INDEX,
    .segment_pin[0].pin       = GPIO_PIN0,
    .segment_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[0].logic     = GPIO_LOW,
    .segment_pin[1].port      = PORTC_INDEX,
    .segment_pin[1].pin       = GPIO_PIN1,
    .segment_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[1].logic     = GPIO_LOW,
    .segment_pin[2].port      = PORTC_INDEX,
    .segment_pin[2].pin       = GPIO_PIN2,
    .segment_pin[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[2].logic     = GPIO_LOW,
    .segment_pin[3].port      = PORTC_INDEX,
    .segment_pin[3].pin       = GPIO_PIN3,
    .segment_pin[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[3].logic     = GPIO_LOW
};

uint8 number = 45;
int main(){
    Std_ReturnType ret = E_NOK;
    application_intialize();
    
    while(1){
        ret = seven_segmant_write_number(&seg1, (uint8)(number/10));
        ret = gpio_pin_write_logic(&seg1_enable, GPIO_HIGH);
        __delay_ms(5);
        ret = gpio_pin_write_logic(&seg1_enable, GPIO_LOW);
        
        ret = seven_segmant_write_number(&seg1, (uint8)(number%10));
        ret = gpio_pin_write_logic(&seg2_enable, GPIO_HIGH);
        __delay_ms(5);
        ret = gpio_pin_write_logic(&seg2_enable, GPIO_LOW);
    }
    return (EXIT_SUCCESS);
}



void application_intialize(void){
    Std_ReturnType ret = E_NOK;
    ret = seven_segmant_initialize(&seg1);
    ret = gpio_pin_intialize(&seg1_enable);
    ret = gpio_pin_intialize(&seg2_enable);
}
*/

//*****************************************************************************************************************************************************
//*****************************************************************************************************************************************************

//DC_MOTOR

/*

dc_motor_t dc_motor_1 = {
    .dc_motor_pin[0].port = PORTC_INDEX ,
    .dc_motor_pin[0].pin = GPIO_PIN0,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].port = PORTC_INDEX ,
    .dc_motor_pin[1].pin = GPIO_PIN1,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT
};

dc_motor_t dc_motor_2 = {
    .dc_motor_pin[0].port = PORTC_INDEX ,
    .dc_motor_pin[0].pin = GPIO_PIN2,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].port = PORTC_INDEX ,
    .dc_motor_pin[1].pin = GPIO_PIN3,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT
};
int main(){
    Std_ReturnType ret = E_NOK;
    application_intialize();
    while(1){
        ret = dc_motor_move_right(&dc_motor_1);
        ret = dc_motor_move_right(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_left(&dc_motor_1);
        ret = dc_motor_move_left(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_stop(&dc_motor_1);
        ret = dc_motor_stop(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_right(&dc_motor_1);
        ret = dc_motor_move_left(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_left(&dc_motor_1);
        ret = dc_motor_move_right(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_stop(&dc_motor_1);
        ret = dc_motor_stop(&dc_motor_2);
        __delay_ms(3000);
        
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOK;
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);

}
*/

//*****************************************************************************************************************************************************
//*****************************************************************************************************************************************************

//RELAY

/*
relay_t relay_1 = {
    .relay_port    = PORTC_INDEX      ,
    .relay_pin     = GPIO_PIN0        ,
    .relay_status  = REALY_OFF_STATUS ,
};


int main() {
    Std_ReturnType ret = E_NOK;
    application_intialize();
    while(1){
        ret = relay_turn_on(&relay_1);
        __delay_ms(5000);
        ret = relay_turn_off(&relay_1);
        __delay_ms(5000);
    }
 * return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOK;
    relay_initialize(&relay_1);
}
*/

//*****************************************************************************************************************************************************
//*****************************************************************************************************************************************************

//PUSH_BUTTON

/*

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};

button_t btn_high = {
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn_low = {
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN0,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_HIGH,
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_state = BUTTON_RELEASED
};

button_state_t btn_high_status = BUTTON_RELEASED;
button_state_t btn_low_status  = BUTTON_RELEASED;

int main() { 
    Std_ReturnType ret = E_NOK;
    
    application_intialize();
    
    ret = button_initialize(&btn_high);
    ret = button_initialize(&btn_low);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);

    while(1){
        ret = button_read_state(&btn_high, &btn_high_status);
        ret = button_read_state(&btn_low, &btn_low_status);
        
        if(BUTTON_PRESSED == btn_high_status){
            led_turn_on(&led1);
        }
        else{
            
        }
        
        if(BUTTON_PRESSED == btn_low_status){
            led_turn_off(&led1);
        }
        else{
            
        }
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOK;
}
 */

