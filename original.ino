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

const char fingerprint[] PROGMEM = "5B FB D1 D4 49 D3 0F A9 C6 40 03 34 BA E0 24 05 AA D2 E2 01";

int LED = D3;
int LDR = A0; // LRD tá conectado aqui
int input = 0; // recebe o valor lido de LDR
 
int frequency = 0; // inicia frequência em 0
int Buzzer = D5; // pino do buzzer = ?? - não sabemos a pinagem do buzzer

int piscina = D4;

char json[400] = {0};
StaticJsonDocument<256> doc;

void setup() {
  // usando a serial pra testes
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(piscina, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Buzzer, OUTPUT);
  
  // iniciando conexão wifi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID, PASSWD);

  // acesse arduinojson.org/v6/assistant e passe uma amostra pra calcular a capacidade
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_ARRAY_SIZE(8) + 146;
  DynamicJsonDocument doc(capacity);

}

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

void loop() {
  Serial.println("loop iniciado");                 
      if ((WiFiMulti.run() == WL_CONNECTED)){
        std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
        client->setFingerprint(fingerprint);
        Serial.println("connected...");
        //WiFiClient client;

        HTTPClient http;

        // iniciamos a URL alvo, pega a resposta e finaliza a conexão
        if (http.begin(*client,"https://fadasprojetotein.000webhostapp.com/values.php")){
          Serial.println("http.begin ok");
        }
        int httpCode = http.GET();
        if (httpCode > 0) { // caso seja maior que 0, tem resposta a ser lida
            String payload = http.getString();

            if (payload.indexOf("1")) {
              digitalWrite(piscina, HIGH);              
            } else {
              digitalWrite(piscina, LOW);              
            }

            if (payload.indexOf("3")) {
              digitalWrite(Buzzer, HIGH);              
            } else {
              digitalWrite(Buzzer, LOW);              
            }

            if (payload.indexOf("5")) {
              digitalWrite(LED, HIGH);              
            } else {
              digitalWrite(LED, LOW);              
            }

            if (payload.indexOf("7")) {
              input = analogRead(LDR);
              Serial.println(input);
              if (input > 900) // quanto maior a leitura, menor é a luminosidade
              {
                digitalWrite(LED, HIGH); // Acender o LED
              }
              else
              {
                digitalWrite(LED, LOW); // Apagar o LED
                delay(100);
              }        
            } else {
              digitalWrite(LED, LOW);              
            }

            if (payload.indexOf("9")) {
              Serial.println("Tem alguém vindo!");                                          
              digitalWrite(trigPin, HIGH);              
            } else {
              Serial.println("Ninguém por perto!");
              digitalWrite(trigPin, LOW);              
            }            
            
            Serial.println(httpCode);
            Serial.println(payload);
            resultOfGet(payload);
        }
        else {
          Serial.println(httpCode);
          Serial.println("Falha durante a requisição");
        }
      http.end();
      }
  delay(5000);
}