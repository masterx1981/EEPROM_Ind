/*
 * Write operation return the number of byte written (max 256 bytes!)
*/

#ifndef EEPROM_Ind_h
#define EEPROM_Ind_h

#include "Arduino.h"  // Arduino data type definitions
#include "I2C_eeprom.h"

#define EEPAGE 4
#define EEPAGESIZE 256
   
class EEPROM_Ind {
 public:
  bool     begin();

  template <typename T>
  uint8_t read(const uint16_t& address, T& value) const {
    //address from 0 to 1023
    if ((address + sizeof(T)) >= (EEPAGESIZE*EEPAGE)) return 0;                 //trying to read over the limits
    uint8_t i{0};
    uint8_t* bytePtr = (uint8_t*)&value;                           // Declare pointer to start of structure
    for (i = 0; i < sizeof(T); i++) {                              // Loop for each byte to be read
      *bytePtr++ = ePage[address>>8]->readByte((address + i) & 0xFF);// Read a byte
    }
    return i;
  } 
    
  template <typename T>
  uint8_t write(const uint16_t& address, const T& value) const {
    //address from 0 to 1023
    if ((address + sizeof(T)) >= (EEPAGESIZE*EEPAGE)) return 0;                                                //trying to write over the limits
    byte i = 0;
    byte* bytePtr = (byte*)&value;                                            // Declare pointer to start of structure
    for (i = 0; i < sizeof(T); i++) {                                                // Loop for each byte to be read
      ePage[address>>8]->writeByte((address + i) & 0xFF, *bytePtr++);             // write operation
      delay(5);                                                                    // NEEDED between successive writings
    }
    //if (i == 0) i = sizeof(T);                 // return number of bytes on success
    return i;                                  // return the number of bytes written
  }

  template <typename T>
  uint8_t update(const uint16_t& address, const T& value) const {
    //address from 0 to 1023
    if ((address + sizeof(T)) >= (EEPAGESIZE*EEPAGE)) return 0;                                                //trying to write over the limits
    byte i = 0;
    byte* bytePtr = (byte*)&value;                                            // Declare pointer to start of structure
    for (i = 0; i < sizeof(T); i++) {                                                // Loop for each byte to be read
      ePage[address>>8]->updateByte((address + i) & 0xFF, *bytePtr++);             // write operation
      delay(5);                                                                    // NEEDED between successive writings
    }
    //if (i == 0) i = sizeof(T);                 // return number of bytes on success
    return i;                                  // return the number of bytes written
  }


 private:
  I2C_eeprom *ePage[EEPAGE];         //array of pointers
};
#endif