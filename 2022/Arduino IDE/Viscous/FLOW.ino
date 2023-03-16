/***************************************************
  This example reads Water flow sensor Sensor.

  Created 2016-3-13
  By berinie Chen <bernie.chen@dfrobot.com style="background-repeat: no-repeat;">

  GNU Lesser General Public License.
  See for details.
  All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
  1.Connection and Diagram can be found here http://www.dfrobot.com/wiki/index.php?title=Water_Flow_Sensor_-_1/8%22_SKU:_SEN0216
  2.This code is tested on Arduino Uno.
 ****************************************************/
volatile double waterFlow;
long last;
void setup() {
  Serial.begin(9600); //baudrate
  waterFlow = 0;
  attachInterrupt(15, pulse, RISING); //DIGITAL Pin 2: Interrupt 0
}
void loop() {
  long now = millis();
  if (now-last > 1000) {
    last = now;
    Serial.print("waterFlow:");
    Serial.print(waterFlow);
    Serial.println(" mL/sec");
    waterFlow = 0;
  }
}
void pulse() //measure the quantity of square wave
{
  waterFlow += 1.0 / 5.880;
}
