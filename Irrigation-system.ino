#include <LiquidCrystal_I2C.h>

const int sensor1Pin = A0; // Sensor 15 cem profundidade
const int sensor2Pin = A1; // Sensor 60 cm de profundidade
const int relePin = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool irrigando = false;
unsigned long tempoInicioIrrigacao = 0;
unsigned long duracaoTotalIrrigacao = 0;
int contagemIrrigacoes = 0;

bool soloSeco(int pin) {
  int valor = analogRead(pin);
  return valor < 500; // Leitura do sensor de 0 a 1023 - próximo de 0 mais seco
}

void setup() {
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(relePin, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Sistema de");
  lcd.setCursor(0, 1);
  lcd.print("Irrigacao");
  delay(2000);
  lcd.clear();
}

void loop() {
  bool sensor1Seco = soloSeco(sensor1Pin);
  bool sensor2Seco = soloSeco(sensor2Pin);

  if (sensor1Seco && sensor2Seco) {
    if (!irrigando) {
      irrigando = true;
      tempoInicioIrrigacao = millis();
      digitalWrite(relePin, HIGH);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Irrigamento");
    }
  } else if (!sensor1Seco && sensor2Seco && irrigando) {
    // Continua irrigando e contando o tempo
  } else if (!sensor1Seco && !sensor2Seco) {
    if (irrigando) {
      irrigando = false;
      unsigned long tempoIrrigacao = millis() - tempoInicioIrrigacao;
      duracaoTotalIrrigacao += tempoIrrigacao;
      contagemIrrigacoes++;
      digitalWrite(relePin, LOW);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Irrigacoes: ");
      lcd.print(contagemIrrigacoes);
      lcd.setCursor(0, 1);
      unsigned long tempoTotalSegundos = duracaoTotalIrrigacao / 1000;
      int minutos = tempoTotalSegundos / 60;
      int segundos = tempoTotalSegundos % 60;
      lcd.print(minutos);
      lcd.print("m ");
      lcd.print(segundos);
      lcd.print("s");
    }
  }

  if (irrigando) {
    unsigned long tempoAtual = millis();
    unsigned long tempoIrrigando = (tempoAtual - tempoInicioIrrigacao) / 1000;
    int minutos = tempoIrrigando / 60;
    int segundos = tempoIrrigando % 60;

    lcd.setCursor(0, 1);
    lcd.print(minutos);
    lcd.setCursor(3, 1);
    lcd.print("m ");
    lcd.print(segundos);
    lcd.setCursor(7, 1);
    lcd.print("s");
  }
}