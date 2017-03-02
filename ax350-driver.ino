
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

//connects pins via the muxes
void connectPins(int pin1, int pin2, bool leaveDisabled = false){
  //disable muxes as connections are being changed
  disableMux();

  //if pin connections dont make sense, dont try and connect them
  if(pin1 > 7 || pin2 > 7){
    return;
  }
  if(pin1 < 0 || pin2 < 0){
    return;
  }
}

void setup() {
  //sets up pins 2-9 for output to control muxes
  for(int i = 2; i < 9; i++){
      pinMode(i, OUTPUT);
  }
  //and disable mux as we aren't ready yet
  disableMux();
}





void loop() {
  //test mux control
  enableMux();
  TXLED1;
  delay(3000);
  disableMux();
  TXLED0;
  delay(3000);
}
