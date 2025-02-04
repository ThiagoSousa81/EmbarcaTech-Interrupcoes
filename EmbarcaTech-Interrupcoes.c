//|=======================================|
//|                                       |
//|            Thiago Sousa               |
//|   https://github.com/ThiagoSousa81    |
//|                                       |
//|=======================================|
// Este projeto foi otimizado para ter o menor tamanho possível
#include <stdio.h>           // Biblioteca padrão de entrada e saída
#include "pico/stdlib.h"     // Biblioteca padrão para o Raspberry Pi Pico
#include <hardware/pio.h>    // Biblioteca para manipulação de periféricos PIO
#include "hardware/timer.h"  // Inclui a biblioteca para gerenciamento de temporizadores de hardware.
#include "ws2818b.pio.h"     // Biblioteca PIO para controle de LEDs WS2818B

// Definições de constantes
#define LED_COUNT 25     // Número de LEDs na matriz
#define LED_PIN 7        // Pino GPIO conectado aos LEDs
#define LED_PIN_RED 13   // Pino do vermelho do LED RGB
const uint BUTTON_A = 5; // Pino GPIO do botão A
const uint BUTTON_B = 6; // Pino GPIO do botão B

// Armazena o tempo do último click de botão (em microssegundos)
static volatile uint32_t last_time = 0;

// Valor inicial que aparece na matriz de LEDs
int display_Value = 0;

// Estado inicial do LED RGB
bool led_on = false;

// Estrutura para representar um pixel com componentes RGB
struct pixel_t
{
    uint8_t G, R, B; // Componentes de cor: Verde, Vermelho e Azul
};

typedef struct pixel_t pixel_t; // Alias para a estrutura pixel_t
typedef pixel_t npLED_t;        // Alias para facilitar o uso no contexto de LEDs

npLED_t leds[LED_COUNT]; // Array para armazenar o estado de cada LED
PIO np_pio;              // Variável para referenciar a instância PIO usada
uint sm;                 // Variável para armazenar o número da máquina de estado (State Machine)

// Função para inicializar o PIO para controle dos LEDs
void npInit(uint pin)
{
    uint offset = pio_add_program(pio0, &ws2818b_program); // Carregar o programa PIO
    np_pio = pio0;                                         // Usar o primeiro bloco PIO

    sm = pio_claim_unused_sm(np_pio, false); // Tentar usar uma state machine do pio0
    if (sm < 0)                              // Se não houver disponível no pio0
    {
        np_pio = pio1;                          // Mudar para o pio1
        sm = pio_claim_unused_sm(np_pio, true); // Usar uma state machine do pio1
    }

    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f); // Inicializar state machine para LEDs

    // Inicializar todos os LEDs como apagados
    for (uint i = 0; i < LED_COUNT; ++i) 
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

// Função para atualizar os LEDs no hardware
void npUpdate()
{
    for (uint i = 0; i < LED_COUNT; ++i) // Iterar sobre todos os LEDs
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].R); // Enviar componente vermelho
        pio_sm_put_blocking(np_pio, sm, leds[i].G); // Enviar componente verde        
        pio_sm_put_blocking(np_pio, sm, leds[i].B); // Enviar componente azul
    }
}

// Função para definir a cor de um LED específico
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds[index].R = r; // Definir componente vermelho
    leds[index].G = g; // Definir componente verde
    leds[index].B = b; // Definir componente azul
}

// Função para limpar (apagar) todos os LEDs
void npClear()
{
    for (uint i = 0; i < LED_COUNT; ++i) // Iterar sobre todos os LEDs
        npSetLED(i, 0, 0, 0);            // Definir cor como preta (apagado)
}

// Função para definir qual número mostrar na tela
void setDisplayNum(int num, const uint8_t r, const uint8_t g, const uint8_t b)
{
/*  Gabarito do Display
    24, 23, 22, 21, 20
    15, 16, 17, 18, 19
    14, 13, 12, 11, 10
    05, 06, 07, 08, 09
    04, 03, 02, 01, 00
*/
    npClear();
    switch (num)
    {
    case 0: // Número 0
        npSetLED(1, r, g, b);
        npSetLED(2, r, g, b);
        npSetLED(3, r, g, b);
        npSetLED(6, r, g, b);
        npSetLED(8, r, g, b);
        npSetLED(11, r, g, b);
        npSetLED(13, r, g, b);
        npSetLED(16, r, g, b);
        npSetLED(18, r, g, b);        
        npSetLED(21, r, g, b);
        npSetLED(22, r, g, b);
        npSetLED(23, r, g, b);
        break;
    case 1: // Número 1
        npSetLED(1, r, g, b);
        npSetLED(2, r, g, b);
        npSetLED(3, r, g, b);
        npSetLED(7, r, g, b);
        npSetLED(12, r, g, b);
        npSetLED(16, r, g, b);
        npSetLED(17, r, g, b);
        npSetLED(22, r, g, b);
        break;
    case 2: // Número 2
        npSetLED(1, r, g, b);
        npSetLED(2, r, g, b);
        npSetLED(3, r, g, b);
        npSetLED(6, r, g, b);
        npSetLED(11, r, g, b);
        npSetLED(12, r, g, b);
        npSetLED(13, r, g, b);
        npSetLED(18, r, g, b);
        npSetLED(21, r, g, b);
        npSetLED(22, r, g, b);
        npSetLED(23, r, g, b);
        break;
    case 3: // Número 3
        npSetLED(1, r, g, b);
        npSetLED(2, r, g, b);
        npSetLED(3, r, g, b);
        npSetLED(8, r, g, b);
        npSetLED(11, r, g, b);
        npSetLED(12, r, g, b);
        npSetLED(13, r, g, b);
        npSetLED(18, r, g, b);
        npSetLED(21, r, g, b);
        npSetLED(22, r, g, b);
        npSetLED(23, r, g, b);
        break;
    case 4: // Número 4
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
    case 5: // Número 5
        npSetLED(1, r, g, b);
        npSetLED(2, r, g, b);
        npSetLED(3, r, g, b);        
        npSetLED(8, r, g, b);
        npSetLED(11, r, g, b);
        npSetLED(12, r, g, b);
        npSetLED(13, r, g, b);
        npSetLED(16, r, g, b); 
        npSetLED(21, r, g, b);
        npSetLED(22, r, g, b);
        npSetLED(23, r, g, b);
        break;
    case 6: // Número 6
        npSetLED(1, r, g, b);
        npSetLED(2, r, g, b);
        npSetLED(3, r, g, b); 
        npSetLED(6, r, g, b);
        npSetLED(8, r, g, b);
        npSetLED(11, r, g, b);
        npSetLED(12, r, g, b);
        npSetLED(13, r, g, b);
        npSetLED(16, r, g, b); 
        npSetLED(21, r, g, b);
        npSetLED(22, r, g, b);
        npSetLED(23, r, g, b);
        break;
    case 7: // Número 7
        npSetLED(1, r, g, b);
        npSetLED(8, r, g, b);
        npSetLED(11, r, g, b);
        npSetLED(18, r, g, b);
        npSetLED(21, r, g, b);
        npSetLED(22, r, g, b);
        npSetLED(23, r, g, b);        
        break;
    case 8: // Número 8
        npSetLED(1, r, g, b);
        npSetLED(2, r, g, b);
        npSetLED(3, r, g, b);
        npSetLED(6, r, g, b);
        npSetLED(8, r, g, b);
        npSetLED(11, r, g, b);
        npSetLED(12, r, g, b);
        npSetLED(13, r, g, b);
        npSetLED(16, r, g, b);
        npSetLED(18, r, g, b);
        npSetLED(22, r, g, b);
        npSetLED(21, r, g, b);
        npSetLED(23, r, g, b);
        break;
    case 9: // Número 9
        npSetLED(1, r, g, b);
        npSetLED(2, r, g, b);
        npSetLED(3, r, g, b);        
        npSetLED(8, r, g, b);
        npSetLED(11, r, g, b);
        npSetLED(12, r, g, b);
        npSetLED(13, r, g, b);
        npSetLED(16, r, g, b);
        npSetLED(18, r, g, b);
        npSetLED(21, r, g, b);
        npSetLED(22, r, g, b);
        npSetLED(23, r, g, b);
        break;
    }
    npUpdate(); // Atualiza o display após colocar o número
}

// Função de callback que será chamada repetidamente pelo temporizador
// O tipo bool indica que a função deve retornar verdadeiro ou falso para continuar ou parar o temporizador.
bool repeating_timer_callback(struct repeating_timer *t)
{
    // Liga ou desliga o led.
    led_on = !led_on;
    gpio_put(LED_PIN_RED, led_on);
    // Retorna true para manter o temporizador repetindo. Se retornar false, o temporizador para.
    return true;
}

// Função de interrupção com debouncing do botão A
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 500000) // 500 ms de debouncing
    {
        if (gpio == BUTTON_A)
        {
            // decremento no valor do display até 0
            if (display_Value != 0)
            {
                display_Value--;
                setDisplayNum(display_Value, 0, 0, 100);
            }
            last_time = current_time; // Atualiza o tempo do último evento
        }
        else
        {
            // incremento no valor do display até 9
            if (display_Value != 9)
            {
                display_Value++;
                setDisplayNum(display_Value, 0, 0, 100);
            }
            last_time = current_time; // Atualiza o tempo do último evento
        }
    }
}

// Método principal
int main()
{
    stdio_init_all(); // Inicializar a comunicação serial
    npInit(LED_PIN);  // Inicializar os LEDs

    // Inicializar o pino GPIO13
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, true);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_A);          // Habilita o pull-up interno
    // Configuração da interrupção com callback do botão A
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);    

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_B);          // Habilita o pull-up interno
    // Configuração da interrupção com callback do botão B
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    
    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback para acender o LED 5 vezes
    // Se considerarmos "piscar" como um ciclo completo (acender e apagar): O LED pisca 5 vezes por segundo (10 mudanças de estado em 100ms / 2) = 5 piscadas.
    // Se considerarmos "piscar" como qualquer mudança de estado: O LED muda de estado 10 vezes por segundo, logo pra piscar 10 vezes por segundo precisaríamos de 200ms.
    add_repeating_timer_ms(100, repeating_timer_callback, NULL, &timer);

    setDisplayNum(display_Value, 0, 0, 100);
    while (true)
    {
        // Essa parte é necessária para o funcionamento das interrupções
    }
    return 0; // nunca chega aqui
}
