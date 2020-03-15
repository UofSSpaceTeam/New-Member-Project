/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/
// 0.4888 , 0.39
int sensorOnePin = A0;    // select the input pin for the potentiometer
int sensorTwoPin = A1;
int sensorThreePin = A2;
//int sensorFourPin = A3;
float sensorOneValue = 0;  // variable to store the value coming from the sensor
float sensorTwoValue = 0;
float sensorThreeValue = 0;
//float sensorFourValue = 0;
String outputString;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorOneValue = modify(analogRead(sensorOnePin));
  sensorTwoValue = modify(analogRead(sensorTwoPin));
  sensorThreeValue = modify(analogRead(sensorThreePin));
  //sensorFourValue = modify(analogRead(sensorFourPin));


  outputString = formatString(sensorOneValue,sensorTwoValue,sensorThreeValue, 0.0356);
  Serial.println(outputString);
  
  delay(3000);
  // turn the ledPin off:
  // stop the program for for <sensorValue> milliseconds:
}

float getAverage(){
  return modify((sensorOneValue + sensorTwoValue + sensorThreeValue)) / 3.0;
}


float modify(int reading){
  return reading * 0.48828;
}

String formatString(float sensorOne, float sensorTwo, float sensorThree, float sensorFour){
  return ("$" + String(sensorOne, 3) + "," + String(sensorTwo, 3) + "," + String(sensorThree, 3) + "," + String(sensorFour, 3) + "&");
}
