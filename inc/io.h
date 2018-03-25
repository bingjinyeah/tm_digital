#ifndef _IO_H
#define _IO_H

#include "stm8s.h"

void io_init(void);
uint8_t read_di0(void);
uint8_t read_di1(void);
void write_do0(uint8_t val);
void write_do1(uint8_t val);
void io_task(void);

#endif