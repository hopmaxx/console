#define cLedAmnt 12
#define cRowAmnt 6
#define cBtnUpPin A1
#define cBtnDownPin A0

#define cLedSpeed 50

//array with 12 led pins 
const uint8_t cLedPins[cLedAmnt] = {12,11,10,9,8,7,A5,2,3,4,5,6};
//array with 6 ID values when button is pressed
const uint8_t cRowId[cRowAmnt] = {63,31,21,15,12,10}; 

bool ledState[cLedAmnt];//used in randomize function, stores if led is on/off

byte timeCode = 0;//stores last button pressed

void setup() {

//setting each led pin to OUTPUT mode one after the other
  for(int i = 0; i < cLedAmnt; i++){
    pinMode(cLedPins[i],OUTPUT);
    ledState[i] = false;
  }

//setting 2 analog pins as INPUT, these give V values from buttons  
  pinMode(cBtnUpPin,INPUT);
  pinMode(cBtnDownPin,INPUT);

  Serial.begin(9600);

  randomSeed(analogRead(A2));

  flashRandomLed();
}//setup


void loop() {  

  //V values from analog pins are read, divided by 16 and stored in int
  int topRow = analogRead(cBtnUpPin) / 16;
  int bottomRow = analogRead(cBtnDownPin) / 16;

  //topRow/bottomRow is changed using function so it becomes number from 1-12
  topRow = getButtonId(topRow, cRowId, cRowAmnt);
  bottomRow = getButtonId(bottomRow, cRowId, cRowAmnt) + 6 * bool(bottomRow);

  //turn on led if V value is read, place in array picked using topRow/bottomRow
  /*
   if(topRow > 0 || bottomRow > 0){
    digitalWrite(cLedPins[topRow-1],HIGH);
    digitalWrite(cLedPins[bottomRow-1],HIGH);
  }else{
    for(int i = i; i < cLedAmnt; i++){
      digitalWrite(cLedPins[i],LOW);   
    }
  }*/

  //led flashes when pressed
  if(topRow > 0 ) { 
    digitalWrite(cLedPins[timeCode-1],LOW);    
    flashLed (cLedPins[topRow-1], cLedSpeed);
    timeCode = topRow;
  }else if(bottomRow > 0 ) { 
    digitalWrite(cLedPins[timeCode-1],LOW);    
    flashLed (cLedPins[bottomRow-1], cLedSpeed);  
    timeCode = bottomRow;
  }else{
    digitalWrite(cLedPins[timeCode-1],HIGH);
  }

sendTimecode(timeCode);

 
 
}//loop

//function assigns number to V value based on length of containing array
int getButtonId(int rawValue, uint8_t * compareArray, int compareArraySize){
  
  int buttonId = 0;

  for(int i = 0; i < compareArraySize; i++){
    if(rawValue == compareArray[i]){
      buttonId = i+1;
      break;
    }//if
  }//for 

  return buttonId;
}

//function flashes led when button is pressed
void flashLed (int ledId, int ledSpeed) {
    
    digitalWrite(ledId,HIGH);
    delay(ledSpeed);
    digitalWrite(ledId,LOW);
    delay(ledSpeed);
    
}

//function random flashy flashy
void flashRandomLed(){
  
  for(int i = 0; i < 10; i++){
    int randomLed = random(12);
    ledState[randomLed] ^=1;
    digitalWrite(cLedPins[randomLed],ledState[randomLed]);
    delay(100);
  }
  for(int i = 5; i >= 0; i--){
    digitalWrite(cLedPins[i],LOW);
    digitalWrite(cLedPins[i+6],LOW);    
    delay(250);
  }

}

//function sends last timecode to serial once
void sendTimecode(int timeCode){
  
  static int oldTimeCode = 0;

  if(timeCode > 0) {
    if(oldTimeCode != timeCode){
      Serial.write((byte)timeCode); 
    }//if
  }//if
  oldTimeCode = timeCode;
  
}
