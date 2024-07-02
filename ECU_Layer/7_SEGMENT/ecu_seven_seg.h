/* 
 * File:   ECU_SEVEN_SEG_H
 * Author: Hossam_ElBassuiony
 * Created on July 16, 2023, 9:04 PM
 */
#ifndef ECU_SEVEN_SEG_H
#define ECU_SEVEN_SEG_H

/* Section : Includes */

#include "ecu_seven_seg_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define SEGMENT_PIN_0  0
#define SEGMENT_PIN_1  1
#define SEGMENT_PIN_2  2
#define SEGMENT_PIN_3  3


/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

typedef enum{
    SEGMANT_COMMON_ANODE,
    SEGMANT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t    segment_pin[4];
    segment_type_t  segmant_type  ;
}segment_t;

/* Section: Function Declarations */

Std_ReturnType seven_segmant_initialize(const segment_t *seg);
Std_ReturnType seven_segmant_write_number(const segment_t *seg, uint8 number);

#endif   /* ECU_SEVEN_SEG_H */
