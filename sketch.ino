#include "DHT.h"

#define DHTPIN 15         
#define DHTTYPE DHT22     

#define LDRPIN 34        
#define BTN_N_PIN 12      
#define BTN_P_PIN 14    
#define BTN_K_PIN 27      
#define RELAY_PIN 26      

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  pinMode(BTN_N_PIN, INPUT_PULLUP);
  pinMode(BTN_P_PIN, INPUT_PULLUP);
  pinMode(BTN_K_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(RELAY_PIN, LOW); 
  dht.begin();
  
  Serial.println("=========================================");
  Serial.println(" FarmTech Solutions - Cultivo de Tomate  ");
  Serial.println("=========================================");
}

void loop() {
  float humidadeSolo = dht.readHumidity();

  int leituraLdr = analogRead(LDRPIN);
  float valorPh = map(leituraLdr, 0, 4095, 0, 1400) / 100.0;

  bool nutN = (digitalRead(BTN_N_PIN) == LOW);
  bool nutP = (digitalRead(BTN_P_PIN) == LOW);
  bool nutK = (digitalRead(BTN_K_PIN) == LOW);
  bool nutOk = nutN && nutP && nutK;

  Serial.print("Humidade Solo: "); Serial.print(humidadeSolo); Serial.print("% | ");
  Serial.print("pH Solo: "); Serial.print(valorPh); Serial.print(" | ");
  Serial.print("NPK: "); Serial.println(nutOk ? "COMPLETO" : "INCOMPLETO");

  if (humidadeSolo < 65.0 && (valorPh >= 6.0 && valorPh <= 6.8) && nutOk) {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("STATUS: [Bomba LIGADA] - Irrigando cultura.");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("STATUS: [Bomba DESLIGADA] - Condicoes normais.");
  }

  delay(2000);
}