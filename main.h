/* 
 * File:   application.h
 * Author: Hossam_ElBassuiony
 * Created on July 16, 2023, 9:04 PM
 */
#ifndef MAIN_H

#define MAIN_H

/* Section : Includes */

#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/PUSH_BUTTON/ecu_button.h"
#include "MCAL_Layer/Timer/Timer0/hal_timer0.h"
#include "MCAL_Layer/Timer/Timer1/hal_timer1.h"
#include "MCAL_Layer/Timer/Timer2/hal_timer2.h"
#include "MCAL_Layer/Timer/Timer3/hal_timer3.h"
#include "MCAL_Layer/CCP_1/hal_ccp1.h"
#include "MCAL_Layer/uart/hal_uart.h"
#include "MCAL_Layer/I2C/hal_i2c.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

// extern keypad_t keypad1;
extern chr_lcd_4bit_t lcd_1;
extern chr_lcd_8bit_t lcd_2;
extern led_t led1;
extern led_t led2;
extern led_t led3;


/* Section: Function Declarations */
void application_intialize(void);

#endif  /* MAIN_H */