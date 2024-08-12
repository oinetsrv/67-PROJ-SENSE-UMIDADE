/* =================================================================================
    Projeto: Medidor de Umidade e Temperatura em Fluxo de Secagem.
    Autor: Eng. Stenio Rodrigues         Data:  maio de 2024.
                                                                                    */
// =================================================================================
// --- Bibliotecas Auxiliares       ---
// --- Mapeamento de Hardware       ---
// --- Instâncias                   ---
// --- Variáveis Globais            ---
// --- Protótipo das Funções        ---
// --- Configurações setup          ---
// --- Loop Infinito                ---
// --- Desenvolvimento das Funções  ---
// =================================================================================
// --- Bibliotecas Auxiliares       ---
#include "driver/gpio.h"
#include "driver/dedic_gpio.h"

// =================================================================================
// --- Mapeamento de Hardware       ---
const int interruptPin = 21;
#define  db7  16
#define  db6  17
#define  db5  18
#define  db4  19

#define  rs   4
#define  en   2  

#define DB7 GPIO_NUM_16
#define DB6 GPIO_NUM_17
#define DB5 GPIO_NUM_18
#define DB4 GPIO_NUM_19

#define RSS GPIO_NUM_4
#define ENN GPIO_NUM_2

 
// =================================================================================
// --- Variáveis Globais            ---
volatile bool has_interrupted = false;
volatile bool dataReady       = false;
int k                         =     0;
volatile  byte m_b002         = B00000000;
byte            rs_b01        = B00000000;
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
                            B00000000, B00000000, B00000000, B00000000,
                            B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000, 
                            B00000000, B00000000, B00000000, B00000000,
                            B00000000, B00000000, B00000000, B00000000};
unsigned long timeold = 0,      // Variavel conta tempo em milis contador
              tld_end = 0;
// =================================================================================
// --- Protótipo das Funções        ---
void IRAM_ATTR myInterruptFunction  ();
void IRAM_ATTR blink                ();
// =================================================================================
// --- Configurações setup          ---
void setup                          (){
 


  gpio_set_direction(DB7, GPIO_MODE_INPUT); 
  gpio_set_direction(DB6, GPIO_MODE_INPUT); 
  gpio_set_direction(DB5, GPIO_MODE_INPUT); 
  gpio_set_direction(DB4, GPIO_MODE_INPUT); 

  gpio_set_direction(RSS, GPIO_MODE_INPUT); 
  gpio_set_direction(ENN, GPIO_MODE_INPUT); 

  
  gpio_set_pull_mode(DB7, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(DB6, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(DB5, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(DB4, GPIO_PULLUP_ONLY);
  
  gpio_set_pull_mode(RSS, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode(ENN, GPIO_PULLUP_ONLY);

  Serial.begin(115200);
  Serial.println("ESP32_BASIC por rs");
  // versão so software sem registradores
  pinMode(interruptPin, INPUT ); // Configure the pin as an input with internal pull-up resistor
  pinMode(db7, INPUT );
  pinMode(db6, INPUT );
  pinMode(db5, INPUT );
  pinMode(db4, INPUT );
  pinMode(en , INPUT );
  pinMode(rs , INPUT );
  //attachInterrupt(digitalPinToInterrupt(en), myInterruptFunction, RISING); // Configure the interrupt
  attachInterrupt(digitalPinToInterrupt(rs), blink, RISING);
} // END void setup ()
// =================================================================================
// --- Loop Infinito                ---
void loop             (){
  // ALFAFA
 /* D7 D6 D5 D4       D7 D6 D5 D4       os quatro primeiros bits BYTE HEX 41
    0  1  0  0        0  0  0  1  
A 41  0100 0001 
L 4C  0100 1100
F 46  0100 0110  
A 41  0100 0001 
F 46  0100 0110  
A 41  0100 0001  */
  
if (dataReady) {
   
      for (size_t i = 0; i < sizeof(m_b001); i += 2) {
          rs_b01 = m_b001[i + 1] + (m_b001[i] << 4);
          // Serial.println(m_b002, BIN); // dado bruto
           Serial.println(m_b001[i], BIN); // dado bruto
          // Serial.println(rs_b01, BIN);
          // Serial.println(rs_b01, HEX);
          //Serial.print((char)rs_b01);
          Serial.print(" ");
      } // END for
    k = 0;
    m_b002 = B00000000;
    for (size_t i = 0; i < sizeof(m_b001); i++) m_b001[i] = B00000000;
    Serial.println("-");
    dataReady = false;
    tld_end = millis();
} // END IF

if (millis() - tld_end >= 3000){
      dataReady = true;
      k = 0;
} 

} // END void loop()
// =================================================================================
void IRAM_ATTR myInterruptFunction() {
  //has_interrupted = true;
  REG_WRITE(GPIO_OUT_W1TS_REG, BIT2);//GPIO2 HIGH (set)
  delay(250);
  REG_WRITE(GPIO_OUT_W1TC_REG, BIT2);//GPIO2 LOW (clear)
  delay(250);
  // Here you can add the code that will be executed when the interrupt occurs
} // end void IRAM_ATTR myInterruptFunction()
// =================================================================================
void IRAM_ATTR blink (){
    int ate = 0;
    
    ate = (gpio_get_level(DB4) ? (m_b002 |= (1 << 0)) : (m_b002 &= ~(1 << 0))); // db4
    ate = (gpio_get_level(DB5) ? (m_b002 |= (1 << 1)) : (m_b002 &= ~(1 << 1))); // db5
    ate = (gpio_get_level(DB6) ? (m_b002 |= (1 << 2)) : (m_b002 &= ~(1 << 2))); // db6
    ate = (gpio_get_level(DB7) ? (m_b002 |= (1 << 3)) : (m_b002 &= ~(1 << 3))); // db7
    m_b001[k] = m_b002;
    k++;
    if (k > 34)
      dataReady = true;
} // END void IRAM_ATTR blink ()
// =================================================================================