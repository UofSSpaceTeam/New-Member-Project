byte s0;    
byte s1;   // the three digital pins for the bits     
byte s2;         
 
int sel0  = 4; // Selecters 0,1,2 to pick channel
int sel1 = 3;
int sel2 = 2;

//Enable reading (Low is enabled);
int enable = 5;

void setup(){
  s0 = 0;
  s1 = 0;
  s2 = 0;
  
  pinMode(sel2, OUTPUT);    // s0
  pinMode(sel1, OUTPUT);    // s1
  pinMode(sel0, OUTPUT);    // s2
  pinMode(enable,OUTPUT);   //vE
 
  Serial.begin(9600); // fire up the serial 
}
 
  
void loop () {
   digitalWrite(enable,LOW);
 for (int count=5; count < 7 ; count++) { //loop through each channel, checking for a signal
   
   Serial.println(" ======================= ");
   int row = count; //channel 5 = 5th element in the bin list -> 101 etc. 
   Serial.print("Row (dec): ");Serial.println(row,DEC);
   Serial.print("Row (bin): ");Serial.println(row,BIN);

   
   s0 = bitRead(row,0); //bitRead() -> parameter 1 = binary sequence, parameter 2 = which bit to read, starting from the right most bit
   s1 = bitRead(row,1); //channel 7 = 111, 1 = 2nd bit 
   s2 = bitRead(row,2); // third bit


    Serial.print("Sending: ");Serial.print("sel2: ");Serial.print(s2);Serial.print(" sel1: ");Serial.print(s1);Serial.print(" sel0: "); Serial.println(s0);
 
   digitalWrite(sel2, s2); // send the bits to the digital pins 
   digitalWrite(sel1, s1);
   digitalWrite(sel0, s0);

    delay(50);
   //Serial.print(count);
   float controlValue = modify(analogRead(A1));

   int reading = analogRead(A0);
   float value = modify(reading);
   Serial.print("sensor: "); Serial.println(count); 
   Serial.print("A"); Serial.println(row); 
   Serial.print("Reading: "); Serial.println(reading);
   Serial.print("Value: "); Serial.println(value);// after sending the binary sequence, the mux determines which channel to read from and sends it to this analog input
   Serial.print("Control: ");Serial.println(controlValue);
 
   delay (50); // time to read the values
    
  }
 
 } 

 float modify(int reading){
  return reading * 0.48828;
}
