#include <stdio.h>
#include "pico/stdlib.h"

// Definições de linhas e colunas do teclado
#define rows 4  // O teclado tem 4 linhas
#define cols 4  // O teclado tem 4 colunas

// Definições dos pinos dos LEDs e do buzzer
#define green 11  // Pino do LED verde
#define blue 12   // Pino do LED azul
#define red 13    // Pino do LED vermelho
#define buzzer 21 // Pino do buzzer
bool led_azul_ativo = 0; // VARIAVEL GLOBAL QUE GUARDA O VALOR INICIAL DO LED 0 = False

// Mapeamento dos pinos do teclado (linhas e colunas do teclado matricial)
const uint8_t row_pins[rows] = {8, 7, 6, 5};  // Pinos das linhas (R1, R2, R3, R4)
const uint8_t col_pins[cols] = {4, 3, 2, 27}; // Pinos das colunas (C1, C2, C3, C4)

// Mapeamento do teclado matricial (associa as teclas aos caracteres)
const char key_map[rows][cols] = {
    {'1', '2', '3', 'A'}, // Primeira linha
    {'4', '5', '6', 'B'}, // Segunda linha
    {'7', '8', '9', 'C'}, // Terceira linha
    {'*', '0', '#', 'D'}  // Quarta linha
};

// Funções auxiliares para controlar os LEDs e o buzzer
void ativar_led_verde() {
    gpio_put(red, 0);  // Desliga o LED vermelho antes de ligar o verde
    gpio_put(blue, 0);  // Desliga o LED azul antes de ligar o verde
    gpio_put(green, 1);  // Liga o LED verde (pino 11)
    sleep_ms(1000);      // Deixa o LED ligado por 1 segundo
    gpio_put(green, 0);  // Desliga o LED verde
    printf("LED VERDE LIGADO\n");
}

void controle_led_azul()
{
    if (led_azul_ativo)
    {
        gpio_put(blue, 0); // Desliga o LED azul
        led_azul_ativo = false;
        printf("LED azul DESLIGADO\n");
    }
    else
    {
        gpio_put(blue, 1); // Liga o LED azul
        led_azul_ativo = true;
        printf("LED azul LIGADO\n");
    }
}

void ativar_led_vermelho() { 
    gpio_put(green, 0);  // Desliga o LED verde antes de ligar o vermelho
    gpio_put(blue, 0);  // Desliga o LED azul antes de ligar o vermelho
    gpio_put(red, 1);  // Liga o LED vermelho(pino 13)
    sleep_ms(1000);      // Deixa o LED ligado por 1 segundo
    gpio_put(red, 0);  // Desliga o LED vermelho
    printf("LED VERMELHO LIGADO\n");
}

void desativar_todas_leds() { //INÁCIO

}

void ativar_todas_leds() {
    gpio_put(green, 1);  // Liga o LED verde
    gpio_put(blue, 1);   // Liga o LED azul
    gpio_put(red, 1);    // Liga o LED vermelho
    printf("TODOS LEDS LIGADOS\n");
}

void alternar_leds() {
    // Função para alternar os LEDs (verde, azul, vermelho) a cada 200ms
    gpio_put(red, 0);  // Desliga o LED vermelho antes de alternar
    gpio_put(green, 0);  // Desliga o LED verde antes de alternar
    gpio_put(blue, 0);  // Desliga o LED azul antes de alternar
     
     while(true){
          gpio_put(green, 1);
          sleep_ms(200);
          gpio_put(green, 0);
          gpio_put(blue, 1);
          sleep_ms(200);
          gpio_put(blue, 0);
          gpio_put(red, 1);
          sleep_ms(200);
          gpio_put(red, 0);
          printf("LEDS ALTERNANDO\n");
    }
}

void ativar_buzzer() {
    gpio_put(buzzer, 0); // Desliga o buzzer antes de começar
    gpio_put(buzzer, 1); // Liga o buzzer
    sleep_ms(500);       // Mantém o buzzer ligado por 0,5 segundo
    gpio_put(buzzer, 0); // Desliga o buzzer
    printf("BUZZER LIGADO\n");
}

// Inicialização do teclado matricial
void keypad_init() {
    // Inicializa as linhas do teclado (como saídas)
    for (int i = 0; i < rows; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], false);  // Inicializa as linhas como LOW
    }

    // Inicializa as colunas do teclado (como entradas) com pull-down
    for (int i = 0; i < cols; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_down(col_pins[i]);  // Garante que a leitura seja 0 quando não pressionado
    }
}

// Leitura das teclas pressionadas no teclado matricial
char read_keypad() {
    for (int row = 0; row < rows; row++) {
        gpio_put(row_pins[row], 1);  // Ativa uma linha de cada vez

        for (int col = 0; col < cols; col++) {
            if (gpio_get(col_pins[col])) {  // Se a tecla correspondente for pressionada
                gpio_put(row_pins[row], 0); // Desativa a linha após detectar a tecla
                sleep_ms(20);  // Espera um curto período para estabilizar a leitura
                return key_map[row][col]; // Retorna o valor da tecla pressionada
            }
        }
        gpio_put(row_pins[row], 0);  // Desativa a linha
    }
    return '\0';  // Retorna '\0' se nenhuma tecla for pressionada
}

// Inicialização dos LEDs
void leds_init() {
    gpio_init(green);  // Inicializa o pino do LED verde
    gpio_set_dir(green, GPIO_OUT);  // Define como saída

    gpio_init(blue);   // Inicializa o pino do LED azul
    gpio_set_dir(blue, GPIO_OUT);   // Define como saída

    gpio_init(red);    // Inicializa o pino do LED vermelho
    gpio_set_dir(red, GPIO_OUT);    // Define como saída
}

// Função principal
int main() {
    stdio_init_all();  // Inicializa a comunicação com o terminal
    keypad_init();     // Inicializa o teclado matricial
    leds_init();       // Inicializa os LEDs

    gpio_init(buzzer);     // Inicializa o pino do buzzer
    gpio_set_dir(buzzer, GPIO_OUT);  // Define como saída

    while (true) {
        char key = read_keypad();  // Lê a tecla pressionada no teclado

        if (key != '\0') {  // Se uma tecla foi pressionada
            switch (key) {
                case 'A':
                    ativar_led_verde();  // Ativa o LED verde ao pressionar a tecla A
                    break;
                case 'B':
                    controle_led_azul();
                    break;
                case 'C':
                    ativar_led_vermelho();  // Ativa o LED vermelho
                    break;
                case 'D':
                    ativar_todas_leds();  // Ativa todos os LEDs (verde, azul, vermelho)
                    break;
                case '#':
                    ativar_buzzer();  // Ativa o buzzer
                    break;
                case '*':
                    desativar_todas_leds();  // Desativa todos os LEDs
                    break;
                case '0':
                    alternar_leds();  // Alterna os LEDs (verde, azul, vermelho)
                    break;
            }
            printf("Tecla pressionada: %c\n", key);  // Exibe a tecla pressionada no terminal
            sleep_ms(200);  // Espera 200ms para evitar múltiplas leituras da mesma tecla
        }
    }
    return 0;
}
