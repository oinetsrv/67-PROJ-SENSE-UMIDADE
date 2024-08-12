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
// =====================================================================================
// --- Mapeamento de Hardware       ---

#define  db7  4
#define  db6  5
#define  db5  6
#define  db4  7

#define  rs   3
#define  en   2    
#define  rww   9  
#define  rss  10 
 
// =====================================================================================
// --- Protótipo das Funções        ---
 // FUNÇÃO QUE LE O BARRAMENTO PARALELO DE 4 BITS E CONCATENA OS DADOS
void temp_com_times     (int val); // FUNÇÃO QUE GERA DELAY

#define  NOP  __asm__("nop\n\t"); // UMA TENTATIVA DE RESOLVER O PROBLEMA CRIANDO ATRASO 
// Ciclo de maquina = 1/Fosc = 1/16E6 = 62,5ns = 62,5E-9s */
// =====================================================================================
// --- Variáveis Globais            ---
const int length      = 84;     // tamanho do vetor  o buffer maximo da serial é 64
int sequencia = 0,
    j         = 0,
    k         = 0;
    // volatile  joga para memoria ram e nao para os registradores
    // ganha velocidade
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
volatile  byte m_b002 = B00000000;
byte rs_b01 = B00000000;
byte m_b004[] = {B00000000, B00000000};
volatile bool dataReady = false; 
volatile byte state = LOW;
unsigned long timeold = 0,      // Variavel conta tempo em milis contador
              tld_end = 0,
              tld_dad = 0;
String    str              = "",
          TEST             = "";
int buffer[length] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned counter = 0x00;
boolean  upd     = 0x00;
// interrupção para ler o estado dos bits
ISR (INT0_vect) {
  PORTD = (PIND & (1 << 4) ? (m_b002 |= (1 << 0)) : (m_b002 &= ~(1 << 0))); // db4
  PORTD = (PIND & (1 << 5) ? (m_b002 |= (1 << 1)) : (m_b002 &= ~(1 << 1))); // db5
  PORTD = (PIND & (1 << 6) ? (m_b002 |= (1 << 2)) : (m_b002 &= ~(1 << 2))); // db6
  PORTD = (PIND & (1 << 7) ? (m_b002 |= (1 << 3)) : (m_b002 &= ~(1 << 3))); // db7
  m_b001[k] = m_b002; // armazena no vetor buffer?
  k++;
  if (k>14) dataReady = true; // ao atingir a quantidade de dados mandar imprimir 
  // o 14 foi definido pela quantidade de pulsos enviados para o display 
  // pode variar de acordo com a palavra.
} //end ISR

// =====================================================================================
// --- Configurações Iniciais       ---
void setup() {
  // USANDO REGISTRADORES PARA GANHAR VELOCIDADE
  DDRD  &= ~(1<<PD2); // CONFIGURA PIN  2 COMO ENTRADA
  PORTD |=  (1<<PORTD2); // HABILITA PUU-UP
  EICRA |= (1 << ISC01) | (1 << ISC00);     //configura interrupção externa 0 como borda de subida
  EIMSK |= (1 << INT0);                     //habilita interrupção externa 0
  sei();                                    //liga interrupções

  DDRD  &= ~(1<<4); // CONFIGURA PIN  4 COMO ENTRADA db7
  DDRD  &= ~(1<<5); // CONFIGURA PIN  5 COMO ENTRADA db6
  DDRD  &= ~(1<<6); // CONFIGURA PIN  6 COMO ENTRADA db5
  DDRD  &= ~(1<<7); // CONFIGURA PIN  7 COMO ENTRADA db4
 
  PORTD &= ~(1<<4); // FORÇA FICAR EM LOW PIN 4
  PORTD &= ~(1<<5); // FORÇA FICAR EM LOW PIN 5
  PORTD &= ~(1<<6); // FORÇA FICAR EM LOW PIN 6
  PORTD &= ~(1<<7); // FORÇA FICAR EM LOW PIN 7
  Serial.begin       (9600     );
  Serial.println     ("DISPLAY_DEBUG2");
  tld_end = millis();
  
} //end setup

// =====================================================================================
// --- Loop Infinito ---
void loop() {
if (dataReady) {
    //for (size_t i = 0; i < sizeof(m_b001); i ++) { // para debugar o vetor inteiro
      for (size_t i = 0; i < sizeof(m_b001); i += 2) { // para juntar os dados
        rs_b01 = m_b001[i+1] + (m_b001[i] << 4);
        //Serial.println(m_b002, BIN); // dado bruto
        //Serial.println(m_b001[i], BIN); // USADO PARA DEBUG
        //Serial.println(m_b001[i], HEX); // converte em hex
        //Serial.println(rs_b01, HEX);
        Serial.print((char)rs_b01); // DADO TRATADO
        Serial.print(" ");
    }
    // LIMPA TODOS OS DADOS 
    k = 0;
    m_b002 = B00000000;
    //for (size_t i = 0; i < sizeof(m_b001); i++) m_b001[i] = B00000000;
    Serial.println("");
    dataReady = false; // Reset O data ready flag
  }// END if (dataReady)
} //end loop
  
// =====================================================================================
// --- Desenvolvimento das Funções ---

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

// =====================================================================================
void temp_com_times     (int val){
  // PENSO QUE ESSE METODO DE DELAY É MAIS ADEQUADO.
      tld_end = millis();
      while (millis() - tld_end <= val){
        // vai ficar aqui até atender o tempo definido em valor
      } // END if (millis() - tld_end >= 5000){
} // END void temp_com_times     (int val)
// =====================================================================================
// =====================================================================================
/*
// NOTAS
//Serial.write(m_b001, sizeof(m_b001));
   
  //m_b002 |= (1<<3)  para setar
  //m_b002 &= ~(1<<3) para zerar
  //m_b002 ^= (1<<3)  para inverter
  //if(m_b002&(1<<3)) se verdadeiro ler  se é um nessa posicao
  //m_b002 |= (1<<7); para setar o bit 
  //      PORTD = (PIND & (1<<2) ? (rs_b01  = 0x01  ) : rs_b01   = 0x00     ); // rs PIN 2
                                // para setar o bit       para limpar o bit
   
  */
// =====================================================================================
// --- Final do Programa ---



