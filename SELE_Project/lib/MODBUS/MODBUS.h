#include "MAX485.h"
#include <avr/io.h>

/**
 * configurar o MC como mestre
 * */
void MODBUS_configMaster();

/** 
 * Configurar o MC como escravo
 * */
void MODBUS_configSlave(uint8_t address);

/**
 * Sets the state of a coil in a determined slave
 * */
void MODBUS_WriteCoil(uint8_t slaveAddress, uint8_t coilAddress, uint8_t value, uint8_t *packet_R, uint8_t *length_R);

void MODBUS_ReceiveComand(uint8_t *packet, uint8_t *length);

void MODBUS_Respond(uint8_t *response, uint8_t length);
