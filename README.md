# Dispositivo de Exercício com Elástico

Este projeto utiliza um display OLED SSD1306 e o microcontrolador RP2040 para criar um contador de repetições de exercício com elástico. O dispositivo monitora a força aplicada através de um joystick analógico, conta repetições e calcula calorias gastas.

## Componentes Necessários

- Microcontrolador RP2040
- Display OLED SSD1306
- Joystick analógico
- LED verde
- Resistores e fios de conexão

## Configuração do Hardware

1. **Conexões I2C para o Display OLED:**

   - SDA: GPIO 14
   - SCL: GPIO 15

2. **Conexão do Joystick:**

   - Eixo Y: GPIO 27

3. **Conexão do LED Verde:**
   - LED: GPIO 11

## Instruções de Compilação e Execução

1. **Configuração do Ambiente:**

   - Certifique-se de ter o SDK do Raspberry Pi Pico configurado no seu ambiente de desenvolvimento.

2. **Compilação:**

   - Compile o código utilizando o CMake e o Makefile fornecidos pelo SDK do Raspberry Pi Pico.

3. **Upload:**

   - Carregue o binário compilado no microcontrolador RP2040.

4. **Execução:**
   - Conecte o dispositivo a uma fonte de alimentação e observe o display OLED para as informações de repetições, tempo e calorias.

## Funcionamento

- O dispositivo conta uma repetição quando a força aplicada no joystick atinge um valor predefinido.
- Após 10 repetições, o LED verde acende.
- O display OLED mostra o número de repetições, o tempo decorrido e as calorias gastas.

## Link do vídeo

https://drive.google.com/file/d/1WJdwBd8EgkV2_d3HcdsqNM8RtqCazG3H/view?usp=sharing
