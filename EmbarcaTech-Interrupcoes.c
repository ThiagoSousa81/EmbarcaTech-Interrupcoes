#include <stdio.h>                  // Biblioteca padrão de entrada e saída
#include "pico/stdlib.h"            // Biblioteca padrão para o Raspberry Pi Pico
#include <hardware/pio.h>           // Biblioteca para manipulação de periféricos PIO
#include "hardware/clocks.h"        // Biblioteca para controle de relógios do hardware
#include "ws2818b.pio.h"            // Biblioteca PIO para controle de LEDs WS2818B

// Definições de constantes
#define LED_COUNT 25                // Número de LEDs na matriz
#define LED_PIN 7                   // Pino GPIO conectado aos LEDs

// Estrutura para representar um pixel com componentes RGB
struct pixel_t { 
    uint8_t G, R, B;                // Componentes de cor: Verde, Vermelho e Azul
};

typedef struct pixel_t pixel_t;     // Alias para a estrutura pixel_t
typedef pixel_t npLED_t;            // Alias para facilitar o uso no contexto de LEDs

npLED_t leds[LED_COUNT];            // Array para armazenar o estado de cada LED
PIO np_pio;                         // Variável para referenciar a instância PIO usada
uint sm;                            // Variável para armazenar o número do state machine usado

// Função para inicializar o PIO para controle dos LEDs
void npInit(uint pin) 
{
    uint offset = pio_add_program(pio0, &ws2818b_program); // Carregar o programa PIO
    np_pio = pio0;                                         // Usar o primeiro bloco PIO

    sm = pio_claim_unused_sm(np_pio, false);              // Tentar usar uma state machine do pio0
    if (sm < 0)                                           // Se não houver disponível no pio0
    {
        np_pio = pio1;                                    // Mudar para o pio1
        sm = pio_claim_unused_sm(np_pio, true);           // Usar uma state machine do pio1
    }

    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f); // Inicializar state machine para LEDs

    for (uint i = 0; i < LED_COUNT; ++i)                  // Inicializar todos os LEDs como apagados
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

// Função para atualizar os LEDs no hardware
void npUpdate() 
{
    for (uint i = 0; i < LED_COUNT; ++i)                  // Iterar sobre todos os LEDs
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);       // Enviar componente verde
        pio_sm_put_blocking(np_pio, sm, leds[i].R);       // Enviar componente vermelho
        pio_sm_put_blocking(np_pio, sm, leds[i].B);       // Enviar componente azul
    }
}

// Função para definir a cor de um LED específico
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) 
{
    leds[index].R = r;                                    // Definir componente vermelho
    leds[index].G = g;                                    // Definir componente verde
    leds[index].B = b;                                    // Definir componente azul

    //npUpdate();
}

// Função para limpar (apagar) todos os LEDs
void npClear() 
{
    for (uint i = 0; i < LED_COUNT; ++i)                  // Iterar sobre todos os LEDs
        npSetLED(i, 0, 0, 0);                             // Definir cor como preta (apagado)
        
    //npUpdate();
}

void setDisplayNum(int num, const uint8_t r, const uint8_t g, const uint8_t b)
{

    /*
    24, 23, 22, 21, 20
    15, 16, 17, 18, 19
    14, 13, 12, 11, 10
    05, 06, 07, 08, 09
    04, 03, 02, 01, 00
    */
    npClear();
    switch (num) {
        case 0:
            npSetLED(0, r, g, b);
            npSetLED(1, r, g, b);
            npSetLED(2, r, g, b);
            npSetLED(3, r, g, b);
            npSetLED(4, r, g, b);
            npSetLED(5, r, g, b);          
            npSetLED(9, r, g, b);
            npSetLED(10, r, g, b);            
            npSetLED(14, r, g, b);
            npSetLED(15, r, g, b);
            npSetLED(19, r, g, b);
            npSetLED(20, r, g, b);
            npSetLED(21, r, g, b);
            npSetLED(22, r, g, b);
            npSetLED(23, r, g, b);
            npSetLED(24, r, g, b);
            break;  
        case 1:
            npSetLED(0, r, g, b);
            npSetLED(1, r, g, b);
            npSetLED(2, r, g, b);
            npSetLED(3, r, g, b);
            npSetLED(4, r, g, b);
            npSetLED(7, r, g, b);
            npSetLED(12, r, g, b);
            npSetLED(16, r, g, b);
            npSetLED(17, r, g, b);
            npSetLED(22, r, g, b);
            break;  
        case 2:
            npSetLED(0, r, g, b);
            npSetLED(1, r, g, b);
            npSetLED(2, r, g, b);
            npSetLED(3, r, g, b);
            npSetLED(4, r, g, b);
            npSetLED(5, r, g, b);
            npSetLED(10, r, g, b);
            npSetLED(11, r, g, b);
            npSetLED(12, r, g, b);
            npSetLED(13, r, g, b);
            npSetLED(14, r, g, b);
            npSetLED(19, r, g, b);
            npSetLED(20, r, g, b);
            npSetLED(21, r, g, b);
            npSetLED(22, r, g, b);
            npSetLED(23, r, g, b);
            npSetLED(24, r, g, b);
            break;
        case 3:
            npSetLED(0, r, g, b);
            npSetLED(1, r, g, b);
            npSetLED(2, r, g, b);
            npSetLED(3, r, g, b);
            npSetLED(4, r, g, b); 
            npSetLED(9, r, g, b);           
            npSetLED(10, r, g, b);
            npSetLED(11, r, g, b);
            npSetLED(12, r, g, b);
            npSetLED(13, r, g, b);
            npSetLED(19, r, g, b);
            npSetLED(20, r, g, b);
            npSetLED(21, r, g, b);
            npSetLED(22, r, g, b);
            npSetLED(23, r, g, b);
            npSetLED(24, r, g, b);
            break;
        case 4:
            npSetLED(2, r, g, b);   
            npSetLED(5, r, g, b);
            npSetLED(6, r, g, b);   
            npSetLED(7, r, g, b);   
            npSetLED(8, r, g, b);   
            npSetLED(12, r, g, b);
            npSetLED(14, r, g, b);  
            npSetLED(16, r, g, b);  
            npSetLED(17, r, g, b);  
            npSetLED(22, r, g, b);  
            break;
        case 5:
            npSetLED(0, r, g, b);   // LED na posição (0, 0)
            npSetLED(1, r, g, b);   // LED na posição (0, 1)
            npSetLED(2, r, g, b);   // LED na posição (0, 2)
            npSetLED(3, r, g, b);   // LED na posição (0, 3)
            npSetLED(4, r, g, b);   // LED na posição (0, 4)
            npSetLED(9, r, g, b);
            npSetLED(10, r, g, b);  // LED na posição (2, 0)
            npSetLED(11, r, g, b);  // LED na posição (2, 1)
            npSetLED(12, r, g, b);  // LED na posição (2, 2)
            npSetLED(13, r, g, b);  // LED na posição (2, 3)
            npSetLED(14, r, g, b);  // LED na posição (3, 4)
            npSetLED(15, r, g, b);  // LED na posição (4, 0)
            npSetLED(20, r, g, b);
            npSetLED(21, r, g, b);  // LED na posição (4, 1)
            npSetLED(22, r, g, b);  // LED na posição (4, 2)
            npSetLED(23, r, g, b);
            npSetLED(24, r, g, b);
            break;
        case 6:
            npSetLED(0, r, g, b);   
            npSetLED(1, r, g, b);   
            npSetLED(2, r, g, b);   
            npSetLED(3, r, g, b);   
            npSetLED(4, r, g, b);  
            npSetLED(5, r, g, b);                 
            npSetLED(9, r, g, b);   
            npSetLED(10, r, g, b);  
            npSetLED(11, r, g, b);  
            npSetLED(12, r, g, b);  
            npSetLED(13, r, g, b);  
            npSetLED(14, r, g, b);  
            npSetLED(15, r, g, b);  
            npSetLED(20, r, g, b); 
            npSetLED(21, r, g, b);  
            npSetLED(22, r, g, b);  
            npSetLED(23, r, g, b);
            npSetLED(24, r, g, b);
            break;
        case 7:            
            npSetLED(1, r, g, b);   
            npSetLED(8, r, g, b);   
            npSetLED(11, r, g, b);  
            npSetLED(18, r, g, b);  
            npSetLED(21, r, g, b);  
            npSetLED(22, r, g, b);
            npSetLED(23, r, g, b);
            npSetLED(24, r, g, b);
            break;
        case 8:
            npSetLED(0, r, g, b);  
            npSetLED(1, r, g, b); 
            npSetLED(2, r, g, b); 
            npSetLED(3, r, g, b);  
            npSetLED(4, r, g, b);  
            npSetLED(5, r, g, b);  
            npSetLED(9, r, g, b);  
            npSetLED(10, r, g, b); 
            npSetLED(11, r, g, b);
            npSetLED(12, r, g, b); 
            npSetLED(13, r, g, b); 
            npSetLED(14, r, g, b); 
            npSetLED(15, r, g, b);
            npSetLED(19, r, g, b); 
            npSetLED(20, r, g, b); 
            npSetLED(22, r, g, b); 
            npSetLED(21, r, g, b);  
            npSetLED(23, r, g, b);
            npSetLED(24, r, g, b);
            break;
        case 9:
            npSetLED(0, r, g, b);   
            npSetLED(1, r, g, b);   
            npSetLED(2, r, g, b);   
            npSetLED(3, r, g, b);   
            npSetLED(4, r, g, b);   
            npSetLED(9, r, g, b);  
            npSetLED(10, r, g, b);  
            npSetLED(11, r, g, b);  
            npSetLED(12, r, g, b);  
            npSetLED(13, r, g, b);  
            npSetLED(14, r, g, b);
            npSetLED(15, r, g, b);
            npSetLED(19, r, g, b);  
            npSetLED(20, r, g, b);  
            npSetLED(21, r, g, b);
            npSetLED(22, r, g, b);
            npSetLED(23, r, g, b);
            npSetLED(24, r, g, b);
            break;
    }
    npUpdate();
}

int main()
{
    stdio_init_all();                                     // Inicializar a comunicação serial
    npInit(LED_PIN);                                      // Inicializar os LEDs

    while (true) {
        for (uint i = 0; i < 10; ++i)
        {
            setDisplayNum(i, 0, 100, 0);        
            sleep_ms(1000);
        }
        
    }
}
