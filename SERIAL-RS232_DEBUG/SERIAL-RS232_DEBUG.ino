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
//
  //{0x0D, 0x50, 0x09, 0x0D, 0x1C, 0x06, 0x18}; 

//


byte msg_boot5[] = {0x0D, 0x50, 0x43, 0x6F, 0x6E, 0x65, 0x78, 0x61, 0x6F, 0x20, 0x63, 0x6F, 0x61, 0x20};
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
byte msg_bot45[] = {0x0D, 0x30, 0x0C, 0x3A, 0x0E, 0x06, 0x18};
byte msg_bot46[] = {0x0D, 0x30, 0x10, 0x15, 0x05, 0x06, 0x18}; // ANALISAR UMIDADE
byte msg_bot47[] = {0x0D, 0x50, 0x41, 0x6E, 0x61, 0x6C, 0x69, 0x73, 0x61, 0x72, 0x20, 0x55, 0x6D, 0x69, 0x64, 0x61, 0x64, 0x65};
byte msg_bot48[] = {0x0D, 0x30, 0x0F, 0x1B, 0x06, 0x06, 0x18};
// FIM DAS MSGS DO BOOT
// PROCESSO MILHO
    
  byte msg_milho002[] = {0x0D, 0x50, 0x49, 0x44, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,0x20, 0x20, 0x20, 0x20};  
  byte msg_milho003[] = {0x0D, 0x50, 0x45, 0x73, 0x76, 0x61, 0x7A, 0x69, 0x61, 0x72, 0x20, 0x6F, 0x20, 0x63, 0x6F, 0x70, 0x6F, 0x20};  
  byte msg_milho004[] = {0x0D, 0x44};   
  byte msg_milho005[] = {0x0D, 0x57};   
  byte msg_milho006[] = {0x0D, 0x30, 0x0E, 0x2D, 0x0E, 0x06, 0x18};   
  byte msg_milho007[] = {0x0D, 0x30, 0x0D, 0x21, 0x0D, 0x06, 0x18};  
  byte msg_milho008[] = {0x0D, 0x50, 0x43, 0x61, 0x6C, 0x69, 0x62, 0x2E, 0x20, 0x61, 0x20, 0x62, 0x61, 0x6C, 0x61, 0x6E, 0x63, 0x61};  
  byte msg_milho009[] = {0x0D, 0x49};   
  byte msg_milho010[] = {0x0D, 0x4C};   
  byte msg_milho011[] = {0x0D, 0x46};   
  byte msg_milho013[] = {0x0D, 0x48};   
  byte msg_milho015[] = {0x0D, 0x47};  
  byte msg_milho017[] = {0x0D, 0x4A}; 
  byte msg_milho024[] = {0x0D, 0x50, 0x45, 0x6E, 0x63, 0x68, 0x65, 0x72, 0x2C, 0x74, 0x69, 0x72, 0x61, 0x72, 0x20, 0x65, 0x78, 0x63}; 
  byte msg_milho032[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x20, 0x36, 0x39, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho033[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x31, 0x30, 0x33, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho034[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x31, 0x33, 0x30, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho035[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x31, 0x37, 0x30, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho036[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x32, 0x30, 0x32, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho037[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x32, 0x33, 0x37, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho038[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x32, 0x36, 0x30, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho039[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x32, 0x38, 0x37, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho040[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x30, 0x39, 0x20, 0x67, 0x72, 0x2E}; 
  
  byte msg_milho041[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x32, 0x39, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho042[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x34, 0x38, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho043[] = {0x0D, 0x50, 0x20, 0x50, 0x72, 0x6F, 0x63, 0x65, 0x73, 0x73, 0x61, 0x6E, 0x64, 0x6F, 0x21, 0x21, 0x21, 0x20}; 
  
  byte msg_milho044[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x36, 0x33, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho045[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x35, 0x39, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho046[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x36, 0x30, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho047[] = {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x36, 0x30, 0x20, 0x67, 0x72, 0x2E}; 
  byte msg_milho048[] = {0x0D, 0x50, 0x20, 0x50, 0x72, 0x6F, 0x63, 0x65, 0x73, 0x73, 0x61, 0x6E, 0x64, 0x6F, 0x21, 0x21, 0x21, 0x20}; 
  byte msg_milho057[] = {0x0D, 0x4B};
  byte msg_milho065[] = {0x0D, 0x50, 0x4D, 0x65, 0x64, 0x69, 0x6E, 0x64, 0x6F, 0x20, 0x74, 0x65, 0x6D, 0x70, 0x2E, 0x20, 0x20, 0x20}; 
  byte msg_milho068[] = {0x0D, 0x50, 0x20, 0x55, 0x6D, 0x69, 0x64, 0x61, 0x64, 0x65, 0x20, 0x20, 0x39, 0x2E, 0x36, 0x20, 0x25, 0x20}; 
  byte msg_milho071[] = {0x0D, 0x30, 0x0C, 0x24, 0x0A, 0x06, 0x18}; 
  byte msg_milho074[] = {0x0D, 0x50, 0x49, 0x44, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}; 
  byte msg_milho075[] = {0x0D, 0x50, 0x41, 0x6E, 0x61, 0x6C, 0x69, 0x73, 0x61, 0x72, 0x20, 0x55, 0x6D, 0x69, 0x64, 0x61, 0x64, 0x65}; 
// FIM PROCESSO MILHO ASEQUENCIA ESTÁ NO FINAL DO CÓDIGO
int byteRead          = 0;      // variavel que inicia processo de comunicação
int c_ctr             = 0;      // variavel que incrementa vetor de leitura
int cont_partida      = 0;      // variavel que auxilia na sequencia de boot
int val               = 1000;   // variavel de tempo
int c_manut           = 0;

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
void rot_milho_coloq  ();
void rot_encher       ();
void temp_com_times   (int val); // função criada para substituir time

void msg_0x23         ();
void msg_0x35         ();
void msg_0xFC         ();
void msg_0x3D         ();
void msg_0xFF_16      ();
void msg_0xFF_19      ();
void msg_0xFF_22      ();
void msg_0xFF_24      ();
void msg_0xFF_25      ();

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
  if (cont_partida <= 8  )    rotina_conexao  ();
  if (cont_partida >= 10 )    rotina_manut    ();
  //if (c_manut      == 1  )    rot_milho_coloq ();
  //if (c_manut      == 2  )    rot_encher      ();


} // END void loop()
// ========================================================================
void rot_encher (){
    for (size_t i = 0; i < c_ctr; i++){
        if (msg[i] == 0x4D && c_manut == 2 ){
            Serial.write(msg_milho024, sizeof(msg_milho024));
            Serial.flush();
            delay(122);
            Serial.write(0x0D);
            Serial.write(0x46);
            int cnt_i = 0;
            msg[i] == 0x0D;
                while (cnt_i < 80) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);
            delay(122);
            Serial.write(msg_milho032, sizeof(msg_milho032));
            Serial.flush();
            delay(50);
            cnt_i = 0;
                while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);
            delay(122);
            Serial.write(msg_milho033, sizeof(msg_milho033));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho034, sizeof(msg_milho034));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho035, sizeof(msg_milho035));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho036, sizeof(msg_milho036));
            Serial.flush();
            delay(50);  
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho037, sizeof(msg_milho037));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho038, sizeof(msg_milho038));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho039, sizeof(msg_milho039));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho040, sizeof(msg_milho040));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho041, sizeof(msg_milho041));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho042, sizeof(msg_milho042));
            Serial.flush();
            delay(50);
            cnt_i = 0;
            while (cnt_i < 8) {
                    delay(46);
                    Serial.write(0x0D);
                    Serial.write(0x46);
                    cnt_i++;
                }  
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x57);
                delay(46);
                Serial.write(0x0D);
                Serial.write(0x45);  
            delay(122);
            Serial.write(msg_milho043, sizeof(msg_milho043));
            Serial.flush();
            delay(50);

     
        }
    }// end for
}// END void rot_encher ()
// ========================================================================
void rot_milho_coloq    (){
    c_manut = 2;
    for (size_t i = 0; i < c_ctr; i++){
        if (msg[i] == 0x3D && c_manut == 1){
            cont_partida = 14;
            msg_0x3D       ();
        }
        if (msg[i] == 0xFF && msg[i+1] == 0xFF && cont_partida == 14){
            cont_partida = 15;
            delay(122);
            Serial.write(0x0D);
            Serial.write(0x44);
        }
        if (msg[i] == 0xFF && cont_partida == 15){
            cont_partida = 16;
            delay(74);
            Serial.write(0x0D);
            Serial.write(0x57);
        }
        if (msg[i] == 0xFF && cont_partida == 16){
            cont_partida = 17;
            msg_0xFF_16       ();
        }
        if (msg[i] == 0xFF && cont_partida == 17){
            cont_partida = 18;
            delay(12);
            Serial.write(0x0D);
            Serial.write(0x49);
        }
        if (msg[i] == 0xFF && cont_partida == 18){
            cont_partida = 19;
            delay(47);
            Serial.write(0x0D);
            Serial.write(0x4C);
        }
        if (msg[i] == 0xFF && cont_partida == 19){
            cont_partida = 20;
            msg_0xFF_19     (); 
        }
        if (msg[i] == 0xFF && cont_partida == 20){
            cont_partida = 21;
            delay(1600);
            Serial.write(0x0D);
            Serial.write(0x49);
        }
        if (msg[i] == 0xFF && cont_partida == 21){
            cont_partida = 22;
            delay(549);
            Serial.write(0x0D);
            Serial.write(0x47);
        }
        if (msg[i] == 0xFF && msg[i+1] == 0xFF && cont_partida == 22){
            cont_partida = 23;
            msg_0xFF_22       (); 
        }
        if (msg[i] == 0xFF && msg[i+1] == 0xFF && cont_partida == 23){
            cont_partida = 24;
            delay(820);
            Serial.write(0x0D);
            Serial.write(0x4A);
        }
        if (msg[i] == 0xFF && msg[i+1] == 0xFF && cont_partida == 24){
            cont_partida = 25;
            msg_0xFF_24       ();
        }
        if (msg[i] == 0xFF && msg[i+1] == 0xFF && cont_partida == 25){
            cont_partida = 26;
            msg_0xFF_25       ();
        }
    } // END for
}
// ========================================================================
void rotina_partida     (){
    Serial.write(0x00);
    delay(10);
    Serial.write(0x41);
    Serial.write(0x21);
} // void rotina_partida (){
// ========================================================================
void rotina_manut       (){
    c_manut = 1;
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
void rotina_conexao     (){
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
        delay(10);
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
        delay(120);
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
    if (msg[i] == 0x02 && cont_partida == 7) {
        cont_partida = 10;
        delay(100);
        Serial.write(msg_bot45, sizeof(msg_bot45));
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
void temp_com_times     (int val){
    tld_end = millis();
    while (millis() - tld_end <= val){
      // vai ficar aqui até atender o tempo definido em valor
    } // END if (millis() - tld_end >= 5000){
} // END void temp_com_times ()
// ========================================================================
// ========================================================================
void msg_0xFF_16        (){
    delay(79);
    Serial.write(0x0D);
    Serial.write(0x45);
    delay(79);
    Serial.write(msg_milho007, sizeof(msg_milho007));
    Serial.flush();
    delay(1000);
    Serial.write(msg_milho008, sizeof(msg_milho008));
    Serial.flush();
}// end void msg_0xFF_16       ()
// ========================================================================
void msg_0xFF_19        (){
    delay(149);
    Serial.write(0x0D);
    Serial.write(0x46);
    delay(36);
    Serial.write(0x0D);
    Serial.write(0x46);
    delay(36);
    Serial.write(0x0D);
    Serial.write(0x46);
    delay(36);
    Serial.write(0x0D);
    Serial.write(0x46);
    delay(36);
    Serial.write(0x0D);
    Serial.write(0x46);
    delay(36);
    Serial.write(0x0D);
    Serial.write(0x46);
    delay(36);
    Serial.write(0x0D);
    Serial.write(0x46);
    delay(36);
    Serial.write(0x0D);
    Serial.write(0x46);
    delay(96);
    Serial.write(0x0D);
    Serial.write(0x48);
} // END void msg_0xFF_19       ()
// ========================================================================
void msg_0xFF_22        (){
    delay(28);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(28);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(28);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(80);
    Serial.write(0x0D);
    Serial.write(0x48);
} // END void msg_0xFF_22       ()
// ========================================================================
void msg_0xFF_24        (){
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x4C);
    delay(99);
    Serial.write(0x0D);
    Serial.write(0x4B);
} // END void msg_0xFF_24       ()
// ========================================================================
void msg_0xFF_25        (){
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x47);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x4C);
    delay(30);
    Serial.write(0x0D);
    Serial.write(0x49);
    delay(30);
}// END void msg_0xFF_25       ()
// ========================================================================
void msg_0x3D           (){
    delay(300);
    Serial.write(msg_milho002, sizeof(msg_milho002));
    Serial.flush();
    delay(76);
    Serial.write(msg_milho003, sizeof(msg_milho003));
    Serial.flush();
    delay(2000);
}// end void msg_0xFC       ()
// ========================================================================
void msg_0xFC           (){
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
void msg_0x23           (){
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
void msg_0x35           (){
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
void limparVetor        (){
    for (size_t i = 0; i < length; i++){
      msg[i] = ' ';
    }
    msg[0] = '\0';
    my_char.remove(0, my_char.length());
    c_ctr = 0; //= '\0'
} // END void limparVetor()
// ========================================================================
/*
    NOTA PARA PEGAR 
    int var = 78
    serial.write(var/10+0x30) vai imprimir em ascii
    var/10+0x30 desloca na tabela ascii 78/10 + 0x30 = 7 na tabela ascii
    agora o resto da divisão
    var%10+0x30 = 8 na tabela ascii
    olha só esse codigo 
    ncyc = Serial.parseInt();  ele pega a variavel inteiro.
    depois utilize a função que limita o inteiro a 0, 256
    ncyc = constrain(ncyc,0,256)
    String string1 = "teste"
    função que comprar string
    strcmp(string1,"teste") // função que comprar string inteira 
    TIPO DO PROTOCOLO
    DADOS   MARCADOR FINAL  CHECKSUM    ENDEREÇO
    "INFO"  0XFF            CSH CSL     ADDR
/////////////////////////////////////////////////////////////

//      {0x0D}      // 151MS
// {0x0D, 0x50, 0x49, 0x44, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}; // 75MS
//      {0x0D}      // 90MS
// {0x0D, 0x50, 0x45, 0x73, 0x76, 0x61, 0x7A, 0x69, 0x61, 0x72, 0x20, 0x6F, 0x20, 0x63, 0x6F, 0x70, 0x6F, 0x20}; // 2SEG
//      {0x0D}      // 2 S
// {0x0D, 0x44};  // 129MS
//      {0x01,0xF3}      // 132MS
// {0x0D, 0x57};  //  72MS
//      {0x01,0xF5}      //  76MS
// {0x0D, 0x45};  //  72MS
//      {0x01,0xFD}      //  62MS
// {0x0D, 0x30, 0x0D, 0x0F, 0x0B, 0x06, 0x18}; // 1,7 SEG
//      {0x0D}      // 2 S
// {0x0D, 0x44};  //  128MS
//      {0x01,0xF3}      // 132MS
// {0x0D, 0x57};  //  72MS
//      {0x01,0xF5}      //  76MS
// {0x0D, 0x45};  //  72MS
//      {0x01,0xFD}      //  76MS
// {0x0D, 0x30, 0x0D, 0x0F, 0x0B, 0x06, 0x18}; // 1 SEG
//      {0x0D}      // 1 S
// {0x0D, 0x50, 0x43, 0x61, 0x6C, 0x69, 0x62, 0x2E, 0x20, 0x61, 0x20, 0x62, 0x61, 0x6C, 0x61, 0x6E, 0x63, 0x61}; // 4MS
//      {0x0D}      // 4 MS
// {0x0D, 0x49};  //  47MS
//      {0x0D}      // 48MS
// {0x0D, 0x4C};  //  150MS
//      {0x0D}      // 180MS
// {0x0D, 0x46};  //   36MS  6x
//      {0x00, 0x77}      // 48MS
// {0x0D, 0x46};  //   36MS
//      {0x00, 0x76}      // 36MS
// {0x0D, 0x46};  //   36MS
//      {0x00, 0x76}      // 48MS
// {0x0D, 0x46};  //   36MS
//      {0x00, 0x77}      // 12MS
// {0x0D, 0x46};  //   36MS
//      {0xFF}      // 34MS
// {0x0D, 0x46};  //   36MS
//      {0x00, 0x76}      // 34MS
// {0x0D, 0x46};  //   95MS
//      {0x00, 0x76}      // 36MS
// {0x0D, 0x46};  //   36MS
//      {0x00, 0x76}      // 36MS
// {0x0D, 0x46};  //   36MS
//      {0x00, 0x77}      // 36MS
// {0x0D, 0x48};  //   1,6SEG
//      {0x0D}      // 1,6SEG
// {0x0D, 0x49};  //   550MS
//      {0x0D}      // 550MS
// {0x0D, 0x47};  //    38MS 4x
//      {0x04, 0x0E}      // 36MS
// {0x0D, 0x47};  //    38MS
//      {0x04, 0x1C}      // 36MS
// {0x0D, 0x47};  //    38MS
//      {0x04, 0x12}      // 36MS
// {0x0D, 0x47};  //    38MS
//      {0x04, 0x0E}      // 36MS
// {0x0D, 0x48};  //   806MS
//      {0xFF, 0x0D}      // 806MS
// {0x0D, 0x4A};  //   149MS
//      {0x0D}      // 174MS
// {0x0D, 0x47};  //    148MS  
//      {0x14, 0x23}      //  43MS
// {0x0D, 0x47};  // 29MS
//      {0x14, 0x20}      //  43MS
// {0x0D, 0x47};  // 29MS
//      {0x14, 0x1F}      //  4MS
// {0x0D, 0x47};  // 29MS
//      {0xFF}      //  25MS
// {0x0D, 0x47};  // 29MS
//      {0x14, 0x20}      //  4MS
// {0x0D, 0x4C};  //   100MS
//      {0x0D}      //   100MS
// {0x0D, 0x4B};  //   100MS
//      {0x0D}      //  100MS
// {0x0D, 0x47};  //
//      {0xFF}      //  100MS
// {0x0D, 0x47};  //
//      {0x13, 0xB0}      //  29MS
// {0x0D, 0x47};  //
//      {0x13, 0xB0}      //  29MS
// {0x0D, 0x47};  //
//      {0x13, 0xB1}      //  29MS
// {0x0D, 0x47};  //
//      {0x13, 0xB2}      //  29MS
// {0x0D, 0x4C};  //    48MS 
//      {0x0D}      //  29MS
// {0x0D, 0x49};  //    1,32 SEG
//      {0x0D}      //  1,32 S
//      {0xFF}      //  1,32 S
// {0x0D, 0x50, 0x45, 0x6E, 0x63, 0x68, 0x65, 0x72, 0x2C, 0x74, 0x69, 0x72, 0x61, 0x72, 0x20, 0x65, 0x78, 0x63}; // 102MS
//      {0x0D}      //  149MSAA
// {0x0D, 0x46};  //    40MS 
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS 
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
//      {0xFF}      //  40MS
// {0x0D, 0x46};  //    40MS

//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x75}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
//      {0xFF}      //  12MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x7A}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x72}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x75}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x75}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x74}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x75}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x76}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x75}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x74}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x74}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x72}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x73}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x72}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x72}      //  40MS
//      {0xFF}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x72}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x72}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x72}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x70}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x70}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x70}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x71}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x72}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x7A}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x7A}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
//      {0xFF}      //  10MS
//      {0xFF}      //  2MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
//      {0xFF}      //  12MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
//      {0xFF}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
//      {0xFF}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x78}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x79}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x7D}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x77}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x84}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x7F}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x7D}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x80}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x84}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x80}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x7C}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x7F}      //  330MS
//      {0xFF}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x82}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x84}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x82}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x84}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x83}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x83}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x83}      //  40MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x82}      //  40MS
// {0x0D, 0x57};  //    40MS
//      {0x00, 0xF4}      //  80MS
// {0x0D, 0x45};  //    40MS
//      {0x00, 0xFC}      //  127MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x20, 0x20, 0x39, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0x0D};  //    90MS  
// {0x0D, 0x46};  //    58MS
//      {0x00, 0x84}      //  9MS
//      {0xFF};  //    34MS  
// {0x0D, 0x46};  //    58MS
//      {0x00, 0x85}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0x86}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0x85}      //  46MS
//      {0xFF}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0x8A}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0x9A}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xA6}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xAC}      //  46MS
// {0x0D, 0x57};  //    46MS
//      {0x00, 0xF4}      //  46MS
// {0x0D, 0x45};  //    46MS
//      {0x00, 0xFC}      //  130MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x20, 0x32, 0x31, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0x0D};  //    90MS 
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xBC}      //  46MS
//      {0xFF};  //    90MS 
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xC8}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xD2}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xD3}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xD6}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xD3}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xDC}      //  46MS
// {0x0D, 0x46};  //    46MS
//      {0x00, 0xE3}      //  60MS
// {0x0D, 0x57};  //    80MS
//      {0x00, 0xF4}      //  80MS
// {0x0D, 0x45};  //    46MS
//      {0x00, 0xFC}      //  128MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x20, 0x37, 0x31, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0xFF};  //    3MS 
//      {0x0D};  //    90MS 
// {0x0D, 0x46};  //    40MS
//      {0x00, 0xF9}      //  80MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x08}      //  80MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x07}      //  80MS
//      {0xFF}      //  11MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x12}      //  80MS
// {0x0D, 0x46};  //    40MS
//      {0x0D}      //  80MS
// {0x0D, 0x46};  //    40MS
//      {0x00, 0x14}      //  80MS
// {0x0D, 0x46};  //    40MS 
//      {0x00, 0x17}      //  80MS
// {0x0D, 0x46};  //    74MS
//      {0x00, 0x1C}      //  80MS
// {0x0D, 0x57};  //    80MS
//      {0x00, 0xF4}      //  80MS
//      {0xFF}      //  18MS
// {0x0D, 0x45};  //   130MS
//      {0x00, 0xFC}      //  80MS
// {0x0D, 0x45};  //   1350MS
//      {0x00, 0xFC}      //  120MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x31, 0x31, 0x37, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0xFF}      //  3MS
//      {0x0D}      //  90MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x45}      //  45MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x48}      //  45MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x55}      //  45MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x53}      //  45MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x60}      //  45MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x5E}      //  11MS
//      {0xFF}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x01, 0x61}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x01, 0x67}      //  45MS
// {0x0D, 0x57};  //    80MS
//      {0x01, 0xF4}      //  80MS
// {0x0D, 0x45};  //    40MS
//      {0x01, 0xFC}      //  80MS
//      {0xFF}      //  3MS
//      {0xFF}      //  3MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x31, 0x37, 0x35, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0x0D}      //  3MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x78}      //  80MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x7D}      //  80MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x7E}      //  80MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x84}      //  80MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x84}      //  80MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x88}      //  80MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x8A}      //  80MS
// {0x0D, 0x46};  //    74MS
//      {0x01, 0x8F}      //  80MS
// {0x0D, 0x57};  //    80MS
//      {0x01, 0xF3}      //  80MS
// {0x0D, 0x45};  //   130MS
//      {0xFF}      //  80MS
//      {0x01, 0xFB}      //  126MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x32, 0x30, 0x39, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0xFF}      //  80MS
//      {0x0D}      //  80MS
// {0x0D, 0x46};  //    40MS 
//      {0x01, 0xA3}      //  40MS
// {0x0D, 0x46};  //    46MS
//      {0x01, 0xA5}      //  40MS
// {0x0D, 0x46};  //    40MS 
//      {0x01, 0xA2}      //  40MS
// {0x0D, 0x46};  //    46MS
//      {0x01, 0xAB}      //  40MS
// {0x0D, 0x46};  //    40MS 
//      {0x01, 0xAB}      //  40MS
// {0x0D, 0x46};  //    46MS
//      {0x01, 0xAD}      //  40MS
// {0x0D, 0x46};  //    46MS
//      {0x01, 0xB3}      //  40MS
// {0x0D, 0x46};  //    46MS
//      {0x01, 0xB2}      //  40MS
// {0x0D, 0x57};  //    46MS
//      {0x01, 0xF3}      //  40MS
// {0x0D, 0x45};  //   130MS
//      {0x01, 0xFB}      //  110MS
//      {0xFF}      //  20MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x32, 0x33, 0x39, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//     {0x01,0x0D}      //  20MS
// {0x0D, 0x46};  //    40MS
//     {0x01,0x0D}      //  40MS
// {0x0D, 0x46};  //    46MS
//     {0x01,0x0D}      //  80MS
// {0x0D, 0x46};  //    40MS  
//     {0x01,0xD9}      //  80MS
// {0x0D, 0x46};  //    46MS
//     {0x01,0xDB}      //  80MS
// {0x0D, 0x46};  //    40MS  
//     {0x01,0xDB}      //  80MS
// {0x0D, 0x46};  //    46MS
//      {0x01,0xE4}      //  80MS
// {0x0D, 0x46};  //    40MS  
//      {0x01,0xE8}      //  80MS
// {0x0D, 0x46};  //    46MS
//      {0x01,0xEB}      //  80MS
// {0x0D, 0x57};  //    80MS
//      {0x01,0xF3}      //  80MS
// {0x0D, 0x45};  //   130MS
//      {0x01,0xFB}      //  80MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x32, 0x37, 0x38, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0x0D}      //  80MS
// {0x0D, 0x46};  //    40MS  
//      {0x01,0xFB}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x01,0xFC}      //  45MS
// {0x0D, 0x46};  //    40MS  
//      {0x01,0xFD}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x01,0xFE}      //  45MS
// {0x0D, 0x46};  //    40MS  
//      {0x02,0x02}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x01}      //  45MS
// {0x0D, 0x46};  //    40MS  
//      {0x02,0x08}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x09}      //  45MS
// {0x0D, 0x57};  //    80MS
//      {0x01,0xF2}      //  85MS
// {0x0D, 0x45};  //   130MS
//      {0x01,0xFA}      //  130MS
//      {0xFF}      //  18MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x30, 0x36, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0x0D}      //  18MS
// {0x0D, 0x46};  //    40MS 
//      {0x02,0x1E}      //  130MS
// {0x0D, 0x46};  //    40MS 
//      {0x02,0x20}      //  130MS
// {0x0D, 0x46};  //    40MS 
//      {0x02,0x23}      //  130MS
// {0x0D, 0x46};  //    40MS 
//      {0x02,0x27}      //  130MS
// {0x0D, 0x46};  //    40MS 
//      {0x02,0x25}      //  130MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x28}      //  130MS
// {0x0D, 0x46};  //    40MS  
//      {0x02,0x2B}      //  130MS
// {0x0D, 0x46};  //    74MS
//      {0x02,0x2C}      //  130MS
// {0x0D, 0x57};  //    80MS
//      {0x01,0xF2}      //  130MS
// {0x0D, 0x45};  //   130MS
//      {0x01,0xFA}      //  130MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x33, 0x34, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0x0D}      //  130MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2E}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2D}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2E}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2E}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
// {0x0D, 0x57};  //    80MS
//      {0xFF}      //  17MS
//      {0x01,0xF2}      //  45MS
// {0x0D, 0x45};  //   130MS
//      {0x01,0xFA}      //  132MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x34, 0x31, 0x20, 0x67, 0x72, 0x2E}; // 58MS
//      {0x0D}      //  132MS
// {0x0D, 0x46};  //    40MS 
//      {0x02,0x2E}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
//      {0xFF}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2E}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
//      {0xFF}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
//      {0xFF}      //  18MS
// {0x0D, 0x57};  //    80MS
//      {0x01,0xF2}      //  45MS
// {0x0D, 0x45};  //   80MS
//      {0x01,0xFA}      //  45MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x34, 0x31, 0x20, 0x67, 0x72, 0x2E}; // 61MS
//      {0x0D}      //  90MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x2F}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x67}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x28}      //  45MS
//      {0xFF}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x15}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x39}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x44}      //  45MS
//      {0xFF}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x35}      //  45MS
//      {0xFF}      //  18MS
// {0x0D, 0x57};  //    80MS
//      {0x01,0xF2}      //  45MS
// {0x0D, 0x45};  //   80MS
//      {0x01,0xFA}      //  45MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x34, 0x38, 0x20, 0x67, 0x72, 0x2E};
//      {0x0D}      //  90MS
//      {0xFF}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x34}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x35}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x35}      //  45MS
//      {0xFF}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x34}      //  45MSV
// {0x0D, 0x46};  //    40MS
//      {0x02,0x35}      //  45MSV
// {0x0D, 0x46};  //    40MS
//      {0x02,0x35}      //  45MSV
// {0x0D, 0x46};  //    40MS
//      {0x02,0x34}      //  45MSV
// {0x0D, 0x46};  //    80MS
//      {0x01,0x34}      //  45MS
// {0x0D, 0x57};  //   80MS
//      {0x01,0xF2}      //  45MS
//      {0xFF}      //  20MSC
// {0x0D, 0x45};  //   80MS
//      {0x01,0xFA}      //  129MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x34, 0x36, 0x20, 0x67, 0x72, 0x2E};
//      {0x0D}      //  90MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x33}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x34}      //  45MS
//      {0xFF}      //  45MS
// {0x0D, 0x46};  //    40MS
//      {0x02,0x34}      //  45MS 
// {0x0D, 0x46};  //    40MS
//      {0x02,0x35}      //  45MS 
// {0x0D, 0x46};  //    40MS
//      {0x02,0x35}      //  45MS 
// {0x0D, 0x46};  //    40MS
//      {0x02,0x34}      //  45MS 
// {0x0D, 0x46};  //    80MS
//      {0x01,0x35}      //  45MS
// {0x0D, 0x46};  //    80MS
//      {0x01,0x34}      //  45MS
// {0x0D, 0x57};  //   80MS
//      {0x01,0xF2}      //  45MS
// {0x0D, 0x45};  //   80MS
//      {0x01,0xFA}      //  129MS
//      {0xFF}      //  112MS
//      {0xFF}      //  15MS
// {0x0D, 0x50, 0x50, 0x65, 0x73, 0x6F, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x33, 0x34, 0x36, 0x20, 0x67, 0x72, 0x2E};
//      {0x0D}      //  78MS
// {0x0D, 0x50, 0x20, 0x50, 0x72, 0x6F, 0x63, 0x65, 0x73, 0x73, 0x61, 0x6E, 0x64, 0x6F, 0x21, 0x21, 0x21, 0x20};
//      {0x0D}      //  109MS
// {0x0D, 0x48};  //   109MS
//      {0x0D}      //  109MS
// {0x0D, 0x49};  //   1 S
//      {0x0D}      //  1S
// {0x0D, 0x47};  //   574MS
//      {0x04,0x20}      //  574MS
// {0x0D, 0x47};  //   37MS
//      {0x04,0x20}      //  37MS
// {0x0D, 0x47};  //   37MS
//      {0x04,0x1F}      //  30MS
// {0x0D, 0x47};  //   30MS
//      {0x04,0x1F}      //  30MS

*/
// ========================================================================