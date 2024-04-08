#include <stdio.h>
#include <string.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define NUMPINS 4
#define ULONG_MAX 4294967295

int RESET_PIN = 7;

int pins[] = {13, 12, 11, 10};
boolean pressed[] = {false, false, false, false};
unsigned long lastPressed[] = {ULONG_MAX, ULONG_MAX, ULONG_MAX, ULONG_MAX}; 
char* words[NUMPINS];

boolean isCurrentlyPressed = false;

unsigned int globalDelayTimeMs = 30 * 1000;
unsigned long globalTime = 0;

LiquidCrystal_I2C lcd (32,16,2);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  for(unsigned short i = 0; i < NUMPINS; i++) {
      pinMode(pins[i], INPUT);
  }
  pinMode(RESET_PIN, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Start");
}

char* intToString(int num) {
    int length = snprintf(NULL, 0, "%d", num);
    char* str = (char*)malloc(length + 1);
    snprintf(str, length + 1, "%d", num);
    return str;
}

char* joinStrings(char* strings[]) {
    int totalLength = 0;
    for (int i = 0; i < NUMPINS; ++i) {
        totalLength += strlen(strings[i]);
    }
    totalLength += NUMPINS - 1; // Account for the commas

    char* result = (char*)malloc(totalLength + 1);
    strcpy(result, strings[0]);
  
    for (int i = 1; i < NUMPINS; ++i) {
        strcat(result, ",");
        strcat(result, strings[i]);
    }

    return result;
}

char* calcRank(int pinIdx) {
  char* posPinA = "-";
  if (lastPressed[pinIdx] != ULONG_MAX) {
    int counter = 1;
    for(unsigned short i = 0; i < NUMPINS; i++) {
      if (i == pinIdx) {
        continue;
      }
      if (lastPressed[i] < lastPressed[pinIdx]) {
        counter++; 
      }
    }
    posPinA = intToString(counter);
  }
  return posPinA;
}

void resetCounter() {  
  for(unsigned short i = 0; i < NUMPINS; i++) {
    lastPressed[i] = ULONG_MAX;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ready");
  isCurrentlyPressed = false;
}

void press(int pinIdx) {
  unsigned long currentTime = millis();
  if (!isCurrentlyPressed) {
    globalTime = currentTime;
  }
  isCurrentlyPressed = true;
  
  if (lastPressed[pinIdx] != ULONG_MAX) {
    return;
  }
  
  lastPressed[pinIdx] = currentTime;
  
  for(unsigned short i = 0; i < NUMPINS; i++) {
    words[i] = calcRank(i);
  }
  
  char* joinedString = joinStrings(words);
  
  //Serial.println(millis());
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(joinedString);
  //Serial.println(millis());
  
}

void scanI2C() {
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}

void loop() {
  unsigned long currentTime = millis();
  if (isCurrentlyPressed && currentTime - globalTime >= globalDelayTimeMs) {
    resetCounter();
  }  
  
  for(unsigned short i = 0; i < NUMPINS; i++) {
    if (digitalRead(pins[i]) == HIGH) {
      if (!pressed[i]) {
        pressed[i] = true;
        press(i);
      }
    } else {
      pressed[i] = false;
    }
  }
  
  if (digitalRead(RESET_PIN) == HIGH) {
    resetCounter();
    delay(500);
  }
  
  
  //scanI2C();
}
