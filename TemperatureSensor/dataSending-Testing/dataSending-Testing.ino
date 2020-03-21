
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

float valuesToSend[8];

String outputString;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // fire up the serial 
}

void loop() {

    float exReading = random(-50, 30);
    float inReading = exReading + random(0,10);

	// loop over 
    for (int count=0; count < 4; count++) { //loop through each channel, checking for a signal
      
        // generate a random value between -5 and 5
        // to add to reading as random noise
        float exNoise = random(-500,500);
        exNoise = exNoise/100;

        exReading = exReading + exNoise;

        //Assign to array
        valuesToSend[count] = exReading;

        delay (50); // time to read the values
    }

        for (int count=4; count < 8; count++) { //loop through each channel, checking for a signal
      
        // generate a random value between -5 and 5
        // to add to reading as random noise
        float inNoise = random(-500,500);
        inNoise = inNoise/100;

        inReading = inReading + inNoise;

        //Assign to array
        valuesToSend[count] = inReading;

        delay (50); // time to read the values
    }
	//Get CSV string
    outputString = formatString(valuesToSend);

	//print the csv
    Serial.println(outputString);

    
 }


/** 
Check if the diff is concenrning
*/
bool DiffCheck(float diff){
	if (abs(diff) <= abs(concernDiff)){
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
    intrThreeSensor= valuesToSend[2];
	intrFourSensor= valuesToSend[3];
	extOneSensor= valuesToSend[4];
	extTwoSensor= valuesToSend[5];
    extThreeSensor= valuesToSend[6];
	extFourSensor= valuesToSend[7];

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
