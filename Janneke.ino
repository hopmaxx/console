#define cLedAmnt 12
#define cRowAmnt 6
#define cBtnUpPin A1
#define cBtnDownPin A0

#define cLedSpeed 50

const uint8_t cLedPins[cLedAmnt] = {12,11,10,9,8,7,A5,2,3,4,5,6};
const uint8_t cRowId[cRowAmnt] = {63,31,21,15,12,10};

int topRow = 0;
int bottomRow = 0;
int buttonPressed = 0; 

void setup() {
    
  for(int i = 0; i < cLedAmnt; i++){
    pinMode(cLedPins[i],OUTPUT);
  }
  
  pinMode(cBtnUpPin,INPUT);
  pinMode(cBtnDownPin,INPUT);

  Serial.begin(9600);
  
}//setup


void loop() {

  
  for(int i = 0; i < cLedAmnt; i++){
    digitalWrite(cLedPins[i],HIGH);
    delay(cLedSpeed);
    digitalWrite(cLedPins[i],LOW);
    delay(cLedSpeed);
  }
  
  topRow = analogRead(cBtnUpPin) / 16;

  buttonPressed = 0;
  for(int i = 0; i < cRowAmnt; i++){
    if(topRow == cRowId[i]){
      buttonPressed = i+1;
      break;
    }//if
  }//for

    
  delay(50);
}//loop
