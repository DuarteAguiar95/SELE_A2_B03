#include <avr/io.h>
#include <avr/interrupt.h>

#define FOSC 16000000
#define BUFFERCAPACITY 50
// Variaveis Globais
uint32_t BAUDRATE = 250000;

//Recetor
uint8_t buffer_in[BUFFERCAPACITY];
uint8_t buffer_in_size = 0;
uint8_t endereco = 0;
uint8_t RX_flag = 0;

//Transmissor
uint8_t buffer_out[BUFFERCAPACITY];
uint8_t buffer_out_size = 0;
uint8_t TX_flag = 0;

//#define MASTER 0

/**
 * Função para iniciar o módulo UART 
 *  -> 9 bits de dados 
 *  -> Sem paridade
 *  -> 2 Stop bits
 * */
void UART9N2_init();

/**
 * Função que ativa o modo MPCM 
 * */
void UART9N2_SetMPCM();

/**
 * Função que desativa o modo MPCM
 * */
void UART9N2_ClearMPCM();

/**
 * 
 * */
void UART9N2_send(uint8_t *data, uint8_t length);