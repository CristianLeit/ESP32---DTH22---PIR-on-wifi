#include "EspMQTTClient.h"
#include "DHTesp.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 4, 5, 18, 19, 21);

EspMQTTClient client(
  "Wokwi-GUEST",         // SSID WiFi
  "",                    // Password WiFi
  "test.mosquitto.org",  // MQTT Broker
  "mqtt-wokwi",          // Client
  1883                   // MQTT port
);

const int DHT_PIN = 22;
DHTesp dhtSensor;

const int PIR_PIN = 15;// Pino do sensor PIR
int ledPin = 23;
int val1 = 0; // Variável para armazenar o valor do sensor PIR
int currentState1 = 0; // Variável para armazenar o estado atual do sensor PIR
int previousState1 = 0; // Variável para armazenar o estado anterior do sensor PIR
int sensorState1 = LOW; // Variável para armazenar o estado do sensor PIR (inicialmente definido como LOW)
int counterSum = 0; // Variável para armazenar a soma dos acionamentos
int counter1 = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "Vou ficar offline");

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Data Bee!");
  lcd.setCursor(0, 1);
  lcd.print("   INJECTION   ");
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CM126 | ");
  lcd.setCursor(8, 0);
  lcd.print("T:");
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.setCursor(8, 1);
  lcd.print("Q:");
}

/**
 * @brief Ler os dados do Sensor PIR, imprime e envia via MQTT
 */
void lerEnviarDados() {
  int pirValue = digitalRead(PIR_PIN);
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  String status = (pirValue == HIGH) ? "Detectado" : "Não detectado";

  Serial.println("Status do PIR: " + status);
  Serial.println("Qtd:"+ counterSum);
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidade: " + String(data.humidity, 1) + "%");
  Serial.println("---");

  client.publish("topicowokwi/Temp", String(data.temperature, 2) + "°C"); 
  client.publish("topicowokwi/Humidade", String(data.humidity, 1) + "%");
  client.publish("topicowokwi/PIR", status);
}

/**
 * @brief Esta função é chamada quando tudo estiver conectado (Wifi e MQTT),
 * para utilizá-la deve-se implemtentar o struct EspMQTTClient
 */
void onConnectionEstablished()
{
  // Subscribe no "topicowokwi/msgRecebida/#" e mostra a mensagem recebida na Serial
  client.subscribe("topicowokwi/msgRecebida/#", [](const String & topic, const String & payload) {
    Serial.println("Mensagem recebida no topic: " + topic + ", payload: " + payload);
  });

  lerEnviarDados();
}


void loop() {
  client.loop();
  val1 = digitalRead(PIR_PIN);

  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  lcd.setCursor(10, 0);
  lcd.print(String(data.temperature, 2)+ "C");
  lcd.setCursor(2, 1);
  lcd.print(String(data.humidity, 1) + "%");
  
  if (val1 == HIGH) {
    digitalWrite(ledPin, HIGH);
    if (sensorState1 == LOW) {
      currentState1 = 1;
      sensorState1 = HIGH;
      delay(100);
    }
  } else {
     digitalWrite(ledPin, LOW);
    if (sensorState1 == HIGH) {
      currentState1 = 0;
      sensorState1 = LOW;
    }
  }
  
  if (currentState1 != previousState1) {
    if (currentState1 == 1) {
      counter1 = counter1 + 1;
      lcd.setCursor(10, 1);
      lcd.print(counter1);
      delay(100);
    }
  }

  previousState1 = currentState1;
}
