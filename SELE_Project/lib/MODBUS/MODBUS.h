#include "MAX485.h"

/**
 * Sets the state of a coil in a determined slave
 * */
void MODBUS_WriteCoil(uint8_t slaveAddress, uint8_t coilAddress, uint8_t value);

/**
 * configurar o MC como mestre
 * */
void MODBUS_configMaster();

/** 
 * Configurar o MC como escravo
 * */
void MODBUS_configSlave();
