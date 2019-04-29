//UI
#include "Arduino.h"
#include "UIMessaging.h"

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#define OLED_RESET 21
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 64
#define LOGO16_GLCD_WIDTH  72
static const unsigned char PROGMEM logo16_glcd_bmp[] =
    {B00000000, B00000001, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B01110000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00011100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11001110,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000111, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B10001011, B10000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000101, B11000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B01000010, B11100000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000001, B01110000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B10000000, B00000000, B00000000, B00111000, B00000000, B00000000, B00000000, B00000000, B00000111,
     B00011110, B00000000, B00000000, B00011100, B00000000, B00000000, B00000000, B00000000, B11111000, B00000111,
     B11100000, B00000000, B00001110, B00000000, B00000000, B00000000, B00000011, B11000000, B00000000, B11111110,
     B00000001, B10000111, B00000000, B00000000, B00000000, B00011110, B00000000, B00110000, B00111111, B11000001,
     B01010011, B10000000, B00000000, B00000000, B01111000, B00000000, B00000001, B10001111, B11111000, B01000001,
     B11000000, B00011111, B11100001, B11100000, B00000000, B00000000, B00100001, B11111110, B00010000, B11000000,
     B01111111, B11111101, B11000000, B00000000, B00000000, B00000100, B01111111, B11000100, B11000001, B11111111,
     B11111011, B00000000, B00000000, B00000000, B01000000, B10001111, B11110000, B01000001, B11110000, B00000110,
     B00000000, B00000000, B00000001, B00001000, B00100011, B11111110, B01000011, B01110011, B00001100, B00000000,
     B00000000, B00000000, B10000001, B00000100, B11111111, B00100111, B11110111, B00001000, B00000000, B00000000,
     B00000000, B00010000, B01000001, B00011111, B10000011, B11110010, B00010000, B00000000, B00000000, B00000000,
     B00000100, B00001000, B00100111, B11000111, B11111100, B00110000, B00000000, B00000000, B00000000, B00000001,
     B00000000, B00010111, B11100111, B11111000, B00100000, B00000000, B00000000, B00000000, B00000000, B00010000,
     B01000011, B11100111, B11110000, B01000000, B00000000, B00000000, B00000000, B00000000, B00000010, B00010001,
     B11100111, B11110000, B01000000, B00000000, B00000000, B00000000, B00000000, B11001100, B00011100, B11100111,
     B11100000, B10000000, B00000000, B00000000, B00000000, B00000010, B00000000, B00110000, B01100111, B11000000,
     B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000010, B00100111, B10000001, B10000000,
     B00000000, B00000000, B00000000, B00000000, B01100000, B01100100, B00110111, B10000001, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00011000, B10110000, B01010111, B00000001, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00001000, B00000111, B00000010, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B10000000, B00000110, B00000010, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000011, B00000110, B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
     B11000010, B00000100, B00000100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01010000,
     B00000100, B00001100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000100, B00000000, B00000000,
     B00011000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001000, B00000000, B00001000, B00010000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00001000, B00000000, B00000000, B00110000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00010000, B00000000, B00000000, B01100000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00110000, B00000000, B00000000, B11000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00110100, B00000000, B00000011, B10000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B01100100, B00000000, B00000111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B01101100, B00000000, B00011110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01101110,
     B00000000, B01111100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11011110, B00000011,
     B11110000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11011110, B01111111, B11000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11011110, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B11111110, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000001, B11111110, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000001, B10111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000001, B10111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000001, B10111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
     B10111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001, B10111110,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001, B10111100, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001, B10111100, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000001, B10111100, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000001, B10111000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B10111000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B10110000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B10100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
     B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
    };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void showGrip(unsigned int grip);
void lock();
void flash(unsigned int t);

unsigned int i = 1;
unsigned int currentI = 1;
unsigned int last = 4;
String gripNames[] =
    {"", "\x10 Open", "\x10 Power", "\x10 Pinch", "\x10 Tripod", "\x10 Index", "\x10 Key", "\x10 Set Primary", ""};
String gripNamesPrimary[] =
    {"", "\x10 Open", "\x10 Power", "\x10 Pinch", "\x10 Tripod", "\x10 Index", "\x10 Key", "\x10 Primary",
     "\x10 Reset"};

unsigned int offsetX = 20;
unsigned int offsetY = 20;
int primary = 0;
bool primaryBool = false;

void setup() {
    Serial.begin(9600);
    Serial.println("UI Arduino starting...");

    pinMode(A0, INPUT);

    pinMode(2, OUTPUT);

    pinMode(3, INPUT);

    pinMode(4, INPUT);

    pinMode(5, INPUT);

    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

    display.setTextColor(WHITE);
    display.clearDisplay();

    // splash
    display.drawBitmap(34, 0, logo16_glcd_bmp, 72, 64, 1);
    display.display();
    delay(1000);

    display.clearDisplay();
    //  testdrawchar(); delay(1000);

    showGrip(i);
}

unsigned long lastChangeMillis = 0;
unsigned long waitMillis = 1400;
int prevVal = 0;
unsigned int boundaries[7] = {0, 171, 342, 513, 684, 855, 1023};
unsigned int width = 10;

UIMessageHandler messageHandler;

void loop() {
    messageHandler.handleSerial();
    unsigned int newI = currentI;
    int val = digitalRead(3);
    int val2 = digitalRead(4);
    int val3 = digitalRead(5);
    if (primary == 0) {
        if (val2 == HIGH && val == HIGH) {
            newI = newI;
        } else if (val == HIGH && currentI != 7) {
            newI = currentI + 1;
        } else if (val2 == HIGH && currentI != 1) {
            newI = currentI - 1;
        }

        if (currentI != i && millis() - lastChangeMillis >= waitMillis) {
            if (primaryBool == true && newI != 7) {
                primary = newI;
                primaryBool = false;
                Serial.print(primary);
            }
            lock();
            showGrip(1);
            Serial.write(newI);
            i = currentI;
            if (newI == 7) {
                currentI = 1;
                i = currentI;
                newI = 1;
                showGrip(1);
                lastChangeMillis = 0;
                primaryBool = true;
            }
        }

        if (currentI != newI) {
            lastChangeMillis = millis();
            currentI = newI;
            showGrip(newI);
            return;
        }
    } else {
        if (val3 == HIGH) {
            newI = primary;
            lock();
            Serial.write(newI);
            i = currentI;
            lastChangeMillis = millis();
            currentI = newI;
            showGrip(newI);
            return;
        }

        if (val2 == HIGH && val == HIGH) {
            newI = newI;
        } else if (val == HIGH && currentI != 8) {
            newI = currentI + 1;
        } else if (val2 == HIGH && currentI != 1) {
            newI = currentI - 1;
        }

        if (currentI != i && millis() - lastChangeMillis >= waitMillis) {
            lock();
            Serial.write(newI);
            i = currentI;
            if (newI == 8) {
                currentI = 1;
                i = currentI;
                newI = 1;
                primary = 0;
                showGrip(1);
            }
        }

        if (currentI != newI) {
            lastChangeMillis = millis();
            currentI = newI;
            showGrip(newI);
            return;
        }
    }
    prevVal = val;
}

void lock() {
    flash(100);
    delay(45);
    flash(300);
}

void showGrip(unsigned int grip) {
    display.clearDisplay();
    digitalWrite(10, HIGH);
    display.setTextColor(WHITE);

    if (primary == 0) {
        display.setTextSize(1);
        display.setCursor(offsetX, 0);
        display.println(gripNames[grip - 1]);

        display.setTextSize(2);
        display.setCursor(offsetX + 0, offsetY + 5);
        display.print(gripNames[grip]);

        display.setCursor(1, offsetY + 5);
        display.print(grip);

        display.setTextSize(1);
        display.setCursor(offsetX, 55);
        display.println(gripNames[grip + 1]);

    } else {
        display.setTextSize(1);
        display.setCursor(offsetX + 100, 0);
        display.println('P');

        display.setTextSize(1);
        display.setCursor(offsetX, 0);
        display.println(gripNamesPrimary[grip - 1]);

        display.setTextSize(2);
        display.setCursor(offsetX + 0, offsetY + 5);
        display.print(gripNamesPrimary[grip]);

        display.setCursor(1, offsetY + 5);
        display.print(grip);

        display.setTextSize(1);
        display.setCursor(offsetX, 55);
        display.println(gripNamesPrimary[grip + 1]);
    }
    display.display();
    //  delay(20);
    digitalWrite(10, LOW);
}

void bottomBarOn() {
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 56);
    display.setTextSize(1);
    display.print("                     ");
    display.setTextColor(WHITE, BLACK);
}

void bottomBarOff() {
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0, 56);
    display.setTextSize(1);
    display.print("                     ");
    display.setTextColor(WHITE, BLACK);
}

void flash(unsigned int t) {
    digitalWrite(10, HIGH);
    display.invertDisplay(1);
    delay(t);
    display.invertDisplay(0);
    digitalWrite(10, LOW);
}
