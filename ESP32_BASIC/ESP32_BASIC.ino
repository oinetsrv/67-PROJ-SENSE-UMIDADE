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
// --- Bibliotecas Auxiliares       ---

// =================================================================================
// --- Mapeamento de Hardware       ---
const int interruptPin = 21;
#define  db7  16
#define  db6  17
#define  db5  18
#define  db4  19

#define  rs   4
#define  en   2  
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
  //REG_WRITE(GPIO_ENABLE_REG, BIT18); //degine GPI18 como saida 
  //REG_WRITE(GPIO_ENABLE_W1TC_REG, BIT19); //como entrada db4
  Serial.begin(115200);
  Serial.println("ESP32_BASIC");
  // versão so software sem registradores
  pinMode(interruptPin, INPUT ); // Configure the pin as an input with internal pull-up resistor
  pinMode(db7, INPUT );
  pinMode(db6, INPUT );
  pinMode(db5, INPUT );
  pinMode(db4, INPUT );
  pinMode(en , INPUT );
  pinMode(rs , INPUT );
  //attachInterrupt(digitalPinToInterrupt(en), myInterruptFunction, RISING); // Configure the interrupt
  attachInterrupt(digitalPinToInterrupt(en), blink, RISING);
} // END void setup ()
// =================================================================================
// --- Loop Infinito                ---
void loop             (){
  if (dataReady) {
      for (size_t i = 0; i < sizeof(m_b001); i += 2) {
          rs_b01 = m_b001[i + 1] + (m_b001[i] << 4);
          // Serial.println(m_b002, BIN); // dado bruto
          // Serial.println(rs_b01, BIN);
          // Serial.println(rs_b01, HEX);
          Serial.print((char)rs_b01);
          Serial.print(" ");
      } // END for
    k = 0;
    m_b002 = B00000000;
    for (size_t i = 0; i < sizeof(m_b001); i++) m_b001[i] = B00000000;
    Serial.println("");
    dataReady = false;
    tld_end = millis();
  } // END IF
  if (millis() - tld_end >= 2000){
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
      ate = (digitalRead(db4) ? (m_b002 |= (1 << 0)) : (m_b002 &= ~(1 << 0))); // db4
      ate = (digitalRead(db5) ? (m_b002 |= (1 << 1)) : (m_b002 &= ~(1 << 1))); // db5
      ate = (digitalRead(db6) ? (m_b002 |= (1 << 2)) : (m_b002 &= ~(1 << 2))); // db6
      ate = (digitalRead(db7) ? (m_b002 |= (1 << 3)) : (m_b002 &= ~(1 << 3))); // db7
      m_b001[k] = m_b002;
      k++;
      tld_end = millis();

      if (k > 34) dataReady = true;
} // END void IRAM_ATTR blink ()
// =================================================================================