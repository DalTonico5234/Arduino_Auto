# Arduino_Auto
## Resumo
Projeto desenvolvido para a disciplina de PIC-1 do curso de Engenharia de Computação da UFES.

Consiste em um robô de duas rodas, projetado para se equilibrar automaticamente por meio de ajustes precisos realizados por um motor de passo, garantindo estabilidade e eficiência no seu funcionamento.

## Estrutura
Sua estrutura é constituída por duas rodas ligadas a dois motores de passo Nema 17, que são ligados à uma placa de mdf de 16x11.5 cm. A placa tem quatro furos que permitem a passagem de 4 fusos trapezoidais, que a conecta com duas placas de mdf de mesmo tamanho situadas acima da primeira.\
Assim, a estrutura do carrinho se assemelha a uma torre, na qual são conectados todos os componentes.

Utiliza um Acelerômetro e Giroscópio 3 Eixos MPU-6050 para detectar a inclinação da torre em relação à horizontal, fornecendo a base para os cálculos do ajuste do motor. \
Utiliza um Driver Motor de Passo A4988 para gerenciar simultaneamente ambos os motores.\
Seu código é executado por uma placa ESP32S NodeMcu ESP-12, que faz todos os cálculos de ajuste, assim como a maioria das conexões.\
A placa recebe uma tensão de entrada de 5V, obtida usando uma bateria alcalina de 9V e um Regulador de Tensão Step Down LM2596.\
Ambos os motores recebem a alimentação de outra bateria alcalina de 9V, conectada ao driver.

![Esquemático completo do projeto](/esquematico.pdf)

## Código
O código do projeto inclui as bibliotecas da Adafruit para o MPU-6050 e para sensores gerais. Também inclui as bibliotecas de conexão Wire, Wifi, WifiClient e a biblioteca do aplicativo Blynk BlynkSimpleEsp32.

Se inicia no setup, definindo a taxa de comunicação serial e realizando a conexão com o aplicativo personalizável Blynk, responsável por receber e enviar todos os comandos remotos ao robô. Além disso, ele define as portas que serão usadas, além de configurar algumas funções de bibliotecas que serão usadas no loop principal. Também realiza a conexão e inicialização do acelerômetro e giroscópio.

No loop principal ocorre a chamada das funções que obtêm a inclinação do carrinho. Também são executadas as funções de balanceamento, usando como parâmetro o eixo Z do MPU-6050, e as de recebimento de comandos enviados via Blynk.