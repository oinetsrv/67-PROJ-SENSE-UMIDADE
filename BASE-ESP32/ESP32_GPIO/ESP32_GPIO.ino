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
#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
 

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};
struct D_bits {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};
// declaração de acordo com a disposição na PCB
D_bits bit7     = {34, 0, false};
D_bits bit6     = {35, 0, false};
D_bits bit5     = {32, 0, false};
D_bits bit4     = {33, 0, false};

D_bits bitrs    = {25, 0, false};
D_bits biten    = {26, 0, false};
 
Button button2 = {27, 0, false};
static uint8_t k = 0;
static byte test = 0;

volatile  byte m_bit7;
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

void ARDUINO_ISR_ATTR isr(void *arg) {
  Button *s = static_cast<Button *>(arg);
  s->numberKeyPresses += 1;
  s->pressed = true;
}

void ARDUINO_ISR_ATTR readData() {
  //test = (esp_rom_gpio_get_level(bit4.PIN    ) ? (m_b002 |= (1 << 0)) : (m_b002 &= ~(1 << 0))); // db4
  test = (digitalRead(bit5.PIN    ) ? (m_b002 |= (1 << 1)) : (m_b002 &= ~(1 << 1))); // db5
  test = (digitalRead(bit6.PIN    ) ? (m_b002 |= (1 << 2)) : (m_b002 &= ~(1 << 2))); // db6
  test = (digitalRead(bit7.PIN    ) ? (m_b002 |= (1 << 3)) : (m_b002 &= ~(1 << 3))); // db7
  m_b001[k] = m_b002;
  k++;
  if (k>14) button2.pressed = true;
  button2.numberKeyPresses += 1;
}

void setup() {
  Serial.begin(115200);
  //attachInterruptArg(button1.PIN, isr, &button1, FALLING);
  pinMode(bit7.PIN, INPUT_PULLUP);
  pinMode(bit6.PIN, INPUT_PULLUP);
  pinMode(bit5.PIN, INPUT_PULLUP);
  pinMode(bit4.PIN, INPUT_PULLUP);

  pinMode(bitrs.PIN, INPUT_PULLUP);
  pinMode(biten.PIN, INPUT_PULLUP);

  pinMode(button2.PIN, INPUT_PULLUP);
  attachInterrupt(button2.PIN, readData, FALLING);
  Serial.printf("partiu\n");
} // END void setup() {

void loop() {
  
  if (button2.pressed) {
      for (size_t i = 0; i < sizeof(m_b001); i ++) {
        //for (size_t i = 0; i < sizeof(m_b001); i += 2) {
          //rs_b01 = m_b001[i+1] + (m_b001[i] << 4);
          //Serial.println(m_b002, BIN); // dado bruto
          Serial.println(m_b001[i], BIN); // USADO PARA DEBUG
          //Serial.println(m_b001[i], HEX);
          //Serial.println(rs_b01, HEX);
          //Serial.print((char)rs_b01); // DADO TRATADO
          Serial.print(" ");
      }
    // LIMPA TODOS OS DADOS 
    k = 0;
    m_b002 = B00000000;
    for (size_t i = 0; i < sizeof(m_b001); i++) m_b001[i] = B00000000;
    Serial.println("");

    //Serial.printf("Button 2 has been pressed %lu times\n", button2.numberKeyPresses);
    button2.pressed = false;
  }
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();

  }
}// END void loop() {