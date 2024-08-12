/* ===========================================================================================
    Projeto: Leitor de display barramento 4 bits.
    Autor: Eng. Stenio Rodrigues         Data:  JULHO de 2024.
    Versão: Etapas do projeto definidas com Vx.xx

   Descrição do projeto:
        Funções mínimas esperadas. 
        ler mensagens enviadas para display e reenviar via rede 485                  */
// =================================================================================
// --- Bibliotecas Auxiliares       ---
// --- Mapeamento de Hardware       ---
// --- Instâncias                   ---
// --- Variáveis Globais            ---
// --- Protótipo das Funções        ---
// --- Configurações setup          ---
// --- Loop Infinito                ---
// --- Desenvolvimento das Funções  ---
// --- Mapeamento de Hardware       ---
// --- Instâncias                   ---
// =================================================================================
// --- Bibliotecas Auxiliares       ---
#include "Wire.h" 
#include <Bonezegei_PCF8574.h>
#define  en   2 
// =====================================================================================
// --- Mapeamento de Hardware       ---
// =====================================================================================
// --- Instâncias                   ---
Bonezegei_PCF8574 io(0x27); // instancia para ler o I/O do PC8574


// =====================================================================================
// --- Variáveis Globais            ---
volatile uint8_t k = 0;
int pressed = 0;

volatile  byte m_b002 = B00000000;
volatile  byte m_b001[] = { B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000,
                            B00000000, B00000000, B00000000, B00000000,
                            B00000000, B00000000, B00000000, B00000000,
                            B00000000, B00000000, B00000000, B00000000,
                            B00000000, B00000000, B00000000, B00000000};
// =====================================================================================
// --- Protótipo das Funções        ---
void qual_end_I2C_PC8574  (); // Identificar na rede I2C qual é o endereço.
void ler_portas_PC8574    ();
// =====================================================================================
void  readData() {
      m_b002 = io.read();
      //m_b002 = B10000000;
      m_b001[k] = m_b002;
      k++;
      if (k>13) pressed = 1;
}
// --- Configurações Iniciais       ---
void setup() {
  Serial.begin    (9600       );
  Serial.println  ("I2C_PC8574_INPUT ");
  Wire.begin      (           );
  io.begin        (           );
  pinMode         (en, INPUT  );
 
} //end setup

// =====================================================================================
// --- Loop Infinito ---
void loop() {
      //qual_end_I2C ();
      ler_portas_PC8574 ();
      // testar ler io via io.read(); sempre que tiver interrupção.
      if (digitalRead(en) == HIGH) {
          //readData();
      }
      
  if (pressed == 1) {
    for (size_t i = 0; i < sizeof(m_b001); i++) Serial.println(m_b001[i], BIN); 
    for (size_t i = 0; i < sizeof(m_b001); i++) m_b001[i] = B00000000;
    Serial.println("");
    m_b002 = B00000000;
    pressed = 0;
    k = 0;
  } // END if (pressed == 1)
} //end loop
// =====================================================================================
void ler_portas_PC8574 (){
    Serial.println("DDDDERR"); 
    Serial.println("7654NWS:"); 
    Serial.println(io.read(),BIN);
    // pesquisar sobre Fast-mode no PCF8574

    /* io.read()
     //Inizializzazione I2C
  Wire.begin();
  Wire.setClock(400000);
  aqui o cara subiu a frequencia da rede wire para ler mais rapido
  analizar!
    Wire.requestFrom(_addr | 0x01, 1);
    while (Wire.available()) {
    p_read = Wire.read();
    }
    */
    Serial.println("\n"); 
    delay(3000);
}// END void ler_portas_PC8574 (){
// === --- Desenvolvimento das Funções  --- ============================================
void qual_end_I2C (){
  byte error, address;
  int nDevices = 0;
  delay(6000);
  Serial.println("procurando por I2C devices ...");
    for (address = 0x01; address < 0x7f; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
          if (error == 0) {
            Serial.print("I2C encontrado: 0x");
            Serial.print(address, HEX);
            Serial.println("\n");
            nDevices++;
          } else if (error != 2) {
            Serial.println("Error address \n");
            Serial.println(address);
          }
    }// END for
  if (nDevices == 0) Serial.println("No I2C devices found");
}// END void qual_end_I2C (){
// =====================================================================================

/*
se RS leia o bit
aguarde 4 us e leia o outro bit
MENSAGEM ENVIADA
A 41  0100 0001 
L 4C  0100 1100
F 46  0100 0110  
A 41  0100 0001 
F 46  0100 0110 X
A 41  0100 0001 
 ALFAFA
 /* D7 D6 D5 D4       D7 D6 D5 D4       os quatro primeiros bits BYTE HEX 41
    0  1  0  0        0  0  0  1  
 */
 
