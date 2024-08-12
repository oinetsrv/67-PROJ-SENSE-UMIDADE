/*----------------------------------------------------------
|   PROJETO  : Controle de display via rede 485            |
|   AUTOR    : STENIO RODRIGUES                            |
|   DATA     : 10/10/2023                                  |
|   OBJETIVO : RECEBER COMANDOS REMOTOS E ENVIAR DADOS     |
|                                                          |
------------------------------------------------------------
    Organizando código.
    // =================================================================================
    // --- Bibliotecas Auxiliares       --- //
    // =================================================================================
    // --- Mapeamento de Hardware       --- //
    // =================================================================================
    // --- Instâncias                   --- //
    // =================================================================================
    // --- Protótipo das Funções        --- //
    // =================================================================================
    // --- Variáveis Globais            --- //
    // =================================================================================
    // --- Interrupções                 --- //
    // =================================================================================
    // --- Configurações Iniciais SETUP --- //
    // =================================================================================
    // --- Loop Infinito                --- //
    // =================================================================================
    // --- Desenvolvimento das Funções  --- //
    // =================================================================================

&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
Objetivo:
            LER BARRAMENTO BINÁRIO DO DISPLAY
            CRIAR ROTINA QUE EXTRAI BYTES 
            CRIAR ROTINA QUE CONVERTE OS BYTES EM STRINGS ASCII
            CRIAR ROTINA QUE ENVIA DADOS CONVERTIDOS PARA SERIAL
            CRIAR ROTINA QUE MANIPULA BOTOES A DISTANCIA
            CRIAR ROTINA QUE RECEBE COMANDOS REMOTOS
            CRIAR ROTINA QUE EXECUTA COMANDOS REMOTOS

&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
// =================================================================================

// =================================================================================

#define  db7  7
#define  db6  6
#define  db5  5
#define  db4  4

#define  db3  11
#define  db2  10
#define  db1  9
#define  db0  8

#define  rs   13
const byte en = 2; //interruptPin 
 
// =================================================================================
boolean 
              state_db0          = 0x00, 
              state_db1          = 0x00,
              state_db2          = 0x00, 
              state_db3          = 0x00,

              state_db4          = 0x00, 
              state_db5          = 0x00,
              state_db6          = 0x00, 
              state_db7          = 0x00,

              state_rs           = 0x00,
              state_en           = 0x00;
volatile byte 
              sum_state          = 0x00;  

unsigned char sum_state_char[10]; 
int           cont               = 0;
unsigned      counter            = 0x00;
boolean       upd                = 0x00;
// =================================================================================
void debug_force();
void ConversorBIN_HEX_ASCII();
// =================================================================================

// =================================================================================
void setup() {

      DDRD &= ~(1<<4); // CONFIGURA COM ENTRADA PIN4 PD4
      DDRD &= ~(1<<5); // CONFIGURA COM ENTRADA PIN5
      DDRD &= ~(1<<6); // CONFIGURA COM ENTRADA PIN6
      DDRD &= ~(1<<7); // CONFIGURA COM ENTRADA PIN7

      DDRB &= ~(1<<0); // CONFIGURA COM ENTRADA PIN8 PB0
      DDRB &= ~(1<<1); // CONFIGURA COM ENTRADA PIN9
      DDRB &= ~(1<<2); // CONFIGURA COM ENTRADA PIN10
      DDRB &= ~(1<<3); // CONFIGURA COM ENTRADA PIN11
      DDRB &= ~(1<<4); // CONFIGURA COM ENTRADA PIN12

   EICRA |= (1<< ISC01) | (1 << ISC00); // PIN 2
   EIMSK |= (1<< INT0 );// PIN 2
   //EICRA |= (1<< ISC11) | (1 << ISC10); // PIN 3
   //EIMSK |= (1<< INT1 );// PIN 3
 
  Serial.begin  (9600               ); 
  Serial.println("\nRACK-OUVIR-DISPLAY-21-12-23");
}// END void setup() 
// =================================================================================
void loop() {
    ConversorBIN_HEX_ASCII();
//debug_force();

//delay(1);  
}// END void loop() 
// =================================================================================
// INTERRUPÇÃO
ISR (INT0_vect){
        /*
      PD4 // PIN 4
      PD5 // PIN 5
      PD6 // PIN 6
      PD7 // PIN 7
      
      PB0 // PIN 8
      PB1 // PIN 9
      PB2 // PIN 10
      PB3 // PIN 11
      PB4 // PIN 12
      */
            cont = 1;
            state_db0 = (PIND & (1 << PIND4));
            state_db1 = (PIND & (1 << PIND5));
            state_db2 = (PIND & (1 << PIND6));
            state_db3 = (PIND & (1 << PIND7));

            state_db4 = (PINB & (1 << PINB0));
            state_db5 = (PINB & (1 << PINB1));
            state_db6 = (PINB & (1 << PINB2));
            state_db7 = (PINB & (1 << PINB3));

            state_rs  = (PINB & (1 << PINB4));

            bitWrite(sum_state, 0, state_db0);
            bitWrite(sum_state, 1, state_db1);
            bitWrite(sum_state, 2, state_db2);
            bitWrite(sum_state, 3, state_db3);
            bitWrite(sum_state, 4, state_db4);
            bitWrite(sum_state, 5, state_db5);
            bitWrite(sum_state, 6, state_db6);
            bitWrite(sum_state, 7, state_db7);
            sum_state_char[0] = sum_state; 
}// END ISR
// =================================================================================
void ConversorBIN_HEX_ASCII(){
        if (cont == 1){
            if (state_rs == 1) {
            //Serial.print    ("ASCII: "  );
                //Serial.println  (sum_state_char[0],BIN );
                //Serial.print    ("HEX:"  );
                //Serial.println  (sum_state_char[0] ,HEX );
                uint8_t my_hex = sum_state_char[0];
                String my_char = String((char)my_hex);
                Serial.print  (my_char);
                Serial.print  (" ");
                // mensagem enviada 
                //0100 1000 w HEX 58
                //0101 0010 r   52
                //0101 1000 x   58
 
            }
            cont = 0;
        }
    } // END void ConversorBIN_HEX_ASCII(){
    

// =================================================================================
void debug_force(){
            Serial.print("db7;db6;db5;db4;db3;db2;db1;db0;\n");   
            Serial.print  (" "); 
            Serial.print  (state_db7);   
            Serial.print  (" :");   
            Serial.print  (" "); 
            Serial.print  (state_db6);   
            Serial.print  (" :");
            Serial.print  (" "); 
            Serial.print  (state_db5);   
            Serial.print  (" :");  
            Serial.print  (" "); 
            Serial.print  (state_db4);   
            Serial.print  (" :");
            Serial.print  (" "); 
            Serial.print  (state_db3);   
            Serial.print  (" :");
            Serial.print  (" "); 
            Serial.print  (state_db2);   
            Serial.print  (" :");
            Serial.print  (" "); 
            Serial.print  (state_db1);   
            Serial.print  (" :");
            Serial.print  (" "); 
            Serial.print  (state_db0);   
            Serial.print  ("\n");
}// END void debug_force(){
/*
//bitSet(x, posiçãoBit)   //Escreve um valor 1 em uma posição especificada de uma variável x.
      //bitClear(x, posiçãoBit) //Apaga (escreve um valor 0) em uma posição especificada de uma variável x.
      //bitWrite(x, posiçãoBit, valor) // Escreve um valor 1 ou 0 em uma posição especificada de uma variável x
state lcd_readState(LCD *l){
        digitalWrite(l->rw_pin, HIGH);
        digitalWrite(l->rs_pin, LOW);
        digitalWrite(l->enable_pin, HIGH);
        pinMode(l->datapin[l->bitmode - 1], INPUT);
        state s = ((digitalRead(l->datapin[l->bitmode - 1]) == LOW)? READY : BUSY);
        pinMode(l->datapin[l->bitmode - 1], OUTPUT);
        return s;
}


typedef enum _bmode {
      BIT_MODE_4      =4,
      BIT_MODE_8      =8
} bmode;

typedef struct _LCD {
      int datapin[8];
      int rs_pin;
      int rw_pin;
      int enable_pin;
      bmode bitmode;
} LCD;

#include <inttypes.h>
#include "WProgram.h"
//some other include that aren't relevant to our issue.
// some interfacing code that has nothing to do with this: lcd_sendRaw()


uint8_t lcd_getRaw(LCD *l, uint8_t rs_mode){
      digitalWrite(l->rs_pin, rs_mode);
      digitalWrite(l->rw_pin, HIGH);

      uint8_t retVal = 0;

      for (int i = 0; i < l->bitmode; i++){
            pinMode(l->datapin[i], INPUT);
            retVal |= (digitalRead(l->datapin[i]) << i);
            pinMode(l->datapin[i], OUTPUT);
      }

      if (l->bitmode == BIT_MODE_4){
            retVal <<= 4; //obtained high nibble, must obtain low.

            digitalWrite(l->enable_pin, HIGH);
            digitalWrite(l->enable_pin, LOW);

            for (int i = 0; i < 4; i++){
                  pinMode(l->datapin[i], INPUT);
                  retVal |= (digitalRead(l->datapin[i]) << i);
                  pinMode(l->datapin[i], OUTPUT);
            }
      }

      digitalWrite(l->enable_pin, HIGH);
      digitalWrite(l->enable_pin, LOW);

      return retVal;
}


busy_flag =  lcd_getRaw(lcd, LOW) >> 7;

address_counter = lcd_getRaw(lcd, LOW) & 127;

data = lcd_getRaw(lcd, HIGH);

#include <inttypes.h>   //needed for uint8_t datatype
#include "WProgram.h"    //needed for wiring extensions to C.
//some other include that aren't relevant to our issue.
// some interfacing code that has nothing to do with this: lcd_sendRaw()


uint8_t lcd_getRaw(LCD *l, uint8_t rs_mode){
      digitalWrite(l->rs_pin, rs_mode);    // registry select
      digitalWrite(l->rw_pin, HIGH);    //set read mode

      uint8_t retVal = 0;    // initializes return variable

      for (int i = 0; i < l->bitmode; i++){    //if bitmode is 4, it will loop until i < 4, if bitmode is 8, it will loop until i<8
            // set pin to input mode
            pinMode(l->datapin[i], INPUT);
            // reads pin, shift value to proper place and add it to retVal
            retVal |= (digitalRead(l->datapin[i]) << i);
            set pin to output mode
            pinMode(l->datapin[i], OUTPUT);
      }

      if (l->bitmode == BIT_MODE_4){
            // LCD is in 4 bit mode, only one nibble was obtained
            // shift nibble to upper end of byte and loop to obtain low
            // end of byte
            retVal <<= 4; //obtained high nibble, must obtain low.

            // trigger the strobe to signal for the next nibble
            digitalWrite(l->enable_pin, HIGH);
            digitalWrite(l->enable_pin, LOW);

            // same loop as above, only this time we know the upper limit
            for (int i = 0; i < 4; i++){
                  pinMode(l->datapin[i], INPUT);
                  retVal |= (digitalRead(l->datapin[i]) << i);
                  pinMode(l->datapin[i], OUTPUT);
            }
      }

      // end of operation, trigger the strobe
      digitalWrite(l->enable_pin, HIGH);
      digitalWrite(l->enable_pin, LOW);

      // return the complete value
      return retVal;
}






*/
 