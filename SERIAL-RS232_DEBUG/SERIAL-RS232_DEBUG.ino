/* ===========================================================================================
    Projeto: Medidor de Umidade e Temperatura em Fluxo de Secagem.
    Autor: Eng. Stenio Rodrigues         Data:  maio de 2024.
    Versão: Etapas do projeto definidas com Vx.xx
FALHOU            V1    teste de comunicação via porta USB -
OK  em 27/05/24   V1.10 Teste de recepção de dados porta serial 232
OK  em 07/06/24   V1.11 Conexão estabelecida via 232
EM execução       V1.12 Leitura de comandos enviados pelo software
                  V1.13 Simular os comandos substituindo o software
                  V1.14 Descrever cada etapa até o final do processo
                  V1.15 Simular todo o processo de envio de dados
                  V1.16 Descrever todos os dados recebidos durante o processo
                  V1.17 Criar método de enviar dados relevantes para o PLC
                  V1.18 Criar protótipo com funções mínimas para teste
                  V1.20 Teste de protocolo via rede 485
                  V1.30 Teste de protocolo conversor ethernet
                  V1.40 Teste de protocolo conversor ethernet com assistência via PLC
                  V1.50 Auxiliar na automação mecânica do processo de coleta de grãos
                  V1.60 Versão física de apresentação de funções mínimas
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
// --- Bibliotecas Auxiliares       ---
// --- Mapeamento de Hardware       ---
// --- Instâncias                   ---
// =================================================================================
// --- Bibliotecas Auxiliares ---
#include <avr/io.h>  // wachdog
#include <avr/wdt.h> // wachdog
                     // --- Mapeamento de Hardware       ---
// --- Instâncias                   ---
// =================================================================================
// --- Variáveis Globais            ---
// mensagens boot
byte msg_boot5[] = {0x0D, 0x50, 0x43, 0x6F, 0x6E, 0x65, 0x78, 
                    0x61, 0x6F, 0x20, 0x63, 0x6F, 0x61, 0x20};
byte msg_boot7[] = {0x0D, 0x4E, 0x0A, 0x30, 0x0A, 0x30};
byte msg_boot8[] = {0x0D, 0x4E, 0x0A, 0x00, 0x0A, 0x00};
byte msg_boot9[] = {0x0D, 0x4E, 0x0A, 0x01, 0x0A, 0x01};
byte msg_bot10[] = {0x0D, 0x4E, 0x0A, 0x02, 0x0A, 0x02};
byte msg_bot11[] = {0x0D, 0x4E, 0x0A, 0x03, 0x0A, 0x03};
byte msg_bot12[] = {0x0D, 0x4E, 0x0A, 0x04, 0x0A, 0x04};
byte msg_bot13[] = {0x0D, 0x4E, 0x0A, 0x05, 0x0A, 0x05};
byte msg_bot14[] = {0x0D, 0x4E, 0x0A, 0x06, 0x0A, 0x06};
byte msg_bot15[] = {0x0D, 0x4E, 0x0A, 0x07, 0x0A, 0x07};
byte msg_bot16[] = {0x0D, 0x4E, 0x0A, 0x08, 0x0A, 0x08};
byte msg_bot17[] = {0x0D, 0x4E, 0x0A, 0x09, 0x0A, 0x09};
byte msg_bot18[] = {0x0D, 0x4E, 0x0A, 0x0A, 0x0A, 0x0A};
byte msg_bot19[] = {0x0D, 0x4E, 0x0A, 0x0B, 0x0A, 0x0B};
byte msg_bot20[] = {0x0D, 0x4E, 0x0A, 0x0C, 0x0A, 0x0C};
byte msg_bot21[] = {0x0D, 0x4E, 0x0A, 0x0D, 0x0A, 0x0D};
byte msg_bot22[] = {0x0D, 0x4E, 0x0A, 0x0E, 0x0A, 0x0E};
byte msg_bot23[] = {0x0D, 0x4E, 0x0A, 0x0F, 0x0A, 0x0F};
byte msg_bot24[] = {0x0D, 0x4E, 0x0A, 0x10, 0x0A, 0x10};
byte msg_bot25[] = {0x0D, 0x4E, 0x0A, 0x11, 0x0A, 0x11};
byte msg_bot26[] = {0x0D, 0x4E, 0x0A, 0x12, 0x0A, 0x12};
byte msg_bot27[] = {0x0D, 0x4E, 0x0A, 0x13, 0x0A, 0x13};
byte msg_bot28[] = {0x0D, 0x4E, 0x0A, 0x14, 0x0A, 0x14};
byte msg_bot29[] = {0x0D, 0x4E, 0x0A, 0x15, 0x0A, 0x15};
byte msg_bot30[] = {0x0D, 0x4E, 0x0A, 0x16, 0x0A, 0x16};
byte msg_bot31[] = {0x0D, 0x4E, 0x0A, 0x17, 0x0A, 0x17};
byte msg_bot32[] = {0x0D, 0x4E, 0x0A, 0x18, 0x0A, 0x18};
byte msg_bot33[] = {0x0D, 0x4E, 0x0A, 0x19, 0x0A, 0x19};
byte msg_bot34[] = {0x0D, 0x4E, 0x0A, 0x1A, 0x0A, 0x1A};
byte msg_bot35[] = {0x0D, 0x4E, 0x0A, 0x1B, 0x0A, 0x1B};
byte msg_bot36[] = {0x0D, 0x4E, 0x0A, 0x1C, 0x0A, 0x1C};
byte msg_bot37[] = {0x0D, 0x4E, 0x0A, 0x1D, 0x0A, 0x1D};
byte msg_bot38[] = {0x0D, 0x4E, 0x11, 0x0F, 0x11, 0x0F};
byte msg_bot39[] = {0x0D, 0x4E, 0x0A, 0x1E, 0x0A, 0x2D};
byte msg_bot40[] = {0x0D, 0x4E, 0x10, 0xF9, 0x10, 0xF9};
byte msg_bot41[] = {0x0D, 0x4E, 0x0A, 0x2F, 0x0A, 0x2F};
byte msg_bot42[] = {0x0D, 0x4E, 0x0A, 0x30, 0x0A, 0x30};
byte msg_bot43[] = {0x0D, 0x44};
byte msg_bot46[] = {0x0D, 0x30, 0x10, 0x15, 0x05, 0x06, 0x18}; // ANALISAR UMIDADE
byte msg_bot47[] = {0x0D, 0x50, 0x41, 0x6E, 0x61, 0x6C, 0x69, 0x73, 0x61, 0x72, 0x20, 
                    0x55, 0x6D, 0x69, 0x64, 0x61, 0x64, 0x65};
byte msg_bot48[] = {0x0D, 0x30, 0x0F, 0x1B, 0x06, 0x06, 0x18};
// FIM DAS MSGS DO BOOT

int byteRead          = 0;      // variavel que inicia processo de comunicação
int c_ctr             = 0;      // variavel que incrementa vetor de leitura
int cont_partida      = 0;      // variavel que auxilia na sequencia de boot
int val               = 1000;   // variavel de tempo
const int length      = 64;     // tamanho do vetor  o buffer maximo da serial é 64
char buffer[length];            // variavel geral
byte msg[length];               // msg convertida em numeros
String str            = "",
       my_char        = "";     // variavel geral
unsigned long timeold = 0,      // Variavel conta tempo em milis contador
              tld_end = 0;      // Variavel conta tempo em milis disparo

// =================================================================================
// --- Protótipo das Funções        ---
void limparVetor      ();
void rotina_partida   ();
void rotina_conexao   ();
void rotina_manut     ();
void temp_com_times   (int val); // função criada para substituir time

void msg_0x23         ();
void msg_0x35         ();
void msg_0xFC         ();

// =================================================================================
// --- Configurações setup       ---
void setup            (){
      Serial.begin(9600);

} // END void setup ()
// =================================================================================
// --- Loop Infinito                ---
void loop             (){
  while (Serial.available() > 0){
      byte request = Serial.read();
      msg[c_ctr] = request;
      my_char = String((char)request);
      tld_end = millis();
      c_ctr++;
      if (c_ctr >= length)
      c_ctr = length - 1; // proteger estourar o vetor
  } // END while (Serial.available())

  // CONSIDERO CRIAR UM CASE NO FUTURO
  if (cont_partida <= 8  )    rotina_conexao ();
  if (cont_partida >= 10 )    rotina_manut   ();
  // 10/06/24 PROXIMOS PASSOS
  // começar implementar comandos para ler milho.
  /*
  SEQUENCIA DE PASSOS PARA COLETAR DADOS
  OK  1  - LIGAR APARELHO
  OK  2  - CONECTAR PORTA USB
  OK  3  - ABRIR APP
  OK  4  - ESTABELECER CONEXÃO 
  5  - SELECIONAR PRODUTO milho
  
  {0x0D, 0x42};  // 1,8 SEGUNDOS
  {0x0D, 0x50, 0x49, 0x44, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}; // 75MS
  {0x0D, 0x50, 0x45, 0x73, 0x76, 0x61, 0x7A, 0x69, 0x61, 0x72, 0x20, 0x6F, 0x20, 0x63, 0x6F, 0x70, 0x6F, 0x20}; // 2SEG
  {0x0D, 0x44};  // 129MS
  {0x0D, 0x57};  //  72MS
  {0x0D, 0x45};  //  72MS
  {0x0D, 0x30, 0x0C, 0x23, 0x0A, 0x06, 0x18}; // 1 SEG
  {0x0D, 0x50, 0x43, 0x61, 0x6C, 0x69, 0x62, 0x2E, 0x20, 0x61, 0x20, 0x62, 0x61, 0x6C, 0x61, 0x6E, 0x63, 0x61}; // 12MS
  {0x0D, 0x49};  //  48MS
  {0x0D, 0x4C};  //  150MS
  {0x0D, 0x46};  //   36MS
  {0x0D, 0x46};  //   45MS
  {0x0D, 0x46};  //   45MS
  {0x0D, 0x46};  //   45MS
  {0x0D, 0x46};  //   36MS
  {0x0D, 0x46};  //   45MS
  {0x0D, 0x46};  //   45MS
  {0x0D, 0x46};  //   95MS
  {0x0D, 0x48};  //   1,6SEG
  {0x0D, 0x49};  //   550MS
  {0x0D, 0x47};  //    38MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x47};  //    28MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x48};  //   806MS
  {0x0D, 0x4A};  //   149MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x4C};  //   100MS
  {0x0D, 0x48};  //   100MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x47};  //    29MS
  {0x0D, 0x4C};  //    48MS 
  {0x0D, 0x49};  //    1,32 SEG
  {0x0D, 0x50, 0x45, 0x6E, 0x63, 0x68, 0x65, 0x72, 0x2C, 0x74, 0x69, 0x72, 0x61, 0x72, 0x20, 0x65, 0x78, 0x63}; // 102MS
  {0x0D, 0x46};  //    40MS 
  {0x0D, 0x46};  //    40MS  80 VEZES!!!
  {0x0D, 0x46};  //   372MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x20, 0x32, 0x31, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x20, 0x37, 0x37, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x31, 0x34, 0x35, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x31, 0x39, 0x31, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x32, 0x35, 0x32, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x30, 0x37, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x34, 0x38, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x35, 0x39, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x36, 0x33, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x35, 0x39, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x36, 0x30, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x46};  //    40MS 7 VEZES!!!
  {0x0D, 0x46};  //    74MS
  {0x0D, 0x57};  //    80MS
  {0x0D, 0x45};  //   130MS
  {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x36, 0x30, 0x20, 0x67, 0x72, 0x2E}; // 58MS
  {0x0D, 0x50, 0x20, 0x50, 0x72, 0x6F, 0x63, 0x65, 0x73, 0x73, 0x61, 0x6E, 0x64, 0x6F, 0x21, 0x21, 0x21, 0x20}; //110MS
  {0x0D, 0x48};  //   1,2 SEG
  {0x0D, 0x49};  // 550MS
  {0x0D, 0x47};  //    3 VEZES 40MS
  {0x0D, 0x47};  //    80MS
  {0x0D, 0x48};  //    80MS
  
   

  6  - CLIQUE EM ANALIZAR
  7  - ESVAZIE O COPO 
  8  - CLIQUE EM CONTINUAR
  9  - CARREGAR PRODUTO
  10 - ANALISAR LEITURA
  11 - FINALIZAR PROCESSO

  
  */
  // criar lista de passos para solicitar.
  // ignorar as respostas do aparelho.
  // focar em enviar comandos somente.

  // criar lista de dados que deverão ser recebidos.
  // criar meios de mostrar dados recebidos.
  // criar meios de receber comandos em outra serial?
  // criar meios de receber comandos via portas digitais?

} // END void loop()
// ========================================================================

// ========================================================================

// ========================================================================

// ========================================================================
void rotina_manut   (){
  for (size_t i = 0; i < c_ctr; i++){
    if (msg[i] == 0x0D && cont_partida == 10){
        cont_partida = 11;
        delay(15);
        Serial.write(msg_bot47, sizeof(msg_bot47));
        Serial.flush();
        delay(1500);
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x0D && cont_partida == 11){
        cont_partida = 12;
        delay(50);
        Serial.write(0x0D);
        Serial.write(0x42);
        delay(1500);
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x0D && cont_partida == 12){
        cont_partida = 13;
        delay(1500);
        Serial.write(0x0D);
        Serial.write(0x44);
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x01 && cont_partida == 13){
        cont_partida = 14;
        delay(50);
        Serial.write(0x0D);
        Serial.write(0x57);
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x01 && cont_partida == 14){
        cont_partida = 15;
        delay(50);
        Serial.write(0x0D);
        Serial.write(0x45);
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x01 && cont_partida == 15){
        cont_partida = 16;
        Serial.write(msg_bot48, sizeof(msg_bot48));
        Serial.flush();
        delay(1500);
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x0D && cont_partida == 16){
        cont_partida = 13;
        delay(1500);
        Serial.write(0x0D);
        Serial.write(0x44);
        i = c_ctr;
        limparVetor();
    }
  } // END for
} // END void rotina_manut       ()
// ========================================================================
void rotina_conexao (){
  for (size_t i = 0; i < c_ctr; i++){
    if (msg[i] == 0xA2){ // envia disparo via COM
        cont_partida = 1;
        Serial.write(0x0D);
        delay(10);
        Serial.write(0x41);
        Serial.write(0x21);
        msg[i] = 0xA3;
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x23 && cont_partida == 1){
        cont_partida = 3;
        msg_0x23();
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x35 && msg[i + 1] == 0x2E && cont_partida == 3){
        cont_partida = 4;
        delay(9);
        msg_0x35();
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0xFC && msg[i + 1] == 0xFB && cont_partida == 4){
        cont_partida = 5;
        msg_0xFC();
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x01 && cont_partida == 5){
        cont_partida = 6;
        delay(100);
        Serial.write(0x0D);
        Serial.write(0x57);
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x01 && cont_partida == 6){
        cont_partida = 7;
        delay(100);
        Serial.write(0x0D);
        Serial.write(0x45);
        i = c_ctr;
        limparVetor();
    }
    if (msg[i] == 0x01 && cont_partida == 7) {
        cont_partida = 10;
        delay(100);
        Serial.write(msg_bot46, sizeof(msg_bot46));
        Serial.flush();
        delay(15);
        Serial.write(msg_bot47, sizeof(msg_bot47));
        Serial.flush();
        i = c_ctr;
        limparVetor();
    }
  } // END FOR
} // END void rotina_conexao ()
// ========================================================================
void temp_com_times (int val){
    tld_end = millis();
    while (millis() - tld_end <= val){
      // vai ficar aqui até atender o tempo definido em valor
    } // END if (millis() - tld_end >= 5000){
} // END void temp_com_times ()
// ========================================================================
void msg_0xFC       (){
    delay(24);
    Serial.write(msg_bot40, sizeof(msg_bot40));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot41, sizeof(msg_bot41));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot42, sizeof(msg_bot42));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot43, sizeof(msg_bot43));
    Serial.flush();
} // END void msg_0xFC (){
// ========================================================================
void msg_0x23       (){
    delay(10);
    Serial.write(0x40);
    delay(10);
    Serial.write(0x0D);
    Serial.write(0x42);
    delay(10);
    Serial.write(msg_boot5, sizeof(msg_boot5));
    Serial.flush();
    delay(140);
    Serial.write(0x0D);
    Serial.write(0x4D);
} // END
// ========================================================================
void msg_0x35       (){
    Serial.write(msg_boot7, sizeof(msg_boot7));
    Serial.flush();
    delay(9);
    Serial.write(msg_boot8, sizeof(msg_boot8));
    Serial.flush();
    delay(10);
    Serial.write(msg_boot9, sizeof(msg_boot9));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot10, sizeof(msg_bot10));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot11, sizeof(msg_bot11));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot12, sizeof(msg_bot12));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot13, sizeof(msg_bot13));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot14, sizeof(msg_bot14));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot15, sizeof(msg_bot15));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot16, sizeof(msg_bot16));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot17, sizeof(msg_bot17));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot18, sizeof(msg_bot18));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot19, sizeof(msg_bot19));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot20, sizeof(msg_bot20));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot21, sizeof(msg_bot21));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot22, sizeof(msg_bot22));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot23, sizeof(msg_bot23));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot24, sizeof(msg_bot24));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot25, sizeof(msg_bot25));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot26, sizeof(msg_bot26));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot27, sizeof(msg_bot27));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot28, sizeof(msg_bot28));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot29, sizeof(msg_bot29));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot30, sizeof(msg_bot30));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot31, sizeof(msg_bot31));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot32, sizeof(msg_bot32));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot33, sizeof(msg_bot33));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot34, sizeof(msg_bot34));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot35, sizeof(msg_bot35));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot36, sizeof(msg_bot36));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot37, sizeof(msg_bot37));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot38, sizeof(msg_bot38));
    Serial.flush();
    delay(10);
    Serial.write(msg_bot39, sizeof(msg_bot39));
    Serial.flush();
} // END void msg_0x35 ()
// ========================================================================
void rotina_partida (){
    Serial.write(0x00);
    delay(10);
    Serial.write(0x41);
    Serial.write(0x21);
} // void rotina_partida (){
// ========================================================================
void limparVetor    (){
    for (size_t i = 0; i < length; i++){
      msg[i] = ' ';
    }
    msg[0] = '\0';
    my_char.remove(0, my_char.length());
    c_ctr = 0; //= '\0'
} // END void limparVetor()
// ========================================================================
// ========================================================================