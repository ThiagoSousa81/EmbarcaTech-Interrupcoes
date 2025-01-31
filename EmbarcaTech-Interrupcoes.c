#include <stdio.h>                   // Biblioteca padrão de entrada e saída
#include "pico/stdlib.h"            // Biblioteca padrão para o Raspberry Pi Pico
#include <hardware/pio.h>           // Biblioteca para manipulação de periféricos PIO
#include "hardware/clocks.h"        // Biblioteca para controle de relógios do hardware
#include "ws2818b.pio.h"            // Biblioteca PIO para controle de LEDs WS2818B

int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
