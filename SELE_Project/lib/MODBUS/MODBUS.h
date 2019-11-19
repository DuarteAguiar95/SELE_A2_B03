#include "MAX485.h"

/**
 * configurar o MC como mestre
 * */
void MODBUS_configMaster();

/** 
 * Configurar o MC como escravo
 * */

void MODBUS_configSlave();
/**
 * Sets the state of a coil in a determined slave
 * */
void MODBUS_WriteCoil(uint8_t slaveAddress, uint8_t coilAddress, uint8_t value, uint8_t *packet_R, uint8_t *length_R);


