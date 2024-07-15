/* ===========================================================================================
    Projeto: Medidor de Umidade e Temperatura em Fluxo de Secagem.
    Autor: Eng. Stenio Rodrigues         Data:  JULHO de 2024.
    Versão: Etapas do projeto definidas com Vx.xx
FALHOU            V1    teste de comunicação via porta USB -
OK  em 27/05/24   V1.10 Teste de recepção de dados porta serial 232
OK  em 07/06/24   V1.11 Conexão estabelecida via 232
FALHOU            V1.12 Leitura de comandos enviados pelo software
             V1.13 Criar meios para ler o barramento do display e tirar o texto enviado para o display
                  Criar uma biblioteca para controlar o display.
                  Criar um meio para debugar usando o analizador logico.
                  Criar uma versão de prova de função que consegue mostrar quais bits foram enviados para o display em sequencia.
                  Criar usando o datasheet lista de instruções para 8 bits. 
                  Criar uma função que traduz essas instruções em dados.
                  Criar usando o datasheet lista de instruções para 4 bits.
                  
OPERAÇÃO FALHOU   V1.70 Utilizar conversor RS232/ porta serial.  CONSIDEREI CONVERSOR --->>>> ENTRADA usb APARELHO NÃO DEU CERTO.
                  V1.71 Remover conexão via jumper na rede física do equipamento

   Descrição do projeto:
        Equipamento destinado a coletar amostras de grãos automaticamente
        recebendo comandos via protocolo ethernet e responder com resultados
        obtidos. Funções mínimas esperadas. Executar coleta de amostra,
        pesar, analisar e retornar com resultados. Descartar amostras após
        conclusão do processo.                                                     */
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
void blink              (       );
void temp_com_times     (int val);
void blink2             (       );
// atraso de ciclo de maquina uma gambiarra braba para pegar o dado do 
// display com 4 us
#define  NOP  __asm__("nop\n\t");
// entendendo essa gambiarra
/*
Ciclo de maquina = 1/Fosc = 1/16E6 = 62,5ns = 62,5E-9s
*/
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
                  B00000000, B00000000, B00000000, B00000000};
volatile  byte m_b002 = B00000000;
byte rs_b01 = B00000000;
byte m_b004[] = {B00000000, B00000000};
volatile bool dataReady = false; // Flag to indicate when data is ready to read
volatile byte state = LOW;
unsigned long timeold = 0,      // Variavel conta tempo em milis contador
              tld_end = 0,
              tld_dad = 0;
String    str              = "",
          TEST             = "";
int buffer[length] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// =====================================================================================
// --- Configurações Iniciais       ---
void setup() {
 

  DDRD  &= ~(1<<2); // CONFIGURA PIN  2 COMO ENTRADA  en
  DDRD  &= ~(1<<3); // CONFIGURA PIN  3 COMO ENTRADA  rs  
  DDRD  &= ~(1<<4); // CONFIGURA PIN  4 COMO ENTRADA db7
  DDRD  &= ~(1<<5); // CONFIGURA PIN  5 COMO ENTRADA db6
  DDRD  &= ~(1<<6); // CONFIGURA PIN  6 COMO ENTRADA db5
  DDRD  &= ~(1<<7); // CONFIGURA PIN  7 COMO ENTRADA db4

  DDRB  |=  (1<<3); // CONFIGURA PIN  11 COMO SAIDA en out  
  DDRB  |=  (1<<2); // CONFIGURA PIN  10 COMO SAIDA rs out  
  DDRB  |=  (1<<1); // CONFIGURA PIN  9 COMO SAIDA rw out  
  PORTB &= ~(1<<1); // FORÇA FICAR EM LOW PIN 9  rw
  PORTB &= ~(1<<2); // FORÇA FICAR EM LOW PIN 10 rs
  PORTB &= ~(1<<3); // FORÇA FICAR EM LOW PIN 10 en

  PORTD &= ~(1<<2); // FORÇA FICAR EM LOW PIN 2
  PORTD &= ~(1<<3); // FORÇA FICAR EM LOW PIN 3
  PORTD &= ~(1<<4); // FORÇA FICAR EM LOW PIN 4
  PORTD &= ~(1<<5); // FORÇA FICAR EM LOW PIN 5
  PORTD &= ~(1<<6); // FORÇA FICAR EM LOW PIN 6
  PORTD &= ~(1<<7); // FORÇA FICAR EM LOW PIN 7
  Serial.begin       (9600     );
  Serial.println     ("display");
  tld_end = millis();
/*  LOW acionar a interrupção quando o estado do pino for LOW,
    CHANGE acionar a interrupção quando o sempre estado do pino mudar
    RISING acionar a interrupção quando o estado do pino for de LOW para HIGH apenas,
    FALLING acionar a interrupção quando o estado do pino for de HIGH para LOW apenas. */
  attachInterrupt(digitalPinToInterrupt(rs), blink, RISING); // sempre que o rs subir
} //end setup

// =====================================================================================
// --- Loop Infinito ---
void loop() {
if (dataReady) {
    for (size_t i = 0; i < sizeof(m_b001); i += 2) {
        rs_b01 = m_b001[i+1] + (m_b001[i] << 4);
        Serial.println(m_b002, BIN); // dado bruto
        Serial.print(" ");
    }
    j = 0;
    for (size_t i = 0; i < sizeof(m_b001); i++) m_b001[i] = B00000000;
    Serial.println("");
    /*
    for (size_t i = 0; i < sizeof(m_b001); i += 2) {
        rs_b01 = m_b001[i+1] + (m_b001[i] << 4);
        //Serial.println(rs_b01, BIN);
        //Serial.println(rs_b01, HEX);
        Serial.print((char)rs_b01);
    }
    */
   // deixar o codigo pronto para o meu controle de display
   // testar hello word no esp32 
   // testar interrupção no esp32
   // testar codigo no display 
   // testar tempo de resposta
   // achar um meio de coletar os dados
   
    dataReady = false; // Reset the data ready flag
  }// END if (dataReady)
} //end loop
 
// =====================================================================================
// --- Desenvolvimento das Funções ---
void blink2(){
    //PORTB &= ~(1<<1); // FORÇA FICAR EM LOW PIN 9  rw
  //PORTB &= ~(1<<2); // FORÇA FICAR EM LOW PIN 10 rs
  //PORTB &= ~(1<<3); // FORÇA FICAR EM LOW PIN 11 en
  PORTB |=  (1<<1); // ativar rw pin 9 para ler
  PORTB |=  (1<<2); // ativar rs pin 10
  delayMicroseconds(2);
  PORTB |=  (1<<3);
  delayMicroseconds(2);
  PORTB &= ~(1<<3);
  delayMicroseconds(16);
  PORTB |=  (1<<3);
  delayMicroseconds(2);
  PORTB &= ~(1<<3);
  delayMicroseconds(16);
// tenta ler os dados na ram do display
 
}// END void blink2(){
void blink() {
PORTB |=  (1<<1); // FORÇA FICAR EM HIGH PIN 9 // medir tempo
  PORTD = (PIND & (1 << 7) ? (m_b002 |= (1 << 0)) : (m_b002 &= ~(1 << 0))); // db4
  PORTD = (PIND & (1 << 6) ? (m_b002 |= (1 << 1)) : (m_b002 &= ~(1 << 1))); // db5
  PORTD = (PIND & (1 << 5) ? (m_b002 |= (1 << 2)) : (m_b002 &= ~(1 << 2))); // db6
  PORTD = (PIND & (1 << 4) ? (m_b002 |= (1 << 3)) : (m_b002 &= ~(1 << 3))); // db7
PORTB &= ~(1<<1); // FORÇA FICAR EM LOW PIN 9 // medir tempo  
k++;
if (k>16) {
      dataReady = true;
      k = 0;
    }
    
    

} // END void blink() 

/*
A 41  0100 0001         U 55  0101 0101
N 4E  0100 1110         M 4D  0100 1101
A 41  0100 0001         I 49  0100 1001
L 4C  0100 1100         D 44  0101 0101
I 49  0100 1001         A 41  0100 0001
Z 5A  0101 1010         D 44  0101 0101
A 41  0100 0001         E 45  0100 0101
R 52  0101 0010
  20  0010 0000
se RS leia o bit
aguarde 4 us e leia o outro bit
A 41  0100 0001 
L 4C  0100 1100
F 46  0100 0110  
A 41  0100 0001 
F 46  0100 0110 X
A 41  0100 0001 
0010
 
 */

// =====================================================================================
void temp_com_times     (int val){
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



