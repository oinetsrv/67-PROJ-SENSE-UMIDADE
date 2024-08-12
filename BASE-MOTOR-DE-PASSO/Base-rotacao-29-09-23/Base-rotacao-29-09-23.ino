/* Example sketch to control a stepper motor with TB6600 
 * stepper motor driver and Arduino without a library: 
 * continuous rotation. */

// Define stepper motor connections:
#define   dirPin          2 //dir+
#define   stepPin         3 //pull+
                            // dir - pull- gnd
#define stepsPerRevolution 1600
const int analogInPin = A0;

int sensorValue =        0; // value read from the pot
int outputValue =        0; // value output to the PWM (analog out)
int cont        =        0;

void setup() {
  // Declare pins as output:
  pinMode       (stepPin, OUTPUT        );
  pinMode       (dirPin , OUTPUT        );
  digitalWrite  (dirPin , HIGH          );
  //digitalWrite  (dirPin , LOW           );
  Serial.begin  (9600                   ); //
  Serial.println("Base-rotacao-30-11-23");
  for (int i = 0; i < 1 * stepsPerRevolution; i++) {
        digitalWrite  (dirPin , LOW           );
        digitalWrite      (stepPin, HIGH);
        delayMicroseconds (600  );
        digitalWrite      (stepPin, LOW );
        delayMicroseconds (600  );
      }
      digitalWrite  (dirPin , HIGH          );
}// END SETUP

void loop() {
  
  cont = 0;
      
      for (int i = 0; i < 2 * stepsPerRevolution; i++) {
        digitalWrite      (stepPin, HIGH);
        delayMicroseconds (600  );
        digitalWrite      (stepPin, LOW );
        delayMicroseconds (600  );
      }
      cont=0;
  while (cont        < 50){
      for (int i = 0; i < 5 * stepsPerRevolution; i++) {
        digitalWrite      (stepPin, HIGH);
        delayMicroseconds (225 );
        digitalWrite      (stepPin, LOW );
        delayMicroseconds (225  );
      }
      cont++;
  }

   delay(2000);
     
 
}// END LOOP

/*

for (int i = 0; i < 2 * stepsPerRevolution; i++) {
    digitalWrite      (stepPin, HIGH);
    delayMicroseconds (75  );
    digitalWrite      (stepPin, LOW );
    delayMicroseconds (75  );
  }
  for (int i = 0; i < 3 * stepsPerRevolution; i++) {
    digitalWrite      (stepPin, HIGH);
    delayMicroseconds (50  );
    digitalWrite      (stepPin, LOW );
    delayMicroseconds (50  );
  }
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    digitalWrite      (stepPin, HIGH);
    delayMicroseconds (25  );
    digitalWrite      (stepPin, LOW );
    delayMicroseconds (25  );
  }
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    digitalWrite      (stepPin, HIGH);
    delayMicroseconds (15  );
    digitalWrite      (stepPin, LOW );
    delayMicroseconds (15  );
  }
  cont = 0;
  while (cont        < 20){
    for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    digitalWrite      (stepPin, HIGH);
    delayMicroseconds (10  );
    digitalWrite      (stepPin, LOW );
    delayMicroseconds (10  );
    }
   cont++;
  }
   
 */
