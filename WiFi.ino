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

ESP8266WiFiMulti WiFiMulti;

const char fingerprint[] PROGMEM =  "5B FB D1 D4 49 D3 0F A9 C6 40 03 34 BA E0 24 05 AA D2 E2 01";
char json[400] = {0};

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

  //2 - iniciamos a conexão WiFi...
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID, PASSWD);

  //3 - acesse arduinojson.org/v6/assistant e passe uma amostra pra calcular a capacidade
  const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_ARRAY_SIZE(8) + 146;
  DynamicJsonDocument doc(capacity);

}

void loop() {
  Serial.println("loop started...");
        if ((WiFiMulti.run() == WL_CONNECTED)){
          std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
          client->setFingerprint(fingerprint);
          Serial.println("connected...");
          //WiFiClient client;

          HTTPClient http;

        //3 - iniciamos a URL alvo, pega a resposta e finaliza a conexão
        if (http.begin(*client,"https://fadasprojetotein.000webhostapp.com/")){
          Serial.println("http.begin ok");
        }
        int httpCode = http.GET();
        if (httpCode > 0) { //Maior que 0, tem resposta a ser lida
            String payload = http.getString();
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