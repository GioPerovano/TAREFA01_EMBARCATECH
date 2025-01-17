#include <stdio.h>
#include "pico/stdlib.h"

// Definições de linhas e colunas do teclado
#define rows 4
#define cols 4

// Definições dos pinos dos LEDs e do buzzer
#define green 11
#define blue 12
#define red 13
#define buzzer 21

// Mapeamento dos pinos do teclado
const uint8_t row_pins[rows] = {8, 7, 6, 5};  // R1, R2, R3, R4
const uint8_t col_pins[cols] = {4, 3, 2, 27}; // C1, C2, C3, C4

// Mapeamento do teclado matricial
const char key_map[rows][cols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Funções auxiliares para LEDs e buzzer
void ativar_led_verde() {
   
}

void ativar_led_azul() {
   
}

void ativar_led_vermelho() {
    
}

void desativar_todas_leds() {
    
}

void ativar_todas_leds() {
    
}

void alternar_leds() {
     
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
    }
    
}

void ativar_buzzer() {
    gpio_put(buzzer, 1);
    sleep_ms(500);
    gpio_put(buzzer, 0);
}

// Inicialização do teclado matricial
void keypad_init() {
    for (int i = 0; i < rows; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], false);
    }
    for (int i = 0; i < cols; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_down(col_pins[i]);
    }
}

// Leitura do teclado matricial
char read_keypad() {
    for (int row = 0; row < rows; row++) {
        gpio_put(row_pins[row], 1);

        for (int col = 0; col < cols; col++) {
            if (gpio_get(col_pins[col])) {
                gpio_put(row_pins[row], 0);
                sleep_ms(20);
                return key_map[row][col];
            }
        }
        gpio_put(row_pins[row], 0);
    }
    return '\0';
}

// Inicialização dos LEDs
void leds_init() {
    gpio_init(green);
    gpio_set_dir(green, GPIO_OUT);
    gpio_init(blue);
    gpio_set_dir(blue, GPIO_OUT);
    gpio_init(red);
    gpio_set_dir(red, GPIO_OUT);
}

// Função principal
int main() {
    stdio_init_all();
    keypad_init();
    leds_init();

    gpio_init(buzzer);
    gpio_set_dir(buzzer, GPIO_OUT);

    while (true) {
        char key = read_keypad();

        if (key != '\0') {
            switch (key) {
                case 'A':
                    //ativar_led_verde();
                    break;
                case 'B':
                    //ativar_led_azul();
                    break;
                case 'C':
                    //ativar_led_vermelho();
                    break;
                case 'D':
                    //ativar_todas_leds();
                    break;
                case '#':
                    ativar_buzzer();
                    break;
                case '*':
                   //desativar_todas_leds();
                    break;
                case '0':
                    alternar_leds();
                    break;
            }
            printf("Tecla pressionada: %c\n", key);  
            sleep_ms(200);  
        }
    }
    return 0;
}
