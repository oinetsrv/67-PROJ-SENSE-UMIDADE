/* ===========================================================================================
    Projeto: Medidor de Umidade e Temperatura em Fluxo de Secagem.
    Autor: Eng. Stenio Rodrigues         Data:  JULHO de 2024.
    Versão: Etapas do projeto definidas com Vx.xx
 
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
 
// =====================================================================================
// --- Configurações Iniciais       ---
#define led_azul 21
void setup() {

  pinMode(led_azul, OUTPUT);
   
} //end setup

// =====================================================================================
// --- Loop Infinito ---
void loop() {
  digitalWrite(led_azul,HIGH);
  delay(1000);
 
} //end loop
 
// =====================================================================================
// --- Desenvolvimento das Funções --- 
// =====================================================================================
// --- Final do Programa ---



