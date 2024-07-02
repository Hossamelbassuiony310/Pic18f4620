/* 
 * File:   ECU_RELAY_C
 * Author: Hossam_ElBassuiony
 * Created on July 16, 2023, 9:04 PM
 */

#include "ecu_seven_seg.h"



Std_ReturnType seven_segmant_initialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
    if(NULL == seg){
        ret = E_NOK;
    }
    else{
        ret = gpio_pin_intialize(&(seg->segment_pin[SEGMENT_PIN_0]));
        ret = gpio_pin_intialize(&(seg->segment_pin[SEGMENT_PIN_1]));
        ret = gpio_pin_intialize(&(seg->segment_pin[SEGMENT_PIN_2]));
        ret = gpio_pin_intialize(&(seg->segment_pin[SEGMENT_PIN_3]));
    }
}


Std_ReturnType seven_segmant_write_number(const segment_t *seg, uint8 number){
    Std_ReturnType ret = E_OK;
    if((NULL == seg) && (number > 9)){
        ret = E_NOK;
    }
    else{
        ret = gpio_pin_write_logic(&(seg->segment_pin[SEGMENT_PIN_0]), (number & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pin[SEGMENT_PIN_1]), ((number>>1) & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pin[SEGMENT_PIN_2]), ((number>>2) & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pin[SEGMENT_PIN_3]), ((number>>3) & 0x01));
    }
}