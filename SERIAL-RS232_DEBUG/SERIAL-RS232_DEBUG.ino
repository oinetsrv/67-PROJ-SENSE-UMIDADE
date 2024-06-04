//ANALISE DADOS PORTA SERIAL
// Estrutura do programa
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
#include <avr/io.h>         // wachdog
#include <avr/wdt.h>        // wachdog
// --- Mapeamento de Hardware       ---
// --- Instâncias                   ---
// =================================================================================
// --- Variáveis Globais            ---
// mensagens boot

byte msg_boot1 [] = {0x00};
byte msg_boot2 [] = {0x41,0x21};
byte msg_boot3 [] = {0x40};
byte msg_boot4 [] = {0x00,0x42};
byte msg_boot5 [] = {0x00,0x50,0x43,0x6F,0x6E,0x65,0x78,0x61,0x6F,0x20,0x63,0x6F,0x72,0x72,0x65,0x74,0x61,0x20};
byte msg_boot6 [] = {0x00,0x04};
byte msg_boot7 [] = {0x00,0x4E,0x0A,0x30,0x0A,0x30};
byte msg_boot8 [] = {0x00,0x4E,0x0A,0x00,0x0A,0x00};
byte msg_boot9 [] = {0x00,0x4E,0x0A,0x01,0x0A,0x01};
byte msg_bot10 [] = {0x00,0x4E,0x0A,0x02,0x0A,0x02};
byte msg_bot11 [] = {0x00,0x4E,0x0A,0x03,0x0A,0x03};
byte msg_bot12 [] = {0x00,0x4E,0x0A,0x04,0x0A,0x04};
byte msg_bot13 [] = {0x00,0x4E,0x0A,0x05,0x0A,0x05};
byte msg_bot14 [] = {0x00,0x4E,0x0A,0x06,0x0A,0x06};
byte msg_bot15 [] = {0x00,0x4E,0x0A,0x07,0x0A,0x07};
byte msg_bot16 [] = {0x00,0x4E,0x0A,0x08,0x0A,0x08};
byte msg_bot17 [] = {0x00,0x4E,0x0A,0x09,0x0A,0x09};
byte msg_bot18 [] = {0x00,0x4E,0x0A,0x0A,0x0A,0x0A};
byte msg_bot19 [] = {0x00,0x4E,0x0A,0x0B,0x0A,0x0B};
byte msg_bot20 [] = {0x00,0x4E,0x0A,0x0C,0x0A,0x0C};
byte msg_bot21 [] = {0x00,0x4E,0x0A,0x0D,0x0A,0x0D};
byte msg_bot22 [] = {0x00,0x4E,0x0A,0x0E,0x0A,0x0E};
byte msg_bot23 [] = {0x00,0x4E,0x0A,0x0F,0x0A,0x0F};
byte msg_bot24 [] = {0x00,0x4E,0x0A,0x10,0x0A,0x10};
byte msg_bot25 [] = {0x00,0x4E,0x0A,0x11,0x0A,0x11};
byte msg_bot26 [] = {0x00,0x4E,0x0A,0x12,0x0A,0x12};
byte msg_bot27 [] = {0x00,0x4E,0x0A,0x13,0x0A,0x13};
byte msg_bot28 [] = {0x00,0x4E,0x0A,0x14,0x0A,0x14};
byte msg_bot29 [] = {0x00,0x4E,0x0A,0x15,0x0A,0x15};
byte msg_bot30 [] = {0x00,0x4E,0x0A,0x16,0x0A,0x16};
byte msg_bot31 [] = {0x00,0x4E,0x0A,0x17,0x0A,0x17};
byte msg_bot32 [] = {0x00,0x4E,0x0A,0x18,0x0A,0x18};
byte msg_bot33 [] = {0x00,0x4E,0x0A,0x19,0x0A,0x19};
byte msg_bot34 [] = {0x00,0x4E,0x0A,0x1A,0x0A,0x1A};
byte msg_bot35 [] = {0x00,0x4E,0x0A,0x1B,0x0A,0x1B};
byte msg_bot36 [] = {0x00,0x4E,0x0A,0x1C,0x0A,0x1C};
byte msg_bot37 [] = {0x00,0x4E,0x0A,0x1D,0x0A,0x1D};
byte msg_bot38 [] = {0x00,0x4E,0x11,0x0F,0x11,0x0F};
byte msg_bot39 [] = {0x00,0x4E,0x0A,0x1E,0x0A,0x2D};
byte msg_bot40 [] = {0x00,0x4E,0x10,0xF9,0x10,0xF9};
byte msg_bot41 [] = {0x00,0x4E,0x0A,0x2F,0x0A,0x2F};
byte msg_bot42 [] = {0x00,0x4E,0x0A,0x30,0x0A,0x30};
byte msg_bot43 [] = {0x00,0x44};
byte msg_bot44 [] = {0x00,0x57};
byte msg_bot45 [] = {0x00,0x45};
byte msg_bot46 [] = {0x00,0x30,0x11,0x32,0x1B,0x05,0x18}; // ANALISAR UMIDADE
byte msg_bot47 [] = {0x00,0x50,0x41,0x6E,0x61,0x6C,0x69,0x73,0x61,0x72,0x20,0x55,0x6D,0x69,0x64,0x61,0x64,0x65};
byte msg_bot48 [] = {0x00,0x50,0x41,0x6E,0x61,0x6C,0x69,0x73,0x61,0x72,0x20,0x55,0x6D,0x69,0x64,0x61,0x64,0x65};
byte msg_bot49 [] = {0x00,0x42};


byte msg_rec01[] = {0x23};
byte msg_rec02[] = {0x00};
byte msg_rec03[] = {0xFF};
byte msg_rec04[] = {0x00};
byte msg_rec05[] = {0xFF};
byte msg_rec06[] = {0x35,0x2E,0x35,0x4A,0x32,0x30,0x31,0x39};
byte msg_rec07[] = {0xFF};
byte msg_rec08[] = {0x00};
byte msg_rec09[] = {0x10};
byte msg_reC10[] = {0x42};
byte msg_reC11[] = {0x20};
byte msg_reC12[] = {0x21};
byte msg_reC13[] = {0xFF};
byte msg_reC14[] = {0x07};
byte msg_reC15[] = {0x23};
byte msg_reC16[] = {0xC8};
byte msg_reC17[] = {0x8F};
byte msg_reC18[] = {0x00};
byte msg_reC19[] = {0x5A};
byte msg_reC20[] = {0xFF};
byte msg_reC21[] = {0x10};
byte msg_reC22[] = {0x01};
byte msg_reC23[] = {0x63};
byte msg_reC24[] = {0x00};
byte msg_reC25[] = {0xFE};
byte msg_reC26[] = {0xFB};
byte msg_reC27[] = {0xFA};
byte msg_reC28[] = {0xFA};
byte msg_reC29[] = {0xFF};
byte msg_reC30[] = {0xFA};
byte msg_reC31[] = {0xF9};
byte msg_reC32[] = {0xF9};
byte msg_reC33[] = {0xFB};
byte msg_reC34[] = {0xFD};
byte msg_reC35[] = {0xFD};
byte msg_reC36[] = {0xFB};
byte msg_reC37[] = {0xFB};
byte msg_reC38[] = {0xFC};
byte msg_reC39[] = {0xFD};
byte msg_reC40[] = {0xFF};
byte msg_reC41[] = {0xFF};
byte msg_reC42[] = {0x47};
byte msg_reC43[] = {0xFC,0xFB,0xFB,0xFB,0xFC,0xFD,0xFF,0x00,0xF8,0xF8,0xF9,0xFA,0xFB,0xFD,0xFE,0xFF};
byte msg_reC44[] = {0x9E};
byte msg_reC45[] = {0x41};
byte msg_reC46[] = {0x00};
byte msg_reC47[] = {0x01,0xF5};
byte msg_reC48[] = {0x01,0xEF};
byte msg_reC49[] = {0x01,0xF7};
byte msg_reC50[] = {0x00};
byte msg_reC51[] = {0xFF};
byte msg_reC52[] = {0xFF};
byte msg_reC53[] = {0x00};
byte msg_reC54[] = {0x00};
byte msg_reC55[] = {0xFF};
byte msg_reC56[] = {0x00};
byte msg_reC57[] = {0x01,0xF6};
byte msg_reC58[] = {0x01,0xF0};
byte msg_reC59[] = {0xFF};
byte msg_reC60[] = {0x01,0xF7};
byte msg_reC61[] = {0x00};
byte msg_reC62[] = {0x01,0xF5};
byte msg_reC63[] = {0x01,0xF0};
byte msg_reC64[] = {0x01,0xF7};
byte msg_reC65[] = {0xFF};
byte msg_reC66[] = {0x00};
byte msg_reC67[] = {0x01,0xF6};
byte msg_reC68[] = {0x01,0xEF};
byte msg_reC69[] = {0x01,0xF7};
byte msg_reC70[] = {0xFF};
byte msg_reC71[] = {0x00};
byte msg_reC72[] = {0x01,0xF5};
byte msg_reC73[] = {0x01,0xEF};
byte msg_reC74[] = {0x01,0xF7};
byte msg_reC75[] = {0x00};
byte msg_reC76[] = {0x01,0xF5};
byte msg_reC77[] = {0x01,0xF0};
byte msg_reC78[] = {0x01,0xF7};
byte msg_reC79[] = {0x00};
// fim msgs boots

int       byteRead = 0;// variavel que inicia processo de comunicação
int       c_ctr  = 0;
const int length    = 72;
char      buffer[length];
byte      msg[length]; // msg convertida em numeros
String    str         = "",
          my_char     = "";  
unsigned long timeold           = 0,        // Variavel conta tempo em milis contador
              timeold_end       = 0;        // Variavel conta tempo em milis disparo 

// =================================================================================
// --- Protótipo das Funções        ---
void limparVetor  ();

// =================================================================================
// --- Configurações setup       ---
void setup (){
  Serial.begin(9600);

} // END void setup ()
// =================================================================================
// --- Loop Infinito                ---
void loop() {
  if (byteRead == 0) { 
      //Serial.write(0x00 );
      //delay(10);
      //Serial.write(0x41 );
      //Serial.write(0x21 );
      //delay(10);
     //Serial.write(msg1, sizeof(msg1));
      byteRead = 1;
  } // END IF
  
  while (Serial.available() ) {
        byte  request = Serial.read();
              msg[c_ctr] = request;
               my_char = String((char)request);
              timeold_end = millis();
              //Serial.write(msg, sizeof(c_ctr));
              //Serial.print(my_char);
              c_ctr++;
           
     }  //END while (Serial.available())
    //c_ctr  = 0;
    
    if (millis() - timeold_end >= 1000){   // LIMPA TUDO A CADA 1 S SEM COMUNICAÇÃO
          Serial.write(msg, sizeof(c_ctr));
          Serial.print(my_char);
          timeold_end = millis();
          str.remove(0, str.length());
          limparVetor();
          c_ctr  = 0;
       }
  /*
simulador
0x0D 10ms 0x410x21
resposta
                  0x23
  */
} // END void loop()
// =================================================================================
 
              
void limparVetor() {
      for (size_t i = 0; i < length; i++) msg[i] = ' ';
      msg[0] = '\0';
      str.remove(0, str.length());
      c_ctr         = 0; //= '\0'
} // END void limparVetor()
// =================================================================================
////// LOG DADOS RECEBIDOS ////// 
/* 
*/



















































/*
Recebe PC
35
13
13
53 46 53 74 50 48 49 57
0
16
66
32
33
7
35
200
143
0
90
16
1
99
255
0
254
251
250
150
255
250
249
249
251
253
253
251
251
252
253
255
255
71
252 251 251 251 252 253 255 0 248 248 249 250 251 253 254 255
158
65
0
1 246
1 222
1 230
13
13
13
13
1 247
1 223
1 230
255
13
1 246
13
1 222
1 230
13
1 246
1 223
1 231
13
13
13
255
13
1 247
1 223
1 230
13
13 
13
13
0 130
0 130
0 130
0 130
0 131
0 130
0 130
0 130
13
13
4 129
4 129
4 129
4 128
13
13
23 168
23 168
23 168
23 168
13
13
23 43
23 40
23 42
23 41
13
13
13
0 130
0 130
0 131
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 131
0 131
0 130
0 131
0 130
0 130
0 130
0 130
0 130
0 131
0 131
0 130
255
0 130
0 130
0 131
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 131
0 130
0 130
0 131
0 130
0 131
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 131
255
0 130
0 130
0 130
0 130
0 130
0 130
0 131
0 130
0 130
0 130
0 130
0 130
0 131
0 131
0 129
0 130
0 129
0 130
0 129
0 131
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 130
255
0 131
0 132
0 130
0 130
0 129
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 130
0 174
0 193
0 255
0 242
0 244
0 248
0 243
0 247
0 244
0 240
0 250
255
0 237
1 223
0 230
13
0 244
0 244
0 246
0 245
0 245
0 246
0 247
0 247
1 223
1 230
13
0 243
0 242
0 246
0 247
0 244
0 245
0 246
0 245
1 223
1 230
13
0 245
0 244
0 243
0 242
0 247
0 244
0 243
0 245
1 223
1 230
13
0 245
0 247
0 240
0 243
0 244
0 244
0 243
0 245
1 222
1 230
13
255
13
13
13
4 129
4 128
4 128
4 129
13
13
23 136
23 136
23 136
23 136
13
13
22 85
255
22 87
22 87
22 88
13
13
0 245
0 244
255
0 245
0 245
0 245
0 245
0 245
0 245
1 223
1 223
255
13
13
13
*/