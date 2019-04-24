#include "Arduino.h"
#include "i2c_Controller.h"
#include "Adafruit_PWMServoDriver.h"
#include "Wire.h"

#define pot_IC_Adrs 0x2F
#define pot0_vol_adrs 0x00
#define pot1_vol_adrs 0x10
#define pot2_vol_adrs 0x60
#define pot3_vol_adrs 0x70

#define del 0b0000100100100100
#define mOpen 0b0000001001001001
#define mClose 0b0000010010010010
#define mStop 0b0000011011011011
#define m0 0b0000000000000111
#define m1 0b0000000000111000
#define m2 0b0000000111000000
#define m3 0b0000111000000000
#define NC 0b1111000000000000

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

i2c_Controller::i2c_Controller()
    : _config({NOT_A_PIN, NOT_A_PIN, NOT_A_PIN, NOT_A_PIN, NOT_A_PIN}) {
}

i2c_Controller::i2c_Controller(Config config) : _config(config) {
    pinMode(startPin, INPUT_PULLUP);
    pinMode(currentPin0, INPUT);
    pinMode(currentPin1, INPUT);
    pinMode(currentPin2, INPUT);
    pinMode(currentPin3, INPUT);
    Wire.begin();
    pwm.begin();
    pwm.setPWMFreq(24);
    for (int i = 0; i < 16; i++){
      pwm.setPin(i, 0);
    }
    shiftOutWord(regState);
    setAllPot(100);
    coast();
}


void i2c_Controller::closeHand() {
  delDis();
  closeAll();
  delay(100);
  delEn();
}

void i2c_Controller::openHand() {
  delDis();
  openAll();
  delay(100);
  delEn();
}

void i2c_Controller::setAllPot(byte b){
  Wire.beginTransmission(pot_IC_Adrs);
  Wire.write(byte(pot0_vol_adrs));
  Wire.write(b);
  Wire.write(byte(pot1_vol_adrs));
  Wire.write(b);
  Wire.write(byte(pot2_vol_adrs));
  Wire.write(b);
  Wire.write(byte(pot3_vol_adrs));
  Wire.write(b);
  Wire.endTransmission();
}

void i2c_Controller::shiftOutWord(word w) {
  for (int i = 0; i < 16; i++){
    if (bitRead(w,i) == true){
      if (bitRead(outState,i) == false) {
        pwm.setPin(i, 4095);
      }
    } else if (bitRead(w,i) == false){
      if (bitRead(outState,i) == true) {
        pwm.setPin(i, 0);
      }
    }
  }
  outState = w;
}

void i2c_Controller::limitBreak() {
  for (int i = 0; (i < 500 && (handStopped(regState) == false)); i++) {
    if (digitalRead(currentPin0) == LOW && m0Stopped(regState) == false){
      breakM0();
    } else if (digitalRead(currentPin1) == LOW && m1Stopped(regState) == false){
      breakM1();
    } else if (digitalRead(currentPin2) == LOW && m2Stopped(regState) == false){
      breakM2();
    } else if (digitalRead(currentPin3) == LOW && m3Stopped(regState) == false){
      breakM3();
    }
    delay(10);
  }
  breakAll();
}

void i2c_Controller::limitIdle() {
  for (int i = 0; (i < 500 && (handStopped(regState) == false)); i++) {
    if (digitalRead(currentPin0) == LOW && m0Stopped(regState) == false){
      idleM0();
    } else if (digitalRead(currentPin1) == LOW && m1Stopped(regState) == false){
      idleM1();
    } else if (digitalRead(currentPin2) == LOW && m2Stopped(regState) == false){
      idleM2();
    } else if (digitalRead(currentPin3) == LOW && m3Stopped(regState) == false){
      idleM3();
    }
    delay(10);
  }
  idleAll();
}

bool i2c_Controller::handStopped(word w){
  if (handBreaked(w) == true || handIdled(w) == true){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::handBreaked(word w) {
  if ((w & ~NC) == mStop || (w & ~NC) == (mStop | del)) {
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::handIdled(word w) {
  if ((w & ~NC) == 0 || (w & ~NC) == del) {
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m0Stopped(word w){
  if (m0Breaked(w) == true || m0Idled(w) == true){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m1Stopped(word w){
  if (m1Breaked(w) == true || m1Idled(w) == true){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m2Stopped(word w){
  if (m2Breaked(w) == true || m2Idled(w) == true){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m3Stopped(word w){
  if (m3Breaked(w) == true || m3Idled(w) == true){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m0Breaked(word w){
  if ((w & m0) == m0 || (w & m0) == (m0 ^ (m0 & del))){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m1Breaked(word w){
  if ((w & m1) == m1 || (w & m1) == (m1 ^ (m1 & del))){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m2Breaked(word w){
  if ((w & m2) == m2 || (w & m2) == (m2 ^ (m2 & del))){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m3Breaked(word w){
  if ((w & m3) == m3 || (w & m3) == (m3 ^ (m3 & del))){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m0Idled(word w){
  if ((w & m0) == 0 || (w & m0) == (m0 & del)){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m1Idled(word w){
  if ((w & m1) == 0 || (w & m1) == (m1 & del)){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m2Idled(word w){
  if ((w & m2) == 0 || (w & m2) == (m2 & del)){
    return true;
  } else {
    return false;
  }
}

bool i2c_Controller::m3Idled(word w){
  if ((w & m3) == 0 || (w & m3) == (m3 & del)){
    return true;
  } else {
    return false;
  }
}

void i2c_Controller::closeAll() {
  regState = regState & ~mStop;
  regState = regState | mClose;
  shiftOutWord(regState);
}

void i2c_Controller::closeM0() {
  regState = regState & ~mStop;
  regState = regState | (m0 & mClose);
  shiftOutWord(regState);
}

void i2c_Controller::closeM1() {
  regState = regState & ~mStop;
  regState = regState | (m1 & mClose);
  shiftOutWord(regState);
}

void i2c_Controller::closeM2() {
  regState = regState & ~mStop;
  regState = regState | (m2 & mClose);
  shiftOutWord(regState);
}

void i2c_Controller::closeM3() {
  regState = regState & ~mStop;
  regState = regState | (m3 & mClose);
  shiftOutWord(regState);
}

void i2c_Controller::openAll() {
  regState = regState & ~mStop;
  regState = regState | mOpen;
  shiftOutWord(regState);
}

void i2c_Controller::openM0() {
  regState = regState & ~mStop;
  regState = regState | (m0 & mOpen);
  shiftOutWord(regState);
}

void i2c_Controller::openM1() {
  regState = regState & ~mStop;
  regState = regState | (m1 & mOpen);
  shiftOutWord(regState);
}

void i2c_Controller::openM2() {
  regState = regState & ~mStop;
  regState = regState | (m2 & mOpen);
  shiftOutWord(regState);
}

void i2c_Controller::openM3() {
  regState = regState & ~mStop;
  regState = regState | (m3 & mOpen);
  shiftOutWord(regState);
}

void i2c_Controller::idleAll() {
  regState = regState & ~mStop;
  shiftOutWord(regState);
}

void i2c_Controller::idleM0() {
  regState = regState & ~(m0 & mStop);
  shiftOutWord(regState);
}

void i2c_Controller::idleM1() {
  regState = regState & ~(m1 & mStop);
  shiftOutWord(regState);
}

void i2c_Controller::idleM2() {
  regState = regState & ~(m2 & mStop);
  shiftOutWord(regState);
}

void i2c_Controller::idleM3() {
  regState = regState & ~(m3 & mStop);
  shiftOutWord(regState);
}

void i2c_Controller::breakAll() {
  regState = regState | mStop;
  shiftOutWord(regState);
}

void i2c_Controller::breakM0() {
  regState = regState | (m0 & mStop);
  shiftOutWord(regState);
}

void i2c_Controller::breakM1() {
  regState = regState | (m1 & mStop);
  shiftOutWord(regState);
}

void i2c_Controller::breakM2() {
  regState = regState | (m2 & mStop);
  shiftOutWord(regState);
}

void i2c_Controller::breakM3() {
  regState = regState | (m3 & mStop);
  shiftOutWord(regState);
}

void i2c_Controller::delEn() {
  regState = regState | del;
  shiftOutWord(regState);
}

void i2c_Controller::delEnM0() {
  regState = regState | (m0 & del);
  shiftOutWord(regState);
}

void i2c_Controller::delEnM1() {
  regState = regState | (m1 & del);
  shiftOutWord(regState);
}

void i2c_Controller::delEnM2() {
  regState = regState | (m2 & del);
  shiftOutWord(regState);
}

void i2c_Controller::delEnM3() {
  regState = regState | (m3 & del);
  shiftOutWord(regState);
}

void i2c_Controller::delDis() {
  regState = regState ^ del;
  shiftOutWord(regState);
}

void i2c_Controller::delDisM0() {
  regState = regState ^ (m0 & del);
  shiftOutWord(regState);
}

void i2c_Controller::delDisM1() {
  regState = regState ^ (m1 & del);
  shiftOutWord(regState);
}

void i2c_Controller::delDisM2() {
  regState = regState ^ (m2 & del);
  shiftOutWord(regState);
}

void i2c_Controller::delDisM3() {
  regState = regState ^ (m3 & del);
  shiftOutWord(regState);
}

void i2c_Controller::test() {
  void test() {
  closeAll();
  delay(2000);
  idleAll();
  delay(1000);
  openAll();
  delay(2000);
  breakAll();
  delay(1000);
  delDis();
  closeAll();
  delay(2000);
  idleAll();
  delay(1000);
  openAll();
  delay(2000);
  breakAll();
  delay(1000);
  delEn();
}
