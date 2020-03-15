byte s0;    
byte s1;   // the three digital pins for the bits     
byte s2;         
 
int sel0  = 4; // Selecters 0,1,2 to pick channel
int sel1 = 3;
int sel2 = 2;
int warnPin = 8;

//Sensor Holders
float intrOneSensor= 0.0;  // variable to store the value coming from the sensor
float intrTwoSensor = 0.0;
float intrThreeSensor = 0.0;
float intrFourSensor = 0.0;
float extOneSensor = 0;
float extTwoSensor = 0;
float extThreeSensor = 0;
float extFourSensor = 0;

//Concerning Level
float concernDiff = 7.0;

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
  pinMode(warnPin,OUTPUT);

  
 
  Serial.begin(9600); // fire up the serial 
}

void loop() {
  	//Enable the mux
    digitalWrite(enable,LOW);
	int numSensors = 3;

	// loop over 
    for (int count=0; count < numSensors ; count++) { //loop through each channel, checking for a signal
      
      int row = count; //channel 5 = 5th element in the bin list -> 101 etc. 
      //Read mux selector bits
      s0 = bitRead(row,0); //bitRead() -> parameter 1 = binary sequence, parameter 2 = which bit to read, starting from the right most bit
      s1 = bitRead(row,1); //channel 7 = 111, 1 = 2nd bit 
      s2 = bitRead(row,2); // third bit

	  //write selector bits gates
      digitalWrite(sel2, s2); // send the bits to the digital pins 
      digitalWrite(sel1, s1);
      digitalWrite(sel0, s0);

      delay(50);

	  //Grab reading through gate
      int reading = analogRead(A0);

	  //Apply mod for correct temp
      float value = modify(reading);

      //Assign to array
      valuesToSend[count] = value;

      delay (50); // time to read the values
    }
	//Get CSV string
    outputString = formatString(valuesToSend);

	//print the csv
    Serial.println(outputString);

    
 }

/**
modify the float to a temperature reading
*/ 
float modify(int reading){
  return reading * 0.48828;
}

/** 
Check if the diff is concenrning
*/
bool DiffCheck(float diff){
	if (abs(diff) <= abs(concernDiff)){
		digitalWrite(warnPin,HIGH);
		return true;
	}
	return false;
}

/**
	Formats the csv string to send to Pi for logging
*/
String formatString(float valuesToSend[]){
	// Grab Values
	intrOneSensor= valuesToSend[0];
	intrTwoSensor= valuesToSend[1];
	extOneSensor= valuesToSend[2];
	extTwoSensor = 0.0;

	//Average and analyze
	float innerAvg = GetAverage(intrOneSensor,intrTwoSensor,intrThreeSensor,intrFourSensor);
	float outerAvg = GetAverage(extOneSensor,extTwoSensor,extThreeSensor,extFourSensor);
	float diff = innerAvg - outerAvg;
	bool isConcerning = DiffCheck(diff);

	return (
	    String(intrOneSensor, 3) + "," + String(intrTwoSensor, 3)
			+ "," + String(intrThreeSensor, 3) + "," + String(intrFourSensor,3) 
			+ "," + String(extOneSensor, 3) + "," + String(extTwoSensor, 3)
			+ "," + String(extThreeSensor, 3) + "," + String(extFourSensor, 3)
			+ "," + String(innerAvg,3) + "," + String(outerAvg,3) +
			+ "," + String(diff,3) + "," + String(isConcerning)
		);
}

/**
	Averages 4 values...
*/
float GetAverage(float v1, float v2, float v3, float v4){
	float sum = v1 + v2 + v3 + v4;
	return sum / 4.0;
}
