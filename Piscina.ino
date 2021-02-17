int pino_som = D2; //Define o pino que será utilizado para o sensor de som
int pino_rele = D4;     //E o que será utilizado para o rele
boolean rele = HIGH; // Define um booleano para poder usar a operacao NAO
 
void setup() {
  pinMode(pino_som, INPUT); //Coloca o pino do sensor de som como entrada
  pinMode(pino_rele, OUTPUT);   // E o do rele como saida
  attachInterrupt(digitalPinToInterrupt(pino_som), funcaoMic, RISING);
}
 
void loop() {

   
   
}
ICACHE_RAM_ATTR void funcaoMic(){
    rele = !rele; //Operacao NAO: Se estiver LOW, passa pra HIGH. Se estiver HIGH passa para LOW
    digitalWrite(pino_rele, rele); // Manda o valor da variavel para o rele

  }
