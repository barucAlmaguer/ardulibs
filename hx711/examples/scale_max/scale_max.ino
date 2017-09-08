/* sample for digital weight scale with HX711 and serial monitor
 */

// Hx711.DOUT - pin #A1
// Hx711.SCK - pin #A0

#include "hx711.h"

#define SHOW_MAX 2000

Hx711 scale(A1, A0);

float max_force = 0.0f;
bool applying_force = false;
bool printMax = false;
long startTime = 0;
bool timing = false;

void setup() {

  Serial.begin(9600);
  Serial.println("Scale test");
  
  //Calibracion:
  scale.setReadTimes(32);
  scale.calibrate(8337205.0f, 0.0f, 8533790.0f, 1001.0f);
  //Fin calibracion
  scale.setReadTimes(4);
}

void loop() {
  //Adq
  float force = scale.getGram();
  
  //Proc
  if (force > 50.0)
    applying_force = true;
  else{
      if (applying_force){
        applying_force = false;
        startTime = millis();
        timing = true;
      }
      else if(timing){
        long actualTime = millis();
        long elapsed = actualTime - startTime;
        if (elapsed > SHOW_MAX){
          printMax = true;
          startTime = actualTime;
          timing = false;
        }
      }
    }
    
  max_force = max(force, max_force);
  //Desp
  Serial.print(force, 1);
  Serial.println(" g");
  if(printMax){
    printMax = false;
    Serial.println("----------------------------");
    Serial.print("Max = ");
    Serial.print(max_force);
    Serial.println(" gr");
    Serial.println("----------------------------");
  }
  delay(200);
}

