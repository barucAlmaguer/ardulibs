/* sample for digital weight scale with HX711 and serial monitor
 */

// Hx711.DOUT - pin #A1
// Hx711.SCK - pin #A0

#include "hx711.h"

Hx711 scale(A1, A0);

void setup() {

  Serial.begin(9600);
  Serial.println("Scale test");
  
  //Calibracion:
  scale.setReadTimes(32);
  //long val = scale.averageValue();
  scale.setScale(0.0050922f);
  scale.setOffset(-42449.76f);
  //x=8337202.0 y = 0gramos
  //x=8533800.0 y = 1001gramos

  //Fin calibracion
  scale.setReadTimes(4);
}

void loop() {
  Serial.print(scale.getGram(), 1);
  Serial.println(" g");

  delay(200);
}

