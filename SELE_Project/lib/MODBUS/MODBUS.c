#include "MODBUS.h"

void MODBUS_configMaster(){
    MAX485_configMaster();
}

void MODBUS_configSlave(uint8_t address){
    MAX485_config_Slave(address);
}

void MODBUS_WriteCoil(uint8_t slaveAddress, uint8_t coilAddress, uint8_t value, uint8_t *packet_R, uint8_t *length_R){
    uint8_t data[15];
    data[0] = slaveAddress;
    data[1] = 3;
    data[2] = 5;
    data[3] = coilAddress;
    data[4] = value;

    MAX485_SendPacket(data, 5);

    MAX485_ReceivePacket(packet_R, length_R);
}

void MODBUS_ReceiveComand(uint8_t *packet, uint8_t *length){
    MAX485_ReceivePacket(packet, length);
}


void MODBUS_Respond(uint8_t *response, uint8_t length){
    MAX485_SendPacket(response, length);
}