#include <Servo.h>

const int buttonPin = 2;     // the number of the pushbutton pin
const int buttonPin2 = 3;
const int ledPin =  13;      // the number of the LED pin

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

// variables will change:
volatile int buttonState = 1;         // variable for reading the pushbutton status
volatile int buttonState2 = 1;         // variable for reading the pushbutton status

Servo myservo6;
Servo myservo9;
Servo myservo10;
Servo myservo11;  

volatile int pos = 90;
volatile int threshold = 500;

int cap(int val) {
  int result;
  result = max(val, 20);
  result = min(result, 130);
  return result;
}

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(2), pin_ISR, HIGH);
  attachInterrupt(digitalPinToInterrupt(3), pin_ISR2, HIGH);

  myservo6.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo9.attach(9);
  myservo10.attach(10);
  myservo11.attach(11);

  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if (sensorValue > 150) {
    pin_ISR();
  }
  if (sensorValue < 100) {
    pin_ISR2();
  }
  
  //delay(1);
}

void pin_ISR() {
  buttonState = digitalRead(buttonPin);
    digitalWrite(ledPin, buttonState);
    pos++;
    int new_pos;
    new_pos = cap(pos);
    myservo9.write(new_pos);
    myservo10.write(new_pos);
    myservo11.write(new_pos);
    myservo6.write(new_pos);
    pos = new_pos;
}

void pin_ISR2() {
  buttonState2 = digitalRead(buttonPin2);
  digitalWrite(ledPin, buttonState2);
  pos--;
  int new_pos;
    new_pos = cap(pos);
    myservo9.write(new_pos);
    myservo10.write(new_pos);
    myservo11.write(new_pos);
    myservo6.write(new_pos);
    pos = new_pos;
}
