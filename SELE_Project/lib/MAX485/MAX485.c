#include "MAX485.h"

uint8_t buffer_in[BUFFERCAPACITY];
uint8_t buffer_in_size = 0;
uint8_t endereco = 0;
uint8_t RX_flag = 0;

uint8_t buffer_out[BUFFERCAPACITY];
uint8_t buffer_out_size = 0;
uint8_t TX_flag = 0;

void MAX485_configMaster(){
    UART9N2_init();
}

void MAX485_config_Slave(uint8_t address){
    //endereco = address;
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