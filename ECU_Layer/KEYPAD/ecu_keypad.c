/* 
 * File:   ECU_KEYPAD_C
 * Author: Hossam_ElBassuiony
 * Created on July 16, 2023, 9:04 PM
 */

#include "ecu_keypad.h"

static const uint8 btn_value[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                           {'7', '8', '9', '/'},
                                                           {'4', '5', '6', '*'},
                                                           {'1', '2', '3', '-'},
                                                           {'#', '0', '=', '+'},
                                                           
                                                       };

Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT;
    
    if(NULL == _keypad_obj){
        ret = E_NOK;
    }
    else{
        for(rows_counter = ZERO_INIT; rows_counter < ECU_KEYPAD_ROWS; rows_counter++){
            ret = gpio_pin_intialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(columns_counter = ZERO_INIT; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++){
            ret = gpio_pin_direction_intialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));
        }
    }
}
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    Std_ReturnType ret = E_OK;
    uint8 l_rows_counter = ZERO_INIT, l_columns_counter = ZERO_INIT, l_counter = ZERO_INIT;
    uint8 column_logic = ZERO_INIT;
    if((NULL == _keypad_obj) || (NULL == value)){
        ret = E_NOK;
    }
    else{
        for(l_rows_counter = ZERO_INIT; l_rows_counter < ECU_KEYPAD_ROWS; l_rows_counter++){
            for(l_counter = ZERO_INIT; l_counter < ECU_KEYPAD_ROWS; l_counter++){
                gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOW);
            }
            gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]), GPIO_HIGH);
            for(l_columns_counter = ZERO_INIT; l_columns_counter < ECU_KEYPAD_COLUMNS; l_columns_counter++){
            ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]), &column_logic);
            if(GPIO_HIGH == column_logic){
                *value = btn_value[l_rows_counter][l_columns_counter];
            }
        }
        }
    }
}