#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>
#include <WiFiClient.h>
#include "ArduinoJson.h"

#define SSID "SEPTO"
#define PASSWD "septowork"

#define trigPin D0 // Declara constante trigPin
#define echoPin D1 // Declara constante como echoPin
#define tempo 10 // Declara constante de tempo

ESP8266WiFiMulti WiFiMulti;

const char fingerprint[] PROGMEM =  "5B FB D1 D4 49 D3 0F A9 C6 40 03 34 BA E0 24 05 AA D2 E2 01";
char json[400] = {0};
 
int frequencia = 0; // Inicializa variável de frequência em 0
int Buzzer = null; // Inicializa buzzer no pino 13 - procurar a pinagem do buzzer que não sabemos
int duration, distance; // Inicializa variável de distância e tempo

int LED = D3;
int LDR = A0; // Pino no qual o LDR está conectado
int entrada = 0; // Variável que receberá o valor lido do LDR

int LEDPis = D4;

StaticJsonDocument<256> doc;

void resultOfGet(String msg){
    memset(json,0,sizeof(json));
    msg.toCharArray(json, 400);
    deserializeJson(doc, json);

    JsonObject ticker = doc["ticker"];
    const char* ticker_high = ticker["high"]; // "33395.00000000"
    const char* ticker_low = ticker["low"]; // "32911.01001000"
    const char* ticker_vol = ticker["vol"]; // "29.80139592"
    const char* ticker_last = ticker["last"]; // "33146.89715000"
    const char* ticker_buy = ticker["buy"]; // "33005.10011000"
    const char* ticker_sell = ticker["sell"]; // "33146.89715000"
    const char* ticker_open = ticker["open"]; // "33094.94851000"
    long ticker_date = ticker["date"]; // 1578889119

    Serial.println(ticker_last);
}

void setup() {
  //1 - Para testar, vamos usar a serial
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LEDPis, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Buzzer, OUTPUT);
  
  //2 - iniciamos a conexão WiFi...
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID, PASSWD);

  //3 - acesse arduinojson.org/v6/assistant e passe uma amostra pra calcular a capacidade
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_ARRAY_SIZE(8) + 146;
  DynamicJsonDocument doc(capacity);

}

void loop() {
  Serial.println("loop started...");


       digitalWrite(trigPin, HIGH);
       delayMicroseconds(10);
       digitalWrite(trigPin, LOW);
       duration = pulseIn(echoPin, HIGH);
       distance = (duration / 2) / 29.1; // Define base do cálculo de conversão
       
       if (distance >= 40 || distance <= 0) { // Define as distâncias bases de verificação
       Serial.println("Ninguem na area");
       digitalWrite(LEDPis, LOW); // teste já q n tem pino de buzzer
       }
       
       else {
       Serial.println("Pessoa Detectada");
       Serial.print("Distância= ");
       Serial.print(distance); // Imprime o valor da distância no Monitor Serial

       digitalWrite(Buzzer, HIGH); // acionando buzzer - caso queira testar o led, colocar o led da piscina no lugar do buzzer
       
       for (frequencia = 150; frequencia < 1800; frequencia += 1) { // Tone que produz sirene de polícia
       tone(Buzzer, frequencia, tempo);
       delay(3);
       }
       for (frequencia = 1800; frequencia > 150; frequencia -= 1) { // Tone que produz sirene de polícia
       tone(Buzzer, frequencia, tempo);
       delay(3);
       }
       }
        
        
        entrada = analogRead(LDR);
        Serial.println(entrada); // Valor que será exibido no Serial Monitor
        if (entrada > 900) // Quanto maior a leitura, menor é a luminosidade
        {
        digitalWrite(LED, HIGH); // Acender o LED
        }
        else
        {
        digitalWrite(LED, LOW); // Apagar o LED
        delay(100);
        }
        
        if ((WiFiMulti.run() == WL_CONNECTED)){
          std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
          client->setFingerprint(fingerprint);
          Serial.println("connected...");
          //WiFiClient client;

          HTTPClient http;

        //3 - iniciamos a URL alvo, pega a resposta e finaliza a conexão
        if (http.begin(*client,"https://tein-g3.000webhostapp.com")){
          Serial.println("http.begin ok");
        }
        int httpCode = http.GET();
        if (httpCode > 0) { //Maior que 0, tem resposta a ser lida
            String payload = http.getString();

            if (payload == "1") {
              digitalWrite(LEDPis, HIGH);
              
            } else {
              digitalWrite(LEDPis, LOW);
              
            }
            
            Serial.println(httpCode);
            Serial.println(payload);
            resultOfGet(payload);
        }
        else {
          Serial.println(httpCode);
            Serial.println("Falha na requisição");
        }
        http.end();
        }
        delay(5000);
}