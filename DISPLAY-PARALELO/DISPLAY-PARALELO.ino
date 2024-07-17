 

// =====================================================================================
// --- Mapeamento de Hardware ---

#include <LiquidCrystal.h>
//D4 PIN7
//D5 PIN6
//D6 PIN5
//D7 PIN4
//EN PIN12
//RS PIN11
const int rs = 11, en = 12, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define  pi2  2

// =====================================================================================
// --- Protótipo das Funções ---
void send_char       (     );
void lcd_init        (     );
void lcd_clear       (     );
void envia_caracter  (     );
void conf_entradas   (     );
void ler_Botao       (int r);

// =====================================================================================
// --- Variáveis Globais            ---
int buttonState   = 0;
int ledState      = 1; 

// =====================================================================================
// --- Configurações Iniciais ---
void setup() {
      lcd.begin(16, 2);
      lcd.setCursor(0, 1);
      pinMode(pi2,  INPUT);
      lcd.clear   (     );
      delay       (1000 );
      lcd.print   ("HELLO WORLD"  );
} //end setup
// =====================================================================================
// --- Loop Infinito ---
void loop            (     ) {
      lcd.clear   (     );
      delay(4000);
      //lcd.print   ("ALFAFA"  );
      lcd.print   ("ANALIZAR UMIDADE"  );
      delay(4000);
 
   /* D7 D6 D5 D4       D7 D6 D5 D4       os quatro primeiros bits BYTE HEX 48
      0  1  0  0        1  0  0  0  */
} //end loop
// =====================================================================================
// --- Desenvolvimento das Funções ---
// =====================================================================================
void ler_Botao       (int r){
      if (r != buttonState) {
            buttonState = !buttonState;
         if (buttonState == HIGH  ) {
            ledState = !ledState;
         }
      }
} // END void ler_Botao ()
// =====================================================================================
// =====================================================================================
// --- Final do Programa ---



