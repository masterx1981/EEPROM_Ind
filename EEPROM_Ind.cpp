#include "EEPROM_Ind.h"

bool EEPROM_Ind::begin() {
  for(uint8_t nE=0; nE<EEPAGE; nE++){
    ePage[nE] = new I2C_eeprom(0x50+nE, EEPAGESIZE);
    ePage[nE]->begin();
    // check if the eeprom at the current address is connected
    if (ePage[nE]->determineSize() == -1) return false;
  }
  return true;
}