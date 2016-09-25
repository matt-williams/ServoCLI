#include <Servo.h> 

bool initialized = false;
Servo servo0;
Servo servo1;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Ready");
} 
 
void loop() 
{
  if (Serial.available()) {
    int target0 = Serial.parseInt();
    int target1 = Serial.parseInt();
    int delayMs = Serial.parseInt();
    if (!initialized) {
      servo0.attach(2);
      servo0.write(target0);
      servo1.attach(3);
      servo1.write(target1);
      Serial.print("Initializing to ");
      Serial.print(target0);
      Serial.print(" and ");
      Serial.print(target1);
      Serial.println(" (ignoring delay)");
      initialized = true;
    } else {
      int current0 = servo0.read();
      int current1 = servo1.read();
      Serial.print("Rotating ");
      Serial.print(current0);
      Serial.print("->");
      Serial.print(target0);
      Serial.print(" and ");
      Serial.print(current1);
      Serial.print("->");
      Serial.print(target1);
      Serial.print(" with a delay of ");
      Serial.print(delayMs);
      Serial.println("ms");
      while ((current0 != target0) || (current1 != target1)) {
        if (current0 < target0) {
          current0 += 1;
        } else if (current0 > target0) {
          current0 -= 1;
        }
        servo0.write(current0);
        if (current1 < target1) {
          current1 += 1;
        } else if (current1 > target1) {
          current1 -= 1;
        }
        servo1.write(current1);
        delay(delayMs);
        Serial.print(".");
      }
      Serial.println();
    }
    Serial.println("Ready");
  }
  delay(10);
} 

