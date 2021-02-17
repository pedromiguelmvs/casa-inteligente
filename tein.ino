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
