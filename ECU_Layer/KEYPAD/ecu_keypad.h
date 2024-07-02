/* 
 * File:   ECU_KEYPAD_H
 * Author: Hossam_ElBassuiony
 * Created on July 16, 2023, 9:04 PM
 */
#ifndef ECU_KEYPAD_H
#define ECU_KEYPAD_H

/* Section : Includes */

#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define ECU_KEYPAD_ROWS     4
#define ECU_KEYPAD_COLUMNS  4

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* Section: Function Declarations */

Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);

#endif   /* ECU_KEYPAD_H */
