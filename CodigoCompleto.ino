#include <ESP8266WebServer.h>

#define pinBotao1 16
#define pinBotao2 2
#define trigPin D0 // Declara constante trigPin
#define echoPin D1 // Declara constante como echoPin
#define tempo 2 // Declara constante de tempo
 
int frequencia = 0; // Inicializa variável de frequência em 0
int Buzzer = D5; // Inicializa buzzer no pino 13
int duration, distance;// Inicializa variável de distância e tempo

int ledPin = D3; //Led no pino 7
int ldrPin = A0; //LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR

int pino_som = D2; //Define o pino que será utilizado para o sensor de som
int pino_rele = D4;     //E o que será utilizado para o rele
boolean rele = HIGH; // Define um booleano para poder usar a operacao NAO

long pledt = 0;

long intervalo = 1000;

ESP8266WebServer server(80);
String botao1="",botao2="";

void pagina(){
    String s="";
    s+= " <!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Testando</title><meta charset=\"utf-8\"><style type=\"text/css\"> ";
    s+= " .onoffswitch {position: relative; width: 90px;-webkit-user-select:none; -moz-user-select:none; -ms-user-select: none;margin-left:70%;} ";
    s+= " .entradaonoff {display: none;}.texto-onoff {display: block; overflow: hidden; cursor: pointer;border: 2px solid #999999; border-radius: 20px;} ";
    s+= " .spanonoff {display: block; width: 200%; margin-left: -100%;transition: margin 0.3s ease-in 0s;} ";
    s+= " .spanonoff:before, .spanonoff:after {display: block; float: left; width: 50%; height: 30px; padding: 0; line-height: 30px; ";
    s+= " font-size: 14px; color: white; font-family: Trebuchet, Arial, sans-serif; font-weight: bold;box-sizing: border-box;} ";
    s+= " .spanonoff:before {content: 'ON';padding-left: 10px;background-color: green; color: #FFFFFF;} ";
    s+= " .spanonoff:after {content: 'OFF';padding-right: 10px;background-color: red; color: #FFF;text-align: right;} ";
    s+= " .bola-onoff {display: block; width: 18px; margin: 6px;background: #FFFFFF;position: absolute; top: 0; bottom: 0; ";
    s+= " right: 56px;border: 2px solid #999999; border-radius: 20px;transition: all 0.3s ease-in 0s;} ";
    s+= " .entradaonoff:checked + .texto-onoff .spanonoff {margin-left: 0px;}.entradaonoff:checked + .texto-onoff .bola-onoff {right: 0px;} ";
    s+= " .teste{background-color: green;border: 2px solid black;}</style></head> ";
    s+= " <body><h1 class=\"teste\">Alarme</h1><div class='onoffswitch'><form action='/salvo1' method='POST' id='formu1'> ";
    s+= " <input onclick= enviar1() name='tes1' type='checkbox' class='entradaonoff' id='onoff' "+botao1+"><label class='texto-onoff' for='onoff'><span class='spanonoff'></span> ";
    s+= " <span class='bola-onoff'></span></label></form></div><br> ";

    s+= " < type='text/java'>function enviar1() {document.getElementById('formu1').submit();}";
    s+= " function enviar2() {document.getElementById('formu2').submit();}";
    s+= "function enviar3() {document.getElementById('formu3').submit();} </>";
    s+= "</body></html> ";
    server.send(200,"text/html",s);
}

void altera_botao1(){
    if (server.arg("tes1")=="on"){
        botao1="checked";
        digitalWrite(pinBotao1,LOW);
    }
    else{
        botao1="";
        digitalWrite(pinBotao1,HIGH);
    }
    pagina();
}
void altera_botao2(){
    if (server.arg("tes2")=="on"){
        botao2="checked";
        digitalWrite(pinBotao2,LOW);
    }
    else{
        botao2="";
        digitalWrite(pinBotao2,HIGH);
    }
    pagina();
}

void configurarAP(void) {
    WiFi.mode(WIFI_AP);
    delay(100);
    WiFi.softAP("Trab-Tein", "12345678", 10);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig (IPAddress(192, 168, 0, 65), IPAddress (192, 168, 0, 1), subnet);
}

void setup() {
    pinMode(pinBotao1,OUTPUT);
    pinMode(pinBotao2,OUTPUT);
    digitalWrite(pinBotao1,HIGH);
    digitalWrite(pinBotao2,HIGH);

    Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(Buzzer, OUTPUT);
 digitalWrite(Buzzer, LOW);

  pinMode(pino_som, INPUT); //Coloca o pino do sensor de som como entrada
  pinMode(pino_rele, OUTPUT);   // E o do rele como saida
  attachInterrupt(digitalPinToInterrupt(pino_som), funcaoMic, RISING);

pinMode(ledPin,OUTPUT); //define a porta 7 como saída
    configurarAP();
    server.on("/",pagina);
    server.on("/salvo1",altera_botao1);
    server.on("/salvo2",altera_botao2);
    server.begin();
}
void loop() {
  server.handleClient();
  delay(200);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration / 2) / 29.1; // Define base do cálculo de conversão
 Serial.print("Distância= ");
 Serial.println(distance); 
 if ( distance < 19 &&  botao1=="checked") { // Define as distâncias bases de verificação

  Serial.println("Pessoa Detectada");
 // Imprime o valor da distância no Monitor Serial
 
   for (frequencia = 150; frequencia < 1800; frequencia += 1) { // Tone que produz sirene de polícia
     tone(Buzzer, frequencia, tempo);
     delay(3);
   }
   for (frequencia = 1800; frequencia > 150; frequencia -= 1) { // Tone que produz sirene de polícia
     tone(Buzzer, frequencia, tempo);
     delay(3);
   }
  }
 
 else {
    digitalWrite(Buzzer, LOW);
    noTone(Buzzer);
 }
  ///ler o valor do LDR
 ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
 
 //se o valor lido for maior que 500, liga o led
 if (ldrValor>= 800) digitalWrite(ledPin,HIGH);
 // senão, apaga o led
 else digitalWrite(ledPin,LOW);
 
 //imprime o valor lido do LDR no monitor serial
 Serial.println(ldrValor);
 delay(100);

}
ICACHE_RAM_ATTR void funcaoMic(){
    unsigned long ledt = millis();
    if (ledt - pledt > intervalo){
          pledt = ledt;
          rele = !rele; //Operacao NAO: Se estiver LOW, passa pra HIGH. Se estiver HIGH passa para LOW
          digitalWrite(pino_rele, rele); // Manda o valor da variavel para o rele
    }
  }
