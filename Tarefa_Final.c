/*
 * Dispositivo de Exercício com Elástico
 *
 * Este programa utiliza o display OLED SSD1306 e o microcontrolador RP2040
 * para criar um contador de repetições de exercício com elástico.
 * Monitora a força aplicada através do joystick analógico,
 * conta repetições e calcula calorias gastas.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "lib/ssd1306.h"
#include "lib/font.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define JOYSTICK_Y_PIN 27    // GPIO para medir a força do elástico
#define LED_VERDE 11         // GPIO para LED verde
#define LIMITE_FORCA 3800    // Valor máximo do ADC para contar uma repetição
#define CALORIAS_POR_REP 1.5 // Calorias gastas por repetição

int main()
{
  // Inicialização I2C
  i2c_init(I2C_PORT, 400 * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  // Inicialização do display
  ssd1306_t ssd;
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
  ssd1306_config(&ssd);
  ssd1306_send_data(&ssd);
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);

  // Inicializa o LED verde
  gpio_init(LED_VERDE);
  gpio_set_dir(LED_VERDE, GPIO_OUT);
  gpio_put(LED_VERDE, 0);

  // Inicializa ADC
  adc_init();
  adc_gpio_init(JOYSTICK_Y_PIN);

  // Variáveis de controle
  uint16_t valor_forca;
  int repeticoes = 0;
  bool rep_contada = false;
  absolute_time_t tempo_inicio = get_absolute_time();
  char str_tempo[20];
  char str_calorias[20];
  char str_reps[5];

  while (true)
  {
    // Lê o valor da força
    adc_select_input(1);
    valor_forca = adc_read();

    // Conta uma repetição quando atinge o limite de força
    if (valor_forca >= LIMITE_FORCA && !rep_contada)
    {
      repeticoes++;
      rep_contada = true;
    }
    else if (valor_forca < LIMITE_FORCA)
    {
      rep_contada = false;
    }

    // Calcula tempo e calorias
    float tempo_decorrido = absolute_time_diff_us(tempo_inicio, get_absolute_time()) / 1000000.0;
    float calorias = repeticoes * CALORIAS_POR_REP;

    // Verifica se completou 10 repetições
    if (repeticoes >= 10)
    {
      gpio_put(LED_VERDE, 1);
    }

    // Prepara as strings para exibição
    sprintf(str_reps, "%d", repeticoes);
    sprintf(str_tempo, "%.1f s", tempo_decorrido);
    sprintf(str_calorias, "%.1f kcal", calorias);

    // Atualiza o display
    ssd1306_fill(&ssd, false);
    ssd1306_rect(&ssd, 2, 2, 124, 60, true, false);

    // Título m
    ssd1306_draw_string(&ssd, "EXERCICIO", 35, 6);

    // Informações em duas colunas
   
    ssd1306_draw_string(&ssd, "R", 6, 28);
    ssd1306_draw_string(&ssd, str_reps, 45, 28);

    ssd1306_draw_string(&ssd, "T", 6, 40);
    ssd1306_draw_string(&ssd, str_tempo, 45, 40);

    
    ssd1306_draw_string(&ssd, "K", 6, 52);
    ssd1306_draw_string(&ssd, str_calorias, 45, 52);

    ssd1306_send_data(&ssd);
    sleep_ms(50);
  }
}