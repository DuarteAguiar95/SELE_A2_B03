#include "MAX485.h"

void MAX485_configMaster(){
    UART9N2_init();
}

void MAX485_config_Slave(){
    UART9N2_init();
    UART9N2_SetMPCM();
}

void MAX485_initDirPin(){
    MAX485_DIR_DDR |= _BV(MAX485_DIR_PIN);
}

void MAX485_setTX(){
    MAX485_DIR_PORT |= _BV(MAX485_DIR_PIN);
}

void MAX485_setRX(){
    MAX485_DIR_PORT &= ~_BV(MAX485_DIR_PIN);
}

void MAX485_SendPacket(uint8_t *packet, uint8_t length){
    while (TX_flag);
    MAX485_setTX();
    UART9N2_send(packet, length);
    while(!TX_flag);
    MAX485_setRX();
}

void MAX485_ReceivePacket(uint8_t *packet, uint8_t *length){
    uint8_t i;
    while(!RX_flag);

    for(i = 0; i < buffer_in_size; i++)
        packet[i] = buffer_in[i];
    *length = buffer_in_size;

    RX_flag = 0;
}