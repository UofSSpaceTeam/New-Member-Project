byte s0;    
byte s1;   // the three digital pins for the bits     
byte s2;         
 
int sel0  = 4; // Selecters 0,1,2 to pick channel
int sel1 = 3;
int sel2 = 2;

float sensorOneValue = 0.0;  // variable to store the value coming from the sensor
float sensorTwoValue = 0.0;
float sensorThreeValue = 0.0;
float sensorFourValue = 0.0;

//Enable reading (Low is enabled);
int enable = 5;

const int valuesToRead = 3;
float valuesToSend[valuesToRead];

String outputString;

void setup() {
  // put your setup code here, to run once:
  s0 = 0;
  s1 = 0;
  s2 = 0;
  
  pinMode(sel2, OUTPUT);    // s0
  pinMode(sel1, OUTPUT);    // s1
  pinMode(sel0, OUTPUT);    // s2
  pinMode(enable,OUTPUT);   //vE
 
  Serial.begin(9600); // fire up the serial 
}

void loop() {
  
    digitalWrite(enable,LOW);

    

    
    for (int count=0; count < 3 ; count++) { //loop through each channel, checking for a signal
      
      int row = count; //channel 5 = 5th element in the bin list -> 101 etc. 
      
      s0 = bitRead(row,0); //bitRead() -> parameter 1 = binary sequence, parameter 2 = which bit to read, starting from the right most bit
      s1 = bitRead(row,1); //channel 7 = 111, 1 = 2nd bit 
      s2 = bitRead(row,2); // third bit

      digitalWrite(sel2, s2); // send the bits to the digital pins 
      digitalWrite(sel1, s1);
      digitalWrite(sel0, s0);

      delay(50);

      int reading = analogRead(A0);
      float value = modify(reading);

      valuesToSend[count] = value;

      delay (50); // time to read the values

      
    }


    outputString = formatString(valuesToSend);
    Serial.println(outputString);

    
 }


 float modify(int reading){
  return reading * 0.48828;
}


String formatString(float valuesToSend[]){

  sensorOneValue = valuesToSend[0];
  sensorTwoValue = valuesToSend[1];
  sensorThreeValue = valuesToSend[2];
  sensorFourValue = 0.0;
  return (String(sensorOneValue, 3) + "," + String(sensorTwoValue, 3) + "," + String(sensorThreeValue, 3) + "," + String(sensorFourValue, 3));
}
