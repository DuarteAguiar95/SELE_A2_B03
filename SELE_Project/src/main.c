#include <avr/io.h>
#include <util/delay.h>

#include "main.h"

int main(void)
{
  BAUDRATE = 9600;
  uint8_t packet_R[15];
  uint8_t length_R;

  #ifndef MASTER
    uint8_t command, coilAddr, coilVal;
    uint8_t response[15];
  #endif

  #ifdef MASTER
    MODBUS_configMaster();
    #ifdef DEBUG
    initCoils();
    #endif
  #else
    //MODBUS_configSlave(SLAVE_1);
    MODBUS_configSlave(SLAVE_2);

    initCoils();
  #endif

    while (1)
    {
      #ifdef MASTER
        MODBUS_WriteCoil(SLAVE_1, 5, 0, packet_R, &length_R);
        MODBUS_WriteCoil(SLAVE_2, 5, 0, packet_R, &length_R);
        _delay_ms(1000);
        MODBUS_WriteCoil(SLAVE_1, 5, 1, packet_R, &length_R);
        MODBUS_WriteCoil(SLAVE_2, 5, 0, packet_R, &length_R);
        _delay_ms(1000);
        MODBUS_WriteCoil(SLAVE_1, 5, 1, packet_R, &length_R);
        MODBUS_WriteCoil(SLAVE_2, 5, 1, packet_R, &length_R);
        _delay_ms(1000);
        MODBUS_WriteCoil(SLAVE_1, 5, 0, packet_R, &length_R);
        MODBUS_WriteCoil(SLAVE_2, 5, 1, packet_R, &length_R);
        _delay_ms(1000);
      #else
        MODBUS_ReceiveComand(packet_R, &length_R);
        if(length_R > 0){
          command = packet_R[0];
          switch (command)
          {
          case 5:
            coilAddr = packet_R[1];
            coilVal = packet_R[2];

            if(coilVal == 0)
              PORTB &= ~_BV(coilAddr);
            else
              PORTB |= _BV(coilAddr);
            response[0] = command;
            response[1] = coilAddr;
            MODBUS_Respond(response, 2);
            break;
          
          default:
            break;
          }
        }
      #endif
    }
    
    return 0;
}

void initCoils(){
  DDRB |= _BV(PB5);
  PORTB &= ~(_BV(PB5));
}