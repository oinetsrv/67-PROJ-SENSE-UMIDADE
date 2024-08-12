// HD44780 DECODER, WRITTEN BY LEONARDO MARTINS 19/01/2019

#define RS_PIN 2 // RS (Register Select) pin
#define RW_PIN 11 // RW (Read/Write) pin
#define EN_PIN 3 // EN (Enable) pin
//#define DATA_PINS {4, 5, 6, 7} // Data pins D4, D5, D6 and D7
#define DATA_PINS {7, 6, 5, 4} // Data pins D4, D5, D6 and D7

 
bool previousEn = LOW; // Previous state of the EN pin
volatile byte data = 0; // Storage for data
volatile bool dataReady = false; // Flag to indicate when data is ready to read
volatile bool highBits = true; // Flag to indicate if we are reading high or low bits

void setup() {
  Serial.begin(9600); // Start serial communication

  // Set control pins as input
  pinMode(RS_PIN, INPUT);
  pinMode(RW_PIN, INPUT);
  pinMode(EN_PIN, INPUT);

  // Set data pins as input
  int dataPins[] = DATA_PINS;
  for (int i = 0; i < 4; i++) {
    pinMode(dataPins[i], INPUT_PULLUP);
  }

  // Setup the interrupt
  attachInterrupt(digitalPinToInterrupt(RS_PIN), readData, RISING);
  //attachInterrupt(digitalPinToInterrupt(EN_PIN), readData, RISING);
}

void loop() {
  if (dataReady) {
    // Print the corresponding ASCII character to the Serial
    Serial.println(data,BIN);
    dataReady = false; // Reset the data ready flag
  }
}

void readData() {
  // Check if it's a write operation (RW == 0) and data is being sent (RS == 1)
  if (digitalRead(RS_PIN) == HIGH) {
    // Read the 4-bit part of data
    int dataPins[] = DATA_PINS;
    byte part = 0;
    for (int i = 0; i < 4; i++) {
      part |= digitalRead(dataPins[i]) << i;
    }

    if (highBits) {
      // This is the high bits part
      data = part << 4;
    } else {
      // This is the low bits part
      data |= part;
      dataReady = true; // Indicate that data is ready to read
    }

    // Flip the highBits flag
    highBits = !highBits;
  }
}