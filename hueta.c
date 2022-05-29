#include "config.h"

typedef union 
{
    uint8_t byte;
    struct hueta
    {
        uint8_t bit8 : 1;
        uint8_t bit7 : 1;
        uint8_t bit6 : 1;
        uint8_t bit5 : 1;
        uint8_t bit4 : 1;
        uint8_t bit3 : 1;
        uint8_t bit2 : 1;
        uint8_t bit1 : 1;
    }; 
}MYBYTE;


// кодирование
uint8_t x = 0;
uint8_t mas[] = {1, 0, 1, 1, 0, 0, 0, 1};
for(int i = 0; i < 8; i++)
{
    x += mas[7-i] * (1 << i);
}


uint8_t x = 10110001;
uint8_t mas[] = {0, 0, 0, 0, 0, 0, 0, 0};
for(int i = 0; i < 8; i++)
{
    mas[i] = x & 1;
    x >>= 1;
}
