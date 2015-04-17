/*
Arduino KCS Encoder

Trevor M. Tomesh

This sketch takes sensor data from A4 and converts to binary. 
It then converts the binary into audible byte-code that is 
transmitted over A4. 

This code is in the public domain and whatnot. 

 */
 
int freq0 = 1200;
int freq1 = 2400;

bool debugon = true; // toggle test features!
int delayZeros = 10000; //number of zeros between samples
//int bufferTime = 1000; //length of pause 

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(6, OUTPUT); //data pin
  pinMode(2, OUTPUT); //ground pin
  pinMode(A4, INPUT); //signal-in from sensor
  
}

// the loop routine runs over and over again forever:
void loop() {
 
digitalWrite(2, LOW); // set the "ground pin" low

//read data from sensor and convert to string
String myText = String(analogRead(A4)); 



if(debugon == true){
//Print values to serial
Serial.print("ASCII:");
Serial.print(myText);
Serial.println(" ");
}


for(int i=0;i<delayZeros;i++){
zero(); 
}


zero(); //Tag zero on front as per KCS

for(int i=0; i<myText.length(); i++){
  
//Convert data to binary bytes called "bytes"  
   char myChar = myText.charAt(i);
    for(int i=7; i>=0; i--){
      byte bytes = bitRead(myChar,i);
    
      //if bytes is zero -- send a zero signal
      if(bytes == 0){  
        //tone(6,freq0,4/freq0);    
        zero();  
      }
      
      //if bytes is one -- send a one signal
      else if(bytes == 1){
        //tone(6,freq1,8/freq1);
        one();
       }

  if(debugon == true){
      Serial.print(bytes);
  }
    }
   
   if(debugon == true){
    Serial.println("  ");
   }   

}

one(); // Add following double-ones as per the KCS
one();

}
       
 
 
// 1200 hz for 4 cycles per KCS       
void zero(){
  
  tone(6,freq0,4/freq0);           

}  

// 2400 hz for 8 cycles per KCS
void one(){
  
   tone(6,freq1,8/freq1);
  
}
  
 
