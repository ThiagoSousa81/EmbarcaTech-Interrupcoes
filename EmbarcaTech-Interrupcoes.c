#include <stdio.h>                  // Biblioteca padrão de entrada e saída
#include "pico/stdlib.h"            // Biblioteca padrão para o Raspberry Pi Pico
#include <hardware/pio.h>           // Biblioteca para manipulação de periféricos PIO
#include "hardware/clocks.h"        // Biblioteca para controle de relógios do hardware
#include "hardware/timer.h"         // Inclui a biblioteca para gerenciamento de temporizadores de hardware.
#include "ws2818b.pio.h"            // Biblioteca PIO para controle de LEDs WS2818B

// Definições de constantes
#define LED_COUNT 25                // Número de LEDs na matriz
#define LED_PIN 7                   // Pino GPIO conectado aos LEDs
#define LED_PIN_RED 13
// Implementar o Debounce para os botões
//https://github.com/wiltonlacerda/EmbarcaTechU4C4/tree/main/05_IntDebounceWokwi
const uint BUTTON_A = 5;
const uint BUTTON_B = 6;

// Armazena o tempo do último evento (em microssegundos)
static volatile uint32_t last_time_A = 0;
static volatile uint32_t last_time_B = 0; 

int display_Value = 5;

bool led_on = false;

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

// Função de callback que será chamada repetidamente pelo temporizador
// O tipo bool indica que a função deve retornar verdadeiro ou falso para continuar ou parar o temporizador.
bool repeating_timer_callback(struct repeating_timer *t) {    
    //Liga ou desliga o led.
    led_on = !led_on;
    gpio_put(LED_PIN_RED, led_on);    
    // Retorna true para manter o temporizador repetindo. Se retornar false, o temporizador para.
    return true;
}

void setup_button(uint button_pin, void (*handler)(uint, uint32_t)) {
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);    // Configura o pino como entrada
    gpio_pull_up(button_pin);             // Habilita o pull-up interno
    gpio_set_irq_enabled_with_callback(button_pin, GPIO_IRQ_EDGE_FALL, true, handler);  // Interrupção na borda de queda
}

// Função de interrupção para o botão A
void gpio_irq_handler_A(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica o debounce (200ms)
    if (current_time - last_time_A > 200000)
    {
        // Decrementa o valor do display, mas não deixa o valor abaixo de 0
        if (display_Value != 0)
        {
            display_Value--;
            printf("Botão A pressionado, valor: %d\n", display_Value);
        }
        last_time_A = current_time; // Atualiza o tempo do último evento
    }
}


// Função de interrupção para o botão B
void gpio_irq_handler_B(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica o debounce (200ms)
    if (current_time - last_time_B > 200000)
    {
        // Incrementa o valor do display, mas não deixa o valor acima de 9
        if (display_Value < 9)
        {
            display_Value++;
            printf("Botão B pressionado, valor: %d\n", display_Value);
        }
        last_time_B = current_time; // Atualiza o tempo do último evento
    }
}

int main()
{
    stdio_init_all();                                     // Inicializar a comunicação serial
    npInit(LED_PIN);                                      // Inicializar os LEDs

    // Inicializar o pino GPIO13
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, true);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_A);          // Habilita o pull-up interno    

    // Configuração da interrupção com callback dos botões A e B

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(BUTTON_B);          // Habilita o pull-up interno

    // Configura as interrupções para os botões A e B
    setup_button(BUTTON_A, gpio_irq_handler_A);  // Para o botão A
    setup_button(BUTTON_B, gpio_irq_handler_B);  // Para o botão B

    // Declaração de uma estrutura de temporizador de repetição.
    // Esta estrutura armazenará informações sobre o temporizador configurado.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback para acender o LED 5 vezes
    add_repeating_timer_ms(100, repeating_timer_callback, NULL, &timer);
    
    
    

    setDisplayNum(5, 0, 0, 100); 
    while (true) {
        /*for (uint i = 0; i < 10; ++i)
        {
            setDisplayNum(i, 0, 0, 100);        
            sleep_ms(1000);
        }*/               
    }
}
