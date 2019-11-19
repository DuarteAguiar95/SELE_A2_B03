#include "UART9N2.h"


// Variaveis locais
uint8_t RX_estado = 0;
uint8_t buffer_in_pos = 0;

uint8_t buffer_out_pos = 0;

void UART9N2_init(){
    // Definir a taxa de transmissão
    uint16_t UBRR0_val = (uint16_t)((FOSC/(16*BAUDRATE))-1);

    cli();

    UBRR0H = (uint8_t)((UBRR0_val >> 8) & 0x000F);
    UBRR0L = (uint8_t)((UBRR0_val) & 0x00FF);

    // Defenir os registos de controlo
    UCSR0A = _BV(RXC0)   | _BV(TXC0)   | _BV(MPCM0);
    UCSR0B = _BV(RXCIE0) | _BV(TXCIE0) | _BV(RXEN0)  | _BV(TXEN0) | _BV(UCSZ02);
    UCSR0C = _BV(USBS0)  | _BV(UCSZ00) | _BV(UCSZ01);
    
    sei();
}

void UART9N2_SetMPCM(){
    UCSR0A |= _BV(MPCM0);
}

void UART9N2_ClearMPCM(){
    UCSR0A &= ~_BV(MPCM0);
}

ISR (USART_RX_vect){
    uint8_t recebido = UDR0;

    switch (RX_estado){
    case 0: // Verificar se é mestre ou escravo
        if((UCSR0A & _BV(MPCM0)) == _BV(MPCM0)){   // É escravo pois está no modo MCPM
            if((recebido & 0x0F) == (endereco)){  // O mestre refere-se a este escravo
                UCSR0A &= _BV(MPCM0);
                RX_estado = 1;
            }
        }else{  // É mestre
            buffer_in_size = recebido;
            buffer_in_pos = 0;
            RX_estado = 3;
        }
        break;
    //Rotina do escravo
    case 1: 
        buffer_in_size = recebido;
        buffer_in_pos = 0;
        RX_estado = 2;
        break;
    case 2:
        buffer_in[buffer_in_pos] = recebido;
        buffer_in_pos++;
        if(buffer_in_pos >= buffer_in_size){
            UCSR0A |= _BV(MPCM0);
            RX_estado = 0;
            RX_flag = 1;
        }
        break;
    case 3:
        buffer_in[buffer_in_pos] = recebido;
        buffer_in_pos++;
        if(buffer_in_pos >= buffer_in_size){
            RX_estado = 0;
            RX_flag = 1;
        }
        break;
    default:
        break;
    }
}