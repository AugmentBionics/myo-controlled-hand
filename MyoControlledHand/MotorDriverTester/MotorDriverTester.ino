#include "Arduino.h"
#include "Config.h"

#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define BUTTON3_PIN 5
#define GRIP_PATTERN_COUNT 5

// 'd' for dynamic: moves when motor controller get "move" (m) message
// 'i' for idle: motor is always idle
// 'o' for open: motor moves to open position then stays there
// 'c' for closed: motor moves to closed position then stays there
const char gripPatterns[GRIP_PATTERN_COUNT][NUMBER_OF_ACTUATORS] = {
  {'d', 'i', 'i', 'i'},
  {'i', 'd', 'i', 'i'},
  {'i', 'i', 'd', 'i'},
  {'i', 'i', 'i', 'd'},
  {'d', 'd', 'd', 'd'}
};

void sendMessageStart(char address, char instrCode) {
  Serial.write('@');
  Serial.write(address);
  Serial.write(instrCode);
}

void sendOpenMessage() {
  sendMessageStart('m', 'm'); // 'm' for motor controller address, 'p' for grip pattern message
  Serial.write('o'); // 'o' for open
  Serial.write('\n');
}

void sendCloseMessage() {
  sendMessageStart('m', 'm'); // 'm' for motor controller address, 'p' for grip pattern message
  Serial.write('c'); // 'c' for close
  Serial.write('\n');
}

void sendBrakeMessage() {
  sendMessageStart('m', 'm'); // 'm' for motor controller address, 'p' for grip pattern message
  Serial.write('b'); // 'b' for brake
  Serial.write('\n');
}

void sendIdleMessage() {
  sendMessageStart('m', 'm'); // 'm' for motor controller address, 'p' for grip pattern message
  Serial.write('i'); // 'i' for idle
  Serial.write('\n');
}

void sendNextGripPattern() {
  static unsigned int i = 0;
  sendMessageStart('m', 'p'); // 'm' for motor controller address, 'p' for grip pattern message
  for (int j = 0; j < NUMBER_OF_ACTUATORS; ++j)
    Serial.write(gripPatterns[i][j]);
  Serial.write('\n');
  i = (i + 1) % GRIP_PATTERN_COUNT;
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("Motor testing Arduino starting..."));

  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  pinMode(BUTTON3_PIN, INPUT);

  sendNextGripPattern();
}

unsigned long last_move_time = 0;
unsigned long move_wait_time = 200;
unsigned long last_pattern_time = 0;
unsigned long pattern_wait_time = 1500;

void loop() {

  // Read from buttons
  int button1 = digitalRead(BUTTON1_PIN);
  int button2 = digitalRead(BUTTON2_PIN);
  int button3 = digitalRead(BUTTON3_PIN);

  if (button1 == LOW && button2 == LOW && (millis() - last_pattern_time > pattern_wait_time)) {
    // Switch grip
    sendNextGripPattern();
    last_pattern_time = millis();
  } else if (button1 == LOW && (millis() - last_move_time > move_wait_time)) {
    sendOpenMessage();
    last_move_time = millis();
  } else if (button2 == LOW && (millis() - last_move_time > move_wait_time)) {
    sendCloseMessage();
    last_move_time = millis();
  }


  if (button3 == LOW && (millis() - last_move_time > move_wait_time)) {
    sendBrakeMessage();
    last_move_time = millis();
  }

  delay(10);
}
