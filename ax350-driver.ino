
const int enablerPins[2] = {5,9};
const int mux1[3] = {2,3,4};
const int mux2[3] = {6,7,8};

//ProMicro only has 2.5KB of RAM. So using 1 KB as input buffer is fairly signifigant.
#define BUFFERSIZE 1024
char inputBuffer[BUFFERSIZE];

void setupBuffer(){
  for(int i = 0; i < BUFFERSIZE; i++){
    inputBuffer[i] = 0;
  }
}

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
  delay(75);
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
  //disable muxes and set to known state as connections are being changed
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
    Serial.print(F("MUX1 # "));
    Serial.print(i);
    if(lpin1){
      Serial.print(F(" HIGH "));
      digitalWrite(mux1[i], HIGH);
    } else {
      Serial.print(F(" LOW  "));
      digitalWrite(mux1[i], LOW);
    }
    Serial.print(mux1[i]);
    Serial.print(F(" MUX2 # "));
    Serial.print(i);
    if(lpin2){
      Serial.print(F(" HIGH "));
      digitalWrite(mux2[i], HIGH);
    } else {
      Serial.print(F(" LOW  "));
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

void testConnect(){
    for(int i = 0; i < 8; i++){
    for(int i2 = 0; i2 < 8; i2++){
      Serial.print(F("Attempting to connect "));
      Serial.print(i);
      Serial.print(F(" - "));
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

void setup() {
  //setup enablerpins first so that the muxes can be turned off
  for(int i = 0; i < 2; i++){
    pinMode(enablerPins[i], OUTPUT);
  }
  //and disable mux as we aren't ready yet
  disableMux();
  //sets up pins for control
  for(int i = 0; i < 3; i++){
      pinMode(mux1[i], OUTPUT);
      pinMode(mux2[i], OUTPUT);
  }
  //initialize the inputBuffer
  setupBuffer();
}

void loop() {
  connectPins(1, 6, true);
  flashMux();
  delay(100);
}
