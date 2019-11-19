#include "UART9N2.h"

/**
* Configurar o UART como mestre
* */
void MAX485_configMaster();

/**
* Configurar o UART como escravo
* */
void MAX485_config_Slave();

/**
 * Coloca o módulo MAX485 em modo de transmissão
 * */
void MAX485_setTX();

/**
 * Coloca o módulo MAX485 em modo de receção
 * */
void MAX485_setRX();

/**
 * Envia um pacote de dados através do módulo Max485
 * fazendo uso do UART.
 * Controla a direção dos dados no módulo MAX485
 * */
void MAX485_SendPacket(uint8_t *packet, uint8_t length);

/**
 * Espera por um pacote de dados através do módulo Max485.
 * Controla a direção dos dados no módulo MAX485
 * */
void MAX485_ReceivePacket(uint8_t *packet, uint8_t *length);