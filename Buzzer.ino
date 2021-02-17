#define trigPin D0 // Declara constante trigPin
#define echoPin D1 // Declara constante como echoPin
#define tempo 5 // Declara constante de tempo
 
int frequencia = 0; // Inicializa variável de frequência em 0
int Buzzer = D5; // Inicializa buzzer no pino 13
int duration, distance;// Inicializa variável de distância e tempo
 
void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(Buzzer, OUTPUT);
 digitalWrite(Buzzer, LOW);
}
 
void loop() {
  delay(200);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration / 2) / 29.1; // Define base do cálculo de conversão
 Serial.print("Distância= ");
 Serial.println(distance); 
 if ( distance < 19) { // Define as distâncias bases de verificação

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
 }

}
