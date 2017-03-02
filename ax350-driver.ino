
const int enablerPins[2] = {5,9};
const int mux1[3] = {2,3,4};
const int mux2[3] = {6,7,8};


void disableMux(){
  digitalWrite(enablerPins[0], HIGH);
  digitalWrite(enablerPins[1], HIGH);
}

void enableMux(){
  digitalWrite(enablerPins[0], LOW);
  digitalWrite(enablerPins[1], LOW);
}

void flashMux(){
  //make sure you start off disabled
  disableMux();

  //connect ends together for 125ms, simulating a keypress.
  enableMux();
  delay(125);
  disableMux();
}

void resetMuxes(){
  for(int i = 0; i < 3; i++){
    digitalWrite(mux1[i], LOW);
    digitalWrite(mux2[i], LOW);
  }
  disableMux();
}

//connects pins via the muxes
void connectPins(int pin1, int pin2, bool leaveDisabled = false){
  //disable muxes as connections are being changed
  disableMux();
  resetMuxes();

  //if pin connections dont make sense, dont try and connect them
  if(pin1 > 7 || pin2 > 7){
    return;
  }
  if(pin1 < 0 || pin2 < 0){
    return;
  }

  for(int i = 0; i < 3; i++){
    int lpin1 = pin1 & (1 << i);
    int lpin2 = pin2 & (1 << i);
    //Serial.print(i);
    //Serial.print("-");
    //Serial.println(lpin1);
    Serial.print("MUX1 # ");
    Serial.print(i);
    if(lpin1){
      Serial.print(" HIGH ");
      digitalWrite(mux1[i], HIGH);
    } else {
      Serial.print(" LOW  ");
      digitalWrite(mux1[i], LOW);
    }
    Serial.print(mux1[i]);
    Serial.print(" MUX2 # ");
    Serial.print(i);
    if(lpin2){
      Serial.print(" HIGH ");
      digitalWrite(mux2[i], HIGH);
    } else {
      Serial.print(" LOW  ");
      digitalWrite(mux2[i], LOW);
    }
    Serial.println(mux2[i]);
  }
  

  //leave pins muxes disabled if desired
  if(leaveDisabled){
    return;
  }
  enableMux();
}

void setup() {
  //sets up pins 2-9 for output to control muxes
  for(int i = 2; i < 9; i++){
      pinMode(i, OUTPUT);
  }
  //and disable mux as we aren't ready yet
  disableMux();
}


void testConnect(){
    for(int i = 0; i < 8; i++){
    for(int i2 = 0; i2 < 8; i2++){
      Serial.print("Attempting to connect ");
      Serial.print(i);
      Serial.print(" - ");
      Serial.println(i2);
      connectPins(i, i2, true);
      delay(500);
    }
  }
}

void blinkenlights(){
  //test mux control
  enableMux();
  TXLED1;
  delay(5000);
  disableMux();
  TXLED0;
  delay(5000);
}



void loop() {
  testConnect();
}
