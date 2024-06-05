# Irrigation-system v 0.1
## Sistema de Irrigação Automatizado
Este projeto é um sistema de irrigação automatizado que usa dois sensores de umidade para determinar quando irrigar o solo. Ele também registra o tempo total de irrigação.
Código de estudo

### Componentes
* Arduino (ou similar)
* 2x Sensores de umidade do solo
* 1x Relé
* 1x Display LCD I2C
  
### Descrição do Código
O código começa incluindo a biblioteca **LiquidCrystal_I2C.h** para controlar o display LCD. Em seguida, define os pinos para os sensores de umidade e o relé.

O display LCD é inicializado com o endereço I2C, o número de colunas e linhas.

As variáveis de controle de irrigação são inicializadas. Estas incluem uma flag para indicar se o sistema está atualmente irrigando, o tempo de início da irrigação atual, a duração total da irrigação e o número total de irrigações.

A função **soloSeco(int pin)** lê o valor do sensor de umidade no pino especificado e retorna **true** se o valor lido for maior que 500, indicando que o solo está seco.

No **setup()**, os pinos são inicializados e o display LCD é configurado.

No **loop()**, o código lê os valores dos sensores de umidade. Se ambos os sensores indicarem que o solo está seco, o sistema inicia a irrigação. Se o sensor1 indicar que o solo está úmido, mas o sensor2 ainda indicar que o solo está seco e o sistema estiver atualmente irrigando, a irrigação continuará. Se ambos os sensores indicarem que o solo está úmido, a irrigação será interrompida.

Durante a irrigação, o tempo de irrigação é atualizado e exibido no display LCD. Quando a irrigação é interrompida, o tempo total de irrigação é atualizado e o número de irrigações é incrementado.

### Uso
Para usar este sistema, conecte os sensores de umidade e o relé aos pinos apropriados no Arduino. Carregue o código no Arduino e observe o display LCD para ver o status da irrigação. O sistema começará a irrigar automaticamente quando ambos os sensores de umidade indicarem que o solo está seco.
