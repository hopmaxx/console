#define cLedAmnt 12
#define cRowAmnt 6
#define cBtnUpPin A1
#define cBtnDownPin A0

#define cLedSpeed 50

const uint8_t cLedPins[cLedAmnt] = {12,11,10,9,8,7,A5,2,3,4,5,6};
const uint8_t cRowId[cRowAmnt] = {63,31,21,15,12,10}; 

void setup() {
    
  for(int i = 0; i < cLedAmnt; i++){
    pinMode(cLedPins[i],OUTPUT);
  }
  
  pinMode(cBtnUpPin,INPUT);
  pinMode(cBtnDownPin,INPUT);

  Serial.begin(9600);
  
}//setup


void loop() {
  /*
  for(int i = 0; i < cLedAmnt; i++){
    digitalWrite(cLedPins[i],HIGH);
    delay(cLedSpeed);
    digitalWrite(cLedPins[i],LOW);
    delay(cLedSpeed);
  }
  */  
  int topRow = analogRead(cBtnUpPin) / 16;
  int bottomRow = analogRead(cBtnDownPin) / 16;

  topRow = getButtonId(topRow, cRowId, cRowAmnt);
  bottomRow = getButtonId(bottomRow, cRowId, cRowAmnt) + 6 * bool(bottomRow);

  if(topRow > 0 || bottomRow > 0){
    digitalWrite(cLedPins[topRow-1],HIGH);
    digitalWrite(cLedPins[bottomRow
    -1],HIGH);    
  }else{
    for(int i = i; i < cLedAmnt; i++){
      digitalWrite(cLedPins[i],LOW);   
    }
  }


  
  Serial.print(topRow);
  Serial.print(" ");
  Serial.println(bottomRow);
  delay(50);
}//loop

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

