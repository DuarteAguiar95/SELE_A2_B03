#include "MODBUS.h"
#include <avr/io.h>
#include <util/delay.h>

#define MASTER
#define DEBUG

#define SLAVE_1 0x01
#define SLAVE_2 0x02

uint32_t BAUDRATE;

// Local functions
void initCoils();