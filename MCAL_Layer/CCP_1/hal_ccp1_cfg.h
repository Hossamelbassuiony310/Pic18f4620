/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef HAL_CCP1_CFG.H
#define	HAL_CCP1_CFG.H

/* ----------------------------------- Section : Includes ----------------------------------- */

/* ----------------------------------- Section: Macro Declarations ----------------------------------- */

#define CCP_CFG_CAPTURE_MODE_SELECTED  0x00
#define CCP_CFG_COMPARE_MODE_SELECTED  0x01
#define CCP_CFG_PWM_MODE_SELECTED      0x02

#define CCP1_CFG_SELECTED_MODE (CCP_CFG_PWM_MODE_SELECTED)
#define CCP2_CFG_SELECTED_MODE (CCP_CFG_PWM_MODE_SELECTED)

/* ----------------------------------- Section: Macro Functions Declarations ----------------------------------- */

/* ----------------------------------- Section: Data Type Declarations ----------------------------------- */

/* -----------------------------------Section: Software Interfaces Declarations ----------------------------------- */

#endif	/* HAL_CCP1_CFG.H */