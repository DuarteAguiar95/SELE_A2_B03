#include "UART9N2.h"

// Variaveis Globais

extern uint32_t BAUDRATE;

//Recetor
extern volatile uint8_t buffer_in[BUFFERCAPACITY];
extern volatile uint8_t buffer_in_size;
extern uint8_t endereco;
extern volatile uint8_t RX_flag ;

//Transmissor
extern uint8_t buffer_out[BUFFERCAPACITY];
extern uint8_t buffer_out_size ;
extern volatile uint8_t TX_flag;

// Variaveis locais
uint8_t volatile RX_estado = 0;
 uint8_t volatile buffer_in_pos = 0;

volatile uint8_t buffer_out_pos = 0;

void UART9N2_init(){
    // Definir a taxa de transmissão
    uint16_t UBRR0_val = (uint16_t)((FOSC/(16*BAUDRATE))-1);

    cli();

    UBRR0H = (uint8_t)((UBRR0_val >> 8) & 0x000F);
    UBRR0L = (uint8_t)((UBRR0_val) & 0x00FF);

    // Defenir os registos de controlo
    UCSR0C = _BV(USBS0)  | _BV(UCSZ00) | _BV(UCSZ01);
    UCSR0B = _BV(RXCIE0) | _BV(TXCIE0) | _BV(RXEN0)  | _BV(TXEN0) | _BV(UCSZ02);
    UCSR0A = _BV(RXC0)   | _BV(TXC0);
    
    sei();
}

void UART9N2_SetMPCM(){
    UCSR0A |= _BV(MPCM0);
}

void UART9N2_ClearMPCM(){
    UCSR0A &= ~_BV(MPCM0);
}

void UART9N2_send(uint8_t *data, uint8_t length){
    uint8_t i;
    for(i = 0; i < length; i++)
        buffer_out[i] = data[i];
    buffer_out_size = length;
    buffer_out_pos = 0;

    TX_flag = 1;
   // Caso seja o mestre enviar o primeiro byte como endereço do escravo
    if((UCSR0A & _BV(MPCM0)) == 0){
        UCSR0B &= ~(1<<TXB80);
        UCSR0B |= _BV(TXB80);
    }
    UDR0 = buffer_out[buffer_out_pos];
    UCSR0B |= _BV(UDRIE0);
}

ISR (USART_UDRE_vect){
    buffer_out_pos++;
    if(buffer_out_pos < buffer_out_size){
        UCSR0B &= ~_BV(TXB80);
        UDR0 = buffer_out[buffer_out_pos];
    }else{
        UCSR0B &= ~_BV(UDRIE0);
    }
}

ISR (USART_TX_vect){
    TX_flag = 0;
}

ISR (USART_RX_vect){
    uint8_t recebido = UDR0;


    switch (RX_estado){
    // Verificar se é mestre ou escravo
    case 0: 
        if((UCSR0A & _BV(MPCM0)) == _BV(MPCM0)){   // É escravo pois está no modo MCPM
            if((recebido & 0x0F) == (endereco)){  // O mestre refere-se a este escravo
                UCSR0A &= ~_BV(MPCM0);
                RX_estado = 1;
                RX_flag = 1;
            }
        }else{  // É mestre
            buffer_in_size = recebido;
            buffer_in_pos = 0;
            RX_estado = 3;
            RX_flag = 1;
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
            RX_flag = 2;
        }
        break;
    // Rotina do mestre
    case 3:
        buffer_in[buffer_in_pos] = recebido;
        buffer_in_pos++;
        if(buffer_in_pos >= buffer_in_size){
            RX_estado = 0;
            RX_flag = 2;
        }
        break;
    default:
        break;
    }
}

