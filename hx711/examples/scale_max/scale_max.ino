// Hx711.DOUT - pin #A1
// Hx711.SCK - pin #A0

#include "hx711.h"
#define SHOW_MAX 2000

Hx711 scale(A1, A0);

float max_force = 0.0f;
bool applying_force = false;
bool printMax = false;
bool timing = false;
long startTime = 0;

void setup() {

  Serial.begin(115200);  
  //Calibracion:
  scale.setReadTimes(32);
  scale.calibrate(8337205.0f, 0.0f, 8533790.0f, 1001.0f);
  //Fin calibracion
  scale.setReadTimes(1);
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
  Serial.print(" ");
  if(printMax){
    printMax = false;
    Serial.println(max_force);
    max_force = 0.0f;
  }
  else{
    Serial.println(0.0f);
  }
  delay(50);
}

