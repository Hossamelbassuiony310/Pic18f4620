/* 
 * File:   hal_eeprom.c
 * Author: 
 * Comments:
 * Revision history: 
 */

#include "hal_eeprom.h"


/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_OK;
    
    /* Read the Interrupt Status "Enable or Disable" */
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Update the Address Register */
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8)(bAdd & 0xFF);
    /* Update the Data Register */
    EEDATA = bData;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;  
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable all interrupt "General Interrupt" */
    INTERRUPT_GlobalInterruptDisable();
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INTIATE_DATA_EEPROM_WRITE_ERASE;
    /* wait for write to complete */
    while(EECON1bits.WR);
    /* Ingibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = Global_Interrupt_Status;
    
    return ret;
}


/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_OK;
    
    if(NULL == bData){
        ret = E_NOK;
    }
    else{
        
        
        /* Update the Address Registers */
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;  
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = INTIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        /* Return data */
        uint8 *bData = EEDATA;
        
        ret = E_OK;
    }
    
    return ret;
}