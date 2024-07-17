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
// --- Mapeamento de Hardware       ---
// --- Instâncias                   ---
// =================================================================================
void IRAM_ATTR myInterruptFunction();
const int interruptPin = 4;
volatile bool has_interrupted = false;
void setup            (){
  REG_WRITE(GPIO_ENABLE_REG, BIT2); //degine GPI02 como saida 
  Serial.begin(115200);
  pinMode(interruptPin, INPUT_PULLUP); // Configure the pin as an input with internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(interruptPin), myInterruptFunction, RISING); // Configure the interrupt
} // END void setup ()
// =================================================================================
// --- Loop Infinito                ---
void loop             (){
    if(has_interrupted) {
        Serial.println("Button pressed!");
        has_interrupted = false;
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
}

// =================================================================================